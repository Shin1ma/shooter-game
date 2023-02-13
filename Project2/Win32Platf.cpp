#include "utility.cpp"
#include "render.h"
#include <Windows.h>

static bool running = true;



static Renderer render_state(0, 0);

BITMAPINFO bitmap_info = render_state.Getbitmap_info();


#include "platform_common.cpp"
#include "game.cpp"




LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;
	
	switch (uMsg)
	{
	case WM_CLOSE:
	case WM_DESTROY: {
		running = false;
	}
	break;
	case WM_SIZE: {
		RECT rect;
		GetClientRect(hwnd, &rect);
		render_state.SetWidth(rect.right - rect.left);
		render_state.SetHeight(rect.bottom - rect.top);

		int buffer_size = render_state.GetWidth() * render_state.GetHeight() * sizeof(unsigned int);
		if (render_state.GetMemory() != NULL) { 
			VirtualFree(render_state.GetMemory(), 0, MEM_RELEASE); }
		render_state.SetMemory(VirtualAlloc(0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE));


		bitmap_info.bmiHeader.biSize = sizeof(render_state.Getbitmap_info().bmiHeader);
		bitmap_info.bmiHeader.biWidth = render_state.GetWidth();
		bitmap_info.bmiHeader.biHeight = render_state.GetHeight();
		bitmap_info.bmiHeader.biPlanes = 1;
		bitmap_info.bmiHeader.biBitCount = 32;
		bitmap_info.bmiHeader.biCompression = BI_RGB;
		render_state.Setbitmap_info(bitmap_info);
	}break;

	default:
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	
	return result;
}


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {



	//creating window object
	WNDCLASS window_class = { };
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = "Game window";
	window_class.lpfnWndProc = window_callback;
	//registering the object
	RegisterClass(&window_class);
	//creating the object
	HWND window = CreateWindow(window_class.lpszClassName, "first window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	input input = {};

	float delta_time = 0.01666666f;
	LARGE_INTEGER frame_begin;
	QueryPerformanceCounter(&frame_begin);

	float perdormance_frequency;
	{
		LARGE_INTEGER perf;
		QueryPerformanceFrequency(&perf);
		perdormance_frequency = (float)perf.QuadPart;
	}

	

	while (running) {
		// Input
		MSG message;
		HDC hdc = GetDC(window);

		for (int i = 0; i < BUTTON_COUNT; i++) {
			input.buttons[i].changed = false;
		}

		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {

			switch (message.message) {
			case WM_KEYUP:
			case WM_KEYDOWN: {
				unsigned int vk_code = (unsigned int)message.wParam;
				bool is_down = ((message.lParam & (1 << 31)) == 0);

#define process_button(b, vk)\
case vk: {\
input.buttons[b].changed = is_down != input.buttons[b].isdown;\
input.buttons[b].isdown = is_down;\
} break;

				switch (vk_code) {
					process_button(BUTTON_UP, VK_UP);
					process_button(BUTTON_DOWN, VK_DOWN);
					process_button(BUTTON_LEFT, VK_LEFT);
					process_button(BUTTON_RIGHT, VK_RIGHT);
					process_button(BUTTON_Z, 0x5A);
					process_button(BUTTON_SPACE, VK_SPACE);
				}
			} break;

			default: {
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
			}

		}		 //simulate
					 Simulate_game(&input, delta_time);
					 Draw_map();

					 //render
					 BITMAPINFO bitmap = render_state.Getbitmap_info();
					 StretchDIBits(hdc, 0, 0, render_state.GetWidth(), render_state.GetHeight(), 0, 0, render_state.GetWidth(), render_state.GetHeight(), render_state.GetMemory(), &bitmap, DIB_RGB_COLORS, SRCCOPY);
					 LARGE_INTEGER frame_end;
					 QueryPerformanceCounter(&frame_end);
					 delta_time = (float)(frame_end.QuadPart - frame_begin.QuadPart) / perdormance_frequency;
					 frame_begin = frame_end;
			}
		}


