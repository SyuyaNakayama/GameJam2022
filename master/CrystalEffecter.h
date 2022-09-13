#pragma once
#include "Vector2.h"
#include "Ease.h"
#include <vector>

class CrystalEffecter
{
private:
	struct CrystalEffect
	{
		Vector2Int pos;
		int height = 0;
		int trans = 0;
		Ease ease;
		bool jet = false;
	};
	std::vector<CrystalEffect> effects;
	int crystalG = 0;
	Vector2Int* leftTop = nullptr;
public:
	void Load();
	void Emit(const Vector2Int& num);
	void Clear();
	void Update();
	void Draw(const Vector2Int& camera);
	void SetLeftTop(Vector2Int* leftTop);
private:
	void Erase(const int num);
};

