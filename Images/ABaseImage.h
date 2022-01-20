#pragma once
#include <vector>

namespace WAL
{
	class ABaseImage
	{
	private:
		std::vector<uint8_t> data;
	public:
		const std::vector<uint8_t>& GetDataBase() const;

	};
}