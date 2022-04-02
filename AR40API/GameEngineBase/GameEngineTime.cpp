#include "GameEngineTime.h"
#include <Windows.h>

GameEngineTime* GameEngineTime::Inst_ = new GameEngineTime();

GameEngineTime::GameEngineTime()
{

}

GameEngineTime::~GameEngineTime()
{

}

void GameEngineTime::Reset()
{
	LARGE_INTEGER Prev;
	LARGE_INTEGER Current;
	LARGE_INTEGER Count;

	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&PrevCount_));//���²� �� ��
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentCount_));//���� ��
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&SecondCount_));//�ʴ� �������� ����?
	Update();
}

void GameEngineTime::Update()
{
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentCount_));

	RealDeltaTime_ = (static_cast<double>(CurrentCount_) - static_cast<double>(PrevCount_)) / static_cast<double>(SecondCount_);//�̰� ��� ���� �ð�(��ŸŸ��)
	PrevCount_ = CurrentCount_;

	DeltaTime_ = static_cast<float>(RealDeltaTime_);//������ ¯ ������ �÷�

}
