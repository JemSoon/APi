#include "PlayLevel.h"
#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include "BackGround.h"
#include "Player.h"
#include "ContentsEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include "UI.h"


PlayLevel::PlayLevel()
{

}

PlayLevel::~PlayLevel()
{

}

void PlayLevel::Loading()
{	
	{	//배경 로드
		BackGround* Back = CreateActor<BackGround>(0);
		Back->GetRenderer()->SetImage("Map1-1All.bmp");
	}

	{	//플레이어 로드
		CreateActor<Player>((int)ORDER::PLAYER);
	}

	{	//UI로드
		CreateActor<UI>((int)ORDER::UI);
	}
}

void PlayLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("Intro"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Intro");
	}

}

void PlayLevel::LevelChangeStart()
{
	//CreateActor<Player>((int)ORDER::PLAYER);
	//CreateActor<UI>((int)ORDER::UI);

}