#pragma once

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class Monster
{
public:
	//����Ʈ ������
	Monster();
	//����Ʈ �Ҹ���
	~Monster();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	Monster(const Monster& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Monster(Monster&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;


protected:

private:

};

