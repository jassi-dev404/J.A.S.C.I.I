#!/bin/bash
cd C_stuff/
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk 
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
cd ..
emcc main.c -o a.out.js -O3 -s INVOKE_RUN=0 -s EXIT_RUNTIME=0 -s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_RUNTIME_METHODS=ccall,cwrap,callMain,FS -s EXPORTED_FUNCTIONS=_main,_get_size,_image_width,_image_height
mv a.out.js ../frontend/
mv a.out.wasm ../frontend/
cd ..
npm install
cd frontend/
npm install
echo "Go to http://localhost:6969/ <-- yes 6969 very funni number :)"
node server.js

