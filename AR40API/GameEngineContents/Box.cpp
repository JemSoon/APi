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
	BoxBotCollision = CreateCollision("BoxBot", { 64, 1 },{0,32});
	BoxTopCollision = CreateCollision("BoxTop", { 64, 1 }, { 0,-32 });
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

void Box::FootCheck()
{
}

void Box::PlayerCheck()
{	
	//����
	//�ִϸ��̼� ����Ӹ��ƴ϶� �ν��� �������� �ö�;��ϰ�(���������ϰ�)
	//�ڽ��� �������� ��� ���� ���ΰ�?
	//�÷��̾�� �ε��� ��� ������ �ƴ϶� ���������Ѵ�
	std::vector<GameEngineCollision*> ColList;
	//if (true == BoxCollision->CollisionResult("PlayerHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	//{
	//	EmptyBox* EBox = GetLevel()->CreateActor<EmptyBox>();
	//	EBox->SetPosition(GetPosition());
	//	Mushroom* Ptr = GetLevel()->CreateActor<Mushroom>();
	//	Ptr->SetPosition(GetPosition() + float4{0,-64});//������ �������� -64��ŭ ���� �̵��ؾ�������..�ϴ�..
	//	BoxCollision->GetActor()->Off();
	//}
	if (true == BoxBotCollision->CollisionResult("PlayerHead", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		EmptyBox* EBox = GetLevel()->CreateActor<EmptyBox>();
		EBox->SetPosition(GetPosition());
		Mushroom* Ptr = GetLevel()->CreateActor<Mushroom>();
		Ptr->SetPosition(GetPosition() /*+ float4{ 0,-16 }*/);//������ �������� -64��ŭ ���� �̵��ؾ�������..�ϴ�..
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