#pragma once
#include "GameEnginePath.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 파일을 쉽게 이용하기 위해 만듬
class GameEngineFile : public GameEnginePath
{
public:
	//디폴트 생성자
	GameEngineFile();
	GameEngineFile(const std::string& _Path);
	GameEngineFile(std::filesystem::path _Path);
	
	GameEngineFile(const GameEngineFile& _Other);

	//디폴트 소멸자
	~GameEngineFile();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	//RValue Reference 생성자 (나중에 배울것)
	//GameEngineFile(GameEngineFile&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	GameEngineFile& operator=(const GameEngineFile& _Other) = delete;
	GameEngineFile& operator=(GameEngineFile&& _Other) noexcept = delete;


protected:

private:

};

