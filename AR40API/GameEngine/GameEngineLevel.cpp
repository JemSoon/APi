#include "GameEngineLevel.h"
#include "GameEngineActor.h"
#include "GameEngineCollision.h"

GameEngineLevel::GameEngineLevel()
	: CameraPos_(float4::ZERO)
{

}

GameEngineLevel::~GameEngineLevel()
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart = AllActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd = AllActor_.end();

	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& Group = GroupStart->second;

		std::list<GameEngineActor*>::iterator StartActor = Group.begin();
		std::list<GameEngineActor*>::iterator EndActor = Group.end();

		for (; StartActor != EndActor; ++StartActor)
		{
			if (nullptr == (*StartActor))
			{
				continue;
			}

			delete (*StartActor);
			(*StartActor) = nullptr;
		}

	}
}

void GameEngineLevel::ActorUpdate()
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart;
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd;

	std::list<GameEngineActor*>::iterator StartActor;
	std::list<GameEngineActor*>::iterator EndActor;

	GroupStart = AllActor_.begin();
	GroupEnd = AllActor_.end();


	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& Group = GroupStart->second;

		StartActor = Group.begin();
		EndActor = Group.end();

		for (; StartActor != EndActor; ++StartActor)
		{
			(*StartActor)->ReleaseUpdate();
			if (false == (*StartActor)->IsUpdate())
			{
				continue;
			}

			(*StartActor)->Update();//Actor를 다 돌면서 업뎃 해줌
		}

	}
}


void GameEngineLevel::ActorRender()
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart;
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd;

	std::list<GameEngineActor*>::iterator StartActor;
	std::list<GameEngineActor*>::iterator EndActor;

	GroupStart = AllActor_.begin();
	GroupEnd = AllActor_.end();



	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& Group = GroupStart->second;

		StartActor = Group.begin();
		EndActor = Group.end();

		for (; StartActor != EndActor; ++StartActor)
		{
			if (false == (*StartActor)->IsUpdate())
			{
				continue;
			}

			(*StartActor)->Renderering();//Actor를 다 돌면서 Renderering 해줌
		}


		StartActor = Group.begin();
		EndActor = Group.end();

		for (; StartActor != EndActor; ++StartActor)
		{
			if (false == (*StartActor)->IsUpdate())
			{
				continue;
			}
			(*StartActor)->Render();//renderering 다 되고 render해줌
		}
	}
}

void GameEngineLevel::CollisionDebugRender()
{
	std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupStart = AllCollision_.begin();
	std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupEnd = AllCollision_.end();

	std::list<GameEngineCollision*>::iterator StartCollision;
	std::list<GameEngineCollision*>::iterator EndCollision;

	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineCollision*>& Group = GroupStart->second;
		StartCollision = Group.begin();
		EndCollision = Group.end();

		for (; StartCollision != EndCollision; ++StartCollision)
		{
			if (false == (*StartCollision)->IsUpdate())
			{
				continue;
			}
			(*StartCollision)->DebugRender();
		}
	}

}

void GameEngineLevel::ActorRelease()
{
	//콜리전, 랜더 삭제(부분 삭제)
	{	//액터가 날라가면 이미 콜리젼,랜더 다 날라가기땜에 먼저
		std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupStart = AllCollision_.begin();
		std::map<std::string, std::list<GameEngineCollision*>>::iterator GroupEnd = AllCollision_.end();

		std::list<GameEngineCollision*>::iterator StartCollision;
		std::list<GameEngineCollision*>::iterator EndCollision;

		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineCollision*>& Group = GroupStart->second;
			StartCollision = Group.begin();
			EndCollision = Group.end();

			for (; StartCollision != EndCollision;)
			{
				if (false == (*StartCollision)->IsDeath())
				{
					++StartCollision;
					continue;//죽은애가 아니니 그냥 지나간다
				}

				StartCollision = Group.erase(StartCollision);
			}
		}
	}

	//액터의 삭제(전체삭제)
	{
		std::map<int, std::list<GameEngineActor*>>::iterator GroupStart;
		std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd;

		std::list<GameEngineActor*>::iterator StartActor;
		std::list<GameEngineActor*>::iterator EndActor;

		GroupStart = AllActor_.begin();
		GroupEnd = AllActor_.end();


		for (; GroupStart != GroupEnd; ++GroupStart)
		{
			std::list<GameEngineActor*>& Group = GroupStart->second;

			StartActor = Group.begin();
			EndActor = Group.end();

			for (; StartActor != EndActor;)
			{
				if (true == (*StartActor)->IsDeath())
				{
					delete* StartActor;//실제적인 메모리를 날림

					StartActor = Group.erase(StartActor);//리스트 노드를 날림

					continue;
				}

				//삭제가 안됬다면 콜리전이나 랜더러를 확인해본다
				(*StartActor)->Release();

				++StartActor;
			}
		}
	}
}


void GameEngineLevel::AddCollision(const std::string& _GroupName
	, GameEngineCollision* _Collision)
{
	//찾아서 없으면 만드는거까지
	AllCollision_[_GroupName].push_back(_Collision);
}
