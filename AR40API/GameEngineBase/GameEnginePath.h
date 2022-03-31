#pragma once
#include <filesystem>

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 
class GameEnginePath
{

public:
	//디폴트 생성자
	GameEnginePath();
	GameEnginePath(const std::filesystem::path& _Path);
	//디폴트 소멸자
	~GameEnginePath();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	GameEnginePath(const GameEnginePath& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	GameEnginePath(GameEnginePath&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	GameEnginePath& operator=(GameEnginePath&& _Other) noexcept = delete;
	
	void SetCurrentPath();

	bool IsExits();

	std::string GetExtension();

	std::string GetFileName();

	std::string GetFullPath();

protected:
	std::filesystem::path Path_;

private:

};

