#pragma once
#include "GameEngineBase/GameEngineNameObject.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngine;
class GameEngineLevel : public GameEngineNameObject
{
	friend GameEngine;
public:
	//����Ʈ ������
	GameEngineLevel();
	//����Ʈ �Ҹ���
	virtual ~GameEngineLevel();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;


protected:
	virtual void Loading() = 0;

private:
	template<typename ActorType>
	ActorType* CreateActor(const std::string& _Name)
	{
		return nullptr;
	}
};

