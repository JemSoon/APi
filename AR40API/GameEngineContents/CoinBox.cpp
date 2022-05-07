#include "CoinBox.h"
#include "BCoin.h"
#include "EmptyBox.h"
#include "UI.h"

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>

CoinBox::CoinBox():
	HP(1),
	HitFlg(false)
{

}

CoinBox::~CoinBox()
{

}

void CoinBox::Start()
{
	SetScale({ 64,64 });

	BoxCollision = CreateCollision("Box", { 64, 64 });
	BoxBotCollision = CreateCollision("BoxBot", { 64, 2 }, { 0,33 });
	BoxTopCollision = CreateCollision("BoxTop", { 64, 2 }, { 0,-32 });
	BoxLeftCollision = CreateCollision("BoxLeft", { 1, 64 }, { -32 , 0 });
	BoxRightCollision = CreateCollision("BoxRight", { 1, 64 }, { 32 , 0 });

	BoxAnimationRender = CreateRenderer((int)ORDER::BOX);
	BoxAnimationRender->CreateAnimation("QBox.bmp", "Box", 0, 3, 0.3f, true);
	BoxAnimationRender->ChangeAnimation("Box");

}

void CoinBox::Render()
{
}

void CoinBox::Update()
{
	PlayerCheck();
}

void CoinBox::PlayerCheck()
{
	std::vector<GameEngineCollision*> ColList;
	{
		if (true == BoxBotCollision->CollisionResult("PlayerHeadHit", ColList, CollisionType::Rect, CollisionType::Rect) &&
			false == HitFlg)
		{
			HitFlg = true;
			HP -= 1;
			GameEngineSound::SoundPlayOneShot("smb_coin.wav");
			BCoin* Ptr = GetLevel()->CreateActor<BCoin>();
			Ptr->SetPosition(GetPosition() + float4{ 0,-64 });
			UI::CoinCount_ += 1;
			if (HP == 0)
			{
				BoxCollision->GetActor()->Off();
				EmptyBox* EBox = GetLevel()->CreateActor<EmptyBox>();
				EBox->SetPosition(GetPosition());
			}

		}

		else if (false == BoxBotCollision->CollisionResult("PlayerHeadHit", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			HitFlg = false;
		}
	}


	if (true == BoxBotCollision->CollisionResult("BigPlayerHeadHit", ColList, CollisionType::Rect, CollisionType::Rect) &&
		false == HitFlg)
	{
		HitFlg = true;
		HP -= 1;
		GameEngineSound::SoundPlayOneShot("smb_coin.wav");
		BCoin* Ptr = GetLevel()->CreateActor<BCoin>();
		Ptr->SetPosition(GetPosition() + float4{ 0,-64 });
		UI::CoinCount_ += 1;
		if (HP == 0)
		{
			BoxCollision->GetActor()->Off();
			EmptyBox* EBox = GetLevel()->CreateActor<EmptyBox>();
			EBox->SetPosition(GetPosition());
		}
	}


	if (true == BoxBotCollision->CollisionResult("WhitePlayerHeadHit", ColList, CollisionType::Rect, CollisionType::Rect)&&
		false == HitFlg)
	{
		GameEngineSound::SoundPlayOneShot("smb_coin.wav");
		EmptyBox* EBox = GetLevel()->CreateActor<EmptyBox>();
		EBox->SetPosition(GetPosition());
		BCoin* Ptr = GetLevel()->CreateActor<BCoin>();
		Ptr->SetPosition(GetPosition() + float4{ 0,-64 });
		BoxCollision->GetActor()->Off();
		UI::CoinCount_ += 1;
	}
	
}
