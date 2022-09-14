#include "UIDrawer.h"

void UIDrawer::LoadAndSet(int* actionNum, int* coinCount, int* crystalNum)
{
	pickel.Load();
	cash.Load();
	crystal.Load();

	pickel.SetActNum(actionNum);
	cash.SetCoinCount(coinCount);
	crystal.SetCrystalNum(crystalNum);

	input = Input::GetInstance();
	font = Font::GetInstance();
}

void UIDrawer::Initialize()
{
	pickel.Initialize();
	cash.Initialize();
	crystal.Initialize();
}

void UIDrawer::Update()
{
	pickel.Update();
	cash.Update();
	crystal.Update();
}

void UIDrawer::DrawTutorial(const Vector2Int& camera) 
{
	pickel.Draw({ 680, 150 }, camera);
	cash.Draw({ 920, 150 }, camera);
	crystal.Draw({ 1320, 470 }, camera);
	DrawInput();
}
void UIDrawer::DrawPlay(const Vector2Int& camera)
{
	pickel.Draw({ 680, 150 }, camera);
	cash.Draw({ 920, 150 }, camera);
	crystal.Draw({ 1320, 470 }, camera);
	DrawInput();
}

void UIDrawer::DrawInput()
{
	if (input->GetConnect() == Input::Connect::JoyPad)
	{
		input->pad->DrawButton({ 1500, 500 });
		input->pad->DrawStick({ 200,500 });
	}
	else if (input->GetConnect() == Input::Connect::Keyboard)
	{
		//input->keys->DrawArrow();
		//input->keys->DrawSpace();
		//input->keys->DrawShift();
		//input->keys->DrawKey();
		//input->keys->DrawShift();
		//input->keys->DrawSpace();
	}
}
