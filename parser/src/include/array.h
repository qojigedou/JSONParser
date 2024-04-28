#ifndef JSON_ARRAY_H
#define JSON_ARRAY_H

#include "member.h"
#include "container.h"
#include <string>
#include <vector>

namespace json
{

    class Array : public Container
    {
    public:
    private:
        friend class Parser;

        std::vector<Member *> data;

        void put(std::string key, Member *value) override;
    };

}; // namespace json

#endif // JSON_ARRAY_H