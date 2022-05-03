#include "UI.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

UI* UI::MainUI = nullptr;

UI::UI()
{

}

UI::~UI()
{

}

void UI::Start()
{
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

	//Pos.y *= 2.0f;

	//SetScale(GameEngineWindow::GetScale());
}

void UI::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainUI = this;
}

