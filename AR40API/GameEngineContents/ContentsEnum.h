#pragma once
enum class ORDER //�̹��� �ö� ���� ����
{
	BACKGROUND,
	MONSTER,
	ITEM,
	BOX,
	PLAYER,
	UI
};

enum class MARIOstate
{
	Small,
	Big,
	White
};

enum class PlayerDir
{
	Start,
	Left,
	Right
};

enum class ItemType
{
	Mushroom,
	Fireflower,
	Star,
	UP
};