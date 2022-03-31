#include "GameEngineRenderer.h"
#include "GameEngineImageManager.h"
#include "GameEngine.h"
#include <GameEngineBase/GameEngineDebug.h>


#pragma comment(lib, "msimg32.lib")
GameEngineRenderer::GameEngineRenderer()
	:Image_(nullptr)
	,PivotType_(RenderPivot::CENTER)
	,ScaleMode_(RenderScaleMode::Image)
	,TransColor_(RGB(255,0,255))
{

}

GameEngineRenderer::~GameEngineRenderer()
{

}

void GameEngineRenderer::SetImageScale()
{
	if (nullptr == Image_)
	{
		MsgBoxAssert("존재하지 않는 이미지로 크기 조절하려 함")
	}
	ScaleMode_ = RenderScaleMode::Image;
	RenderScale_ = Image_->GetScale();
}

void GameEngineRenderer::SetImage(const std::string& _Name)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find(_Name);
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

	switch (PivotType_)
	{
	case RenderPivot::CENTER:
		GameEngine::BackBufferImage()->TransCopyCenter(Image_, RenderPos, TransColor_);
		//이거 쓰면 스케일 조절안됨
		//GameEngine::BackBufferImage()->TransCopyCenterScale(Image_, RenderPos, RenderScale_, TransColor_);
		//이거쓰면 CreateRenderer이 아니라(이거쓰면 일반크기로 나옴) CreateRendererToScale함수 써야 제대로 나옴
		break;
	case RenderPivot::BOT:
		//봇 기준선은 따로 스케일 안만듦(어차피 안쓸듯) 포샵 만세
		GameEngine::BackBufferImage()->TransCopyCenter(Image_, RenderPos, TransColor_);
		
		break;
	default:
		break;
	}

}