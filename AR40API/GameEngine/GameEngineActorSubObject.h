#pragma once
#include <GameEngine/GameEngineActor.h>

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 
class GameEngineActorSubObject : public GameEngineUpdateObject
{
	friend GameEngineActor;

public:
	//디폴트 생성자
	GameEngineActorSubObject();
	//디폴트 소멸자
	virtual ~GameEngineActorSubObject();




	//======아래것들은 명시적으로 안쓰겠습니다(delete)======

	//디폴트 복사 생성자
	GameEngineActorSubObject(const GameEngineActorSubObject& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	GameEngineActorSubObject(GameEngineActorSubObject&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	GameEngineActorSubObject& operator=(const GameEngineActorSubObject& _Other) = delete;
	GameEngineActorSubObject& operator=(GameEngineActorSubObject&& _Other) noexcept = delete;

	inline GameEngineActor* GetActor()
	{
		return Actor_;
	}

	inline bool IsUpdate() override
	{
		//나의 IsUpdate_ && false == IsDeath_
		return GameEngineUpdateObject::IsUpdate() && Actor_->IsUpdate();
	}

	inline bool IsDeath() override
	{
		return GameEngineUpdateObject::IsDeath() || Actor_->IsDeath();
	}

protected:
	inline void SetActor(GameEngineActor* _Actor)
	{
		Actor_ = _Actor;
	}

private:
	GameEngineActor* Actor_;
};

