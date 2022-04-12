#include "GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngineLevel.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

std::map<std::string, GameEngineLevel*> GameEngine::AllLevel_;
GameEngineLevel* GameEngine::CurrentLevel_ = nullptr;
GameEngineLevel* GameEngine::NextLevel_ = nullptr;
GameEngine* GameEngine::UserContents_ = nullptr;

GameEngineImage* GameEngine::BackBufferImage_ = nullptr;//백버퍼
GameEngineImage* GameEngine::WindowMainImage_ = nullptr;//진짜 그려지는 이미지

HDC GameEngine::BackBufferDC()
{
	return BackBufferImage_->ImageDC();
}

GameEngine::GameEngine()
{

}

GameEngine::~GameEngine()
{

}

void GameEngine::GameInit()
{

}
void GameEngine::GameLoop()
{

}
void GameEngine::GameEnd()
{

}

void GameEngine::WindowCreate()
{
	GameEngineWindow::GetInst().CreateGameWindow(nullptr, "GameWindow");//이걸 통해 만들고
	GameEngineWindow::GetInst().ShowGameWindow();//이걸로 띄운다
	//게임 창은 한개니 한번만 띄워용(설명 할수 있자)

	GameEngineWindow::GetInst().MessageLoop(EngineInit, EngineLoop);
}

void GameEngine::EngineInit()
{
	//여기서 윈도우의 크기가 결정될 것이므로
	UserContents_->GameInit();
	//여기서 백버퍼를 만들어 받아낸다
	WindowMainImage_ = GameEngineImageManager::GetInst()->Create("WindowMain", GameEngineWindow::GetHDC());
	BackBufferImage_ = GameEngineImageManager::GetInst()->Create("BackBuffer", GameEngineWindow::GetScale());
}

void GameEngine::EngineLoop()
{
	GameEngineTime::GetInst()->Update();
	//엔진 수준에서 매 프레임마다 체크하고 싶은거
	UserContents_->GameLoop();

	//시점 함수 라고 하는데 레벨이 바뀌는 순간의 가상함수를 만듦

	if (nullptr != NextLevel_)
	{
		if (nullptr != CurrentLevel_)
		{
			CurrentLevel_->LevelChangeEnd();
		}

		CurrentLevel_ = NextLevel_;

		if (nullptr != CurrentLevel_)
		{
			CurrentLevel_->LevelChangeStart();
		}
		NextLevel_ = nullptr;
		GameEngineTime::GetInst()->Reset();//리셋 다 끝나고 나서 시간을 잰다

		//넘어갈때 화면청소
		Rectangle(WindowMainImage_->ImageDC(), 0, 0, WindowMainImage_->GetScale().ix(), WindowMainImage_->GetScale().iy());
		Rectangle(BackBufferImage_->ImageDC(), 0, 0, BackBufferImage_->GetScale().ix(), BackBufferImage_->GetScale().iy());

	}

	if (nullptr == CurrentLevel_)
	{
		MsgBoxAssert("Level is nullptr GameEngine Loop Error");
	}

	GameEngineInput::GetInst()->Update(GameEngineTime::GetInst()->GetDeltaTime());

	//레벨수준 시간제한이 있는 게임이라면
	//매 프레임마다 시간을 체크해야하는데 그런일을 하라고 만든것
	CurrentLevel_->Update();
	CurrentLevel_->ActorUpdate();
	CurrentLevel_->ActorRender();
	CurrentLevel_->CollisionDebugRender();
	WindowMainImage_->BitCopy(BackBufferImage_);
	CurrentLevel_->ActorRelease();
}

void GameEngine::EngineEnd()
{
	UserContents_->GameEnd();

	std::map<std::string, GameEngineLevel*>::iterator StartIter = AllLevel_.begin();
	std::map<std::string, GameEngineLevel*>::iterator EndIter = AllLevel_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr == StartIter->second)
		{
			continue;
		}
		delete StartIter->second;
	}

	GameEngineImageManager::Destroy();
	GameEngineWindow::Destroy();
	GameEngineInput::Destroy();
	GameEngineTime::Destroy();
}

void GameEngine::ChangeLevel(const std::string& _Name)
{
	std::map<std::string, GameEngineLevel*>::iterator FindIter = AllLevel_.find(_Name);

	if (AllLevel_.end() == FindIter)
	{
		MsgBoxAssert("Level Find Error");
		return;
	}

	NextLevel_ = FindIter->second;
}