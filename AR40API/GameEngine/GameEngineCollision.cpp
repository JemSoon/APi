#include "GameEngineCollision.h"
#include "GameEngine.h"
#include "GameEngineLevel.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>

bool (*CollisionCheckArray[static_cast<int>(CollisionType::Max)][static_cast<int>(CollisionType::Max)])(GameEngineCollision*, GameEngineCollision*);

bool RectToRect(GameEngineCollision* _Left, GameEngineCollision* _Right)
{

}

GameEngineCollision::GameEngineCollision()
	:Pivot_(float4::ZERO)
	,Scale_(float4::ZERO)
{
	CollisionCheckArray[static_cast<int>(CollisionType::Rect)][static_cast<int>(CollisionType::Rect)] = RectToRect;
}

GameEngineCollision::~GameEngineCollision()
{

}

bool GameEngineCollision::CollisionCheck(
	const std::string& _TargetGroup, 
	CollisionType _This /*= CollisionType::Circle*/,
	CollisionType _Target /*= CollisionType::Circle*/)
{
	std::map<std::string, std::list<GameEngineCollision*>>::iterator FindTargetGroup = GetActor()->GetLevel()->AllCollision_.find(_TargetGroup);
	//_TargetGroup랑 충돌할 것이다

	if (FindTargetGroup == GetActor()->GetLevel()->AllCollision_.end())
	{
		MsgBoxAssert("존재하지 않는 충돌 그룹과 충돌하려 했습니다");
	}

	std::list<GameEngineCollision*>& TargetGroup = FindTargetGroup->second;

	std::list<GameEngineCollision*>::iterator StartIter = TargetGroup.begin();
	std::list<GameEngineCollision*>::iterator EndIter = TargetGroup.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		//나와 상대의 비교
		//_This, _Tartget
	
		if (CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)](this, *StartIter))
		{
			return true;
		}
		

		//bool CollCheck(GameEngineCollision* _Left, GameEngineCollision* _Right);
		//bool RectToRect(GameEngineCollision* _Left, GameEngineCollision* _Right);
		//bool CircleToCircle(GameEngineCollision* _Left, GameEngineCollision* _Right);
		//bool CollCheck(GameEngineCollision* _Left, GameEngineCollision* _Right);
		
		//this 비교 (*StartIter)
	}
	return false;
}