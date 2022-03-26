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
	//1280 X 720�̹���(GetHDC)ȭ�鿡 100�� 100 ��ǥ���� ����+100���� �������� ���

	//�������� �⺻������ �߾��� �������� �ϴ°� ������
	//Rectangle(
	//			GameEngineWindow::GetHDC(), 
	//			DebugRect.CenterLeft(), 
	//			DebugRect.CenterTop(),
	//			DebugRect.CenterRight(),
	//			DebugRect.CenterBot()
	//		  );//�ΰ� �׸�
}