#include "PlayLevel.h"
#include "Player.h"
#include "UI.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>

enum class ORDER //�̹��� �ö� ���� ����
{
	BACKGROUND,
	MONSTER,
	PLAYER,
	UI
};

PlayLevel::PlayLevel()
{

}

PlayLevel::~PlayLevel()
{

}

void PlayLevel::Loading()
{
	CreateActor<Player>((int)ORDER::PLAYER);
	CreateActor<UI>((int)ORDER::UI);
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