struct BUTTON_STATE {
	bool isdown;
	bool changed;
};

enum {
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_Z,
	BUTTON_SPACE,

	BUTTON_COUNT,
};

struct input {
	BUTTON_STATE buttons[BUTTON_COUNT];
};