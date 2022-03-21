#pragma once
#include "GameEngine/GameEngineLevel.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class TitleLevel:public GameEngineLevel
{
public:
	//����Ʈ ������
	TitleLevel();
	//����Ʈ �Ҹ���
	~TitleLevel();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	TitleLevel(const TitleLevel& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;


protected:
	void Loading() override;
private:
	
};

