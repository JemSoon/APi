#pragma once
#include <string>

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 어떤 애가 이름을 가지기 위한 기능
class GameEngineNameObject
{
public:
	//디폴트 생성자
	GameEngineNameObject();
	//디폴트 소멸자
	virtual ~GameEngineNameObject();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	GameEngineNameObject(const GameEngineNameObject& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	GameEngineNameObject(GameEngineNameObject&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	GameEngineNameObject& operator=(const GameEngineNameObject& _Other) = delete;
	GameEngineNameObject& operator=(GameEngineNameObject&& _Other) noexcept = delete;

	//그냥 std::string으로 하면 값이 복사가 되면서 문제가 많아짐
	inline void SetName(const std::string& _Name)
	{
		Name_ = _Name;
	}

	std::string GetNameCopy()
	{
		return Name_;
	}

	const std::string& GetNameConstRef()
	{
		return Name_;
	}

	const char* GetNameConstPtr()
	{
		return Name_.c_str();
	}

protected:
private:
	std::string Name_;
};

