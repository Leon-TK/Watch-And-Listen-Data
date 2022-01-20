#pragma once
#include <vector>
#include <string>

/*    
* Wraps directory into context
*/    

namespace WAL
{
	//Forwarding
	class IDirectory;
	template<typename>
	class TVec2;

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
		TVec2<uint16_t> GetResolution(float aspectRatio) const;

	};
}