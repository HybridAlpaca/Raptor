#pragma once

#include <Core/Common/Required.h>

namespace Core
{
namespace Utils
{

class TypeID
{
	static size_t counter = 0;
	
public:

	template <typename Type>
	static size_t value ()
	{
		static size_t id = counter++;
		return id;
	}
};

}
}