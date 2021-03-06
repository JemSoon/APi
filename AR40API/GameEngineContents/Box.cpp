#include "Box.h"
#include "EmptyBox.h"
#include "Mushroom.h"
#include "FireFlower.h"

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>

Box::Box()
{

}

Box::~Box()
{

}

void Box::Start()
{
	SetScale({ 64,64 });

	BoxCollision = CreateCollision("Box", { 64, 64 });
	BoxBotCollision = CreateCollision("BoxBot", { 64, 2 },{0,33});
	BoxTopCollision = CreateCollision("BoxTop", { 64, 2 }, { 0,-32 });
	BoxLeftCollision = CreateCollision("BoxLeft", { 1, 64 }, { -32 , 0 });
	BoxRightCollision = CreateCollision("BoxRight", { 1, 64 }, { 32 , 0 });

	BoxAnimationRender = CreateRenderer((int)ORDER::BOX);
	BoxAnimationRender->CreateAnimation("QBox.bmp", "Box", 0, 3, 0.3f, true);
	BoxAnimationRender->ChangeAnimation("Box");
	
}

void Box::Render()
{
}

void Box::Update()
{
	PlayerCheck();
}

void Box::PlayerCheck()
{	
	//문제
	//애니메이션 변경뿐만아니라 인식후 아이템이 올라와야하고(움직여야하고)
	//박스에 아이템을 어떻게 담을 것인가?
	//플레이어는 부딪힌 즉시 관통이 아니라 떨어져야한다
	std::vector<GameEngineCollision*> ColList;

	if (true == BoxBotCollision->CollisionResult("PlayerHeadHit", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineSound::SoundPlayOneShot("smb_powerup_appears.wav");
		EmptyBox* EBox = GetLevel()->CreateActor<EmptyBox>();
		EBox->SetPosition(GetPosition());
		Mushroom* Ptr = GetLevel()->CreateActor<Mushroom>();
		Ptr->SetPosition(GetPosition());
		BoxCollision->GetActor()->Off();
	}

	else if (true == BoxBotCollision->CollisionResult("BigPlayerHeadHit", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineSound::SoundPlayOneShot("smb_powerup_appears.wav");
		EmptyBox* EBox = GetLevel()->CreateActor<EmptyBox>();
		EBox->SetPosition(GetPosition());
		FireFlower* Ptr = GetLevel()->CreateActor<FireFlower>();
		Ptr->SetPosition(GetPosition() + float4{ 0,-64 });
		BoxCollision->GetActor()->Off();
	}

	else if (true == BoxBotCollision->CollisionResult("WhitePlayerHeadHit", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineSound::SoundPlayOneShot("smb_powerup_appears.wav");
		EmptyBox* EBox = GetLevel()->CreateActor<EmptyBox>();
		EBox->SetPosition(GetPosition());
		FireFlower* Ptr = GetLevel()->CreateActor<FireFlower>();
		Ptr->SetPosition(GetPosition() + float4{ 0,-64 });
		BoxCollision->GetActor()->Off();
	}
}