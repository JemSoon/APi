#pragma once
#include "GameEngineActorSubObject.h"
#include "GameEngineEnum.h"
#include "GameEngineImage.h"
#include <map>

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 
//class GameEngineImage;
class GameEngineCollision : public GameEngineActorSubObject
{
	friend GameEngineActor;

public:
	//디폴트 생성자
	GameEngineCollision();
	//디폴트 소멸자
	~GameEngineCollision();




	//======아래것들은 명시적으로 안쓰겠습니다(delete)======

	//디폴트 복사 생성자
	GameEngineCollision(const GameEngineCollision& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	GameEngineCollision(GameEngineCollision&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	GameEngineCollision& operator=(const GameEngineCollision& _Other) = delete;
	GameEngineCollision& operator=(GameEngineCollision&& _Other) noexcept = delete;



	inline void SetPivot(const float4& _Pos)
	{
		Pivot_ = _Pos;
	}

	inline void SetScale(const float4& _Scale)
	{
		Scale_ = _Scale;
	}

	inline float4 GetCollisionPos()
	{
		return GetActor()->GetPosition() + Pivot_;
	}

	inline GameEngineRect GetRect()
	{
		return GameEngineRect(GetActor()->GetPosition() + Pivot_, Scale_);
	}

	//충돌한 대상이 존재하면 ture리턴하는 함수(충돌한 대상이 있는지 없는지만 체크하는 함수)
	bool CollisionCheck(
		const std::string& _TargetGroup, 
		CollisionType _This = CollisionType::Circle, 
		CollisionType _Target = CollisionType::Circle);
	//부딪히는 대상이랑 충돌판별, 그리고 나는 무슨타입으로 볼거냐
	//Player	Bullet
	//방패		적의 총알을 막는다
	//방패		적의 총알
	

private:
	friend class FrameAnimation;

	//액터(ex:플레이어)에서 {50,0}만큼 떨어진 곳에 있고 그게 충돌체크를 한다(센터기준)
	float4 Pivot_;

	//그 위치에서 얼만한 크기로
	float4 Scale_;


};

