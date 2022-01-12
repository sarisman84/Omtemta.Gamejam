#pragma once
#include <iostream>
#include <string>

class ErrorHandler
{
public:
	template <typename T>
	_inline static void NullRefExpection(T* anObj = nullptr)
	{
		std::cout << "[Error]: A Pointer is invalid (" << anObj << ")" << std::endl;
	}

	template <typename T>
	_inline static void CustomLog(std::string aMessage, T* anObj = nullptr)
	{
		std::cout << "[Error] <Object: " << anObj << ">:" << aMessage << std::endl;
	}
};



