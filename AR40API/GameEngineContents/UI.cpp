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
	TimeCount_ = 300;
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

			Ten->CameraEffectOff();//UI�� ī�޶� ����ȹ޴´�
		}
		{
			//���� ����(���� �ڸ�)
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

			One->CameraEffectOff();//UI�� ī�޶� ����ȹ޴´�
		}
	}

		//==================Ÿ�̸� �׽�Ʈ======================//
	{
		TH = CreateRenderer((int)ORDER::UI);
		TH->CreateAnimation("0.bmp", "0", 0, 0, 0.0f, false);
		TH->CreateAnimation("1.bmp", "1", 0, 0, 0.0f, false);
		TH->CreateAnimation("2.bmp", "2", 0, 0, 0.0f, false);
		TH->CreateAnimation("3.bmp", "3", 0, 0, 0.0f, false);
		TH->CreateAnimation("4.bmp", "4", 0, 0, 0.0f, false);
		TH->CreateAnimation("5.bmp", "5", 0, 0, 0.0f, false);
		TH->CreateAnimation("6.bmp", "6", 0, 0, 0.0f, false);
		TH->CreateAnimation("7.bmp", "7", 0, 0, 0.0f, false);
		TH->CreateAnimation("8.bmp", "8", 0, 0, 0.0f, false);
		TH->CreateAnimation("9.bmp", "9", 0, 0, 0.0f, false);

		TH->ChangeAnimation("3");

		float4 UIPivot = GameEngineWindow::GetScale().Half();
		UIPivot.x = 570.0f;
		UIPivot.y = -440.0f;

		TH->SetPivot(UIPivot);
		TH->CameraEffectOff();//UI�� ī�޶� ����ȹ޴´�

	}
	{
		TTen = CreateRenderer((int)ORDER::UI);
		TTen->CreateAnimation("0.bmp", "0", 0, 0, 0.0f, false);
		TTen->CreateAnimation("1.bmp", "1", 0, 0, 0.0f, false);
		TTen->CreateAnimation("2.bmp", "2", 0, 0, 0.0f, false);
		TTen->CreateAnimation("3.bmp", "3", 0, 0, 0.0f, false);
		TTen->CreateAnimation("4.bmp", "4", 0, 0, 0.0f, false);
		TTen->CreateAnimation("5.bmp", "5", 0, 0, 0.0f, false);
		TTen->CreateAnimation("6.bmp", "6", 0, 0, 0.0f, false);
		TTen->CreateAnimation("7.bmp", "7", 0, 0, 0.0f, false);
		TTen->CreateAnimation("8.bmp", "8", 0, 0, 0.0f, false);
		TTen->CreateAnimation("9.bmp", "9", 0, 0, 0.0f, false);

		TTen->ChangeAnimation("0");

		float4 UIPivot = GameEngineWindow::GetScale().Half();
		UIPivot.x = 595.0f;
		UIPivot.y = -440.0f;

		TTen->SetPivot(UIPivot);
		TTen->CameraEffectOff();//UI�� ī�޶� ����ȹ޴´�
	}
	{
		TOne = CreateRenderer((int)ORDER::UI);
		TOne->CreateAnimation("0.bmp", "0", 0, 0, 0.0f, false);
		TOne->CreateAnimation("1.bmp", "1", 0, 0, 0.0f, false);
		TOne->CreateAnimation("2.bmp", "2", 0, 0, 0.0f, false);
		TOne->CreateAnimation("3.bmp", "3", 0, 0, 0.0f, false);
		TOne->CreateAnimation("4.bmp", "4", 0, 0, 0.0f, false);
		TOne->CreateAnimation("5.bmp", "5", 0, 0, 0.0f, false);
		TOne->CreateAnimation("6.bmp", "6", 0, 0, 0.0f, false);
		TOne->CreateAnimation("7.bmp", "7", 0, 0, 0.0f, false);
		TOne->CreateAnimation("8.bmp", "8", 0, 0, 0.0f, false);
		TOne->CreateAnimation("9.bmp", "9", 0, 0, 0.0f, false);

		TOne->ChangeAnimation("0");

		float4 UIPivot = GameEngineWindow::GetScale().Half();
		UIPivot.x = 620.0f;
		UIPivot.y = -440.0f;

		TOne->SetPivot(UIPivot);
		TOne->CameraEffectOff();//UI�� ī�޶� ����ȹ޴´�
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

	{	//���ΰ��� ����
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

		std::string TenText = CoinText.substr(0, 1);//�����ڸ�
		std::string OneText = CoinText.substr(1, 1);//�����ڸ�

		Ten->ChangeAnimation(TenText);
		One->ChangeAnimation(OneText);

		if (CoinCount_ > 99)
		{
			CoinCount_ = 0;
			//��� +1
			//��� +1 ����
		}
	}

	{
		////������ ���� Ÿ�̸ӵ� ���� ���� Test
		//char Arr[10];
		//_itoa_s(TimeCount_, Arr, 10); //0~9�� ���ڿ���
		//
		////TimeCount_ = TimeCount_ + GameEngineTime::GetDeltaTime();
		//std::string TimeText = Arr;
		//if (1 == TimeText.size())
		//{
		//	TimeText = "0" + TimeText;
		//}
		//
		//std::string HTime = TimeText.substr(0,2);//���ڸ��� �����ڸ�
		//std::string TTime = TimeText.substr(1, 2);//���ڸ��� �����ڸ�
		//std::string OneTime = TimeText.substr(2, 2);
		//
		//TH->ChangeAnimation(HTime);
		//TTen->ChangeAnimation(TTime);
		//TOne->ChangeAnimation(OneTime);
	}
}