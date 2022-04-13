#pragma once
#include "GameEngineBase/GameEngineNameObject.h"
#include <list>
#include <map>
#include <GameEngineBase/GameEngineMath.h>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngine;
class GameEngineActor;
class GameEngineCollision;
class GameEngineLevel : public GameEngineNameObject
{
	friend GameEngine;
	friend GameEngineActor;
	friend GameEngineCollision;

public:
	//����Ʈ ������
	GameEngineLevel();
	//����Ʈ �Ҹ���
	virtual ~GameEngineLevel();




	//======�Ʒ��͵��� ��������� �Ⱦ��ڽ��ϴ�(delete)======

	//����Ʈ ���� ������
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	//RValue Reference ������ (���߿� ����)
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	//operater= (�ڱ��ڽ��� �����ϴ�)
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;


	template<typename ActorType>
	ActorType* CreateActor(int _Order = 0, const std::string& _Name = "")
	{
		//�� ȭ�鿡 ������� �˼�����(�����Ҵ�)
		ActorType* NewActor = new ActorType();//�갡 Name, Level�޴°� �����ʳ�? = ��� �ް��ִµ�?

		GameEngineActor* StartActor = NewActor;

		NewActor->SetName(_Name);

		NewActor->SetLevel(this);

		StartActor->Start();//�������� �� �غ�� �������� Start

		std::list<GameEngineActor*>& Group = AllActor_[_Order];
		Group.push_back(NewActor);

		//_Order���͵��� ���ư��� ������ �ǹ�(���� ���� �ൿ�ؾ��ϴ� ��=���� ����)
		//���� ���� �����̳ʰ� �⺻������ ���� �༮�� �� �տ� ���Ե�
		// 
		//insert�� find�� ���ÿ� �ϰ� �ȴ�
		//std::map<int, std::list<GameEngineActor* >>::iterator FindGroup = AllActor_.find(_Order);

		//if (FindGroup == AllActor_.end())//���� end���(���ٸ�) ���� ������ش�
		//{
		//	AllActor_.insert(std::map<int,std::list<GameEngineActor*>>::value_type(_Order,std::list<GameEngineActor*>()));
		//}
		//FindGroup = AllActor_.find(_Order);

		return NewActor;
	}

	inline float4 GetCameraPos()
	{
		return CameraPos_;
	}

	inline void MoveCameraPos(const float4& _Value)
	{
		CameraPos_ += _Value;
	}

	inline void SetCameraPos(const float4& _Value)
	{
		CameraPos_ = _Value;
	}

protected:
	virtual void Loading() = 0;
	virtual void Update() = 0;

	virtual void LevelChangeStart() {}
	//��������->���緹�� �̵��� ���緹���� �����ϴ��Լ�
	virtual void LevelChangeEnd() {}
	//��������->���緹�� �̵��� ���������� �����ϴ� �Լ�



private:
	//���� �������� ����ž� �Ź��̸� ����ž� �� ���� �����Ե�
	std::map<int, std::list<GameEngineActor*>> AllActor_;

	//string�� ����ϴ°� �־��� ����
	//std::map<std::string, std::list<GameEngineActor* >> AllActor_;

	float4 CameraPos_;

	void ActorUpdate();
	void ActorRender();
	void CollisionDebugRender();
	void ActorRelease();

private:
	//������ ���Ͱ� ������ ���� ����� Level�� ��
	//���⼭ �Ժη� GameEngineCollision*�� delete�ϴ� ���� ������ �ȵȴ�
	std::map<std::string, std::list<GameEngineCollision*>> AllCollision_;

	void AddCollision(const std::string& _GroupName, GameEngineCollision* _Collision);
};

