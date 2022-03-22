#include "GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngineLevel.h"

std::map<std::string, GameEngineLevel*> GameEngine::AllLevel_;
GameEngine* GameEngine::UserContents_;

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
	GameEngineWindow::GetInst().CreateGameWindow(nullptr, "GameWindow");//�̰� ���� �����
	GameEngineWindow::GetInst().ShowGameWindow();//�̰ɷ� ����
	//���� â�� �Ѱ��� �ѹ��� �����(���� �Ҽ� ����)
	GameEngineWindow::GetInst().MessageLoop(EngineInit, EngineLoop);
}

void GameEngine::EngineInit()
{
	UserContents_->GameInit();
}

void GameEngine::EngineLoop()
{
	UserContents_->GameLoop();
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