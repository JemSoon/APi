#include "Intro.h"
#include <GameEngineBase/GameEngineWindow.h>

Intro::Intro()
{

}

Intro::~Intro()
{

}

void Intro::Start()
{
	CreateRenderer("idle-R.bmp");
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale(GameEngineWindow::GetScale());
}

void Intro::Render()
{
	//DebugRectRender();
}