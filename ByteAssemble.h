#pragma once
#include <array>
#include <fstream>
#include <cmath>

namespace WAL
{
	namespace ByteAssemble
	{
		/*
		* Creates integer from given binary data. Shifts each array byte.
		* Last byte in array will be at the begining of integer.
		* You can cast result to lower types like short or char
		* @param bytes Array of binary data
		*/
		template <int Count>
		unsigned long GlueBytes(std::array<char, Count>& bytes)
		{
			unsigned long result = 0;
			for (unsigned int i = 0; i < Count; i++)
			{
				result = bytes[i];
				result <<= 8;
			}
			return result;
		}

		/*
		* Stream must be in binary mode. Uses standart iostream get()
		* @param Size How much bytes to extract
		*/
		template <int Size>
		std::array<uint8_t, Size> DEPRECATED_GetBytesFrom(std::ifstream* strm)
		{
			if (!strm) return std::array<uint8_t, Size>();

			std::array<uint8_t, Size> arr;
			for (int i = 0; i < Size; i++)
			{
				arr[i] = strm->get();
			}
			return arr;
		}

		/*
		* It uses std::ceil
		*/
		template <typename T>
		T GetAverageFrom(std::vector<T>& arr, size_t size)
		{
			size_t sum = 0;

			for (size_t i = 0; i < size; i++)
			{
				sum += (size_t)arr.at(i);
			}

			return (T)std::ceil(sum / size);
		}

		template <typename T, int X, int Y>
		std::array<T, (X* Y)> SetupImageArray()
		{
			return std::array<T, (X* Y)>();
		}
	}
	
}