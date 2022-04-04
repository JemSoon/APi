#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include <Windows.h>
#include <vector>


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
	bool Create(HDC _DC);
	bool Load(const std::string& _Path);

	inline float4 GetScale()
	{
		return float4(static_cast<float>(Info_.bmWidth), static_cast<float>(Info_.bmHeight));
	}

	inline HDC ImageDC()
	{
		return ImageDC_;
	}

	//BitBlt
	void BitCopy(GameEngineImage* _Other);

	void BitCopy(GameEngineImage* _Other, const float4& _CopyPos);

	void BitCopyCenter(GameEngineImage* _Other, const float4& _CopyPos);

	void BitCopyCenterPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot);

	void BitCopyBot(GameEngineImage* _Other, const float4& _CopyPos);

	void BitCopyBotPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot);

	void BitCopy(GameEngineImage* _Other, const float4& _CopyPos
		,const float4& _CopyScale
		,const float4& _OtherPivot);

	//Trans

	void TransCopy(GameEngineImage* _Other,	const float4& _CopyPos, 
		const float4& _CopyScale, 
		const float4& _OtherPivot, const float4 _OtherScale, unsigned int _TransColor);


	void Cut(const float4& _CutSize);


	bool IsCut()
	{
		return 0 != CutPivot_.size();
	}

	float4 GetCutPivot(size_t _Index)
	{
		return CutPivot_[_Index];
	}

	float4 GetCutScale(size_t _Index)//이미지마다 쪼개는 크기를 다르게 하고싶다
	{
		return CutScale_[_Index];
	}

	void Cut(const float4& _CutScale, const float4& _CutPos)
	{
		CutPivot_.push_back(_CutPos);
		CutScale_.push_back(_CutScale);
	}

protected:

private:
	HDC ImageDC_;
	HBITMAP BitMap_;
	HBITMAP OldBitMap_;
	BITMAP Info_;

	std::vector<float4> CutPivot_;
	std::vector<float4> CutScale_;

	void ImageScaleCheck();

};

