Compilation instructions:

To complile the project for the web application, first need to download emscripten. Instructions provided by emscripten
at https://emscripten.org/docs/getting_started/downloads.html.
To comple for wasm, will have to do something like 

emcc -I. -o webpages/testing.js -Oz -s MODULARIZE=1 -s EXPORT_NAME=createModule --bind Dataset.cpp Datapoint.cpp bindings.cpp --preload-file dataForProject.csv -s INLINING_LIMIT=0

However, this may be unnecessary as the needed .wasm, .js, and .data files have already been created. However, it is necessary to run the server
using node.js (node server.js) and access the webpage through the server (go to http://localhost:4500/home.html).

Sources
Main compilation statement: https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html
--bind option: https://emscripten.org/docs/porting/files/file_systems_overview.html
Inilining limit inspired by: https://github.com/emscripten-core/emscripten/issues/5316 (uses outlining)


Update 8/9/2023:
Additional sources used:
https://emscripten.org/docs/porting/files/packaging_files.html#packaging-files: including external files
https://medium.com/netscape/javascript-c-modern-ways-to-use-c-in-javascript-projects-a19003c5a9ff
https://medium.com/jspoint/a-simple-guide-to-load-c-c-code-into-node-js-javascript-applications-3fcccf54fd32
https://blog.esciencecenter.nl/using-c-in-a-web-app-with-webassembly-efd78c08469: for main compilation statement
