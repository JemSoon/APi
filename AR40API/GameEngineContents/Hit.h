#pragma once
#include <GameEngine/GameEngineActor.h>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : �Ѿ��� �浹�� ������ �̹�����
class Hit : public GameEngineActor
{
public:
	//����Ʈ ������
	Hit();
	//����Ʈ �Ҹ���
	~Hit();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	Hit(const Hit& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Hit(Hit&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Hit& operator=(const Hit& _Other) = delete;
	Hit& operator=(Hit&& _Other) noexcept = delete;
	
	float Time;

protected:

private:
	void Start() override;
	void Update() override;

};

