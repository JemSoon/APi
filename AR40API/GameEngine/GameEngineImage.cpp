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
	//window���� �Ҵ��ؿ� �༮���� ������ üũ�� �ȵ�����
	//�����ִ°� ����ϴ�
	//�翬�� �����쿡�� �Ҵ��� �����Ƿ� �Լ��� �̿��ؼ� ������ �Ѵ�

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
		MsgBoxAssert("ũ�Ⱑ 0 �� �̹��� ���۽�Ŵ")
		return false;
	}

	//���� ��Ʈ���� �����
	//�̹��� ũ�� ����
	BitMap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _Scale.ix(), _Scale.iy());
	
	//������� ����
	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("ImageDC ���� ����");
	}

	//Bit���� DC�� �ٲ���(�ݴ��ΰ�?)
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
		MsgBoxAssertString(_Path + "�̹��� �ε忡 ���� - ��� Ȯ��, ����� üũ ���");
	}

	//���̹��� ����� ��ü�ϴ� ����
	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("ImageDC ���� ����");
	}

	//Bit���� DC�� �ٲ���(�ݴ��ΰ�?)
	OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	ImageScaleCheck();

	return true;
}

void GameEngineImage::ImageScaleCheck()
{
	//DC ���ο� �����ִ� BITMAP�� �������� �Լ�
	HBITMAP CurrentBitMap = (HBITMAP)GetCurrentObject(ImageDC_, OBJ_BITMAP);
	GetObject(CurrentBitMap, sizeof(BITMAP), &Info_);
}

void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos)
{
	BitCopy(_Other, _CopyPos, float4{ 0, 0 }, _Other->GetScale());
}

//ĳ���� �̹����� �� ����� ����
void GameEngineImage::BitCopyCenter(GameEngineImage* _Other, const float4& _CopyPos)
{
	BitCopy(_Other, _CopyPos - _Other->GetScale().Half(), float4{ 0, 0 }, _Other->GetScale());
}

//�� ��� ���� + @��ǥ
void GameEngineImage::BitCopyCenterPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
	BitCopy(_Other, _CopyPos - _Other->GetScale().Half() + _CopyPivot, float4{ 0, 0 }, _Other->GetScale());
}

//ĳ���� �ٴ� ����� ����
void GameEngineImage::BitCopyBot(GameEngineImage* _Other, const float4& _CopyPos)
{
	float4 ImagePivot = _Other->GetScale().Half();

	ImagePivot.y = _Other->GetScale().y;

	BitCopy(_Other, _CopyPos - ImagePivot, float4{ 0, 0 }, _Other->GetScale());
}

void GameEngineImage::BitCopyBotPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
	float4 ImagePivot = _Other->GetScale().Half();

	ImagePivot.y = _Other->GetScale().y;

	BitCopy(_Other, _CopyPos - ImagePivot + _CopyPivot, float4{0, 0}, _Other->GetScale());
}


void GameEngineImage::BitCopy(GameEngineImage* _Other)
{
	BitCopy(_Other, { 0, 0 }, { 0, 0 }, _Other->GetScale());
}


void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _OtherPivot, const float4& _OtherPivotScale)
{
	BitBlt(
		ImageDC_,	//���⿡ �����ض�
		_CopyPos.ix(),	//��� �̹��� ��ǥx
		_CopyPos.iy(),	//��� �̹��� ��ǥy
		_OtherPivotScale.ix(),	//�� �̹����� xũ�⸸ŭ
		_OtherPivotScale.iy(),	//�� �̹����� yũ�⸸ŭ
		_Other->ImageDC_,	//�����Ϸ��� �����
		_OtherPivot.ix(),	//�����Ϸ��� ����� ������ x(��� �κ� �����Ұ���)
		_OtherPivot.iy(),	//�����Ϸ��� ����� ������ y(��� �κ� �����Ұ���)
		SRCCOPY	//����(������ ���)
	);
}
