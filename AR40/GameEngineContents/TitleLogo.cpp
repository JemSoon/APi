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
	SetPosition(GameEngineWindow::GetScale().Half());//Ÿ��Ʋ �ΰ� ��ġ

	SetScale({ 500, 500 });//Ÿ��Ʋ �ΰ� ũ��
}

void TitleLogo::Render()
{
	//DebugRectRender();
}