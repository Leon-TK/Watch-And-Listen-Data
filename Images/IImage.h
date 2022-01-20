#pragma once
#include <vector>

/*    
* Holds image data. Standart formats
*/    

namespace WAL
{
	class IImage
	{
	public:
		virtual ~IImage() {};
		virtual const std::vector<uint8_t>& GetData() const = 0;

	};
}