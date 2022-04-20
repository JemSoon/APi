#include "IntroLevel.h"
#include "Intro.h"
#include "BackGround.h"
#include <GameEngineBase/GameEngineInput.h>
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>


enum class ORDER //이미지 올라갈 순서 설정
{
	BACKGROUND,
	MONSTER,
	PLAYER,
	UI
};

IntroLevel::IntroLevel()
{

}

IntroLevel::~IntroLevel()
{

}

void IntroLevel::Loading()
{
	BackGround* Back = CreateActor<BackGround>(0);
	Back->GetRenderer()->SetImage("idle-R.bmp");
}

void IntroLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("Play1"))
	{
		GameEngine::GetInst().ChangeLevel("Play1");//넘기는기능
	}

	if (true == GameEngineInput::GetInst()->IsDown("Pipe1"))
	{
		GameEngine::GetInst().ChangeLevel("Pipe1");//넘기는기능
	}

	if (true == GameEngineInput::GetInst()->IsDown("Play2"))
	{
		GameEngine::GetInst().ChangeLevel("Play2");//넘기는기능
	}

	if (true == GameEngineInput::GetInst()->IsDown("Play3"))
	{
		GameEngine::GetInst().ChangeLevel("Play3");//넘기는기능
	}

	if (true == GameEngineInput::GetInst()->IsDown("Title"))
	{
		GameEngine::GetInst().ChangeLevel("Title");//넘기는기능
	}
}

void IntroLevel::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
}

void IntroLevel::LevelChangeStart(GameEngineLevel* _NextLevel)
{
}

