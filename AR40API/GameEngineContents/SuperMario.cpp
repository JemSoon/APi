#include "SuperMario.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngine/GameEngineImageManager.h>

SuperMario::SuperMario()
{

}

SuperMario::~SuperMario()
{

}

void SuperMario::GameInit()
{
	//창에 띄울 이미지 영역 사이즈
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });

	GameEngineDirectory ResourcesDir;//생성과 동시에 현재 디렉토리

	ResourcesDir.MoveParent("AR40API");//어디까지 상위 폴더로 올라가느냐


	//디렉토리 덕분에 일일히 적을 필요 없다
	/*GameEngineImageManager::GetInst()->Load("C:\\Users\\highy\\Desktop\\C++\\AR40API\\AllResources\\Texture\\idle-R.bmp","idle-R.bmp");
	GameEngineImageManager::GetInst()->Load("C:\\Users\\highy\\Desktop\\C++\\AR40API\\AllResources\\Texture\\turtle-back.bmp", "turtle-back.bmp");
	GameEngineImageManager::GetInst()->Load("C:\\Users\\highy\\Desktop\\C++\\AR40API\\AllResources\\Texture\\GameTitle.bmp", "GameTitle.bmp");*/


	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Play");//인게임 화면 보고싶을때 체크용
	//ChangeLevel("Title");//플레이를 킬거면 이건 꺼야지!
}

void SuperMario::GameLoop()
{
}

void SuperMario::GameEnd()
{
}
