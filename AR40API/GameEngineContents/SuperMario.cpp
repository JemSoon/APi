#include "SuperMario.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

SuperMario::SuperMario()
{

}

SuperMario::~SuperMario()
{

}

void SuperMario::GameInit()
{
	//â�� ��� �̹��� ���� ������
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });

	GameEngineImageManager::GetInst()->Load("C:\\Users\\highy\\Desktop\\C++\\AR40API\\AllResources\\Texture\\idle-R.bmp","idle-R.bmp");


	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Play");//�ΰ��� ȭ�� ��������� üũ��
	//ChangeLevel("Title");//�÷��̸� ų�Ÿ� �̰� ������!
}

void SuperMario::GameLoop()
{
}

void SuperMario::GameEnd()
{
}
