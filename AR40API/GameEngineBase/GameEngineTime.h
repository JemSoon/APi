#pragma once

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 
class GameEngineTime
{
private:
	static GameEngineTime* Inst_;

public:
	static GameEngineTime* GetInst()
	{
		return Inst_;
	}

	static void Destroy()
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}
public:
	void Reset();
	void Update();

	inline float GetDeltaTime() 
	{
		return DeltaTime_;
	}

protected:

private:
	__int64 SecondCount_;
	__int64 CurrentCount_;
	__int64 PrevCount_;
	float DeltaTime_;
	double RealDeltaTime_;

	//디폴트 생성자
	GameEngineTime();
	//디폴트 소멸자
	~GameEngineTime();

	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	GameEngineTime(const GameEngineTime& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	GameEngineTime(GameEngineTime&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(GameEngineTime&& _Other) noexcept = delete;
};

