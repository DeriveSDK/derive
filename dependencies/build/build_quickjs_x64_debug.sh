# create dependency lib folder if it doesn't exist yet
mkdir -p ../lib/debug

# go to quickjs and build it
cd ../quickjs
premake5 gmake2 --cc=clang --jsx --storage --debugging
cd build/gmake2
make config=debug_x64 quickjs

# copy library to dependency lib folder
cd ../../
cp -R bin/quickjs.lib ../lib/debug/quickjs.lib
