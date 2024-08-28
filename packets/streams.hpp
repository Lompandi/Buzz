
#pragma once

#include <string>

class ReadOnlyBinaryStream {
public:
    size_t             mReadPointer{};   // this+0x8
    bool               mHasOverflowed{}; // this+0x10
    std::string        mOwnedBuffer;     // this+0x18
    const std::string* mBuffer;          // this+0x38

    explicit ReadOnlyBinaryStream() : mBuffer(std::addressof(mOwnedBuffer)) {}

    explicit ReadOnlyBinaryStream(std::string&& buffer)
        : mOwnedBuffer(std::move(buffer)),
        mBuffer(std::addressof(mOwnedBuffer)) {}

    ReadOnlyBinaryStream(std::string const& buffer, bool copyBuffer) {
        if (copyBuffer) {
            mOwnedBuffer = buffer;
            mBuffer = std::addressof(mOwnedBuffer);
        }
        else {
            mBuffer = std::addressof(buffer);
        }
    }

    ReadOnlyBinaryStream& operator=(ReadOnlyBinaryStream const&) = delete;
    ReadOnlyBinaryStream(ReadOnlyBinaryStream const&) = delete;
    ReadOnlyBinaryStream& operator=(ReadOnlyBinaryStream&&) = delete;
    ReadOnlyBinaryStream(ReadOnlyBinaryStream&&) = delete;
};

struct ReadOnlyBinaryStreamS {
public:
    uintptr_t          mVtablePtr{};
    size_t             mReadPointer{};   // this+0x0
    bool               mHasOverflowed{}; // this+0x8
    std::string        mOwnedBuffer;     // this+0x10 eight bytes more...why?
    const std::string* mBuffer;          // this+0x30
};