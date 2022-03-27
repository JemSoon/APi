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

public:
	bool IsZero2D()
	{
		return x == 0.0f && y == 0.0f;
	}

public:
	int ix()
	{
		return static_cast<int>(x);
	}

	int iy()
	{
		return static_cast<int>(y);
	}

	int iz()
	{
		return static_cast<int>(z);
	}

	int iw()
	{
		return static_cast<int>(w);
	}


	int hix()
	{
		return static_cast<int>(x * 0.5f);
	}

	int hiy()
	{
		return static_cast<int>(y * 0.5f);
	}

	int hiz()
	{
		return static_cast<int>(z * 0.5f);
	}

	float4 Half()
	{
		return { x * 0.5f, y * 0.5f,z * 0.5f, 1.0f};
	}

public:
	float4()
		:x(0.0f), y(0.0f), z(0.0f), w(1.0f)
	{

	}
	float4(float _x, float _y)
		:x(_x), y(_y), z(0.0f), w(1.0f)
	{

	}
	float4(float _x, float _y, float _z)
		:x(_x), y(_y), z(_z), w(1.0f)
	{

	}
	float4(float _x, float _y, float _z, float _w)
		:x(_x), y(_y), z(_z), w(_w)
	{

	}

};

struct GameEngineRect
{
public:
	float4 Pos;
	float4 Scale;

public:
	int CenterLeft()
	{
		return Pos.ix() - Scale.hix();//센터 기준으로 할거라 절반
	}

	int CenterRight()
	{
		return Pos.ix() + Scale.hix();//센터 기준으로 할거라 절반
	}

	int CenterTop()
	{
		return Pos.iy() - Scale.hiy();//센터 기준으로 할거라 절반
	}

	int CenterBot()
	{
		return Pos.iy() + Scale.hiy();//센터 기준으로 할거라 절반
	}

public:
	GameEngineRect(float4 _Pos, float4 _Scale)
		:Pos(_Pos)
		,Scale(_Scale)
	{

	}

};