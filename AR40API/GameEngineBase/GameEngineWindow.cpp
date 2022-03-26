//exe가 만들어질 필요가 없는 "라이브러리 프로젝트"

#include "GameEngineWindow.h"
#include "GameEngineDebug.h"

//HWND hWnd 어떤 윈도우에 무슨일이 생겼는지 그 윈도우의 핸들
//UINT messange 그 메세지의 종류가 뭔지
//WPARAM wParam
//LPARAM lParam

LRESULT CALLBACK MessageProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
     case WM_DESTROY:
        //윈도우를 종료하고 프로그램도 종료(창이 꺼진다고 프로그램이 꺼지는게 아니다)
        GameEngineWindow::GetInst().Off();
        return DefWindowProc(hWnd, message, wParam, lParam);

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        //TODO: 여기에 hdc를 사용하는 그리기 코드 추가
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
    : hInst_(nullptr)//게임 엔진 윈도우가 만들어질때 null
    , hWnd_(nullptr)//게임 엔진 윈도우가 만들어질때 null
    , WindowOn_(true)//게임이 켜졌으니까 시작시 true
    , HDC_(nullptr)
{

}

GameEngineWindow::~GameEngineWindow()
{
    //내가 만들어준게 아니라면 다 지워준다
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
    //윈도우 클래스 등록
    WNDCLASSEXA wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = MessageProcess;//무슨일이 생겼을때 이 행동을 해줘(=함수포인터[콜백방식])
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
    //클래스를 만듦(클래스 등록은 1번만 하려고 친 코드)
    //방어코드(혹시나의 경우를 대비)
    if(nullptr != hInst_)
    {   //이미 hInst_가 만들어져 있다면 패스
        //(게임창 여러개 띄울거 아니니까)
        MsgBoxAssert("윈도우 두번띄우려 함");
        return;
    }

    Title_ = _Title;
    //클래스 등록은 한번만 하려고 만든 코드
    hInst_ = _hInst;
    RegClass(_hInst);

    //클래스로 객체를 만듦
    //윈도우가 만들어 지는일
    hWnd_ = CreateWindowExA(0L, "GameEngineWindowClass", Title_.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInst, nullptr);

    //화면에 무언가를 그리기 위한 핸들(그리는 권한을 얻어온다)
    HDC_ = GetDC(hWnd_);

    if (!hWnd_)
    {
        return;
    }
}

void GameEngineWindow::ShowGameWindow()
{
    //역시나 방어코드
    if (nullptr == hWnd_)
    {
        MsgBoxAssert("메인 윈도우가 안만들어짐 화면출력 불가");
        return;
    }
    
    //호출되기 전까진 그릴수 없다
    ShowWindow(hWnd_, SW_SHOW);
    UpdateWindow(hWnd_);
    //이 다음부터 그러기 가능
}

void GameEngineWindow::MessageLoop(void(*_InitFunction)(), void(*_LoopFunction)())
{
    //윈도우는 다 준비되어 있고
    //루프 돌기 전 할게 있다면 준비함수를 실행
    if (nullptr != _InitFunction)
    {
        _InitFunction();
    }

    MSG msg;
    //윈도우 내부에서는 보이지 않지만
    //std::list<MSG> MessageQueue; 가 있다
    //메세지를 처리했다면 MessagneQueue.clear();

    //종료 된다는건 이 while문을 나간다는 것
    while (WindowOn_)
    {

        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        //우리게임은 여기 안에서 만든다
        //여기에서 뭔가가 돌아가야 게임이 된다는 것

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
    
    //메뉴바 등의 설정을 고려해서 만져주면 거기에 맞춰 사이즈를 잡아줌
    //메뉴바에 메뉴옵션 안띄울거니까 FALSE
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    Scale_ = _Scale;//사이즈를 알아온다

    //1280 + 메뉴바
    
    //창 사이즈 설정(진짜[강제])
    SetWindowPos(hWnd_, nullptr,_Pos.ix(), _Pos.iy(), Rc. right - Rc.left, Rc.bottom - Rc.top, SWP_NOZORDER);


}