#include "PlayLevel2.h"
#include "Player.h"
#include "UI.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>

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
	if (true == GameEngineInput::GetInst()->IsDown("Intro"))
	{
		GameEngine::GetInst().ChangeLevel("Intro");
	}
}

void PlayLevel2::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
}

void PlayLevel2::LevelChangeStart(GameEngineLevel* _NextLevel)
{
}


