#pragma once

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class EndingCredit
{
public:
	//����Ʈ ������
	EndingCredit();
	//����Ʈ �Ҹ���
	~EndingCredit();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	EndingCredit(const EndingCredit& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	EndingCredit(EndingCredit&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	EndingCredit& operator=(const EndingCredit& _Other) = delete;
	EndingCredit& operator=(EndingCredit&& _Other) noexcept = delete;


protected:

private:

};

