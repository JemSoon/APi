#include "GameEngineActor.h"
#include "GameEngine/GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

GameEngineActor::GameEngineActor()
	: Level_(nullptr)
{

}

GameEngineActor::~GameEngineActor()
{
	std::list<GameEngineRenderer*>::iterator StartIter = RenderList_.begin();
	std::list<GameEngineRenderer*>::iterator EndIter = RenderList_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		delete (*StartIter);
		(*StartIter) = nullptr;
	}

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
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetActor(this);
	NewRenderer->SetImage(_Image);
	NewRenderer->SetPivot(_PivotPos);
	NewRenderer->SetType(_PivotType);

	RenderList_.push_back(NewRenderer);

	return NewRenderer;
}


void GameEngineActor::Renderering()
{
	StartRenderIter = RenderList_.begin();
	EndRenderIter = RenderList_.end();

	for (; StartRenderIter != EndRenderIter; ++StartRenderIter)
	{
		(*StartRenderIter)->Render();
	}
}