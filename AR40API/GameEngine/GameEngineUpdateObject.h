#pragma once

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : ���߻��
class GameEngineUpdateObject
{
public:
	//����Ʈ ������
	GameEngineUpdateObject();
	//����Ʈ �Ҹ���
	~GameEngineUpdateObject();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineUpdateObject(const GameEngineUpdateObject& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineUpdateObject(GameEngineUpdateObject&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineUpdateObject& operator=(const GameEngineUpdateObject& _Other) = delete;
	GameEngineUpdateObject& operator=(GameEngineUpdateObject&& _Other) noexcept = delete;


protected:

private:

};

