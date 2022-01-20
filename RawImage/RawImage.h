#pragma once
#include <vector>
#include "../Vectors/Vec2.h"
#include "../Vectors/Vec3.h"

/*    
* Holds raw binary data in pixel containers. Should be converted to standart image formats except video encoder can work with raw data, otherwise you must convert raw data to foramt that encoder understand.
* template class
*/    
namespace WAL
{
	/**
	* Represents array of Pixel classes
	* @param PixelType which type of Pixel to use
	* 
	*/
	template <typename PixelType>
	class RawImageArray
	{
		typedef Vec3<PixelType> Pixel;
		typedef Vec2<uint16_t> Resolution;
	private:
		/*
		* At which index pixel will be puted by PutNextPixel()
		*/
		size_t currentPxl{ 0 };
		std::vector<Pixel> data; //{Pixel(0,0)}

	public:
		RawImageArray() = delete;
		RawImageArray(Resolution resolution);
		std::vector<Pixel> GetData();

		/*
		* Put pixel at end of data
		* @param pxl Pixel to put
		*/
		void PutNextPixel(Pixel& pxl);
	};

	template <typename PixelType>
	inline void RawImageArray<PixelType>::PutNextPixel(Pixel& pxl)
	{
		data.at(currentPxl) = pxl;
		currentPxl++;
	}

	template<typename PixelType>
	inline RawImageArray<PixelType>::RawImageArray(Resolution resolution)
	{
		this->data(resolution.X * resolution.Y);
	}

	template <typename PixelType>
	inline std::vector<Vec3<PixelType>> RawImageArray<PixelType>::GetData()
	{
		return data;
	}

}