#pragma once
//#include "PixelExtractor/PixelExtractor.h"

namespace WAL
{
	class PixelExtractor;

	/*
	* This class is context for pixel extraction.
	* It contains all needed types, functions.
	*/
	class ExtractionContext final
	{
	private:
		PixelExtractor* extractor;
		//raw image*
	public:
		ExtractionContext() = delete;
		ExtractionContext(PixelExtractor* extractor);
	};
}