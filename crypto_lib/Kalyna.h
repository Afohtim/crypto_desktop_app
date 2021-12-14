#pragma once
#include <cstdint>
#include <vector>
#include <array>

#ifdef ENCRYPTIONS_LIB_EXPORTS
#define ENCRYPTIONS_LIB_API __declspec(dllexport)
#else
#define ENCRYPTIONS_LIB_API __declspec(dllimport)
#endif

namespace kalyna
{
	struct Kalyna_column
	{
		uint64_t word;

		Kalyna_column()
		{
			word = 0;
		}

		Kalyna_column(uint64_t w)
		{
			word = w;
		}

		uint8_t& operator[](int i)
		{
			return ((uint8_t*)&word)[i];
		}

		uint64_t operator+(uint64_t other)
		{
			return word + other;
		}

		uint64_t operator-(uint64_t other)
		{
			return word + other;
		}

		uint64_t operator^(uint64_t other)
		{
			return word ^ other;
		}

		uint64_t operator=(uint64_t other)
		{
			return word = other;
		}

		uint64_t operator+=(uint64_t other)
		{
			return word += other;
		}

		uint64_t operator-=(uint64_t other)
		{
			return word -= other;
		}

		uint64_t operator^=(uint64_t other)
		{
			return word ^= other;
		}

	};


	struct Kalyna_state
	{
		int state_size;
		std::vector<Kalyna_column> state;

		Kalyna_state()
		{
			state_size = 0;
		}

		Kalyna_state(int nk)
		{
			state_size = nk;
			state = std::vector<Kalyna_column>(nk);
		}

		Kalyna_state(Kalyna_state& other)
		{
			state_size = other.state_size;
			state = std::vector<Kalyna_column>(other.state.begin(), other.state.end());
		}

		Kalyna_state(std::vector<uint64_t> state_vector)
		{
			state_size = state_vector.size();
			for (int i = 0; i < state_size; ++i)
			{
				state.push_back(state_vector[i]);
			}

		}


		int size()
		{
			return state.size();
		}

		Kalyna_column& operator[](int i)
		{
			return state[i];
		}
	};

	extern "C" ENCRYPTIONS_LIB_API void key_expansion_kalyna(uint8_t* key, uint64_t** w);
	ENCRYPTIONS_LIB_API void key_expansion(const std::vector<uint8_t>& key, std::vector<std::vector<uint64_t>>& w);
	
	extern "C" ENCRYPTIONS_LIB_API void cipher_kalyna(uint8_t* in, uint8_t* out, uint64_t** dw);
	ENCRYPTIONS_LIB_API void cipher(std::vector<uint8_t>& in, std::vector<uint8_t>& out, std::vector<std::vector<uint64_t>>& dw);
	
	extern "C" ENCRYPTIONS_LIB_API void inv_cipher_kalyna(uint8_t * in, uint8_t * out, uint64_t * *dw);
	ENCRYPTIONS_LIB_API void inv_cipher(std::vector<uint8_t>& in, std::vector<uint8_t>& out, std::vector<std::vector<uint64_t>>& dw);
}

