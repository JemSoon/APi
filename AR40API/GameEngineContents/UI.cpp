#include "UI.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

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
		UIPivot.y = -333.0f;// Renderer->GetImage()->GetScale().Half().y;//반 아래로 내림

		Renderer->SetPivot(UIPivot);
	}
	//Pos.y *= 2.0f;

	//SetScale(GameEngineWindow::GetScale());
}

