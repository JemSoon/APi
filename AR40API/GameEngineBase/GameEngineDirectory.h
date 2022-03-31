#pragma once
#include "GameEnginePath.h"

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

class GameEngineFile;
//설명 : 디렉토리를 쉽게 사용하기 위해 만듦 (폴더 설정)
class GameEngineDirectory : public GameEnginePath
{
public:
	//디폴트 생성자
	GameEngineDirectory();
	//디폴트 소멸자
	~GameEngineDirectory();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	GameEngineDirectory(const GameEngineDirectory& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	GameEngineDirectory(GameEngineDirectory&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	GameEngineDirectory& operator=(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory& operator=(GameEngineDirectory&& _Other) noexcept = delete;

	void MoveParent();

	void MoveParent(const std::string& _Name);

	bool IsRoot();

	void Move(const std::string& _Name);

	std::vector<GameEngineFile> GetAllFile(const std::string& _Ext = "");

protected:

private:

};

