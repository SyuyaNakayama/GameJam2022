#pragma once
#include <string>
#include <vector>
#include "DxLib.h"

enum FontSize { M, L };

class Font
{
private:
	std::string fontName = "廻想体 ネクスト UP B";
	std::vector<int>fontSize = { 32,48 };
	std::vector<int>fonts;
public:
	Font();
	int GetFontSize(FontSize fontSize_) { return fontSize[fontSize_]; }
	int Use(FontSize fontSize_) { return fonts[fontSize_]; }
};