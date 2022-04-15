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

	{	//�ʰ� ĳ������ �浹������
		//(����)���� BG�� ��ǥ�� �ȸ��� ����
		MapColImage_ = GameEngineImageManager::GetInst()->Find("ColMap1-1.bmp");


		if (nullptr == MapColImage_)
		{
			MsgBoxAssert("�� �浹�� �̹����� ã�� ���߽��ϴ�");
		}
	}


	{	//�� �̷���ġ
		float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		//�� �� �߹ٴ� ��ġ
		float4 CheckPos = NextPos + float4(0.0f, 32.0f);//�߹ٴ��� üũ�ϸ� �ƿ� ����

		int Color = MapColImage_->GetImagePixel(CheckPos);//���� �ֳ� ���� �� üũ

		if (RGB(255, 0, 0) != Color)
		{	//�������� �ƴ϶�� ���� �̽�
			MoveDir = float4::LEFT;
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
			//�� �� ������ ����������?? �� ���� ���������� �� ĥ�ص״µ� GameEngineImage::GetImagePixel����
		}
	

		//SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		
	}

	//{	//�߷�
	//	int Color = MapColImage_->GetImagePixel(GetPosition() + float4(0.0f, 32.0f));

	//	AccGravity_ += GameEngineTime::GetDeltaTime() * Gravity_;//���� ���ӵ�

	//	if (RGB(255, 0, 0) == Color/*���� ��Ҵٸ�(������)*/)
	//	{
	//		AccGravity_ = 0.0f;//����-�߷�0�Ǹ� �ؿ� �̵��� 0�̵Ǽ� ���� ������ �̵�����
	//	}
	//	SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * AccGravity_);
	//}
}