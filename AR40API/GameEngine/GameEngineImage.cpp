#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

#pragma comment(lib, "msimg32.lib")

GameEngineImage::GameEngineImage()
	:ImageDC_(nullptr)
{

}

GameEngineImage::~GameEngineImage()
{
	//window에서 할당해온 녀석들은 릭으로 체크가 안되지만
	//지워주는게 깔끔하다
	//당연히 윈도우에게 할당해 왔으므로 함수를 이용해서 지워야 한다

	if (nullptr != BitMap_)
	{
		DeleteObject(BitMap_);
		BitMap_ = nullptr;
	}

	if (nullptr != OldBitMap_)
	{
		DeleteObject(OldBitMap_);
		OldBitMap_ = nullptr;
	}

	if (nullptr != ImageDC_)
	{
		DeleteDC(ImageDC_);
		ImageDC_ = nullptr;
	}
}

bool GameEngineImage::Create(HDC _DC)
{
	ImageDC_ = _DC;
	ImageScaleCheck();
	return true;
}

bool GameEngineImage::Create(float4 _Scale)
{
	if (true == _Scale.IsZero2D())
	{
		MsgBoxAssert("크기가 0 인 이미지 제작시킴")
		return false;
	}

	//먼저 비트맵을 만들어
	//이미지 크기 만한
	BitMap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _Scale.ix(), _Scale.iy());
	
	//비어있지 않음
	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("ImageDC 생성 실패");
	}

	//Bit맵을 DC로 바꿔조(반대인가?)
	OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	ImageScaleCheck();

	return true;
}

void GameEngineImage::ImageScaleCheck()
{
	//DC 내부에 박혀있는 BITMAP을 꺼내오는 함수
	HBITMAP CurrentBitMap = (HBITMAP)GetCurrentObject(ImageDC_, OBJ_BITMAP);
	GetObject(CurrentBitMap, sizeof(BITMAP), &Info_);
}

void GameEngineImage::BitCopy(GameEngineImage* _Other)
{
	BitCopy(_Other, { 0, 0 }, { 0, 0 }, _Other->GetScale());
}


void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _OtherPivot, const float4& _OtherPivotScale)
{
	BitBlt(
		ImageDC_,	//여기에 복사해라
		_CopyPos.ix(),	//띄울 이미지 좌표x
		_CopyPos.iy(),	//띄울 이미지 좌표y
		_OtherPivotScale.ix(),	//내 이미지의 x크기만큼
		_OtherPivotScale.iy(),	//내 이미지의 y크기만큼
		_Other->ImageDC_,	//복사하려는 대상은
		_OtherPivot.ix(),	//복사하려는 대상의 시작점 x(어느 부분 복사할건지)
		_OtherPivot.iy(),	//복사하려는 대상의 시작점 y(어느 부분 복사할건지)
		SRCCOPY	//복사(윈도우 기능)
	);
}
