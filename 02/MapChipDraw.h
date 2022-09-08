#pragma once
class MapChipDraw
{
public:
	enum BlockName
	{
		None,
		Block,
		Coin,
		Crystal,
	};
private:

	int goldG;
	int oreG;
	int oreMaskG;
public:
	void Load();
	void Draw();
};