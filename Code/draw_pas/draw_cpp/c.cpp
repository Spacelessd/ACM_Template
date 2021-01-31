#include <windows.h> 

HINSTANCE hInst; 
HWND hWnd; 

ATOM MyRegisterClass(HINSTANCE hInstance); 
BOOL InitInstance(HINSTANCE, int); 
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); 

int APIENTRY WinMain(HINSTANCE hInstance, 
HINSTANCE hPrevInstance, 
LPSTR lpCmdLine, 
int nCmdShow) 
{ 
MSG msg; 

MyRegisterClass(hInstance); 


if (!InitInstance (hInstance, nCmdShow)) 
{ 
return FALSE; 
} 


while( msg.message!=WM_QUIT ) 
{ 
if( PeekMessage( &msg, NULL, 0,0 ,PM_REMOVE) ) 
{ 
TranslateMessage( &msg ); 
DispatchMessage( &msg ); 
} 
else 
{ 

} 
} 

return msg.wParam; 
} 


ATOM MyRegisterClass(HINSTANCE hInstance) 
{ 
WNDCLASSEX wcex; 

wcex.cbSize = sizeof(WNDCLASSEX); 
wcex.style = CS_HREDRAW | CS_VREDRAW; 
wcex.lpfnWndProc = (WNDPROC)WndProc; 
wcex.cbClsExtra = 0; 
wcex.cbWndExtra = 0; 
wcex.hInstance = hInstance; 
wcex.hIcon = NULL; 
wcex.hCursor = NULL; 
wcex.hCursor = LoadCursor(NULL, IDC_ARROW); 
wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); 
wcex.lpszMenuName = NULL; 
wcex.lpszClassName = "canvas"; 
wcex.hIconSm = NULL; 

return RegisterClassEx(&wcex); 
} 


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) 
{ 
hInst = hInstance; 

hWnd = CreateWindow("canvas", "Բ" , WS_OVERLAPPEDWINDOW, 
CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL); 

if (!hWnd) 
{ 
return FALSE; 
} 

MoveWindow(hWnd,10,10,640,480,true); 
ShowWindow(hWnd, nCmdShow); 
UpdateWindow(hWnd); 

return TRUE; 
} 


/*

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{ 
HDC hdc; 
PAINTSTRUCT ps; 
switch (message) 
{ 

case WM_PAINT: 
hdc = BeginPaint( hWnd,&ps); 
Arc( hdc,100,100,200,200,0,0,0,0 ); 
EndPaint( hWnd,&ps); 
break; 
case WM_DESTROY: 
PostQuitMessage(0); 
break; 
default: 
return DefWindowProc(hWnd, message, wParam, lParam); 
} 
return 0; 
}*/
int main(){
}
