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

void GameEngineRenderer::SetImage(const std::string& _Name)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find(_Name);
	if (nullptr == FindImage)
	{
		MsgBoxAssertString(_Name + "�������� �ʴ� �̹����� �������� ������");
		return;
	}

	Image_ = FindImage;
}

void GameEngineRenderer::Render()
{
	//�̹����� ������ �������� ���ϰԲ� �Ѵ�
	if (nullptr == Image_)
	{
		MsgBoxAssert("�������� �̹����� ���õǾ� ���� ������ �������� �ȵ�");
		return;
	}

	float4 RenderPos = GetActor()->GetPosition() + RenderPivot_;
	float4 RenderScale = RenderScale_;

	switch (ScaleMode_)
	{
	case RenderScaleMode::Image:
		RenderScale = Image_->GetScale();
		break;
	case RenderScaleMode::User:
		break;
	default:
		break;
	}


	switch (PivotType_)
	{
	case RenderPivot::CENTER:
		//GameEngine::BackBufferImage()->TransCopyCenter(Image_, RenderPos, TransColor_);
		GameEngine::BackBufferImage()->TransCopyCenterScale(Image_, RenderPos, RenderScale, TransColor_);
		break;
	case RenderPivot::BOT:
		//�� ���ؼ��� ���� ������ �ȸ���(������ �Ⱦ���) ���� ����
		GameEngine::BackBufferImage()->TransCopyCenter(Image_, RenderPos, TransColor_);
		
		break;
	default:
		break;
	}

}