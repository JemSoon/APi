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

	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&PrevCount_));//여태껏 센 수
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentCount_));//현재 수
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&SecondCount_));//초당 오차범위 정리?
	Update();
}

void GameEngineTime::Update()
{
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentCount_));

	RealDeltaTime_ = (static_cast<double>(CurrentCount_) - static_cast<double>(PrevCount_)) / static_cast<double>(SecondCount_);//이게 평균 공통 시간(델타타임)
	PrevCount_ = CurrentCount_;

	DeltaTime_ = static_cast<float>(RealDeltaTime_);//더블이 짱 느려서 플롯

}
