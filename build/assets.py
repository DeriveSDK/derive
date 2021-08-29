import json
import os
import re

assetroot = ".."+os.sep+"assets"
assetout = ".."+os.sep+"assets"+os.sep+"include"

print("Building assets")


def slugify(txt):
    slug = txt.lower().lstrip('0123456789.- ')
    slug = re.sub(r'[_]+', '', slug)
    slug = re.sub(r'[/\\]+', '_', slug)
    slug = re.sub(r'[^a-z0-9_]+', '', slug).strip('-')
    return slug


def bin2header(data, name):
    out = []
    out.append('#pragma once\n')
    out.append('#include "derive/assets/EmbeddedAsset.h"\n')
    out.append('using namespace derive::assets;\n')
    out.append('const unsigned char {name}_data[] = {{'.format(name=name))
    l = [data[i:i+32] for i in range(0, len(data), 32)]
    for i, x in enumerate(l):
        line = ', '.join(['0x{val:02x}'.format(val=c) for c in x])
        out.append('\t{line}{end_comma}'.format(
            line=line, end_comma=',' if i < len(l)-1 else ''))
    out.append('};')
    out.append('const EmbeddedAssetData {name} = {{'.format(name=name))
    out.append('\t{name}_data,'.format(name=name))
    out.append('\t{length}'.format(length=len(data)))
    out.append('};\n')
    return '\n'.join(out)


def cleanpath(p):
    p = p.lower()
    p = p[len(assetroot)+1:]
    p = re.sub(r'[\\]+', '/', p)
    return p


# Check if the assets folder exists
if os.path.exists(assetroot):

    # Create assets output directory if it doesn't exist
    if not os.path.exists(assetout):
        os.makedirs(assetout)

    # Load last list of assets processed
    try:
        with open(assetout+os.sep+"EmbeddedAssets.json") as f:
            assetlist = json.load(f)
    except:
        assetlist = {}

    processedlist = {}

    # Iterate the assets folder (except output folder)
    fname = []
    for root, d_names, f_names in os.walk(assetroot):
        if not root == assetout:
            for f in f_names:
                process = True
                filepath = os.path.join(root, f)
                fileslug = slugify(filepath[len(assetroot)+1:])
                filesize = os.path.getsize(filepath)
                filedate = os.path.getmtime(filepath)
                print("Checking "+filepath)
                # Check if file exists in asset list, and if it
                # has changed since it was added to the list
                if fileslug in assetlist:
                    assetentry = assetlist[fileslug]
                    assetsize = 0
                    assetdate = 0
                    if "size" in assetentry:
                        assetsize = assetentry["size"]
                    if "modified" in assetentry:
                        assetdate = assetentry["modified"]
                    if (assetsize == filesize) and (assetdate == filedate):
                        process = False
                # Check if the file has a header
                if not os.path.exists(assetout+os.sep+fileslug+".h"):
                    process = True
                # Process the asset
                processedlist[fileslug] = {
                    "size": filesize, "modified": filedate, "path": filepath}
                if process:
                    print("  Process as "+fileslug)
                    with open(filepath, "rb") as f:
                        filedata = f.read()
                    with open(assetout+os.sep+fileslug+".h", "w") as f:
                        f.write(bin2header(filedata, fileslug))
                else:
                    print("  Skipping (unmodified)")

    # Generate master asset header
    out = []
    out.append('#pragma once\n')
    out.append('#include "derive/assets/EmbeddedAsset.h"')
    out.append('#include <map>')
    out.append('#include <string>\n')
    for key in processedlist:
        out.append('#include "{name}.h"'.format(name=key))
    out.append('\nnamespace derive {')
    out.append('\tnamespace assets {\n')
    out.append('\t\tclass EmbeddedAssets {')
    out.append('\t\tpublic:')
    out.append(
        '\t\t\tstd::map<std::string, derive::assets::EmbeddedAssetData> items = {')
    for key in processedlist:
        out.append('\t\t\t\t{{ "{path}", {name} }},'.format(
            path=cleanpath(processedlist[key]["path"]), name=key))
    out.append('\t\t\t};')
    out.append('\t\t};\n')
    out.append('\t}')
    out.append('}')
    with open(assetout+os.sep+"EmbeddedAssets.h", "w") as f:
        f.write('\n'.join(out))

    # Save the processed file list
    with open(assetout+os.sep+"EmbeddedAssets.json", "w") as f:
        json.dump(processedlist, f)

else:
    print("asset folder not found")

print("")
