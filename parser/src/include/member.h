#ifndef JSON_MEMBER_H
#define JSON_MEMBER_H

namespace json {

class Member {
protected:
    friend class Parser;

    typedef enum {
        OBJECT,
        ARRAY,
        BOOLEAN,
        NIL,
        INTEGER,
        FLOAT,
        STRING
    } Type;

    Type type;

    bool isContainer() { return (type == OBJECT || type == ARRAY); };
};

}; // namespace json

#endif // JSON_MEMBER_H