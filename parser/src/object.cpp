#include "include/object.h"

#include <utility>
#include <iostream>

using namespace json;

void Object::put(std::string key, Member *value) {
    data.insert(std::pair<std::string, Member *>(key, value));
}
