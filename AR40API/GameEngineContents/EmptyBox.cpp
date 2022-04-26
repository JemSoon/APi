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

	EmptyBoxCollision = CreateCollision("EmptyBox", { 64, 64 });
	EmptyBoxAnimationRender = CreateRenderer();
	EmptyBoxAnimationRender->CreateAnimation("empty-Box.bmp", "EmptyBox", 0, 0, 0.1f, false);
	EmptyBoxAnimationRender->ChangeAnimation("EmptyBox");
}

void EmptyBox::Render()
{
}

void EmptyBox::Update()
{
}
