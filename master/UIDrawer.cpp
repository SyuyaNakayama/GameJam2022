#include "UIDrawer.h"

void UIDrawer::LoadAndSet(int* actionNum, int* coinCount, int* crystalNum)
{
	pickel.Load();
	cash.Load();
	crystal.Load();

	pickel.SetActNum(actionNum);
	cash.SetCoinCount(coinCount);
	crystal.SetCrystalNum(crystalNum);

	pActNum = actionNum;
	pCoinCount = coinCount;

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

void UIDrawer::DrawTitle()
{
	DrawFormatStringToHandle(600, 700, GetColor(255, 255, 255), font->Use(FontSize::L), "PRESS");
	DrawFormatStringToHandle(1100, 700, GetColor(255, 255, 255), font->Use(FontSize::L), "START");
	if (input->GetConnect() == Input::Connect::JoyPad)
	{
		input->pad->DrawB({ 900, 690 }, 2);
	}
	else if (input->GetConnect() == Input::Connect::Keyboard)
	{
		input->keys->DrawSpace({ 825, 690 }, 2);
	}
}

void UIDrawer::DrawPro(const Vector2Int& camera)
{
	if (input->GetConnect() == Input::Connect::JoyPad)
	{
		input->pad->DrawX({ 1640,70 });
	}
	else if (input->GetConnect() == Input::Connect::Keyboard)
	{
		input->keys->DrawKey({ 1640,70 });
		DrawFormatStringToHandle(1665, 75, GetColor(100, 200, 235), font->Use(FontSize::S), "S");
	}
	font->DrawUseFont({ 1700,80 }, GetColor(255, 255, 255), "：SKIP", FontSize::M);
}

void UIDrawer::DrawTutorial(const Vector2Int& camera, const int bombCount)
{
	pickel.Draw({ 700, 160 }, camera);
	DrawFormatStringToHandle(760, 170, GetColor(255, 255, 255), font->Use(FontSize::M),
		"：%d回", *pActNum);

	cash.Draw({ 1420, 660 }, camera);
	DrawFormatStringToHandle(1500, 670, GetColor(255, 255, 255), font->Use(FontSize::M),
		"：%d枚", *pCoinCount);

	crystal.Draw({ 1320, 470 }, camera);

	if (input->GetConnect() == Input::Connect::JoyPad)
	{
		input->pad->DrawButton({ 160, 300 });
		DrawFormatStringToHandle(400, 360, GetColor(220, 270, 30), font->Use(FontSize::M),
			"選択");
		DrawFormatStringToHandle(330, 270, GetColor(240, 220, 20), font->Use(FontSize::M),
			"破壊", bombCount);
		DrawFormatStringToHandle(240, 480, GetColor(80, 200, 60), font->Use(FontSize::M),
			"キャンセル", bombCount);

		input->pad->DrawStick({ 192, 600 });
		DrawFormatStringToHandle(120, 750, GetColor(255, 255, 255), font->Use(FontSize::M),
			"カーソル移動", bombCount);

		input->pad->DrawX({ 1640,70 });
	}
	else if (input->GetConnect() == Input::Connect::Keyboard)
	{
		input->keys->DrawSpace({ 220, 400 });
		DrawFormatStringToHandle(235, 480, GetColor(220, 270, 30), font->Use(FontSize::M),
			"選択");
		input->keys->DrawEnter({ 370, 280 });
		DrawFormatStringToHandle(370, 220, GetColor(240, 220, 20), font->Use(FontSize::M),
			"破壊", bombCount);
		input->keys->DrawShift({ 130, 340 });
		DrawFormatStringToHandle(50, 280, GetColor(80, 200, 60), font->Use(FontSize::M),
			"キャンセル", bombCount);


		input->keys->DrawArrow({ 160, 560 });
		DrawFormatStringToHandle(120, 750, GetColor(255, 255, 255), font->Use(FontSize::M),
			"カーソル移動", bombCount);

		input->keys->DrawKey({ 1640,70 });
		DrawFormatStringToHandle(1665, 75, GetColor(100, 200, 235), font->Use(FontSize::S),
			"S", bombCount);
	}

	font->DrawUseFont({ 1700,80 }, GetColor(255, 255, 255), "：SKIP", FontSize::M);

	DrawFormatStringToHandle(1350, 770, GetColor(255, 255, 255), font->Use(FontSize::M),
		"ボムによる破壊：%d個", bombCount);
}

void UIDrawer::DrawPlay(const Vector2Int& camera, const int bombCount, const int stage)
{
	pickel.Draw({ 700, 160 }, camera);
	DrawFormatStringToHandle(760, 170, GetColor(255, 255, 255), font->Use(FontSize::M),
		"：%d回", *pActNum);

	cash.Draw({ 1420, 660 }, camera);
	DrawFormatStringToHandle(1500, 670, GetColor(255, 255, 255), font->Use(FontSize::M),
		"：%d枚", *pCoinCount);

	crystal.Draw({ 1320, 470 }, camera);

	if (input->GetConnect() == Input::Connect::JoyPad)
	{
		input->pad->DrawButton({ 160, 300 });
		DrawFormatStringToHandle(400, 360, GetColor(220, 270, 30), font->Use(FontSize::M),
			"選択");
		DrawFormatStringToHandle(330, 270, GetColor(240, 220, 20), font->Use(FontSize::M),
			"破壊", bombCount);
		DrawFormatStringToHandle(240, 480, GetColor(80, 200, 60), font->Use(FontSize::M),
			"キャンセル", bombCount);

		input->pad->DrawStick({ 192, 600 });
		DrawFormatStringToHandle(120, 750, GetColor(255, 255, 255), font->Use(FontSize::M),
			"カーソル移動", bombCount);

		input->pad->DrawX({ 1640,70 });
	}
	else if (input->GetConnect() == Input::Connect::Keyboard)
	{
		input->keys->DrawSpace({ 220, 400 });
		DrawFormatStringToHandle(235, 480, GetColor(220, 270, 30), font->Use(FontSize::M),
			"選択");
		input->keys->DrawEnter({ 370, 280 });
		DrawFormatStringToHandle(370, 220, GetColor(240, 220, 20), font->Use(FontSize::M),
			"破壊", bombCount);
		input->keys->DrawShift({ 130, 340 });
		DrawFormatStringToHandle(50, 280, GetColor(80, 200, 60), font->Use(FontSize::M),
			"キャンセル", bombCount);


		input->keys->DrawArrow({ 160, 560 });
		DrawFormatStringToHandle(120, 750, GetColor(255, 255, 255), font->Use(FontSize::M),
			"カーソル移動", bombCount);

		input->keys->DrawKey({ 1640,70 });
		DrawFormatStringToHandle(1665, 75, GetColor(100, 200, 235), font->Use(FontSize::S), "S");
	}

	font->DrawUseFont({ 1700,80 }, GetColor(255, 255, 255), "：MENU", FontSize::M);

	DrawFormatStringToHandle(1350, 770, GetColor(255, 255, 255), font->Use(FontSize::M),
		"ボムによる破壊：%d個", bombCount);

	DrawFormatStringToHandle(950, 70, GetColor(255, 255, 255), font->Use(FontSize::M), "ステージ：%d", stage);
}

void UIDrawer::DrawMenu()
{
	font->DrawUseFont({ 820, 150 }, GetColor(255, 255, 255), "MENU", FontSize::LL);
	if (input->GetConnect() == Input::Connect::JoyPad)
	{
		input->pad->DrawX({ 450, 400 }, 2);
		font->DrawUseFont({ 600, 400 }, GetColor(255, 255, 255), "：リザルトへ", FontSize::LL);
		input->pad->DrawB({ 450, 600 }, 2);
		font->DrawUseFont({ 600, 600 }, GetColor(255, 255, 255), "：ゲームに戻る", FontSize::LL);
	}
	else if (input->GetConnect() == Input::Connect::Keyboard)
	{
		input->keys->DrawSpace({ 420, 400 }, 2);
		font->DrawUseFont({ 650, 400 }, GetColor(255, 255, 255), "：リザルトへ", FontSize::LL);
		input->keys->DrawKey({ 430, 580 }, 3);
		DrawFormatStringToHandle(505, 610, GetColor(100, 200, 235), font->Use(FontSize::L), "S");
		font->DrawUseFont({ 600, 600 }, GetColor(255, 255, 255), "：ゲームに戻る", FontSize::LL);

	}
}

void UIDrawer::DrawResult(const int offset)
{
	if (input->GetConnect() == Input::Connect::JoyPad)
	{
		input->pad->DrawB({ 730 + offset, 870 });
		input->pad->DrawB({ 730 + offset - 1880, 870 });
	}
	else if (input->GetConnect() == Input::Connect::Keyboard)
	{
		input->keys->DrawSpace({ 680 + offset, 870 });
		input->keys->DrawSpace({ 680 + offset - 1880, 870 });
	}
}
