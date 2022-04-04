#pragma once
#include "GameEngine/GameEngineLevel.h"

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : ����� �̹� �������� �ȳ� ȭ��
class IntroLevel : public GameEngineLevel
{
public:
	//����Ʈ ������
	IntroLevel();
	//����Ʈ �Ҹ���
	~IntroLevel();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	IntroLevel(const IntroLevel& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	IntroLevel(IntroLevel&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	IntroLevel& operator=(const IntroLevel& _Other) = delete;
	IntroLevel& operator=(IntroLevel&& _Other) noexcept = delete;


protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;

private:

};

