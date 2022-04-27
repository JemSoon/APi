#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

enum class PlayerState
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
class Player : public GameEngineActor
{
public:
	static Player* MainPlayer;

	//디폴트 생성자
	Player();
	//디폴트 소멸자
	~Player();



	//======아래것들은 명시적으로 안쓰겠습니다(delete)======

	//디폴트 복사 생성자
	Player(const Player& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	Player(Player&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;


	float4 CurDir()
	{
		return PlayerDir_;
	}

protected:
	GameEngineRenderer* PlayerAnimationRender;
	
	std::string AnimationName;


	//void PlayerStateUpdate();


private:
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	static float4 NextLevelPosition;
	GameEngineRenderer* Render1;

	float Speed_;
	float AccSpeed_;
	float4 MoveDir;

	GameEngineImage* MapColImage_;

	GameEngineCollision* PlayerCollision;//기본 충돌체
	GameEngineCollision* PlayerHeadCollision;//머리
	GameEngineCollision* PlayerFootCollision;//발

	// bullet 용 dir
	float4 PlayerDir_;

	// 애니메이션 방향체크용
	std::string DirString;//지금 방향
	std::string PrevDirString;//방향이 바뀌었을때

public:
	void Start() override;
	void Render() override;
	void Update() override;

	void DoorCheck();
	void WallCheck();
	void MushroomCheck();
	void FireFlowerCheck();

	bool IsMoveKey();
	void CameraOutCheck();

	//===내가 추가한 퍼블릭 함수===//
	void FootCheck();//발 위치 확인용
	void LeftCheck();
	void RightCheck();
	void RightBotCheck();
	void Fire();//총알 발사함수
	
	//===내 발바닥 갈수있는 위치 판별용 멤버 변수===//
private:
	float4 NextPos_;
	float4 CheckPos_;
	int Color_;
	//아이템 체크용 마리오상태
	PlayerType Type_;
	
	//카메라 좌표 설정용 멤버변수
	float4 CameraPos_;

	// state용 함수
private:
	PlayerState CurState_;

	void ChangeState(PlayerState _State);
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


