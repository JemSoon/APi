#include "BonusLevel.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include "BackGround.h"
#include "Player.h"
#include "BigPlayer.h"
#include "WhitePlayer.h"
#include "Monster.h"
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
}

void BonusLevel::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
	BackGround* Actor = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	Actor->GetRenderer()->SetImage("Pipe1-1.bmp");
	float4 BackActor = {};
	BackActor.x = (Actor->GetRenderer()->GetImage()->GetScale().Half().x);
	BackActor.y = (Actor->GetRenderer()->GetImage()->GetScale().Half().y);
}

void BonusLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
	BackGround* Actor = CreateActor<BackGround>((int)ORDER::BACKGROUND);
	Actor->GetRenderer()->SetImage("Pipe1-1.bmp");

	{	//맵 이미지 첫화면에 맞게 맞추기
		float4 BackActor = {};
		BackActor.x = (Actor->GetRenderer()->GetImage()->GetScale().Half().x);
		BackActor.y = (Actor->GetRenderer()->GetImage()->GetScale().Half().y);

		Actor->GetRenderer()->SetPivot(BackActor);
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

		Player::MainPlayer->SetPosition({ 300.0f,300.0f });
	}
}
