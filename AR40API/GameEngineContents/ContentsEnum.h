#pragma once
enum class ORDER //이미지 올라갈 순서 설정
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

enum class ItemType
{
	Mushroom,
	Fireflower,
	Star,
	UP
};