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

}

void TitleLogo::Render()
{
	Rectangle(GameEngineWindow::GETDC(), 100, 100, 500, 500);//로고 네모
}