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

bool GameEngineImage::Load(const std::string& _Path)
{
	BitMap_ = static_cast<HBITMAP>(LoadImageA(
		nullptr,
		_Path.c_str(),
		IMAGE_BITMAP,
		0,
		0,
		LR_LOADFROMFILE
		));

	if (nullptr == BitMap_)
	{
		MsgBoxAssertString(_Path + "이미지 로드에 실패 - 경로 확인, 디버깅 체크 요망");
	}

	//빈이미지 만들고 교체하는 과정
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

void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos)
{
	BitCopy(_Other, _CopyPos, _Other->GetScale(), float4{ 0, 0 });
}

//캐릭터 이미지의 한 가운데가 센터
void GameEngineImage::BitCopyCenter(GameEngineImage* _Other, const float4& _CopyPos)
{
	BitCopy(_Other, _CopyPos - _Other->GetScale().Half(), _Other->GetScale(), float4{ 0, 0 });
}

//한 가운데 센터 + @좌표
void GameEngineImage::BitCopyCenterPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
	BitCopy(_Other, _CopyPos - _Other->GetScale().Half() + _CopyPivot, _Other->GetScale(), float4{ 0, 0 });
}

//캐릭터 바닥 가운데가 센터
void GameEngineImage::BitCopyBot(GameEngineImage* _Other, const float4& _CopyPos)
{
	float4 ImagePivot = _Other->GetScale().Half();

	ImagePivot.y = _Other->GetScale().y;

	BitCopy(_Other, _CopyPos - ImagePivot, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyBotPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
	float4 ImagePivot = _Other->GetScale().Half();

	ImagePivot.y = _Other->GetScale().y;

	BitCopy(_Other, _CopyPos - ImagePivot + _CopyPivot, _Other->GetScale(), float4{0, 0});
}


void GameEngineImage::BitCopy(GameEngineImage* _Other)
{
	BitCopy(_Other, { 0, 0 }, _Other->GetScale(), { 0, 0 });
}


void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyScale, const float4& _OtherPivot)
{
	BitBlt(
		ImageDC_,	//여기에 복사해라
		_CopyPos.ix(),	//띄울 이미지 좌표x
		_CopyPos.iy(),	//띄울 이미지 좌표y
		_CopyScale.ix(),	//내 이미지의 x크기만큼
		_CopyScale.iy(),	//내 이미지의 y크기만큼
		_Other->ImageDC_,	//복사하려는 대상은
		_OtherPivot.ix(),	//복사하려는 대상의 시작점 x(어느 부분 복사할건지)
		_OtherPivot.iy(),	//복사하려는 대상의 시작점 y(어느 부분 복사할건지)
		SRCCOPY	//복사(윈도우 기능)
	);
}


//////////////////////////////////////////////////////////////////////Trans



void GameEngineImage::TransCopy(GameEngineImage* _Other, 
	const float4& _CopyPos, 
	const float4& _CopyScale, 
	const float4& _OtherPivot, 
	const float4 _OtherScale, 
	unsigned int _TransColor)
{
	TransparentBlt(
		ImageDC_,	//여기에 복사해라(이 창에 그려라)
		_CopyPos.ix(),	//띄울 이미지 좌표x
		_CopyPos.iy(),	//띄울 이미지 좌표y(여기서 부터 그려라)
		_CopyScale.ix(),	//내 이미지의 x크기만큼
		_CopyScale.iy(),	//내 이미지의 y크기만큼(이 크기만큼 그려라)
		_Other->ImageDC_,	//복사하려는 대상은
		_OtherPivot.ix(),	//복사하려는 대상의 시작점 x(어느 부분 복사할건지)
		_OtherPivot.iy(),	//복사하려는 대상의 시작점 y(어느 부분 복사할건지)
		_OtherScale.ix(),	//복사하려는 대상의 시작점 x(어느 부분 복사할건지)
		_OtherScale.iy(),
		_TransColor	//복사(윈도우 기능)
	);
}

void GameEngineImage::CutCount(int _x, int _y)
{
	float4 Scale = { GetScale().x / _x, GetScale().y / _y };
	Cut(Scale);
}

void GameEngineImage::Cut(const float4& _CutSize)
{
	if (0 != (GetScale().ix() % _CutSize.ix()))
	{
		MsgBoxAssert("자를 수 있는 수치가 딱 맞지 않음(x축)");
	}

	if (0 != (GetScale().iy() % _CutSize.iy()))
	{
		MsgBoxAssert("자를 수 있는 수치가 딱 맞지 않음(y축)");
	}

	int XCount = (GetScale().ix() / _CutSize.ix());
	int YCount = (GetScale().iy() / _CutSize.iy());


	for (int y = 0; y < YCount; y++)
	{
		for (int x = 0; x < XCount; x++)
		{
			CutPivot_.push_back({ static_cast<float>(x * _CutSize.ix()), static_cast<float>(y * _CutSize.iy()) });
			CutScale_.push_back(_CutSize);
		}
	}

}

int GameEngineImage::GetImagePixel(int _x, int _y)
{
	return GetPixel(ImageDC_, _x, _y);
}