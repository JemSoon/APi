#pragma once
#include <GameEngine/GameEngineActor.h>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class Intro : public GameEngineActor
{
public:
	//����Ʈ ������
	Intro();
	//����Ʈ �Ҹ���
	~Intro();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	Intro(const Intro& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Intro(Intro&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Intro& operator=(const Intro& _Other) = delete;
	Intro& operator=(Intro&& _Other) noexcept = delete;


protected:
	void Start() override;

	void Render() override;

private:

};

