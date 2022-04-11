#pragma once
#include "GameEngineBase/GameEngineNameObject.h"
#include <list>
#include <map>
#include <GameEngineBase/GameEngineMath.h>

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 
class GameEngine;
class GameEngineActor;
class GameEngineCollision;
class GameEngineLevel : public GameEngineNameObject
{
	friend GameEngine;
	friend GameEngineActor;
	friend GameEngineCollision;

public:
	//디폴트 생성자
	GameEngineLevel();
	//디폴트 소멸자
	virtual ~GameEngineLevel();




	//======아래것들은 명시적으로 안쓰겠습니다(delete)======

	//디폴트 복사 생성자
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;


	template<typename ActorType>
	ActorType* CreateActor(int _Order = 0, const std::string& _Name = "")
	{
		//한 화면에 몇개만들지 알수없다(동적할당)
		ActorType* NewActor = new ActorType();//얘가 Name, Level받는게 낫지않냐? = 상속 받고있는데?

		GameEngineActor* StartActor = NewActor;

		NewActor->SetName(_Name);

		NewActor->SetLevel(this);

		StartActor->Start();//레벨까지 다 준비된 시점에서 Start

		std::list<GameEngineActor*>& Group = AllActor_[_Order];
		Group.push_back(NewActor);

		//_Order액터들이 돌아가는 순서를 의미(가장 먼저 행동해야하는 애=작은 숫자)
		//맵은 연관 컨테이너고 기본적으로 작은 녀석이 맨 앞에 오게됨
		// 
		//insert와 find를 동시에 하게 된다
		//std::map<int, std::list<GameEngineActor* >>::iterator FindGroup = AllActor_.find(_Order);

		//if (FindGroup == AllActor_.end())//만약 end라면(없다면) 새로 만들어준다
		//{
		//	AllActor_.insert(std::map<int,std::list<GameEngineActor*>>::value_type(_Order,std::list<GameEngineActor*>()));
		//}
		//FindGroup = AllActor_.find(_Order);

		return NewActor;
	}

	inline float4 GetCameraPos()
	{
		return CameraPos_;
	}

	inline void MoveCameraPos(const float4& _Value)
	{
		CameraPos_ += _Value;
	}

	inline void SetCameraPos(const float4& _Value)
	{
		CameraPos_ = _Value;
	}

protected:
	virtual void Loading() = 0;
	virtual void Update() = 0;

	virtual void LevelChangeStart() {}
	//이전레벨->현재레벨 이동시 현재레벨이 실행하는함수
	virtual void LevelChangeEnd() {}
	//이전레벨->현재레벨 이동시 이전레벨이 실행하는 함수



private:
	//내가 마리오를 만들거야 거묵이를 만들거야 다 여기 들어오게됨
	std::map<int, std::list<GameEngineActor*>> AllActor_;

	//string을 사용하는건 최악의 수다
	//std::map<std::string, std::list<GameEngineActor* >> AllActor_;

	float4 CameraPos_;

	void ActorUpdate();
	void ActorRender();
	void CollisionDebugRender();
	void ActorRelease();

private:
	//삭제는 액터가 하지만 실제 사용은 Level이 함
	//여기서 함부로 GameEngineCollision*를 delete하는 일이 있으면 안된다
	std::map<std::string, std::list<GameEngineCollision*>> AllCollision_;

	void AddCollision(const std::string& _GroupName, GameEngineCollision* _Collision);
};

