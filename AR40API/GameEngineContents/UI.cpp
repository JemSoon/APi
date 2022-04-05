#include "UI.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

UI::UI()
{

}

UI::~UI()
{

}

void UI::Start()
{
	{	//�ش� �̹����� ȭ�� �߰��� ���´�
		float4 Pos = GameEngineWindow::GetScale().Half();
		SetPosition(Pos);
	}

	{	//ȭ�� ui������ �����
		GameEngineRenderer* Renderer = CreateRenderer("UI-Test.bmp");
		
		//Renderer->GetImage();

		float4 UIPivot = GameEngineWindow::GetScale().Half();
		UIPivot.x = 0.0f;
		UIPivot.y = -333.0f;// Renderer->GetImage()->GetScale().Half().y;//�� �Ʒ��� ����

		Renderer->SetPivot(UIPivot);
	}
	//Pos.y *= 2.0f;

	//SetScale(GameEngineWindow::GetScale());
}

