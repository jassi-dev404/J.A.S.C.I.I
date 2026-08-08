#!/bin/bash
set -e

mkdir -p C_stuff/header_files frontend/scripts

curl -sL https://raw.githubusercontent.com/nothings/stb/master/stb_image.h -o C_stuff/external/stb_image.h
curl -sL https://raw.githubusercontent.com/nothings/stb/master/stb_image_resize2.h -o C_stuff/external/stb_image_resize2.h

rm -rf emsdk
git clone https://github.com/emscripten-core/emsdk.git

cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
cd ..

cd C_stuff
emcc main.c -Iheader_files -o ../frontend/scripts/a.out.js -O3 \
  -s INVOKE_RUN=0 \
  -s EXIT_RUNTIME=0 \
  -s ALLOW_MEMORY_GROWTH=1 \
  -s EXPORTED_RUNTIME_METHODS=ccall,cwrap,callMain,FS \
  -s EXPORTED_FUNCTIONS=_main,_get_size,_image_width,_image_height
cd ..

npm install
cd frontend
npm install ejs
npm install
curl -L https://unpkg.com/@tailwindcss/browser@4 -o scripts/tailwind-browser.js