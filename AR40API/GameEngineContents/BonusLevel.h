#pragma once
#include <GameEngine/GameEngineLevel.h>

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 
class BonusLevel : public GameEngineLevel
{
public:
	//디폴트 생성자
	BonusLevel();
	//디폴트 소멸자
	~BonusLevel();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	BonusLevel(const BonusLevel& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	BonusLevel(BonusLevel&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	BonusLevel& operator=(const BonusLevel& _Other) = delete;
	BonusLevel& operator=(BonusLevel&& _Other) noexcept = delete;


protected:
	void Loading() override;
	void Update() override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
private:

};

