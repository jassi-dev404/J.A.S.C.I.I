#!/bin/bash
set -e

mkdir -p C_stuff/external frontend/scripts

curl -sL https://raw.githubusercontent.com/nothings/stb/master/stb_image.h -o C_stuff/external/stb_image.h
curl -sL https://raw.githubusercontent.com/nothings/stb/master/stb_image_resize2.h -o C_stuff/external/stb_image_resize2.h

git submodule update --init --recursive

cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
cd ../C_stuff

emmake make -j

mv a.out.js ../frontend/
mv a.out.wasm ../frontend/
cd ..

npm install
cd frontend
npm install ejs
npm install
curl -L https://unpkg.com/@tailwindcss/browser@4 -o scripts/tailwind-browser.js
cd ..
npm install
