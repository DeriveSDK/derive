cd ../skia
bin/gn gen out/x64 --args=" \
    is_debug=true \
    is_official_build=false \
    skia_use_angle=false \
    skia_use_dng_sdk=false \
    skia_use_egl=false \
    skia_use_expat=false \
    skia_use_fontconfig=false \
    skia_use_freetype=true \
    skia_use_system_freetype2=false \
    skia_use_icu=false \
    skia_use_libheif=false \
    skia_use_system_libpng=false \
    skia_use_libjpeg_turbo_encode=false \
    skia_use_libjpeg_turbo_decode=false \
    skia_use_libwebp_encode=false \
    skia_use_libwebp_decode=false \
    skia_use_lua=false \
    skia_use_piex=false \
    skia_use_vulkan=false \
    skia_use_metal=false \
    skia_use_gl=true \
    skia_use_zlib=true \
    skia_use_system_zlib=false \
    skia_enable_gpu=true \
    skia_enable_fontmgr_empty=false \
    skia_enable_spirv_validation=false \
    skia_enable_pdf=false \
    skia_use_libpng_encode = true \
    skia_use_libpng_decode = true \
    skia_enable_skrive = true \
    target_cpu = \"x64\"
    win_vc = \"C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\"
    clang_win = \"C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\Llvm\\x64\"
    "
ninja skia -C out/x64
