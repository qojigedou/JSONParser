#ifndef JSON_CONTAINER_H
#define JSON_CONTAINER_H

#include "member.h"
#include <string>

namespace json {

class Container : public Member {
public:
    virtual void put(std::string key, Member *member) = 0;
};

}; // namespace json

#endif // JSON_CONTAINER_H