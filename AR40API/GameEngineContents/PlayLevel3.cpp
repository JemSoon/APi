#include "PlayLevel3.h"
#include "Player.h"
#include "UI.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>

PlayLevel3::PlayLevel3()
{

}

PlayLevel3::~PlayLevel3()
{

}

void PlayLevel3::Loading()
{
}

void PlayLevel3::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("Intro"))
	{
		GameEngine::GetInst().ChangeLevel("Intro");
	}
}

void PlayLevel3::LevelChangeStart()
{
}
