#include "GameEngineActor.h"
#include "GameEngine/GameEngine.h"
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

	//선생님은 기본적으로 중앙을 기준으로 하는걸 조아함
	Rectangle(
				GameEngine::BackBufferDC(), 
				DebugRect.CenterLeft(), 
				DebugRect.CenterTop(),
				DebugRect.CenterRight(),
				DebugRect.CenterBot()
			  );//로고 네모
}

GameEngineRenderer* GameEngineActor::CreateRenderer(
	const std::string& _Image, 
	RenderPivot _PivotType /*= RenderPivot::CENTER*/, 
	const float4& _PivotPos /*= { 0, 0 }*/)
{
	return;
}