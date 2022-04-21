#include "SuperMario.h"
#include "IntroLevel.h"
#include "PlayLevel.h"
#include "BonusLevel.h"
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
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({860,120}, {1280, 720});
	{
		//���ҽ� ���
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

		{
			//�̹����� ã��
			GameEngineImage* Image0 = GameEngineImageManager::GetInst()->Find("walk-R.bmp");
			//�׸��� �̹����� �������� ������ �߶���
			Image0->CutCount( 3, 1 );//Walk-L�̹����� ����3 ����1�� ©���

			GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("walk-L.bmp");
			
			Image1->CutCount(3, 1);

			GameEngineImage* Image3 = GameEngineImageManager::GetInst()->Find("idle-L.bmp");
			
			Image3->Cut({ 64, 64 });

			GameEngineImage* Image4 = GameEngineImageManager::GetInst()->Find("idle-R.bmp");

			Image4->Cut({ 64, 64 });

			GameEngineImage* Image5 = GameEngineImageManager::GetInst()->Find("gumba-walk.bmp");

			Image5->CutCount(2, 1);

			//�Ѿ˵� ã��
			GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("Bullet.bmp");
			//�׸��� �̹����� �������� ������ �߶���
			Image2->Cut({ 32, 32 });
			//�Ѿ� ����
			GameEngineImage* Image6 = GameEngineImageManager::GetInst()->Find("Hit.bmp");

			Image6->Cut({ 32, 32 });

			GameEngineImage* Image7 = GameEngineImageManager::GetInst()->Find("jump-R.bmp");

			Image7->Cut({ 64, 64 });

			GameEngineImage* Image8 = GameEngineImageManager::GetInst()->Find("jump-L.bmp");

			Image8->Cut({ 64, 64 });

		}
	}
	if (false == GameEngineInput::GetInst()->IsKey("Play1"))
	{	//false�� ������� �� ���� Ű �̴�
		GameEngineInput::GetInst()->CreateKey("Title", VK_RETURN);
		GameEngineInput::GetInst()->CreateKey("Intro", VK_RETURN);
		GameEngineInput::GetInst()->CreateKey("Play1", '1');
		GameEngineInput::GetInst()->CreateKey("Pipe1", 'F');
		GameEngineInput::GetInst()->CreateKey("Play2", '2');
		GameEngineInput::GetInst()->CreateKey("Play3", '3');
		GameEngineInput::GetInst()->CreateKey("Debug", 'R');
	}


	////�̹����� ã��
	//GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("walk-L.bmp");
	////�׸��� �̹����� �������� ������ �߶���
	//Image->Cut({ 64, 64 });


	//GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("Bullet.bmp");
	////�׸��� �̹����� �������� ������ �߶���
	//Image2->Cut({ 32, 32 });
	

	CreateLevel<TitleLevel>("Title");
	CreateLevel<IntroLevel>("Intro");
	CreateLevel<PlayLevel>("Play1");
	CreateLevel<BonusLevel>("Pipe1");
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
