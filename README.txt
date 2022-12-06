Compilation instructions:

To complile the project for the web application, first need to download emscripten. Instructions provided by emscripten
at https://emscripten.org/docs/getting_started/downloads.html.
To comple for wasm, will have to do something like 

emcc -I. -o webpages/testing.js -Oz -s MODULARIZE=1 -s EXPORT_NAME=createModule --bind Dataset.cpp Datapoint.cpp bindings.cpp --preload-file dataForProject.csv -s INLINING_LIMIT=0

However, this may be unnecessary as the needed .wasm, .js, and .data files have already been created.

Sources
Main compilation statement: https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html
--bind option: https://emscripten.org/docs/porting/files/file_systems_overview.html
Inilining limit inspired by: https://github.com/emscripten-core/emscripten/issues/5316 (uses outlining)