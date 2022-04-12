#include "GameEngineCollision.h"
#include "GameEngine.h"
#include "GameEngineLevel.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>

//전역변수
bool (*CollisionCheckArray[static_cast<int>(CollisionType::Max)][static_cast<int>(CollisionType::Max)])(GameEngineCollision*, GameEngineCollision*);

bool RectToRect(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	if (nullptr == _Left || nullptr == _Right)
	{
		return false;
	}

	GameEngineRect LeftRc = _Left->GetRect();
	GameEngineRect RightRC = _Right->GetRect();

	return LeftRc.OverLap(RightRC);
}

class CollisionInit
{
public:
	CollisionInit()
	{
		CollisionCheckArray[static_cast<int>(CollisionType::Rect)][static_cast<int>(CollisionType::Rect)] = RectToRect;
	}
};

//전역변수
CollisionInit InitInst = CollisionInit();

GameEngineCollision::GameEngineCollision()
	:Pivot_(float4::ZERO)
	, Scale_(float4::ZERO)
{

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
		//MsgBoxAssert("존재하지 않는 충돌 그룹과 충돌하려 했습니다");//test용
		return false;
	}

	if (nullptr == CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)])
	{
		MsgBoxAssert("처리할 수 없는 충돌체크 조합입니다");
		return false;
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

void GameEngineCollision::DebugRender()
{
	GameEngineRect DebugRect(GetActor()->GetCameraEffectPosition() + Pivot_, Scale_);

	Rectangle(
		GameEngine::BackBufferDC(),
		DebugRect.CenterLeft(),
		DebugRect.CenterTop(),
		DebugRect.CenterRight(),
		DebugRect.CenterBot()
	);
}

bool GameEngineCollision::CollisionResult(
	const std::string& _TargetGroup,
	std::vector<GameEngineCollision*>& _ColResult,//니가 여기다 넣어줘
	CollisionType _This /*= CollisionType::Circle*/,
	CollisionType _Target /*= CollisionType::Circle*/)
{
	size_t StartSize = _ColResult.size();

	std::map<std::string, std::list<GameEngineCollision*>>::iterator FindTargetGroup = GetActor()->GetLevel()->AllCollision_.find(_TargetGroup);
	//_TargetGroup랑 충돌할 것이다

	if (FindTargetGroup == GetActor()->GetLevel()->AllCollision_.end())
	{
		//MsgBoxAssert("존재하지 않는 충돌 그룹과 충돌하려 했습니다");//test용
		return false;
	}

	if (nullptr == CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)])
	{
		MsgBoxAssert("처리할 수 없는 충돌체크 조합입니다");
		return false;
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
			_ColResult.push_back(*StartIter);
		}

	}
	return StartSize != _ColResult.size();
}