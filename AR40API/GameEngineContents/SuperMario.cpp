#include "SuperMario.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>

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

	CreateLevel<PlayLevel>("Play");
	CreateLevel<TitleLevel>("Title");
	CreateLevel<EndingLevel>("Ending");
	ChangeLevel("Title");
}

void SuperMario::GameLoop()
{
}

void SuperMario::GameEnd()
{
}
