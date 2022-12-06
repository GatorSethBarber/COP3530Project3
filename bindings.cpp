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