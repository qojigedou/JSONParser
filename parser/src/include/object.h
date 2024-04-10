#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#include "member.h"
#include "container.h"
#include <string>
#include <map>

namespace json
{

    class Object : public Container
    {

    private:
        friend class Parser;

        std::map<std::string, Member *> data;

        void put(std::string key, Member *value) override;
    };

}; // namespace json

#endif // JSON_OBJECT_H