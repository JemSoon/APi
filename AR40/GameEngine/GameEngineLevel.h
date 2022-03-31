#pragma once
#include "GameEngineBase/GameEngineNameObject.h"
#include <list>
#include <map>

//�������� ������ �͵鵵 ��������� ĥ ���̴�
//���� ������ �ʾƵ� �ڵ����� �����Ǿ� ������ �ִ°͵�

//���� : 
class GameEngine;
class GameEngineActor;
class GameEngineLevel : public GameEngineNameObject
{
	friend GameEngine;
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


protected:
	virtual void Loading() = 0;
	virtual void Update() = 0;

	virtual void LevelChangeStart() {}
	//��������->���緹�� �̵��� ���緹���� �����ϴ��Լ�
	virtual void LevelChangeEnd() {}
	//��������->���緹�� �̵��� ���������� �����ϴ� �Լ�

	template<typename ActorType>
	ActorType* CreateActor(const std::string& _Name, int _Order)
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

		return nullptr;
	}

private:
	//���� �������� ����ž� �Ź��̸� ����ž� �� ���� �����Ե�
	std::map<int, std::list<GameEngineActor*>> AllActor_;

	//string�� ����ϴ°� �־��� ����
	//std::map<std::string, std::list<GameEngineActor* >> AllActor_;

	void ActorUpdate();
	void ActorRender();
};

