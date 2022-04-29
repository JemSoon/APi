#include "EmptyBox.h"
#include "Box.h"

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>

EmptyBox::EmptyBox()
{

}

EmptyBox::~EmptyBox()
{

}

void EmptyBox::Start()
{
	SetScale({ 64,64 });

	EmptyBoxCollision = CreateCollision("Box", { 64, 64 });
	EmptyBoxTopCollision = CreateCollision("BoxTop", { 64, 1 }, {0,-32});
	EmptyBoxAnimationRender = CreateRenderer((int)ORDER::EMPTYBOX);
	EmptyBoxAnimationRender->CreateAnimation("empty-Box.bmp", "EmptyBox", 0, 0, 0.1f, false);
	EmptyBoxAnimationRender->ChangeAnimation("EmptyBox");
}

void EmptyBox::Render()
{
}

void EmptyBox::Update()
{
}
