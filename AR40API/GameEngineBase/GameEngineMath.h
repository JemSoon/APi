#pragma once

//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 3D에 쓰일 것까지 미리
class GameEngineMath
{
private:
	//디폴트 생성자
	GameEngineMath();
	//디폴트 소멸자
	~GameEngineMath();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	GameEngineMath(const GameEngineMath& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	GameEngineMath(GameEngineMath&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	GameEngineMath& operator=(const GameEngineMath& _Other) = delete;
	GameEngineMath& operator=(GameEngineMath&& _Other) noexcept = delete;


protected:

private:

};

class float4
{
public:
	float x;
	float y;
	float z;
	float w;
};