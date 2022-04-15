#include "Monster.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>

Monster::Monster()
	: Speed_(50.0f)
	, Gravity_(100.0f)
{

}

Monster::~Monster()
{

}

void Monster::Start()
{
	SetScale({ 64,64 });

	MonsterCollision = CreateCollision("MonsterHitBox", { 64, 64 });
	MonsterAnimationRender = CreateRenderer();
	MonsterAnimationRender->CreateAnimation("gumba-walk.bmp", "gumba-walk", 0, 1, 0.3f, true);
	MonsterAnimationRender->ChangeAnimation("gumba-walk");
}

void Monster::Render()
{

}

void Monster::Update()
{
	float4 CheckPos;
	float4 MoveDir = float4::ZERO;

	{	//맵과 캐릭터의 충돌설정용
		//(참고)실제 BG랑 좌표가 안맞음 현재
		MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");


		if (nullptr == MapColImage_)
		{
			MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다");
		}
	}


	{	//내 미래위치
		float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		//그 때 발바닥 위치
		float4 CheckPos = NextPos + float4(0.0f, 32.0f);//발바닥을 체크하면 아예 못감

		int Color = MapColImage_->GetImagePixel(CheckPos);//갈수 있냐 없냐 색 체크

		if (RGB(255, 0, 0) != Color)
		{	//빨간색이 아니라면 갈수 이써
			MoveDir = float4::LEFT;
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
			//왜 맵 밖으로 나가버리지?? 맵 밖은 빨간색으로 다 칠해뒀는데 GameEngineImage::GetImagePixel참고
		}
	

		//SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		
	}

	//{	//중력
	//	int Color = MapColImage_->GetImagePixel(GetPosition() + float4(0.0f, 32.0f));

	//	AccGravity_ += GameEngineTime::GetDeltaTime() * Gravity_;//점점 가속됨

	//	if (RGB(255, 0, 0) == Color/*땅에 닿았다면(빨간색)*/)
	//	{
	//		AccGravity_ = 0.0f;//문제-중력0되면 밑에 이동이 0이되서 땅에 닿으면 이동못함
	//	}
	//	SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * AccGravity_);
	//}
}