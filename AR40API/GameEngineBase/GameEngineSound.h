#pragma once

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngineSound
{
public:
	//����Ʈ ������
	GameEngineSound();
	//����Ʈ �Ҹ���
	~GameEngineSound();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineSound(const GameEngineSound& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineSound(GameEngineSound&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineSound& operator=(const GameEngineSound& _Other) = delete;
	GameEngineSound& operator=(GameEngineSound&& _Other) noexcept = delete;


protected:

private:

};

