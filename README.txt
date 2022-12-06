Compilation instructions:

To complile the project for the web application, first need to download emscripten. Instructions provided by emscripten
at https://emscripten.org/docs/getting_started/downloads.html.
To comple for wasm, will have to do something like 

emcc -I. -o webpages/testing.js -Oz -s MODULARIZE=1 -s EXPORT_NAME=createModule --bind Dataset.cpp Datapoint.cpp bindings.cpp

source: https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html