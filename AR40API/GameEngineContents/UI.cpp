#include "UI.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

UI* UI::MainUI = nullptr;

UI::UI():
	CoinCount_(0)
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

	{	//=================���� ���� ���� ������==================
		{
			//���� ����(���� �ڸ�)
			GameEngineRenderer* Ten = CreateRenderer((int)ORDER::UI);
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

			Ten->CameraEffectOff();//UI�� ī�޶� ����ȹ޴´�
		}
		{
			//���� ����(���� �ڸ�)
			GameEngineRenderer* One = CreateRenderer((int)ORDER::UI);
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

			One->CameraEffectOff();//UI�� ī�޶� ����ȹ޴´�
		}
	}
	//Pos.y *= 2.0f;

	//SetScale(GameEngineWindow::GetScale());
}

void UI::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainUI = this;
}

