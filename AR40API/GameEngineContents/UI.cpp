#include "UI.h"

UI::UI()
{

}

UI::~UI()
{

}

void UI::Start()
{
	//UI위치 잡기
	SetPosition({640, 0 });
	SetScale({ 1280, 200 });
}

void UI::Render()
{
	DebugRectRender();
}