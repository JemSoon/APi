#pragma once
#include "Player.h"
//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class BigPlayer : public Player
{
public:
	//����Ʈ ������
	BigPlayer();
	//����Ʈ �Ҹ���
	~BigPlayer();

	void Start() override;
	void Render() override;
	void Update() override;
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	BigPlayer(const BigPlayer& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	BigPlayer(BigPlayer&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	BigPlayer& operator=(const BigPlayer& _Other) = delete;
	BigPlayer& operator=(BigPlayer&& _Other) noexcept = delete;


protected:

private:

};

