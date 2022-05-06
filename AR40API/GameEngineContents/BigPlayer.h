#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineSound.h>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

enum class BigPlayerState
{
	Idle,
	Attck,
	Move,
	Jump,
	Fall,
	Dead,
	Max,
};

//���� : 
class GameEngineImage;
class BigPlayer : public GameEngineActor
{
public:
	static BigPlayer* MainBigPlayer;

	//����Ʈ ������
	BigPlayer();
	//����Ʈ �Ҹ���
	~BigPlayer();



	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======

	//����Ʈ ���� ������
	BigPlayer(const BigPlayer& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	BigPlayer(BigPlayer&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	BigPlayer& operator=(const BigPlayer& _Other) = delete;
	BigPlayer& operator=(BigPlayer&& _Other) noexcept = delete;


	float4 CurDir()
	{
		return BigPlayerDir_;
	}

protected:
	GameEngineRenderer* BigPlayerAnimationRender;

	std::string AnimationName;


	//void BigPlayerStateUpdate();


private:
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	static float4 NextLevelPosition;
	GameEngineRenderer* Render1;

	float Speed_;
	float AccSpeed_;
	float4 MoveDir;

	GameEngineImage* MapColImage_;

	GameEngineCollision* BigPlayerCameraCollision;//ī�޶� ����

	GameEngineCollision* BigPlayerCollision;//�⺻ �浹ü
	GameEngineCollision* BigPlayerHeadCollision;//�Ӹ�(�������)
	GameEngineCollision* BigPlayerHeadHitCollision;//�ڽ� ��Ʈ��(�ߺ��ȵǰ�)
	GameEngineCollision* BigPlayerFootHitCollision;//�� ��Ʈ��(�ߺ��ȵǰ�)
	GameEngineCollision* BigPlayerFootCollision;//��
	GameEngineCollision* BigPlayerLeftCollision;//����
	GameEngineCollision* BigPlayerRightCollision;//������
	GameEngineCollision* BigPlayerDownCollision;
	// bullet �� dir
	float4 BigPlayerDir_;

public:
	void Start() override;
	void Render() override;
	void Update() override;

	void DoorCheck();
	void WallCheck();
	void MushroomCheck();
	void FireFlowerCheck();
	void MonsterOnCheck();

	void MonsterHit();

	bool IsMoveKey();
	void CameraOutCheck();

	//===���� �߰��� �ۺ� �Լ�===//
	void FootCheck();//�� ��ġ Ȯ�ο�
	void HeadCheck();
	void LeftCheck();
	void RightCheck();

	void FallDead();

	void BreakAnimation();

	void TurtleOnCheck();
	void TBOnCheck();
	void SetColImage();

	void NoHit()
	{
		BigPlayerCollision->Off();
		BigPlayerDownCollision->Off();
	}
	void OnHit()
	{
		BigPlayerCollision->On();
		BigPlayerDownCollision->On();
	}

	void HitTimeCheck();

	//���Ŀ�
	GameEngineRenderer* GetRenderer1()
	{
		return BigPlayerAnimationRender;
	}

	//===�� �߹ٴ� �����ִ� ��ġ �Ǻ��� ��� ����===//
private:
	float4 NextPos_;
	float4 CheckPos_;
	int Color_;
	float Time_;
	float HitTime_;

	//���� ���� ������
	std::string BigDirString;//���� ����

	//ī�޶� ��ǥ ������ �������
	float4 CameraPos_;

	// state�� �Լ�
private:
	BigPlayerState CurState_;

	void ChangeState(BigPlayerState _State);
	void StateUpdate();

private:
	// FSM���� �ݱⰡ �ֽ��ϴ�.
	void IdleUpdate();
	void MoveUpdate();
	void JumpUpdate();
	void FallUpdate();


	void IdleStart();
	void MoveStart();
	void JumpStart();
	void FallStart();

};


