#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineSound.h>

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

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

//설명 : 
class GameEngineImage;
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

	GameEngineCollision* BigPlayerCameraCollision;//카메라 세팅

	GameEngineCollision* BigPlayerCollision;//기본 충돌체
	GameEngineCollision* BigPlayerHeadCollision;//머리(떨구기용)
	GameEngineCollision* BigPlayerHeadHitCollision;//박스 히트용(중복안되게)
	GameEngineCollision* BigPlayerFootHitCollision;//몹 히트용(중복안되게)
	GameEngineCollision* BigPlayerFootCollision;//발
	GameEngineCollision* BigPlayerLeftCollision;//왼쪽
	GameEngineCollision* BigPlayerRightCollision;//오른쪽
	GameEngineCollision* BigPlayerDownCollision;
	// bullet 용 dir
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

	//===내가 추가한 퍼블릭 함수===//
	void FootCheck();//발 위치 확인용
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

	//알파용
	GameEngineRenderer* GetRenderer1()
	{
		return BigPlayerAnimationRender;
	}

	//===내 발바닥 갈수있는 위치 판별용 멤버 변수===//
private:
	float4 NextPos_;
	float4 CheckPos_;
	int Color_;
	float Time_;
	float HitTime_;

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
	void FallUpdate();


	void IdleStart();
	void MoveStart();
	void JumpStart();
	void FallStart();

};


