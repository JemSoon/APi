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
		MsgBoxAssert("�������� �ʴ� �̹����� ũ�� �����Ϸ� ��")
	}
	ScaleMode_ = RenderScaleMode::Image;
	RenderScale_ = Image_->GetScale();
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

	switch (PivotType_)
	{
	case RenderPivot::CENTER:
		GameEngine::BackBufferImage()->TransCopyCenter(Image_, RenderPos, TransColor_);
		//�̰� ���� ������ �����ȵ�
		//GameEngine::BackBufferImage()->TransCopyCenterScale(Image_, RenderPos, RenderScale_, TransColor_);
		//�̰ž��� CreateRenderer�� �ƴ϶�(�̰ž��� �Ϲ�ũ��� ����) CreateRendererToScale�Լ� ��� ����� ����
		break;
	case RenderPivot::BOT:
		//�� ���ؼ��� ���� ������ �ȸ���(������ �Ⱦ���) ���� ����
		GameEngine::BackBufferImage()->TransCopyCenter(Image_, RenderPos, TransColor_);
		
		break;
	default:
		break;
	}

}