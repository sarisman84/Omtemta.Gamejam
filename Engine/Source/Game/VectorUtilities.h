#pragma once
#include<tga2d/math/vector2.h>
#include <Vector2.h>

#define SCREEN Tga2D::CEngine::GetInstance()->GetTargetSize()
#define SCREENSCALE_X ((float)SCREEN.x / ((float)SCREEN.x / 2.0f))
#define SCREENSCALE_Y ((float)SCREEN.y / ((float)SCREEN.y / 2.0f))

class Convert
{
public:
	template<typename T>
	_inline static Tga2D::Vector2<T> ToTga(CommonUtilities::Vector2<T> aValue)
	{
		return { aValue.x, aValue.y };
	}


	template<typename T>
	_inline static CommonUtilities::Vector2<T> ToCustom(Tga2D::Vector2<T> aValue)
	{
		return { aValue.x, aValue.y };
	}
};

