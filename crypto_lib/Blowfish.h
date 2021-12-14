#pragma once
#include <cstdint>
#include <vector>
#include <array>
#include <string>

#ifdef ENCRYPTIONS_LIB_EXPORTS
#define ENCRYPTIONS_LIB_API __declspec(dllexport)
#else
#define ENCRYPTIONS_LIB_API __declspec(dllimport)
#endif

namespace Blowfish
{
	extern "C" ENCRYPTIONS_LIB_API void cipher_blowfish(uint32_t* text, int& text_size);
	ENCRYPTIONS_LIB_API void cipher(std::vector<uint32_t>& text);

	extern "C" ENCRYPTIONS_LIB_API void inv_cipher_blowfish(uint32_t * text, int& text_size);
	ENCRYPTIONS_LIB_API void inv_cipher(std::vector<uint32_t>& text);

	extern "C" ENCRYPTIONS_LIB_API void set_key_blowfish(char* s, int& s_size);
	ENCRYPTIONS_LIB_API void set_key(std::string s);
};

