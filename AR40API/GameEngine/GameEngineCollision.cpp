#include "GameEngineCollision.h"
#include "GameEngine.h"
#include "GameEngineLevel.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineTime.h>

//��������
bool (*CollisionCheckArray[static_cast<int>(CollisionType::Max)][static_cast<int>(CollisionType::Max)])(GameEngineCollision*, GameEngineCollision*);

bool RectToRect(GameEngineCollision* _Left, GameEngineCollision* _Right)
{
	if (nullptr == _Left || nullptr == _Right)
	{
		return false;
	}

	GameEngineRect LeftRc = _Left->GetRect();
	GameEngineRect RightRC = _Right->GetRect();

	return LeftRc.OverLap(RightRc);
}

class CollisionInit
{
public:
	CollisionInit()
	{
		CollisionCheckArray[static_cast<int>(CollisionType::Rect)][static_cast<int>(CollisionType::Rect)] = RectToRect;
	}
};

//��������
CollisionInit InitInst = CollisionInit();

GameEngineCollision::GameEngineCollision()
	:Pivot_(float4::ZERO)
	,Scale_(float4::ZERO)
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
	//_TargetGroup�� �浹�� ���̴�

	if (FindTargetGroup == GetActor()->GetLevel()->AllCollision_.end())
	{
		//MsgBoxAssert("�������� �ʴ� �浹 �׷�� �浹�Ϸ� �߽��ϴ�");//test��
		return false;
	}

	if (nullptr == CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)])
	{
		MsgBoxAssert("ó���� �� ���� �浹üũ �����Դϴ�");
		return false;
	}

	std::list<GameEngineCollision*>& TargetGroup = FindTargetGroup->second;

	std::list<GameEngineCollision*>::iterator StartIter = TargetGroup.begin();
	std::list<GameEngineCollision*>::iterator EndIter = TargetGroup.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		//���� ����� ��
		//_This, _Tartget
	
		if (CollisionCheckArray[static_cast<int>(_This)][static_cast<int>(_Target)](this, *StartIter))
		{
			return true;
		}
		

		//bool CollCheck(GameEngineCollision* _Left, GameEngineCollision* _Right);
		//bool RectToRect(GameEngineCollision* _Left, GameEngineCollision* _Right);
		//bool CircleToCircle(GameEngineCollision* _Left, GameEngineCollision* _Right);
		//bool CollCheck(GameEngineCollision* _Left, GameEngineCollision* _Right);
		
		//this �� (*StartIter)
	}
	return false;
}