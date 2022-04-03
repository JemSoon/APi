#pragma once
#include <GameEngine/GameEngineActor.h>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class Bullet : public GameEngineActor
{
public:
	//����Ʈ ������
	Bullet();
	//����Ʈ �Ҹ���
	~Bullet();




	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======

	//����Ʈ ���� ������
	Bullet(const Bullet& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Bullet(Bullet&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Bullet& operator=(const Bullet& _Other) = delete;
	Bullet& operator=(Bullet&& _Other) noexcept = delete;

	float Time;

protected:

private:
	void Start() override;
	void Update() override;
	//void Render() override;
};

