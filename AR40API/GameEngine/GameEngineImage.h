#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include <Windows.h>


//선생님은 생략된 것들도 명시적으로 칠 것이다
//직접 만들지 않아도 자동으로 생략되어 생성되 있는것들

//설명 : 이미지 그 자체의 클래스
class GameEngineImage : public GameEngineNameObject
{
public:
	//디폴트 생성자
	GameEngineImage();
	//디폴트 소멸자
	~GameEngineImage();

	
	
	
	//======아래것들은 명시적으로 안쓰겠습니다(delete)======
	
	//디폴트 복사 생성자
	GameEngineImage(const GameEngineImage& _Other) = delete;
	//RValue Reference 생성자 (나중에 배울것)
	GameEngineImage(GameEngineImage&& _Other) noexcept = delete;
	//operater= (자기자신을 리턴하는)
	GameEngineImage& operator=(const GameEngineImage& _Other) = delete;
	GameEngineImage& operator=(GameEngineImage&& _Other) noexcept = delete;

	bool Create(float4 _Scale);

	inline float4 Scale()
	{
		return float4(static_cast<float>(Info_.bmWidth), static_cast<float>(Info_.bmHeight));
	}

	inline HDC ImageDC()
	{
		return ImageDC_;
	}

protected:

private:
	HDC ImageDC_;
	HBITMAP BitMap_;
	HBITMAP OldBitMap_;
	BITMAP Info_;

	void ImageScaleCheck();

};

