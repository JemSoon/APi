#pragma once
#include <GameEngine/GameEngineActor.h>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class Player : public GameEngineActor
{
public:
	//����Ʈ ������
	Player();
	//����Ʈ �Ҹ���
	~Player();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	Player(const Player& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Player(Player&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;


protected:

private:
	float Speed_;
	float Gravity_;
	float AccGravity_;

	void Start() override;
	void Render() override;
	void Update() override;
};

