#pragma once

#include <cstdlib>
#include <stdint.h>
#include <cassert>

inline bool isNegativeZero(double number) {
    return number == 0 && *reinterpret_cast<int64_t *>(&number) != 0;
}

class Value {
private:
    union {
        double asDouble;
        uint64_t asBits;
    };

    static const uint64_t MaxDouble = 0xfff8000000000000;
    static const uint64_t Int32Tag  = 0xfff9000000000000;
    static const uint64_t PtrTag    = 0xfffa000000000000;
public:
    inline Value(const double number) {
        int32_t asInt32 = static_cast<int32_t>(number);

        // if the double can be losslessly stored as an int32 do so
        // (int32 doesn't have -0, so check for that too)
        if (number == asInt32 && !isNegativeZero(number)) {
            *this = Value(asInt32);
            return;
        }

        asDouble = number;
    }

    inline Value(const int32_t number) {
        asBits = number | Int32Tag;
    }

    inline Value(void *pointer) {
        // ensure that the pointer really is only 48 bit
        assert((reinterpret_cast<uint64_t>(pointer) & PtrTag) == 0);

        asBits = reinterpret_cast<uint64_t>(pointer) | PtrTag;
    }

    inline bool isDouble() const {
        return asBits < MaxDouble;
    }
    inline bool isInt32() const {
        return (asBits & Int32Tag) == Int32Tag;
    }
    inline bool isPointer() const {
        return (asBits & PtrTag) == PtrTag;
    }

    inline double getDouble() const {
        assert(isDouble());

        return asDouble;
    }
    inline int32_t getInt32() const {
        assert(isInt32());

        return static_cast<int32_t>(asBits & ~Int32Tag);
    }
    inline void *getPointer() const {
        assert(isPointer());

        return reinterpret_cast<void *>(asBits & ~PtrTag);
    }
};

typedef enum {
		OBJ_FN,
		OBJ_STRING,
		OBJ_UPVALUE
} ObjectType;

typedef uint64_t FunValue;

void* allocate_mem(uint32_t size);


