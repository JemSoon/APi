#include "IntroLevel.h"
#include "Intro.h"
#include "BackGround.h"
#include <GameEngineBase/GameEngineInput.h>
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>


enum class ORDER //�̹��� �ö� ���� ����
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
		GameEngine::GlobalEngine().ChangeLevel("Play1");//�ѱ�±��
	}

	if (true == GameEngineInput::GetInst()->IsDown("Play2"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Play2");//�ѱ�±��
	}

	if (true == GameEngineInput::GetInst()->IsDown("Play3"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Play3");//�ѱ�±��
	}

	if (true == GameEngineInput::GetInst()->IsDown("Title"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Title");//�ѱ�±��
	}
}

void IntroLevel::LevelChangeStart()
{

}