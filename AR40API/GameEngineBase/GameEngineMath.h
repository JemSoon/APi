#pragma once

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 3D�� ���� �ͱ��� �̸�
class GameEngineMath
{
private:
	//����Ʈ ������
	GameEngineMath();
	//����Ʈ �Ҹ���
	~GameEngineMath();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineMath(const GameEngineMath& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineMath(GameEngineMath&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineMath& operator=(const GameEngineMath& _Other) = delete;
	GameEngineMath& operator=(GameEngineMath&& _Other) noexcept = delete;


protected:

private:

};

class float4
{
public:
	float x;
	float y;
	float z;
	float w;
};