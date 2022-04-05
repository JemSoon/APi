#include "TitleLevel.h"
#include "GameEngine/GameEngine.h"
#include "ContentsEnum.h"
#include "TitleBackGround.h"
#include <GameEngineBase/GameEngineInput.h>



TitleLevel::TitleLevel()
{

}

TitleLevel::~TitleLevel()
{

}

void TitleLevel::Loading()
{
	//Ÿ��Ʋ �ΰ� ���������
	//TitleLogo.h���� CreateActor�Լ� �ޱ�
	//���� ���� ���� ��� ����
	CreateActor<TitleBackGround>(0); //"TitleBackGround"�� �� ó������(�� ����)

	//CreateActor<TitleLogo>(1);//�� ���� �ΰ� �ø���

}

void TitleLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("Intro"))
	{
		GameEngine::GlobalEngine().ChangeLevel("Intro");//�ѱ�±��
	}
	
}