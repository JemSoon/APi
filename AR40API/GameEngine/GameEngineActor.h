#pragma once
#include <GameEngineBase/GameEngineNameObject.h>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngineActor
{
public:
	//����Ʈ ������
	GameEngineActor();
	//����Ʈ �Ҹ���
	~GameEngineActor();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineActor(const GameEngineActor& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;


protected:

private:

};

