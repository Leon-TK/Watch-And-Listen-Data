#pragma once
#include <vector>

/*    
* Wraps file into context
*/    

namespace WAL
{
	class FileChunkDispencer;
	class IFile;

	namespace File
	{
		//Forwarding
		

		class FileHandler final
		{
		private:
			size_t handledSize{ 0 };
			const size_t chunkSize{ 0 };
			WAL::IFile* file{ nullptr };
			WAL::FileChunkDispencer* fileChunkDispenser{ nullptr };

		public:
			FileHandler() = delete;
			FileHandler(WAL::IFile* file, const size_t chunkSize);
			~FileHandler();


			/**
			* Returns chunk of buffer for extracting pixels. Size of chunk must be precalculated for rows being filled without empty bytes at the end
			* @param size
			*/
			std::vector<uint8_t> GetNextChunk(size_t size, bool& outIsNextExist);
			bool canGetNextChunk();

		};
	}
}