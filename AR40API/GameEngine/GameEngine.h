#pragma once
#include <map>
#include <string>
#include <GameEngineBase/GameEngineDebug.h>

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

class GameEngineLevel;
//설명 : 게임엔진이란 게임 그 자체의 시작점과 끝점 실행중을 담당
class GameEngine
{
public:
	//디폴트 생성자
	GameEngine();
	//디폴트 소멸자
	~GameEngine();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	GameEngine(const GameEngine& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	GameEngine(GameEngine&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	GameEngine& operator=(const GameEngine& _Other) = delete;
	GameEngine& operator=(GameEngine&& _Other) noexcept = delete;


	//내가 만든 프레임워크 에서는
	//게임엔진이 세 가지를 구현 안하면
	//내용이 없다고 하더라도 안됨
	virtual void GameInit() = 0;
	virtual void GameLoop() = 0;
	virtual void GameEnd() = 0;

	template<typename GameType>
	static void Start()
	{
		GameEngineDebug::LeakCheckOn();//릭체크

		GameType UserGame;//내가 만들고 싶은 게임타입 받고
		UserContents_ = &UserGame;

		WindowCreate();//창을 만듦

		EngineEnd();
	}

protected:
	template<typename LevelType>
	void CreateLevel(const std::string& _Name)
	{
		LevelType* NewLevel = new LevelType();
		NewLevel->SetName(_Name);
		GameEngineLevel* Level = NewLevel;
		Level->Loading();
		AllLevel_.insert(std::make_pair(_Name, NewLevel));
	}

private: 
	static std::map<std::string, GameEngineLevel*> AllLevel_;
	static GameEngine* UserContents_;

	static void WindowCreate();

	static void EngineInit();
	static void EngineLoop();
	static void EngineEnd();
};

