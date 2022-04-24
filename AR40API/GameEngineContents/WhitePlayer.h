#pragma once

#include "BigPlayer.h"
//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class WhitePlayer : public BigPlayer
{
public:
	//����Ʈ ������
	WhitePlayer();
	//����Ʈ �Ҹ���
	~WhitePlayer();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	WhitePlayer(const WhitePlayer& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	WhitePlayer(WhitePlayer&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	WhitePlayer& operator=(const WhitePlayer& _Other) = delete;
	WhitePlayer& operator=(WhitePlayer&& _Other) noexcept = delete;


protected:

private:

};

