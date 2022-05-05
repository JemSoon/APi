#include "UI.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include "Coin.h"
#include <GameEngine/GameEngineCollision.h>

UI* UI::MainUI = nullptr;
int UI::CoinCount_ = 0;
UI::UI()
{

}

UI::~UI()
{

}

void UI::Start()
{
	CoinCount_ = 00;
	{	//해당 이미지를 화면 중간에 놓는다
		float4 Pos = GameEngineWindow::GetScale().Half();
		SetPosition(Pos);
	}

	{	//화면 ui랜더를 만든다
		GameEngineRenderer* Renderer = CreateRenderer("UI-Test.bmp");
		
		//Renderer->GetImage();

		float4 UIPivot = GameEngineWindow::GetScale().Half();
		UIPivot.x = 0.0f;
		UIPivot.y = -450.0f;// Renderer->GetImage()->GetScale().Half().y;//반 아래로 내림

		Renderer->SetPivot(UIPivot);

		Renderer->CameraEffectOff();//UI는 카메라 영향안받는다
	}

	{	//코인 반짝반짝
		GameEngineRenderer* Renderer = CreateRenderer((int)ORDER::UI);
		Renderer->CreateAnimation("UI-Coin-icon.bmp", "UI-Coin", 0, 2, 0.3f, true);
		Renderer->ChangeAnimation("UI-Coin");
	
	
		float4 UIPivot = GameEngineWindow::GetScale().Half();
		UIPivot.x = -240.0f;
		UIPivot.y = -440.0f;
	
		Renderer->SetPivot(UIPivot);
	
		Renderer->CameraEffectOff();//UI는 카메라 영향안받는다
	}

	{	//=================코인 개수 숫자 렌더링==================
		{
			//코인 개수(십의 자리)
			Ten = CreateRenderer((int)ORDER::UI);
			Ten->CreateAnimation("0.bmp", "0", 0, 0, 0.0f, false);
			Ten->CreateAnimation("1.bmp", "1", 0, 0, 0.0f, false);
			Ten->CreateAnimation("2.bmp", "2", 0, 0, 0.0f, false);
			Ten->CreateAnimation("3.bmp", "3", 0, 0, 0.0f, false);
			Ten->CreateAnimation("4.bmp", "4", 0, 0, 0.0f, false);
			Ten->CreateAnimation("5.bmp", "5", 0, 0, 0.0f, false);
			Ten->CreateAnimation("6.bmp", "6", 0, 0, 0.0f, false);
			Ten->CreateAnimation("7.bmp", "7", 0, 0, 0.0f, false);
			Ten->CreateAnimation("8.bmp", "8", 0, 0, 0.0f, false);
			Ten->CreateAnimation("9.bmp", "9", 0, 0, 0.0f, false);

			Ten->ChangeAnimation("0");


			float4 UIPivot = GameEngineWindow::GetScale().Half();
			UIPivot.x = -192.0f;
			UIPivot.y = -440.0f;

			Ten->SetPivot(UIPivot);

			Ten->CameraEffectOff();//UI는 카메라 영향안받는다
		}
		{
			//코인 개수(일의 자리)
			One = CreateRenderer((int)ORDER::UI);
			One->CreateAnimation("0.bmp", "0", 0, 0, 0.0f, false);
			One->CreateAnimation("1.bmp", "1", 0, 0, 0.0f, false);
			One->CreateAnimation("2.bmp", "2", 0, 0, 0.0f, false);
			One->CreateAnimation("3.bmp", "3", 0, 0, 0.0f, false);
			One->CreateAnimation("4.bmp", "4", 0, 0, 0.0f, false);
			One->CreateAnimation("5.bmp", "5", 0, 0, 0.0f, false);
			One->CreateAnimation("6.bmp", "6", 0, 0, 0.0f, false);
			One->CreateAnimation("7.bmp", "7", 0, 0, 0.0f, false);
			One->CreateAnimation("8.bmp", "8", 0, 0, 0.0f, false);
			One->CreateAnimation("9.bmp", "9", 0, 0, 0.0f, false);

			One->ChangeAnimation("0");


			float4 UIPivot = GameEngineWindow::GetScale().Half();
			UIPivot.x = -168.0f;
			UIPivot.y = -440.0f;

			One->SetPivot(UIPivot);

			One->CameraEffectOff();//UI는 카메라 영향안받는다
		}
	}
	//Pos.y *= 2.0f;

	//SetScale(GameEngineWindow::GetScale());
}

void UI::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainUI = this;
}

void UI::Update()
{
	//CoinCount_ = 00;
	//std::vector<Coin> Test;

	char Arr[10];
	_itoa_s(CoinCount_, Arr, 10);
	// char
	// 01
	// '1'
	// "1"


	std::string CoinText = Arr;
	if (1 == CoinText.size())
	{
		CoinText = "0" + CoinText;
	}

	std::string TenText = CoinText.substr(0, 1);
	std::string OneText = CoinText.substr(1, 1);

	Ten->ChangeAnimation(TenText);
	One->ChangeAnimation(OneText);

	if (CoinCount_ > 99)
	{
		CoinCount_ = 0;
		//목숨 +1
		//목숨 +1 사운드
	}
}