This is a readme about the project in general.

To complile the project for the wasm, will have to do something like 
emcc -I. -o testing.js -Oz -s MODULARIZE=1 -s EXPORT_NAME=createModule --bind Testing.cpp bindings.cpp

source: https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html