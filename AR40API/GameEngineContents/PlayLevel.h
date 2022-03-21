#pragma once
#include "GameEngine/GameEngineLevel.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class PlayLevel : public GameEngineLevel 
{
public:
	//����Ʈ ������
	PlayLevel();
	//����Ʈ �Ҹ���
	~PlayLevel();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	PlayLevel(const PlayLevel& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;


protected:

private:

};

