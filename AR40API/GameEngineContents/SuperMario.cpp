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
	//창에 띄울 이미지 영역 사이즈
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({860,120}, {1280, 720});
	{
		//리소스 경로
		GameEngineDirectory ResourcesDir;//생성과 동시에 현재 디렉토리
		ResourcesDir.MoveParent("AR40API");//어디까지 상위 폴더로 올라가느냐
		ResourcesDir.Move("Resources");//그다음 리소스 폴더로 이동

		//(참고)자식 경로까지는 찾지 않는다
		//나중에 폴더 따로 분류하면 디렉토리 따로 또 만들어줘야 한다
		//폴더안에 모든 이미지 파일을 찾는다
		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());

		}

		{
			//이미지를 찾아
			GameEngineImage* Image0 = GameEngineImageManager::GetInst()->Find("walk-R.bmp");
			//그리구 이미지를 한프레임 단위로 잘라줘
			Image0->CutCount( 3, 1 );//Walk-L이미지를 가로3 세로1로 짤라라

			GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("walk-L.bmp");
			
			Image1->CutCount(3, 1);

			GameEngineImage* Image3 = GameEngineImageManager::GetInst()->Find("idle-L.bmp");
			
			Image3->Cut({ 64, 64 });

			GameEngineImage* Image4 = GameEngineImageManager::GetInst()->Find("idle-R.bmp");

			Image4->Cut({ 64, 64 });

			GameEngineImage* Image5 = GameEngineImageManager::GetInst()->Find("gumba-walk.bmp");

			Image5->CutCount(2, 1);

			//총알도 찾아
			GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("Bullet.bmp");
			//그리구 이미지를 한프레임 단위로 잘라줘
			Image2->Cut({ 32, 32 });
			//총알 터짐
			GameEngineImage* Image6 = GameEngineImageManager::GetInst()->Find("Hit.bmp");

			Image6->Cut({ 32, 32 });

			GameEngineImage* Image7 = GameEngineImageManager::GetInst()->Find("jump-R.bmp");

			Image7->Cut({ 64, 64 });

			GameEngineImage* Image8 = GameEngineImageManager::GetInst()->Find("jump-L.bmp");

			Image8->Cut({ 64, 64 });

		}
	}
	if (false == GameEngineInput::GetInst()->IsKey("Play1"))
	{	//false면 만들어진 적 없는 키 이다
		GameEngineInput::GetInst()->CreateKey("Title", VK_RETURN);
		GameEngineInput::GetInst()->CreateKey("Intro", VK_RETURN);
		GameEngineInput::GetInst()->CreateKey("Play1", '1');
		GameEngineInput::GetInst()->CreateKey("Pipe1", 'F');
		GameEngineInput::GetInst()->CreateKey("Play2", '2');
		GameEngineInput::GetInst()->CreateKey("Play3", '3');
		GameEngineInput::GetInst()->CreateKey("Debug", 'R');
	}


	////이미지를 찾아
	//GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("walk-L.bmp");
	////그리구 이미지를 한프레임 단위로 잘라줘
	//Image->Cut({ 64, 64 });


	//GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("Bullet.bmp");
	////그리구 이미지를 한프레임 단위로 잘라줘
	//Image2->Cut({ 32, 32 });
	

	CreateLevel<TitleLevel>("Title");
	CreateLevel<IntroLevel>("Intro");
	CreateLevel<PlayLevel>("Play1");
	CreateLevel<BonusLevel>("Pipe1");
	CreateLevel<PlayLevel2>("Play2");
	CreateLevel<PlayLevel3>("Play3");
	CreateLevel<EndingLevel>("Ending");
	//ChangeLevel("Play1");//인게임 화면 보고싶을때 체크용
	ChangeLevel("Title");//플레이를 킬거면 이건 꺼야지!
}

void SuperMario::GameLoop()
{
}

void SuperMario::GameEnd()
{
}
