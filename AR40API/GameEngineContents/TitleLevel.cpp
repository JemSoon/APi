#include "TitleLevel.h"
#include "GameEngine/GameEngine.h"
#include "TitleLogo.h"
#include "TitleBackGround.h"


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

	CreateActor<TitleLogo>(1);//�� ���� �ΰ� �ø���
}

void TitleLevel::Update()
{
	//GameEngine::GlobalEngine().ChangeLevel("Play");//�ѱ�±��
}