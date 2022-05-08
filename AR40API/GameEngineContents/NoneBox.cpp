#include "NoneBox.h"
#include "EmptyBox.h"
#include "UPMushroom.h"

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>

NoneBox::NoneBox()
{

}

NoneBox::~NoneBox()
{

}

void NoneBox::Start()
{
	SetScale({ 64,64 });
	
	//투명박스는 쳤을때만 나타난다
	//BoxCollision = CreateCollision("Box", { 64, 64 });
	BoxBotCollision = CreateCollision("BoxBot", { 64, 2 }, { 0,33 });
	//BoxTopCollision = CreateCollision("BoxTop", { 64, 2 }, { 0,-32 });
	//BoxLeftCollision = CreateCollision("BoxLeft", { 1, 64 }, { -32 , 0 });
	//BoxRightCollision = CreateCollision("BoxRight", { 1, 64 }, { 32 , 0 });

	BoxAnimationRender = CreateRenderer((int)ORDER::BOX);
	BoxAnimationRender->CreateAnimation("None.bmp", "Box", 0, 0, 0.3f, false);
	BoxAnimationRender->ChangeAnimation("Box");
}

void NoneBox::Render()
{
}

void NoneBox::Update()
{
	PlayerCheck();
}

void NoneBox::PlayerCheck()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == BoxBotCollision->CollisionResult("PlayerHeadHit", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineSound::SoundPlayOneShot("smb_powerup_appears.wav");
		EmptyBox* EBox = GetLevel()->CreateActor<EmptyBox>();
		EBox->SetPosition(GetPosition());
		UPMushroom* Ptr = GetLevel()->CreateActor<UPMushroom>();
		Ptr->SetPosition(GetPosition());
		BoxBotCollision->GetActor()->Off();
	}
	if (true == BoxBotCollision->CollisionResult("BigPlayerHeadHit", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineSound::SoundPlayOneShot("smb_powerup_appears.wav");
		EmptyBox* EBox = GetLevel()->CreateActor<EmptyBox>();
		EBox->SetPosition(GetPosition());
		UPMushroom* Ptr = GetLevel()->CreateActor<UPMushroom>();
		Ptr->SetPosition(GetPosition());
		BoxBotCollision->GetActor()->Off();
	}
	if (true == BoxBotCollision->CollisionResult("WhitePlayerHeadHit", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		GameEngineSound::SoundPlayOneShot("smb_powerup_appears.wav");
		EmptyBox* EBox = GetLevel()->CreateActor<EmptyBox>();
		EBox->SetPosition(GetPosition());
		UPMushroom* Ptr = GetLevel()->CreateActor<UPMushroom>();
		Ptr->SetPosition(GetPosition());
		BoxBotCollision->GetActor()->Off();
	}
}
