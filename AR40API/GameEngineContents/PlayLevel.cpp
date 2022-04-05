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
	{	//��� �ε�
		BackGround* Back = CreateActor<BackGround>(0);
		Back->GetRenderer()->SetImage("Map1-1All.bmp");
	}

	{	//�÷��̾� �ε�
		CreateActor<Player>((int)ORDER::PLAYER);
	}

	{	//UI�ε�
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