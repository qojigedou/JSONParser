#include "include/array.h"

using namespace json;

void Array::put(std::string key, Member *value) {
    (void) key;

    data.push_back(value);
}
