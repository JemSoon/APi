#pragma once

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngineLevel
{
public:
	//����Ʈ ������
	GameEngineLevel();
	//����Ʈ �Ҹ���
	~GameEngineLevel();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;


protected:

private:

};

