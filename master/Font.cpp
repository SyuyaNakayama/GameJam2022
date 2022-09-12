#include "Font.h"

Font::Font()
{
	for (size_t i = 0; i < fontSize.size(); i++)
	{
		fonts.push_back(CreateFontToHandle(fontName.c_str(), fontSize[i], 1));
	}
}
