//exe�� ������� �ʿ䰡 ���� "���̺귯�� ������Ʈ"

#include "GameEngineWindow.h"
#include "GameEngineDebug.h"

//HWND hWnd � �����쿡 �������� ������� �� �������� �ڵ�
//UINT messange �� �޼����� ������ ����
//WPARAM wParam
//LPARAM lParam

LRESULT CALLBACK MessageProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
     case WM_DESTROY:
        //�����츦 �����ϰ� ���α׷��� ����(â�� �����ٰ� ���α׷��� �����°� �ƴϴ�)
        GameEngineWindow::GetInst().Off();
        return DefWindowProc(hWnd, message, wParam, lParam);

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        //TODO: ���⿡ hdc�� ����ϴ� �׸��� �ڵ� �߰�
        EndPaint(hWnd, &ps);
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    default:
        break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}


GameEngineWindow* GameEngineWindow::Inst_ = new GameEngineWindow();

GameEngineWindow::GameEngineWindow()
    : hInst_(nullptr)//���� ���� �����찡 ��������� null
    , hWnd_(nullptr)//���� ���� �����찡 ��������� null
    , WindowOn_(true)//������ �������ϱ� ���۽� true
    , HDC_(nullptr)
{

}

GameEngineWindow::~GameEngineWindow()
{
    //���� ������ذ� �ƴ϶�� �� �����ش�
    if (nullptr != HDC_)
    {
        ReleaseDC(hWnd_, HDC_);
        HDC_ = nullptr;
    }
    
    if (nullptr != hWnd_)
    {
        DestroyWindow(hWnd_);
        hWnd_ = nullptr;
    }
}

void GameEngineWindow::Off()
{
    WindowOn_ = false;
}

void GameEngineWindow::RegClass(HINSTANCE _hInst)
{
    //������ Ŭ���� ���
    WNDCLASSEXA wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = MessageProcess;//�������� �������� �� �ൿ�� ����(=�Լ�������[�ݹ���])
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInst;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "GameEngineWindowClass";
    wcex.hIconSm = nullptr;

    RegisterClassExA(&wcex);
}

void GameEngineWindow::CreateGameWindow(HINSTANCE _hInst, const std::string& _Title)
{
    //Ŭ������ ����(Ŭ���� ����� 1���� �Ϸ��� ģ �ڵ�)
    //����ڵ�(Ȥ�ó��� ��츦 ���)
    if(nullptr != hInst_)
    {   //�̹� hInst_�� ������� �ִٸ� �н�
        //(����â ������ ���� �ƴϴϱ�)
        MsgBoxAssert("������ �ι����� ��");
        return;
    }

    Title_ = _Title;
    //Ŭ���� ����� �ѹ��� �Ϸ��� ���� �ڵ�
    hInst_ = _hInst;
    RegClass(_hInst);

    //Ŭ������ ��ü�� ����
    //�����찡 ����� ������
    hWnd_ = CreateWindowExA(0L, "GameEngineWindowClass", Title_.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInst, nullptr);

    //ȭ�鿡 ���𰡸� �׸��� ���� �ڵ�(�׸��� ������ ���´�)
    HDC_ = GetDC(hWnd_);

    if (!hWnd_)
    {
        return;
    }
}

void GameEngineWindow::ShowGameWindow()
{
    //���ó� ����ڵ�
    if (nullptr == hWnd_)
    {
        MsgBoxAssert("���� �����찡 �ȸ������ ȭ����� �Ұ�");
        return;
    }
    
    //ȣ��Ǳ� ������ �׸��� ����
    ShowWindow(hWnd_, SW_SHOW);
    UpdateWindow(hWnd_);
    //�� �������� �׷��� ����
}

void GameEngineWindow::MessageLoop(void(*_InitFunction)(), void(*_LoopFunction)())
{
    //������� �� �غ�Ǿ� �ְ�
    //���� ���� �� �Ұ� �ִٸ� �غ��Լ��� ����
    if (nullptr != _InitFunction)
    {
        _InitFunction();
    }

    MSG msg;
    //������ ���ο����� ������ ������
    //std::list<MSG> MessageQueue; �� �ִ�
    //�޼����� ó���ߴٸ� MessagneQueue.clear();

    //���� �ȴٴ°� �� while���� �����ٴ� ��
    while (WindowOn_)
    {

        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //�츮������ ���� �ȿ��� �����
        //���⿡�� ������ ���ư��� ������ �ȴٴ� ��

        if (nullptr == _LoopFunction)
        {
            continue;
        }

        _LoopFunction();
    }
}

void GameEngineWindow::SetWindowScaleAndPosition(float4 _Pos, float4 _Scale)
{
    RECT Rc = {0, 0, _Scale.ix(), _Scale.iy() };
    
    //�޴��� ���� ������ ����ؼ� �����ָ� �ű⿡ ���� ����� �����
    //�޴��ٿ� �޴��ɼ� �ȶ��Ŵϱ� FALSE
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    Scale_ = _Scale;//����� �˾ƿ´�

    //1280 + �޴���
    
    //â ������ ����(��¥[����])
    SetWindowPos(hWnd_, nullptr,_Pos.ix(), _Pos.iy(), Rc. right - Rc.left, Rc.bottom - Rc.top, SWP_NOZORDER);


}