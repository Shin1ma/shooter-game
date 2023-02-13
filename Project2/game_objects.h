#pragma once
class Game_Objects {
private:
	float y_pos;
	float x_pos;
	float y_halfsize;
	float x_halfsize;

public:
	Game_Objects(float x, float y, float xSiz, float ySiz) {
		y_pos = y;
		x_pos = x;
		y_halfsize = ySiz;
		x_halfsize = xSiz;
	}
	float GetY() { return y_pos; }
	float GetX() { return x_pos; }
	float GetYSize() { return y_halfsize; }
	float GetXSize() { return x_halfsize; }
	void setY(int n) { y_pos = n; }
	void setX(int n) { x_pos = n; }
	void setYSize(int n) { y_halfsize = n; }
	void setXSize(int n) { x_halfsize = n; }
};

class Moving_Object : public Game_Objects {
private:
	float obj_DP;
	float obj_DDP;

public:
};
