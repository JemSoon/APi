#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngineLevel;
class GameEngineActor : public GameEngineNameObject
{
public:
	friend GameEngineLevel;

	//����Ʈ ������
	GameEngineActor();
	//����Ʈ �Ҹ���
	virtual ~GameEngineActor();

	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======
	
	//����Ʈ ���� ������
	GameEngineActor(const GameEngineActor& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;


protected:
	//start�� ������ ����
	virtual void Start() = 0;//�����ϸ� ���� �ϰ������ �����ڿ����� ����� ���� �κе��� ó���Ѵ�
	
	virtual void Update() {}//��ų�� ���´� ������ �ø��� ����� ������Ʈ(���������� ���� ����ɶ� ȣ���)

	virtual void Render() {}
private:
	GameEngineLevel* Level_;

	float4 Position_;
	float4 Scale_;

	//���� ������� ����
	inline void SetLevel(GameEngineLevel* _Level)
	{
		Level_ = _Level;
	}
};

