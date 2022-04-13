#pragma once
#include <map>
#include <string>
#include <GameEngineBase/GameEngineDebug.h>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

class GameEngineImage;
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

	static inline GameEngineImage* BackBufferImage()
	{
		return BackBufferImage_;
	}

	static HDC BackBufferDC();


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

	static GameEngine& GetInst()
	{
		if (nullptr == UserContents_)
		{
			MsgBoxAssert("Global Engine Error Engine is not Start");
		}
		return *UserContents_;
	}


	void ChangeLevel(const std::string& _Name);


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
	static GameEngineLevel* CurrentLevel_;
	static GameEngineLevel* NextLevel_;
	static GameEngine* UserContents_;

	static GameEngineImage* WindowMainImage_;//��¥ ���� �̹���
	static GameEngineImage* BackBufferImage_;//����۷� �̸� �׷����� �̹���(������ ��)


	static void WindowCreate();

	static void EngineInit();
	static void EngineLoop();
	static void EngineEnd();
};

