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
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());
	Image_ = CreateRenderer();
}

void BackGround::Render()
{

	//DebugRectRender();
}

