#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

enum class BigPlayerState
{
	Idle,
	Attck,
	Move,
	Jump,
	Dead,
	Max,
};

//설명 : 
class GameEngineImage;
class GameEngineCollision;
class BigPlayer : public GameEngineActor
{
public:
	static BigPlayer* MainBigPlayer;

	//디폴트 생성자
	BigPlayer();
	//디폴트 소멸자
	~BigPlayer();



	//======아래것들은 명시적으로 안쓰겠습니다(delete)======

	//디폴트 복사 생성자
	BigPlayer(const BigPlayer& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	BigPlayer(BigPlayer&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
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

	GameEngineCollision* BigPlayerCollision;//기본 충돌체
	GameEngineCollision* BigPlayerHeadCollision;//머리
	GameEngineCollision* BigPlayerFootCollision;//발

	// bullet 용 dir
	float4 BigPlayerDir_;

public:
	void Start() override;
	void Render() override;
	void Update() override;

	void DoorCheck();
	void WallCheck();
	void MushroomCheck();

	bool IsMoveKey();
	void CameraOutCheck();

	//===내가 추가한 퍼블릭 함수===//
	void FootCheck();//발 위치 확인용
	void Fire();//총알 발사함수

	//===내 발바닥 갈수있는 위치 판별용 멤버 변수===//
private:
	float4 NextPos_;
	float4 CheckPos_;
	int Color_;

	//점프 방향 설정용
	std::string BigDirString;//지금 방향

	//카메라 좌표 설정용 멤버변수
	float4 CameraPos_;

	// state용 함수
private:
	BigPlayerState CurState_;

	void ChangeState(BigPlayerState _State);
	void StateUpdate();

private:
	// FSM에서 금기가 있습니다.
	void IdleUpdate();
	void MoveUpdate();
	void JumpUpdate();

	void IdleStart();
	void MoveStart();
	void JumpStart();
};


