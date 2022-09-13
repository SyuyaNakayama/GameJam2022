#pragma once
#include <string>
#include <vector>
#include "DxLib.h"
#include "Vector2.h"

enum FontSize { M, L, LL };

class Font
{
private:
	std::string fontName = "Resources/Font/Kaisotai-Next-UP-B.ttf";
	std::vector<int>fontSize = { 32,48,96 };
	std::vector<int>fonts;
public:
	Font();
	int GetFontSize(FontSize fontSize_) { return fontSize[fontSize_]; }
	int Use(FontSize fontSize_) { return fonts[fontSize_]; }
	void DrawUseFont(Vector2Int pos, int color, std::string str, FontSize fontSize);
};