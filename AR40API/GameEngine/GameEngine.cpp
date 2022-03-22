#include "GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngineLevel.h"

std::map<std::string, GameEngineLevel*> GameEngine::AllLevel_;
GameEngineLevel* GameEngine::CurrentLevel_=nullptr;
GameEngineLevel* GameEngine::NextLevel_ = nullptr;
GameEngine* GameEngine::UserContents_ = nullptr;

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
	UserContents_->GameInit();
}

void GameEngine::EngineLoop()
{
	//엔진 수준에서 매 프레임마다 체크하고 싶은거
	UserContents_->GameLoop();

	if (nullptr!= NextLevel_)
	{
		CurrentLevel_ = NextLevel_;
		NextLevel_ = nullptr;
	}

	if (nullptr == CurrentLevel_)
	{
		MsgBoxAssert("Level is nullptr GameEngine Loop Error");
	}

	//레벨수준 시간제한이 있는 게임이라면
	//매 프레임마다 시간을 체크해야하는데 그런일을 하라고 만든것
	CurrentLevel_->Update();
}

void GameEngine::EngineEnd()
{
	UserContents_->GameEnd();

	std::map<std::string, GameEngineLevel*>::iterator StartIter= AllLevel_.begin();
	std::map<std::string, GameEngineLevel*>::iterator EndIter= AllLevel_.begin();
	AllLevel_.end();

	for (; StartIter!=EndIter;++StartIter)
	{
		if (nullptr == StartIter->second)
		{
			continue;
		}
		delete StartIter->second;
	}
	GameEngineWindow::Destroy();
}

void GameEngine::ChangeLevel(const std::string& _Name)
{
	static std::map<std::string, GameEngineLevel*>::iterator FindIter = AllLevel_.find(_Name);

	if (AllLevel_.end() == FindIter)
	{
		MsgBoxAssert("Level Find Error");
		return;
	}

	NextLevel_ = FindIter->second;
}