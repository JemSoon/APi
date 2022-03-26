#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineWindow.h>

GameEngineActor::GameEngineActor()
	: Level_(nullptr)
{

}

GameEngineActor::~GameEngineActor()
{

}

void GameEngineActor::DebugRectRender()
{

	GameEngineRect DebugRect(Position_, Scale_);

	for (size_t i = 0; i < 100; i++)
	{
	SetPixel(GameEngineWindow::GetHDC(), 100, 100, RGB(255, 0, 0));
	}
	//1280 X 720이미지(GetHDC)화면에 100에 100 좌표부터 가로+100까지 빨간색을 찍어

	//선생님은 기본적으로 중앙을 기준으로 하는걸 조아함
	//Rectangle(
	//			GameEngineWindow::GetHDC(), 
	//			DebugRect.CenterLeft(), 
	//			DebugRect.CenterTop(),
	//			DebugRect.CenterRight(),
	//			DebugRect.CenterBot()
	//		  );//로고 네모
}