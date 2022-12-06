 /**
 * Bindings to allow emscripten to compile the code to WebAssembly.
 * Source for binding classes: https://blog.esciencecenter.nl/using-c-in-a-web-app-with-webassembly-efd78c08469
 * Source for binding data types: https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html
*/
#include <emscripten/bind.h>
#include "Dataset.h"

using namespace emscripten;
EMSCRIPTEN_BINDINGS(Dataset) {
    class_<Dataset>("Dataset")
        .constructor<>()
        .function("rankAll", &Dataset::rankAll)
        .function("mergeSort", &Dataset::mergeSort)
        .function("quickSort", &Dataset::quickSort)
        .function("getLastN", &Dataset::getLastN)
        .function("readInData", &Dataset::readInData)
        ;

    register_vector<vector<string>>("vector<vector<string>>");
    register_vector<string>("vector<string>");
}