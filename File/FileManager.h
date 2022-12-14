#pragma once
#include <vector>

/*    
* Wraps file into context
*/    

namespace WAL
{
	
	

	namespace File
	{
		namespace Interface
		{
			class IFile;
		}
		
		class FileChunkDispencer;

		class FileManager final
		{
		private:
			size_t processedSize{ 0 };
			const size_t chunkSize{ 0 };
			Interface::IFile* file{ nullptr };
			FileChunkDispencer* fileChunkDispenser{ nullptr };

		public:
			FileManager() = delete;
			FileManager(Interface::IFile* file, const size_t chunkSize);
			~FileManager();


			/**
			* Returns chunk of buffer for extracting pixels. Size of chunk must be precalculated for rows being filled without empty bytes at the end
			* @param size
			*/
			std::vector<uint8_t> GetNextChunk(size_t size, bool& outIsNextExist);
			bool canGetNextChunk();

		};
	}
}