#ifndef JSON_PRIMITIVE_H
#define JSON_PRIMITIVE_H

#include "member.h"
#include <string>

namespace json
{

    class Primitive : public Member
    {
        friend class Parser;

        void *data;
    };

}; // namespace json

#endif // JSON_PRIMITIVE_H