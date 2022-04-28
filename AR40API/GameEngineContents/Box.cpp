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
	BoxAnimationRender = CreateRenderer();
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

void Box::FootCheck()
{
}

void Box::PlayerCheck()
{	
	//문제
	//애니메이션 변경뿐만아니라 인식후 아이템이 올라와야하고(움직여야하고)
	//박스에 아이템을 어떻게 담을 것인가?
	//플레이어는 부딪힌 즉시 관통이 아니라 떨어져야한다
	std::vector<GameEngineCollision*> ColList;
	if (true == BoxCollision->CollisionResult("PlayerHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		EmptyBox* EBox = GetLevel()->CreateActor<EmptyBox>();
		EBox->SetPosition(GetPosition());
		Mushroom* Ptr = GetLevel()->CreateActor<Mushroom>();
		Ptr->SetPosition(GetPosition() + float4{0,-64});//원래는 움직여서 -64만큼 위로 이동해야하지만..일단..
		BoxCollision->GetActor()->Off();
	}

	else if (true == BoxCollision->CollisionResult("BigPlayerHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		EmptyBox* EBox = GetLevel()->CreateActor<EmptyBox>();
		EBox->SetPosition(GetPosition());
		FireFlower* Ptr = GetLevel()->CreateActor<FireFlower>();
		Ptr->SetPosition(GetPosition() + float4{ 0,-64 });
		BoxCollision->GetActor()->Off();
	}

	else if (true == BoxCollision->CollisionResult("WhitePlayerHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		EmptyBox* EBox = GetLevel()->CreateActor<EmptyBox>();
		EBox->SetPosition(GetPosition());
		FireFlower* Ptr = GetLevel()->CreateActor<FireFlower>();
		Ptr->SetPosition(GetPosition() + float4{ 0,-64 });
		BoxCollision->GetActor()->Off();
	}
}