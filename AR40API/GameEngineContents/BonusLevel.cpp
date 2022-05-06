#include "BonusLevel.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include "BackGround.h"
#include "Player.h"
#include "BigPlayer.h"
#include "WhitePlayer.h"
#include "Monster.h"
#include "Coin.h"
#include "ContentsEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include "UI.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImage.h>

BonusLevel::BonusLevel()
{

}

BonusLevel::~BonusLevel()
{

}

void BonusLevel::Loading()
{
}

void BonusLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("Intro"))
	{
		GameEngine::GetInst().ChangeLevel("Intro");
	}
	if (true == GameEngineInput::GetInst()->IsDown("Debug"))
	{
		GameEngineLevel::IsDebugModeSwitch();
	}
}

void BonusLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BackGround* Actor = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	Actor->GetRenderer()->SetImage("Pipe1-1.bmp");
	float4 BackActor = {};
	BackActor.x = (Actor->GetRenderer()->GetImage()->GetScale().Half().x);
	BackActor.y = (Actor->GetRenderer()->GetImage()->GetScale().Half().y);
	
	if ((_NextLevel->GetNameCopy() != "Title" || _NextLevel->GetNameCopy() != "Intro") && Player::ChangeLevel_ == true)
	{	//Ÿ��Ʋ�� ��Ʈ��(�������)ȭ������ �Ѿ�� �÷��̾ �ȳѾ��
		Player::MainPlayer->NextLevelOn();
		BigPlayer::MainBigPlayer->NextLevelOn();
		WhitePlayer::MainWhitePlayer->NextLevelOn();
		UI::MainUI->NextLevelOn();
	}
		Player::ChangeLevel_ == false;//�ٽò���� ��
}

void BonusLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BackGround* Actor = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	Actor->GetRenderer()->SetImage("Pipe1-1.bmp");

	{	//�� �̹��� ùȭ�鿡 �°� ���߱�
		float4 BackActor = {};
		BackActor.x = (Actor->GetRenderer()->GetImage()->GetScale().Half().x);
		BackActor.y = (Actor->GetRenderer()->GetImage()->GetScale().Half().y);

		Actor->GetRenderer()->SetPivot(BackActor);
		Actor->CreateCollision("Wall-L", { 200,100 }, { 961,704 });//��������
	}
	{
		//���� �׽�Ʈ
		Coin* Coin1 = CreateActor<Coin>((int)ORDER::ITEM);
		Coin1->SetPosition({ 400.0f,335.0f });

		Coin* Coin2 = CreateActor<Coin>((int)ORDER::ITEM);
		Coin2->SetPosition({ 464.0f,335.0f });

		Coin* Coin3 = CreateActor<Coin>((int)ORDER::ITEM);
		Coin3->SetPosition({ 518.0f,335.0f });
	}

	{
		if (nullptr == Player::MainPlayer)
		{
			//���������� �÷��̾� �ε�
			Player::MainPlayer = CreateActor<Player>((int)ORDER::PLAYER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());

			//ū������
			BigPlayer::MainBigPlayer = CreateActor<BigPlayer>((int)ORDER::PLAYER);

			//�򸶸���
			WhitePlayer::MainWhitePlayer = CreateActor<WhitePlayer>((int)ORDER::PLAYER);

			//���������� UI �ε�
			CreateActor<UI>((int)ORDER::UI);
		}
		//CreateActor<UI>((int)ORDER::UI);
		Player::MainPlayer->SetPosition({ 300.0f,300.0f });
		BigPlayer::MainBigPlayer->SetPosition({ 300.0f,300.0f });
		WhitePlayer::MainWhitePlayer->SetPosition({ 300.0f,300.0f });
	}
}
