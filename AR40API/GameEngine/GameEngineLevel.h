#pragma once
#include "GameEngineBase/GameEngineNameObject.h"
#include <list>
#include <map>

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 
class GameEngine;
class GameEngineActor;
class GameEngineLevel : public GameEngineNameObject
{
	friend GameEngine;
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


protected:
	virtual void Loading() = 0;
	virtual void Update() = 0;

	virtual void SceneChangeStart() {}
	//이전레벨->현재레벨 이동시 현재레벨이 실행하는함수
	virtual void SceneChangeEnd() {}
	//이전레벨->현재레벨 이동시 이전레벨이 실행하는 함수

	template<typename ActorType>
	ActorType* CreateActor(const std::string& _Name, int _Order)
	{
		//한 화면에 몇개만들지 알수없다(동적할당)
		ActorType* NewActor = new ActorType();
		NewActor->SetName(_Name);

		NewActor->SetLevel(this);

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

		return nullptr;
	}

private:
	//내가 마리오를 만들거야 거묵이를 만들거야 다 여기 들어오게됨
	std::map<int, std::list<GameEngineActor*>> AllActor_;

	//string을 사용하는건 최악의 수다
	//std::map<std::string, std::list<GameEngineActor* >> AllActor_;

	void ActorUpdate();
	void ActorRender();
};

