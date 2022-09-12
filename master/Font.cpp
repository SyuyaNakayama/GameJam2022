#include "Font.h"

Font::Font()
{
	for (size_t i = 0; i < fontSize.size(); i++)
	{
		fonts.push_back(CreateFontToHandle(fontName.c_str(), fontSize[i], 1));
	}
}

void Font::DrawUseFont(Vector2Int pos, int color, std::string str, FontSize fontSize)
{
	DrawStringToHandle(pos.x, pos.y, str.c_str(), color, fonts[fontSize]);
}