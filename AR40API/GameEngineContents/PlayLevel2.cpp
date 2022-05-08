#include "PlayLevel2.h"
#include "Player.h"
#include "BackGround.h"
#include <GameEngineBase/GameEngineInput.h>
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>


PlayLevel2::PlayLevel2()
{

}

PlayLevel2::~PlayLevel2()
{

}

void PlayLevel2::Loading()
{
}

void PlayLevel2::Update()
{

}

void PlayLevel2::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
	Player::ChangeLevel_ = false;
}

void PlayLevel2::LevelChangeStart(GameEngineLevel* _NextLevel)
{
	BackGround* Back = CreateActor<BackGround>(0);
	Back->GetRenderer()->SetImage("End.bmp");
	//Back->SetPosition({ 576,480 });
	Back->SetPosition({ 640,480 });
}


