#pragma once
#include <cstdint>

namespace itch::bytes {

template <typename T>
inline T read_b(const uint8_t* p) {
    T v;
    for(int i{0u}; i<sizeof(T); i++) {
        v = (v<<8) | p[i];
    }
    return v;
}

template <typename T>
inline T read_nb(const uint8_t* p, int n) {
    T v;
    for(int i{0u}; i<n;i++) {
        v = (v<<8) | p[i];
    }
    return v;
}

} //namespace itch::bytes