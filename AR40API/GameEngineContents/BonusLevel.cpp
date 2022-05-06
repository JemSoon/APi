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
	{	//타이틀과 인트로(목숨정보)화면으로 넘어갈땐 플레이어가 안넘어간다
		Player::MainPlayer->NextLevelOn();
		BigPlayer::MainBigPlayer->NextLevelOn();
		WhitePlayer::MainWhitePlayer->NextLevelOn();
		UI::MainUI->NextLevelOn();
	}
		Player::ChangeLevel_ == false;//다시꺼줘야 함
}

void BonusLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BackGround* Actor = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	Actor->GetRenderer()->SetImage("Pipe1-1.bmp");

	{	//맵 이미지 첫화면에 맞게 맞추기
		float4 BackActor = {};
		BackActor.x = (Actor->GetRenderer()->GetImage()->GetScale().Half().x);
		BackActor.y = (Actor->GetRenderer()->GetImage()->GetScale().Half().y);

		Actor->GetRenderer()->SetPivot(BackActor);
		Actor->CreateCollision("Wall-L", { 200,100 }, { 961,704 });//파이프관
	}
	{
		//코인 테스트
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
			//스테이지의 플레이어 로드
			Player::MainPlayer = CreateActor<Player>((int)ORDER::PLAYER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());

			//큰마리오
			BigPlayer::MainBigPlayer = CreateActor<BigPlayer>((int)ORDER::PLAYER);

			//흰마리오
			WhitePlayer::MainWhitePlayer = CreateActor<WhitePlayer>((int)ORDER::PLAYER);

			//스테이지의 UI 로드
			CreateActor<UI>((int)ORDER::UI);
		}
		//CreateActor<UI>((int)ORDER::UI);
		Player::MainPlayer->SetPosition({ 300.0f,300.0f });
		BigPlayer::MainBigPlayer->SetPosition({ 300.0f,300.0f });
		WhitePlayer::MainWhitePlayer->SetPosition({ 300.0f,300.0f });
	}
}
