#include "GameEngineRenderer.h"
#include "GameEngineImageManager.h"
#include "GameEngine.h"
#include <GameEngineBase/GameEngineDebug.h>

GameEngineRenderer::GameEngineRenderer()
	:Image_(nullptr)
	,PivotType(RenderPivot::CENTER)
{

}

GameEngineRenderer::~GameEngineRenderer()
{

}

void GameEngineRenderer::SetImage(const std::string& _Name)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("idle-R.bmp");
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name + "존재하지 않는 이미지를 랜더러에 세팅함");
		return;
	}

	Image_ = FindImage;
}

void GameEngineRenderer::Render()
{
	//이미지가 없으면 랜더링을 못하게끔 한다
	if (nullptr == Image_)
	{
		MsgBoxAssert("랜더러에 이미지가 세팅되어 있지 않으면 랜더링이 안됨");
		return;
	}

	float4 RenderPos = GetActor()->GetPosition() + RenderPivot_;

	switch (PivotType)
	{
	case RenderPivot::CENTER:
		GameEngine::BackBufferImage()->BitCopyCenter(Image_, RenderPos);
		break;
	case RenderPivot::BOT:
		GameEngine::BackBufferImage()->BitCopyBot(Image_, RenderPos);
		break;
	default:
		break;
	}

}