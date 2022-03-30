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