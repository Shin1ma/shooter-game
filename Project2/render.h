#pragma once
#include <Windows.h>

class Renderer {
private:
	void *memory;
	int height, width;
	float render_scale = 0.01f;
	BITMAPINFO bitmap_info;
public:

	Renderer(void *mem, int h, int w, float renderscale, BITMAPINFO bitmap) {
		height = h;
		width = w;
		bitmap_info = bitmap;
		render_scale = renderscale;
	}
	Renderer(int h, int w) {
		height = h;
		width = w;
	}

	int GetWidth() { return width; }
	int GetHeight() { return height; }
	float GetRenderScale() { return render_scale; }
	BITMAPINFO Getbitmap_info() { return bitmap_info; }
	void *GetMemory() { return memory; }

	void SetWidth(int w) { width = w; }
	void SetHeight(int h) { height = h; }
	void SetRenderScale(float render) { render_scale = render; }
	void Setbitmap_info(BITMAPINFO bitmap) { bitmap_info = bitmap; }
	void SetMemory(void *mem) { memory = mem; }

	void ClearScreen(unsigned int color) {
		unsigned int *pixel = (unsigned int*)memory;
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				*pixel++ = color;
			}
		}
	}



	void DrawRectPixels(int x0, int y0, int x1, int y1, unsigned int color) {
		x0 = clamp(0, x0, width);
		x1 = clamp(0, x1, width);
		y0 = clamp(0, y0, height);
		y1 = clamp(0, y1, height);
		for (int y = y0; y < y1; y++) {
			unsigned int *pixel = (unsigned int*)memory + x0 + y * width;
			for (int x = x0; x < x1; x++) {
				*pixel++ = color;
			}
		}
	}

	void DrawRect(float x, float y, float halfsizex, float halfsizey, unsigned int color) {
		x *= height * render_scale;
		y *= height * render_scale;
		halfsizex *= height * render_scale;
		halfsizey *= height * render_scale;

		x += width / 2.f;
		y += height / 2.f;

		int x0 = x - halfsizex;
		int x1 = x + halfsizex;
		int y0 = y - halfsizey;
		int y1 = y + halfsizey;


		DrawRectPixels(x0, y0, x1, y1, color);
	}
};
