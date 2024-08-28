#pragma once

#include <cstdint>

#include "../packets/streams.hpp"

namespace buz {
    template <typename... TParam>
    struct bzFuzzFrame {
        using Constructor_t = void(*)(void*, TParam...);
        using ReadFn_t = void(*)(void*, void*, ReadOnlyBinaryStream&);

        bzFuzzFrame(Constructor_t ctor, uintptr_t ctor_addr, ReadFn_t read_fn, uintptr_t read_fn_addr)
        {
            M_Ctor_t = reinterpret_cast<Constructor_t>(ctor_addr);
            M_Read_t = reinterpret_cast<ReadFn_t>(read_fn_addr);
        }

        void Construct(void* pThis, TParam... params) {
            if (M_Ctor_t) 
                M_Ctor_t(pThis, std::forward<TParam>(params)...);
        }

        void Read(void* pThis, void* pRet, ReadOnlyBinaryStream& rStream) {
            if (M_Read_t)
                M_Read_t(pThis, pRet, rStream);
        }

    private:
        Constructor_t M_Ctor_t;
        ReadFn_t M_Read_t;
    };
}