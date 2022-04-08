#include "GameEngineRenderer.h"
#include "GameEngineImageManager.h"
#include "GameEngine.h"
#include "GameEngineLevel.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>


#pragma comment(lib, "msimg32.lib")
GameEngineRenderer::GameEngineRenderer()
	:Image_(nullptr)
	,PivotType_(RenderPivot::CENTER)
	,ScaleMode_(RenderScaleMode::Image)
	,TransColor_(RGB(255,0,255))
	,RenderImagePivot_({0, 0})
	, IsCameraEffect_(true)
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
	RenderImageScale_ = Image_->GetScale();
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
	SetImageScale();
}

void GameEngineRenderer::Render()
{

	if (nullptr != CurrentAnimation_)
	{
		CurrentAnimation_->Update();
	}

	//이미지가 없으면 랜더링을 못하게끔 한다
	if (nullptr == Image_)
	{
		MsgBoxAssert("랜더러에 이미지가 세팅되어 있지 않으면 랜더링이 안됨");
		return;
	}
	
	float4 RenderPos = GetActor()->GetPosition() + RenderPivot_;

	if (true == IsCameraEffect_)
	{	//플레이어 위치 카메라 위치를 뺀다=0이된다 즉 카메라가 플레이어를 따라간다
		RenderPos -= GetActor()->GetLevel()->GetCameraPos();
	}

	switch (PivotType_)
	{
	case RenderPivot::CENTER:
		GameEngine::BackBufferImage()->TransCopy(Image_, RenderPos - RenderScale_.Half(), RenderScale_, RenderImagePivot_, RenderImageScale_, TransColor_);
		
		break;
	case RenderPivot::BOT:
	{
		float4 Scale = RenderScale_.Half();
		Scale.y *= 2.0f;
		GameEngine::BackBufferImage()->TransCopy(Image_, RenderPos - RenderScale_.Half(), RenderScale_, RenderImagePivot_, RenderImageScale_, TransColor_);

		break;
	}
	default:
		break;
	}

}

void GameEngineRenderer::SetIndex(size_t _Index, const float4& _Scale /*= {-1, -1}*/)//기본적으로 이미지 스케일 설정-1(-1이면 기본사이즈)
{
	if (false == Image_->IsCut())
	{
		MsgBoxAssert("이미지를 부분적으로 사용할 수 있게 잘려진 이미지가 아닙니다");
		return;
	}

	if (_Scale.x <= 0 || _Scale.y <= 0)
	{
		RenderScale_ = Image_->GetCutScale(_Index);
	}
	else
	{
		RenderScale_ = _Scale;
	}
	RenderImagePivot_ = Image_->GetCutPivot(_Index);
	RenderImageScale_ = Image_->GetCutScale(_Index);
}


//=================애니메이션↓=====================

void GameEngineRenderer::ChangeAnimation(const std::string& _Name)
{
	std::map<std::string, FrameAnimation>::iterator FindIter = Animations_.find(_Name);

	if (Animations_.end() == FindIter)
	{
		MsgBoxAssert("존재하지 않는 애니메이션으로 체인지 하려고 했습니다");
		return;
	}

	CurrentAnimation_ = &FindIter->second;
}


void GameEngineRenderer::CreateAnimation(
	const std::string& _Image, 
	const std::string& _Name, 
	int _StartIndex, 
	int _EndIndex, 
	float _InterTime, 
	bool _Loop /*= true*/)
{
	GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find(_Image);

	if (nullptr == FindImage)
	{
		MsgBoxAssert("존재하지 않는 이미지로 애니메이션을 만들려고 했습니다");
		return;
	}

	if (Animations_.end() != Animations_.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 애니메이션을 또 만들려고 했습니다");
		return;
	}

	FrameAnimation& NewAnimation = Animations_[_Name];

	NewAnimation.Renderer_ = this;
	NewAnimation.Image_ = FindImage;
	NewAnimation.CurrentFrame_ = _StartIndex;
	NewAnimation.StartFrame_ = _StartIndex;
	NewAnimation.EndFrame_ = _EndIndex;
	NewAnimation.CurrentInterTime_ = _InterTime;
	NewAnimation.InterTime_ = _InterTime;
	NewAnimation.Loop_ = _Loop;
}

void GameEngineRenderer::FrameAnimation::Update()
{
	CurrentInterTime_ -= GameEngineTime::GetInst()->GetDeltaTime();

	if (0 >= CurrentInterTime_)
	{
		CurrentInterTime_ = InterTime_;
		++CurrentFrame_;

		if (EndFrame_ < CurrentFrame_)
		{
			if (true == Loop_)
			{
				CurrentFrame_ = StartFrame_;
			}

			else
			{
				CurrentFrame_ = EndFrame_;
			}
		}

	}
		Renderer_->Image_ = Image_;//이미지 세팅

		Renderer_->SetIndex(CurrentFrame_);//이미지의 인덱스 셋팅
}