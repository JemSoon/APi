#include "BackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

BackGround::BackGround()
{
	// Level_ = nullptr;
}

BackGround::~BackGround()
{
}

void BackGround::Start()
{	//배경을 0,0기준으로 설정
	
	SetScale(GameEngineWindow::GetScale());
	Image_ = CreateRenderer();
}

void BackGround::Render()
{

	//DebugRectRender();
}

