#pragma once
enum class ORDER //이미지 올라갈 순서 설정
{
	BACKGROUND,
	MONSTER,
	ITEM,
	BOX,
	EMPTYBOX,
	PLAYER,
	UI
};

enum class ItemType
{
	Mushroom,
	Fireflower,
	Star,
	UP
};

enum class PlayerType
{
	Small,
	Big,
	White
};