#pragma once
#include <vector>
#include <string>

/*    
* Wraps directory into context
*/    

namespace WAL
{
	namespace Vectors
	{
		template<typename>
		class TVec2;
	}

	namespace Directory
	{
		//Forwarding
		class IDirectory;

		class DirectoryHandler final
		{
		private:
			IDirectory* dir{ nullptr };

		public:
			DirectoryHandler() = delete;
			DirectoryHandler(IDirectory* dir);
			~DirectoryHandler();

			/**
			* Gets size of all files in that directory. Uses File class
			*/
			size_t GetAllFilesSize() const;

			/**
			* Calculates directory "resolution" for further calcultaions
			* @param aspectRatio
			*/
			Vectors::TVec2<uint16_t> GetResolution(float aspectRatio) const;

		};
	}
	
}