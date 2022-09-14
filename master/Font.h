#pragma once
#include <string>
#include <vector>
#include "Vector2.h"

enum FontSize { S, M, L, LL };

class Font
{
private:
	std::string fontName = "Resources/Font/Kaisotai-Next-UP-B.ttf";
	std::vector<int>fontSize = { 32,48,96,128 };
	std::vector<int>fonts;
public:
	void Load();
	int GetFontSize(FontSize fontSize_) { return fontSize[fontSize_]; }
	int Use(FontSize fontSize_) { return fonts[fontSize_]; }
	void DrawUseFont(Vector2Int pos, int color, std::string str, FontSize fontSize);
	void DrawCenterXLine(int yPos, int color, std::string str, FontSize fontSize); // ���E�̒��S�ɕ`�悳���
public:
	static Font* GetInstance();
private:
	Font() = default;
	~Font() = default;
	Font(const Font&) = delete;
	const Font& operator=(const Font&) = delete;
};