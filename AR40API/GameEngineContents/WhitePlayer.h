#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

enum class WhitePlayerState
{
	Idle,
	Attck,
	Move,
	Jump,
	Dead,
	Max,
};

//���� : 
class GameEngineImage;
class GameEngineCollision;
class WhitePlayer : public GameEngineActor
{
public:
	static WhitePlayer* MainWhitePlayer;

	//����Ʈ ������
	WhitePlayer();
	//����Ʈ �Ҹ���
	~WhitePlayer();



	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======

	//����Ʈ ���� ������
	WhitePlayer(const WhitePlayer& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	WhitePlayer(WhitePlayer&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	WhitePlayer& operator=(const WhitePlayer& _Other) = delete;
	WhitePlayer& operator=(WhitePlayer&& _Other) noexcept = delete;


	float4 CurDir()
	{
		return WhitePlayerDir_;
	}

protected:
	GameEngineRenderer* WhitePlayerAnimationRender;

	std::string AnimationName;


	//void WhitePlayerStateUpdate();


private:
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	static float4 NextLevelPosition;
	GameEngineRenderer* Render1;

	float Speed_;
	float AccSpeed_;
	float4 MoveDir;

	std::string WhiteDirString;//�ִϸ��̼� �����

	GameEngineImage* MapColImage_;

	GameEngineCollision* WhitePlayerCollision;//�⺻ �浹ü
	GameEngineCollision* WhitePlayerHeadCollision;//�Ӹ�
	GameEngineCollision* WhitePlayerFootCollision;//��

	// bullet �� dir
	float4 WhitePlayerDir_;

public:
	void Start() override;
	void Render() override;
	void Update() override;

	void DoorCheck();
	void WallCheck();
	void MushroomCheck();

	bool IsMoveKey();
	void CameraOutCheck();

	//===���� �߰��� �ۺ� �Լ�===//
	void FootCheck();//�� ��ġ Ȯ�ο�
	void Fire();//�Ѿ� �߻��Լ�

	//===�� �߹ٴ� �����ִ� ��ġ �Ǻ��� ��� ����===//
private:
	float4 NextPos_;
	float4 CheckPos_;
	int Color_;

	//ī�޶� ��ǥ ������ �������
	float4 CameraPos_;

	// state�� �Լ�
private:
	WhitePlayerState CurState_;

	void ChangeState(WhitePlayerState _State);
	void StateUpdate();

private:
	// FSM���� �ݱⰡ �ֽ��ϴ�.
	void IdleUpdate();
	void MoveUpdate();
	void JumpUpdate();

	void IdleStart();
	void MoveStart();
	void JumpStart();
};


