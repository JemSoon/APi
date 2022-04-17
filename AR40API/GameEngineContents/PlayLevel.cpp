#include "PlayLevel.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include "BackGround.h"
#include "Player.h"
#include "Monster.h"
#include "ContentsEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include "UI.h"
#include <GameEngineBase/GameEngineWindow.h>

PlayLevel::PlayLevel()
{

}

PlayLevel::~PlayLevel()
{

}

void PlayLevel::Loading()
{	
	{	//1스테이지의 배경 로드
		BackGround* Actor = CreateActor<BackGround>((int)ORDER::BACKGROUND);
		Actor->GetRenderer()->SetImage("Map1-1.bmp");

		{	//맵 이미지 첫화면에 맞게 맞추기
			float4 BackActor = {};
			BackActor.x = (Actor->GetRenderer()->GetImage()->GetScale().Half().x) - (GameEngineWindow::GetScale().Half().x);
			BackActor.y = (Actor->GetRenderer()->GetImage()->GetScale().Half().y) - (GameEngineWindow::GetScale().Half().y) /*- 240*/;
			
			Actor->GetRenderer()->SetPivot(BackActor);

			Actor->CreateCollision("Door",{100,100}, {100, 100});//문 콜리젼 임시생성

			Actor->CreateCollision("Wall", { 100,100 }, { 0, -200 });

		}

		{
			//1스테이지의 플레이어 로드
			Player* Mario = CreateActor<Player>((int)ORDER::PLAYER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Mario->SetPosition({ 320.0f,740.0f });
		}

		{
			//1스테이지의 플레이어 로드
			Monster* Gumba = CreateActor<Monster>((int)ORDER::MONSTER);
			//Player->SetPosition(GameEngineWindow::GetScale().Half());
			Gumba->SetPosition({ 320.0f,740.0f });
		}

		{	
			//1스테이지의 UI 로드
			CreateActor<UI>((int)ORDER::UI);
		}
	}

 }

void PlayLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("Intro"))
	{
		GameEngine::GetInst().ChangeLevel("Intro");
	}

}

void PlayLevel::LevelChangeStart()
{
	//CreateActor<Player>((int)ORDER::PLAYER);
	//CreateActor<UI>((int)ORDER::UI);

}