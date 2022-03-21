#pragma once
#include "GameEngine/GameEngineLevel.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class EndingLevel:public GameEngineLevel
{
public:
	//����Ʈ ������
	EndingLevel();
	//����Ʈ �Ҹ���
	~EndingLevel();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	EndingLevel(const EndingLevel& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	EndingLevel(EndingLevel&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	EndingLevel& operator=(const EndingLevel& _Other) = delete;
	EndingLevel& operator=(EndingLevel&& _Other) noexcept = delete;


protected:
	void Loading() override;
private:

};

