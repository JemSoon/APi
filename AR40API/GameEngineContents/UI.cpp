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
	{	//�ش� �̹����� ȭ�� �߰��� ���´�
		float4 Pos = GameEngineWindow::GetScale().Half();
		SetPosition(Pos);
	}

	{	//ȭ�� ui������ �����
		GameEngineRenderer* Renderer = CreateRenderer("UI-Test.bmp");
		
		//Renderer->GetImage();

		float4 UIPivot = GameEngineWindow::GetScale().Half();
		UIPivot.x = 0.0f;
		UIPivot.y = -450.0f;// Renderer->GetImage()->GetScale().Half().y;//�� �Ʒ��� ����

		Renderer->SetPivot(UIPivot);

		Renderer->CameraEffectOff();//UI�� ī�޶� ����ȹ޴´�
	}

	{	//���� ��¦��¦
		GameEngineRenderer* Renderer = CreateRenderer((int)ORDER::UI);
		Renderer->CreateAnimation("UI-Coin-icon.bmp", "UI-Coin", 0, 2, 0.3f, true);
		Renderer->ChangeAnimation("UI-Coin");
	
	
		float4 UIPivot = GameEngineWindow::GetScale().Half();
		UIPivot.x = -240.0f;
		UIPivot.y = -440.0f;
	
		Renderer->SetPivot(UIPivot);
	
		Renderer->CameraEffectOff();//UI�� ī�޶� ����ȹ޴´�
	}

	//Pos.y *= 2.0f;

	//SetScale(GameEngineWindow::GetScale());
}

void UI::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainUI = this;
}

