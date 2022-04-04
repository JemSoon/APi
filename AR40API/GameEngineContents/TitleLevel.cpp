#include "TitleLevel.h"
#include "GameEngine/GameEngine.h"
#include "TitleLogo.h"
#include "TitleBackGround.h"
#include <GameEngineBase/GameEngineInput.h>

enum class ORDER //이미지 올라갈 순서 설정
{
	BACKGROUND,
	MONSTER,
	PLAYER,
	UI
};

TitleLevel::TitleLevel()
{

}

TitleLevel::~TitleLevel()
{

}

void TitleLevel::Loading()
{
	//타이틀 로고가 만들어졌다
	//TitleLogo.h에서 CreateActor함수 받기
	//게임 엔진 레벨 헤더 참고
	CreateActor<TitleBackGround>(0); //"TitleBackGround"가 맨 처음으로(맵 구조)

	//CreateActor<TitleLogo>(1);//그 위에 로고를 올린다

}

void TitleLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("Intro"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Intro");//넘기는기능
	}
	
}