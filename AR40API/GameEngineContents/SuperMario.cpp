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

			GameEngineImage* Image9 = GameEngineImageManager::GetInst()->Find("break-L.bmp");

			Image9->Cut({ 64, 64 });

			GameEngineImage* Image10 = GameEngineImageManager::GetInst()->Find("break-R.bmp");

			Image10->Cut({ 64, 64 });

			GameEngineImage* Image11 = GameEngineImageManager::GetInst()->Find("QBox.bmp");

			Image11->CutCount(4, 1);

			GameEngineImage* Image12 = GameEngineImageManager::GetInst()->Find("Mushroom.bmp");

			Image12->Cut({ 64, 64 });

			GameEngineImage* Image13 = GameEngineImageManager::GetInst()->Find("big-walk-R.bmp");

			Image13->CutCount(3, 1);

			GameEngineImage* Image14 = GameEngineImageManager::GetInst()->Find("big-walk-L.bmp");

			Image14->CutCount(3, 1);

			GameEngineImage* Image15 = GameEngineImageManager::GetInst()->Find("big-idle-R.bmp");

			Image15->Cut({ 64, 128 });

			GameEngineImage* Image16 = GameEngineImageManager::GetInst()->Find("big-idle-L.bmp");

			Image16->Cut({ 64, 128 });

			GameEngineImage* Image17 = GameEngineImageManager::GetInst()->Find("big-jump-L.bmp");

			Image17->Cut({ 64, 128 });

			GameEngineImage* Image18 = GameEngineImageManager::GetInst()->Find("big-jump-R.bmp");

			Image18->Cut({ 64, 128 });

			GameEngineImage* Image19 = GameEngineImageManager::GetInst()->Find("FireFlower.bmp");

			Image19->CutCount(4, 1);


			GameEngineImage* Image20 = GameEngineImageManager::GetInst()->Find("big-break-R.bmp");

			Image20->Cut({ 64, 128 });

			GameEngineImage* Image21 = GameEngineImageManager::GetInst()->Find("big-break-L.bmp");

			Image21->Cut({ 64, 128 });

			GameEngineImage* Image22 = GameEngineImageManager::GetInst()->Find("fire-walk-R.bmp");

			Image22->CutCount(3, 1);

			GameEngineImage* Image23 = GameEngineImageManager::GetInst()->Find("fire-walk-L.bmp");

			Image23->CutCount(3, 1);

			GameEngineImage* Image24 = GameEngineImageManager::GetInst()->Find("fire-idle-R.bmp");

			Image24->Cut({ 64, 128 });

			GameEngineImage* Image25 = GameEngineImageManager::GetInst()->Find("fire-idle-L.bmp");

			Image25->Cut({ 64, 128 });

			GameEngineImage* Image26 = GameEngineImageManager::GetInst()->Find("fire-jump-L.bmp");

			Image26->Cut({ 64, 128 });

			GameEngineImage* Image27 = GameEngineImageManager::GetInst()->Find("fire-jump-R.bmp");

			Image27->Cut({ 64, 128 });

			GameEngineImage* Image28 = GameEngineImageManager::GetInst()->Find("fire-break-R.bmp");

			Image28->Cut({ 64, 128 });

			GameEngineImage* Image29 = GameEngineImageManager::GetInst()->Find("fire-break-L.bmp");

			Image29->Cut({ 64, 128 });

			GameEngineImage* Image30 = GameEngineImageManager::GetInst()->Find("FireAttack-L.bmp");

			Image30->Cut({ 64, 128 });

			GameEngineImage* Image31 = GameEngineImageManager::GetInst()->Find("FireAttack-R.bmp");

			Image31->Cut({ 64, 128 });

			GameEngineImage* Image32 = GameEngineImageManager::GetInst()->Find("FireAttack-R.bmp");

			Image32->Cut({ 64, 64 });

			GameEngineImage* Image33 = GameEngineImageManager::GetInst()->Find("empty-Box.bmp");

			Image33->Cut({ 64, 64 });

			GameEngineImage* Image34 = GameEngineImageManager::GetInst()->Find("Hit.bmp");

			Image34->Cut({ 32, 32 });

			GameEngineImage* Image35 = GameEngineImageManager::GetInst()->Find("gumba-Bdead.bmp");

			Image35->Cut({ 64, 64 });

			GameEngineImage* Image36 = GameEngineImageManager::GetInst()->Find("Block.bmp");

			Image36->Cut({ 64, 64 });

			GameEngineImage* Image37 = GameEngineImageManager::GetInst()->Find("big-down-R.bmp");

			Image37->Cut({ 64, 88 });

			GameEngineImage* Image38 = GameEngineImageManager::GetInst()->Find("big-down-L.bmp");

			Image38->Cut({ 64, 88 });
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
	ChangeLevel("Play1");//인게임 화면 보고싶을때 체크용
	//ChangeLevel("Title");//플레이를 킬거면 이건 꺼야지!
}

void SuperMario::GameLoop()
{
}

void SuperMario::GameEnd()
{
}
