#pragma once
#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineMath.h>
#include <map>

//기본적으로 리소스는 그냥 쓸 수도 있지만
//관리되는 리소스들은 전부 다 이름이 있다고 보고 쓴다

//설명 : 이미지를 관리 해주는 역할
class GameEngineImageManager
{
private:
	static GameEngineImageManager* Inst_;//싱글톤

public:
	static GameEngineImageManager* GetInst()
	{
		return Inst_;
	}

	static void Destroy()
	{
		if (nullptr == Inst_)
		{
			return;
		}
		delete Inst_;
		Inst_ = nullptr;
	}

	GameEngineImage* Find(const std::string& _Name);//이미지 찾는 함수
	
	//내가 비어있는 이미지를 만드는 기능
	GameEngineImage* Create(const std::string& _Name, const float4& _Scale);//이미지를 만들어 주는 함수
	GameEngineImage* Create(const std::string& _Name, HDC _DC);//이미지를 만들어 주는 함수

	GameEngineImage* Load(const std::string& _Path);
	GameEngineImage* Load(const std::string& _Path, const std::string& _Name);

private://싱글톤(하나만 만든다)
	//디폴트 생성자
	GameEngineImageManager();
	//디폴트 소멸자
	~GameEngineImageManager();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	GameEngineImageManager(const GameEngineImageManager& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	GameEngineImageManager(GameEngineImageManager&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	GameEngineImageManager& operator=(const GameEngineImageManager& _Other) = delete;
	GameEngineImageManager& operator=(GameEngineImageManager&& _Other) noexcept = delete;


protected:

private:
	std::map<std::string, GameEngineImage*> AllRes;
};

