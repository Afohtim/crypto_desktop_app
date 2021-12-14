#pragma once
#include <vector>
#include <cstdint>
#include <array>


#ifdef ENCRYPTIONS_LIB_EXPORTS
#define ENCRYPTIONS_LIB_API __declspec(dllexport)
#else
#define ENCRYPTIONS_LIB_API __declspec(dllimport)
#endif

namespace aes
{
	struct Aes_word
	{
		uint32_t word;

		Aes_word()
		{
			word = 0;
		}

		Aes_word(uint32_t w)
		{
			word = w;
		}

		uint8_t& operator[](int i)
		{
			return ((uint8_t*)&word)[3 - i];
		}

		uint32_t operator+(uint32_t other)
		{
			return word + other;
		}

		uint32_t operator-(uint32_t other)
		{
			return word + other;
		}

		uint32_t operator^(uint32_t other)
		{
			return word ^ other;
		}

		uint32_t operator=(uint32_t other)
		{
			return word = other;
		}

		uint32_t operator+=(uint32_t other)
		{
			return word += other;
		}

		uint32_t operator-=(uint32_t other)
		{
			return word -= other;
		}

		uint32_t operator^=(uint32_t other)
		{
			return word ^= other;
		}
	};

	struct Aes_state
	{
		std::array<Aes_word, 4> state;

		Aes_state() {}


		Aes_state(Aes_state& other)
		{
			state = std::array<Aes_word, 4>(other.state);
		}

		Aes_state(std::vector<uint32_t> state_vector)
		{
			for (int i = 0; i < 4; ++i)
			{
				state[i] = state_vector[i];
			}

		}


		int size()
		{
			return state.size();
		}

		Aes_word& operator[](int i)
		{
			return state[i];
		}
	};

	extern "C" ENCRYPTIONS_LIB_API void key_expansion_aes(uint8_t * key, int& key_size, uint32_t * w, int& w_size);
	ENCRYPTIONS_LIB_API void key_expansion(const std::vector<uint8_t>& key, std::vector<uint32_t>& w);

	extern "C" ENCRYPTIONS_LIB_API void cipher_aes(uint8_t* in, uint8_t* out, uint32_t* dw, int& dw_size);
	ENCRYPTIONS_LIB_API void cipher(std::vector<uint8_t>& in, std::vector<uint8_t>& out, std::vector<uint32_t>& dw);

	extern "C" ENCRYPTIONS_LIB_API void inv_cipher_aes(uint8_t * in, uint8_t * out, uint32_t * dw, int& dw_size);
	ENCRYPTIONS_LIB_API void inv_cipher(std::vector<uint8_t>& in, std::vector<uint8_t>& out, std::vector<uint32_t>& dw);
}
