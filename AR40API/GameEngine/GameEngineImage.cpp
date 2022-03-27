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

void GameEngineImage::ImageScaleCheck()
{
	//DC ���ο� �����ִ� BITMAP�� �������� �Լ�
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
