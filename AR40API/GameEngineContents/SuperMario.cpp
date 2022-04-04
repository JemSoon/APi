#include "SuperMario.h"
#include "IntroLevel.h"
#include "PlayLevel.h"
#include "PlayLevel2.h"
#include "PlayLevel3.h"
#include "EndingLevel.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>

SuperMario::SuperMario()
{

}

SuperMario::~SuperMario()
{

}

void SuperMario::GameInit()
{
	//â�� ��� �̹��� ���� ������
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({1720,120}, {1280, 720});

	GameEngineDirectory ResourcesDir;//������ ���ÿ� ���� ���丮

	ResourcesDir.MoveParent("AR40API");//������ ���� ������ �ö󰡴���

	ResourcesDir.Move("Resources");//�״��� ���ҽ� ������ �̵�

	//(����)�ڽ� ��α����� ã�� �ʴ´�
	//���߿� ���� ���� �з��ϸ� ���丮 ���� �� �������� �Ѵ�
	//�����ȿ� ��� �̹��� ������ ã�´�
	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		
	}

	if (false == GameEngineInput::GetInst()->IsKey("Title"))
	{	//false�� ������� �� ���� Ű �̴�
		GameEngineInput::GetInst()->CreateKey("Title", 'P');
		GameEngineInput::GetInst()->CreateKey("Intro", 'O');
		GameEngineInput::GetInst()->CreateKey("Play1", '1');
		GameEngineInput::GetInst()->CreateKey("Play2", '2');
		GameEngineInput::GetInst()->CreateKey("Play3", '3');
	}


	//�̹����� ã��
	GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("walk-L.bmp");
	
	//�׸��� �̹����� �������� ������ �߶���
	Image->Cut({ 64, 64 });

	CreateLevel<TitleLevel>("Title");
	CreateLevel<IntroLevel>("Intro");
	CreateLevel<PlayLevel>("Play1");
	CreateLevel<PlayLevel2>("Play2");
	CreateLevel<PlayLevel3>("Play3");
	CreateLevel<EndingLevel>("Ending");
	//ChangeLevel("Play1");//�ΰ��� ȭ�� ��������� üũ��
	ChangeLevel("Title");//�÷��̸� ų�Ÿ� �̰� ������!
}

void SuperMario::GameLoop()
{
}

void SuperMario::GameEnd()
{
}
