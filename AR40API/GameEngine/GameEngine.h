#pragma once
#include <map>
#include <string>
#include <GameEngineBase/GameEngineDebug.h>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

class GameEngineLevel;
//���� : ���ӿ����̶� ���� �� ��ü�� �������� ���� �������� ���
class GameEngine
{
public:
	//����Ʈ ������
	GameEngine();
	//����Ʈ �Ҹ���
	~GameEngine();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngine(const GameEngine& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngine(GameEngine&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngine& operator=(const GameEngine& _Other) = delete;
	GameEngine& operator=(GameEngine&& _Other) noexcept = delete;


	//���� ���� �����ӿ�ũ ������
	//���ӿ����� �� ������ ���� ���ϸ�
	//������ ���ٰ� �ϴ��� �ȵ�
	virtual void GameInit() = 0;
	virtual void GameLoop() = 0;
	virtual void GameEnd() = 0;

	template<typename GameType>
	static void Start()
	{
		GameEngineDebug::LeakCheckOn();//��üũ

		GameType UserGame;//���� ����� ���� ����Ÿ�� �ް�
		UserContents_ = &UserGame;

		WindowCreate();//â�� ����

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

