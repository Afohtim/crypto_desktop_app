#pragma once
#include <cstdint>

#ifdef ENCRYPTIONS_LIB_EXPORTS
#define ENCRYPTIONS_LIB_API __declspec(dllexport)
#else
#define ENCRYPTIONS_LIB_API __declspec(dllimport)
#endif

namespace DES
{
    extern "C" ENCRYPTIONS_LIB_API uint64_t des(uint64_t block, bool mode);
    extern "C" ENCRYPTIONS_LIB_API uint64_t encrypt(uint64_t block);
    extern "C" ENCRYPTIONS_LIB_API uint64_t decrypt(uint64_t block);
    extern "C" ENCRYPTIONS_LIB_API  void keygen(uint64_t key);
};

