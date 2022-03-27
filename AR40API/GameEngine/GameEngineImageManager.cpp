#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineDebug.h>

GameEngineImageManager* GameEngineImageManager::Inst_= new GameEngineImageManager();

GameEngineImageManager::GameEngineImageManager()
{

}

GameEngineImageManager::~GameEngineImageManager()
{
	std::map<std::string, GameEngineImage*>::iterator StartIter= AllRes.begin();
	std::map<std::string, GameEngineImage*>::iterator EndIter = AllRes.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != StartIter->second)
		{
			delete StartIter->second;
			StartIter->second = nullptr;
		}
	}

}

GameEngineImage* GameEngineImageManager::Create(const std::string& _Name, float4 _Scale)
{
	//맵이 끝까지 돌지 않았다=이미 있다
	if (AllRes.end()!=AllRes.find(_Name))
	{
		MsgBoxAssert("이미 존재하는 이름의 이미지를 또 만들려함 ");
		return nullptr;
	}
	
	//없으면 동적할당으로 하나 생성
	GameEngineImage* NewImage = new GameEngineImage();
	
	NewImage->SetName(_Name);

	if (false == NewImage->Create(_Scale))
	{
		delete NewImage;
		MsgBoxAssert((_Name+"이미지를 생성하는데 실패").c_str());
		return nullptr;
	}

	//이미지를 만들었으면 모아놓고 관리한다
	AllRes.insert(std::make_pair(_Name, NewImage));
	
	return NewImage;
}