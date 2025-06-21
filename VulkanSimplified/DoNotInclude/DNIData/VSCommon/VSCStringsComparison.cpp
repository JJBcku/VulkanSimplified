#include "VSCommonNIpch.h"
#include "VSCStringsComparison.h"

namespace VulkanSimplified
{
	bool AreCStringEqual(const char* str1, const char* str2)
	{
		if (str1 == str2)
			return true;
		else
		{
			if (str1 == nullptr || str2 == nullptr)
				return false;
			else
				return std::strcmp(str1, str2) == 0;
		}
	}

	bool ISFirstCStringLesser(const char* str1, const char* str2)
	{
		if (str1 == nullptr)
		{
			if (str2 == nullptr)
				return false;
			else
				return true;
		}
		else
		{
			if (str2 == nullptr)
				return false;
			else
			{
				int comp = std::strcmp(str1, str2);

				return comp < 0;
			}
		}
	}
}