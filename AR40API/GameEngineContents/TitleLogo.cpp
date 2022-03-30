#include "TitleLogo.h"
#include <Windows.h>
#include <GameEngineBase/GameEngineWindow.h>


TitleLogo::TitleLogo()
{

}

TitleLogo::~TitleLogo()
{

}

void TitleLogo::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());//타이틀 로고 위치

	SetScale({ 500, 500 });//타이틀 로고 크기
}

void TitleLogo::Render()
{
	//DebugRectRender();
}