﻿#pragma once
#include <vector>

/*    
* Wraps file into context
*/    

namespace WAL
{
	//Forwarding
	class IFile;

	class FileHandler final
	{
	private:
		size_t currentPos{ 0 };
		//size_t handledSize{ 0 };
		IFile* file{ nullptr };

	public:
		FileHandler() = delete;
		FileHandler(IFile* file);


		/**
		* Returns chunk of buffer for extracting pixels. Size of chunk must be precalculated for rows being filled without empty bytes at the end
		* @param size
		*/
		std::vector<uint8_t> GetNextChunk(size_t size, bool &outIsEnd);

	};
}