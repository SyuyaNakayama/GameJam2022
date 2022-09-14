#include "Font.h"
#include "DxLib.h"
#include <cassert>
#include "WindowSize.h"

void Font::Load()
{
	assert(AddFontResourceEx(fontName.c_str(), FR_PRIVATE, NULL) > 0);
	std::string f = "廻想体 ネクスト UP B";
	for (size_t i = 0; i < fontSize.size(); i++)
	{
		fonts.push_back(CreateFontToHandle(f.c_str(), fontSize[i], 1));
	}
}

void Font::DrawUseFont(Vector2Int pos, int color, std::string str, FontSize fontSize)
{
	DrawStringToHandle(pos.x, pos.y, str.c_str(), color, fonts[fontSize]);
}

void Font::DrawCenterXLine(int yPos, int color, std::string str, FontSize fontSize)
{
	int fontlen = GetDrawStringWidthToHandle(str.c_str(), str.size(), fonts[fontSize]);
	int xPos = (WIN_SIZE.x - fontlen) / 2;
	DrawUseFont({ xPos,yPos }, color, str, fontSize);
}

Font* Font::GetInstance()
{
	static Font instance;
	return &instance;
}
