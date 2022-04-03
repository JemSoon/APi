#include "SuperMario.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
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

	//�̹����� ã��
	GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("walk-L.bmp");
	
	//�׸��� �̹����� �������� ������ �߶���
	Image->Cut({ 64, 64 });

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
