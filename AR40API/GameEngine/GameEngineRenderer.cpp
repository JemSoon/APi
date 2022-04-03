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
	,RenderImagePivot_({0, 0})
{

}

GameEngineRenderer::~GameEngineRenderer()
{

}

void GameEngineRenderer::SetImageScale()
{
	if (nullptr == Image_)
	{
		MsgBoxAssert("�������� �ʴ� �̹����� ũ�� �����Ϸ� ��")
	}
	ScaleMode_ = RenderScaleMode::Image;
	RenderScale_ = Image_->GetScale();
	RenderImageScale_ = Image_->GetScale();
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
	SetImageScale();
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

	switch (PivotType_)
	{
	case RenderPivot::CENTER:
		GameEngine::BackBufferImage()->TransCopy(Image_, RenderPos - RenderScale_.Half(), RenderScale_, RenderImagePivot_, RenderImageScale_, TransColor_);
		//GameEngine::BackBufferImage()->TransCopyCenter(Image_, RenderPos, TransColor_);//����
		//�̰� ���� ������ �����ȵ�
		//GameEngine::BackBufferImage()->TransCopyCenterScale(Image_, RenderPos, RenderScale_, TransColor_);
		//�̰ž��� CreateRenderer�� �ƴ϶�(�̰ž��� �Ϲ�ũ��� ����) CreateRendererToScale�Լ� ��� ����� ����
		break;
	case RenderPivot::BOT:
		//�� ���ؼ��� ���� ������ �ȸ���(������ �Ⱦ���) ���� ����
		//GameEngine::BackBufferImage()->TransCopyCenter(Image_, RenderPos, TransColor_);
		
		break;
	default:
		break;
	}

}

void GameEngineRenderer::SetIndex(size_t _Index)
{
	if (false == Image_->IsCut())
	{
		MsgBoxAssert("�̹����� �κ������� ����� �� �ְ� �߷��� �̹����� �ƴմϴ�");
		return;
	}


	RenderImagePivot_ = Image_->GetCutPivot(_Index);
	RenderScale_ = Image_->GetCutScale(_Index);
	RenderImageScale_ = Image_->GetCutScale(_Index);
}