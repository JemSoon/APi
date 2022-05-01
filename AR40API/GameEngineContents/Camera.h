#pragma once
#include <GameEngine/GameEngineActor.h>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class Camera :public GameEngineActor
{
public:
	//����Ʈ ������
	Camera();
	//����Ʈ �Ҹ���
	~Camera();

	
	
	
	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	Camera(const Camera& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	Camera(Camera&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	Camera& operator=(const Camera& _Other) = delete;
	Camera& operator=(Camera&& _Other) noexcept = delete;


protected:

private:

};

