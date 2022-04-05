#pragma once
#include <GameEngine/GameEngineActor.h>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : �ΰ��� ȭ�鿡 ��µ� UI
class GameEngineRenderer;
class UI : public GameEngineActor
{
public:
	//����Ʈ ������
	UI();
	//����Ʈ �Ҹ���
	~UI();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	UI(const UI& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	UI(UI&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	UI& operator=(const UI& _Other) = delete;
	UI& operator=(UI&& _Other) noexcept = delete;


protected:

	void Start() override;
	//void Render() override;
private:
};

