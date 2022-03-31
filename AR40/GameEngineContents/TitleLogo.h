#pragma once
#include <GameEngine/GameEngineActor.h>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class TitleLogo : public GameEngineActor
{
public:
	//����Ʈ ������
	TitleLogo();
	//����Ʈ �Ҹ���
	~TitleLogo();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	TitleLogo(const TitleLogo& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	TitleLogo(TitleLogo&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	TitleLogo& operator=(const TitleLogo& _Other) = delete;
	TitleLogo& operator=(TitleLogo&& _Other) noexcept = delete;


protected:
	void Start();

	void Render();

private:

};

