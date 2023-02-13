#define isdown(b) input->buttons[b].isdown
#define pressed(b) (input->buttons[b].isdown && input->buttons[b].changed)
#define realeased(b) (!input->buttons[b].isdown && input->buttons[b].changed)




float y_player_pos, player_dp;

 bool shoot(float y_Pos, float x_Pos, float y_halfsize, float x_halfsize, bool negative, unsigned int color, float delta, float dp) {
	x_Pos += dp * delta;
		if (negative) {
			render_state.DrawRect(x_Pos + x_halfsize + 2.f, y_Pos, 1, 1, color);
			dp *= 1;
			return true;
		}
		else {
			render_state.DrawRect(x_Pos - x_halfsize + 1.f, y_Pos, 1, 1, color);
			dp *= -1;
			return true;
		}
}

 static void Simulate_game(input *input, float delta) {
	bool generated;
	//player movement
	bool IsDown;
	float x_player_pos = -80.f;
	float xplayer_half_size = 2.f;
	float yplayer_half_size = 4.f;
	float mult = 1;
	float player_ddp = 0.f;
	render_state.ClearScreen(0x707070);
	if (isdown(BUTTON_Z)) { mult = 2; }
	if (isdown(BUTTON_UP)) { player_ddp += 200 * mult; IsDown = true;}
	if (isdown(BUTTON_DOWN)) player_ddp -= 200 * mult;
	if (y_player_pos + yplayer_half_size > 50.f - 2.5f) {
		y_player_pos -= 0.1;
		player_dp = 0;
	}
	else if (y_player_pos - yplayer_half_size < -50.f + 2.5f) {
		y_player_pos += 0.1;
		player_dp = 0;
	}
	else {
		y_player_pos = y_player_pos + player_dp * delta + player_ddp * delta * delta * .5f;
		player_dp = player_dp + player_ddp * delta;
	}
	IsDown = false;

	render_state.DrawRect(x_player_pos, y_player_pos, xplayer_half_size, yplayer_half_size, 0xFF0F0);
	render_state.DrawRect(x_player_pos, y_player_pos, xplayer_half_size, yplayer_half_size, 0xFF0F0);

	if (pressed(BUTTON_SPACE)) { generated = shoot(y_player_pos, x_player_pos, yplayer_half_size, xplayer_half_size, true, 0xFFFF00, delta, 100); }
	//if (generated){}
}

static void Draw_map() {
	render_state.DrawRect(-93.f, 0.f, 4, 100.5, 0xFFFFFF);
	render_state.DrawRect(0.f, 50.f, 100.5, 2.5, 0xFFFFFF);
	render_state.DrawRect(0.f, -50.f, 100.5, 2.5, 0xFFFFFF);
	render_state.DrawRect(40.f, 0.f, 10, 10, 0xFF0000);
	render_state.DrawRect(30.f, 30.f, 5, 5, 0x00FF00);
	render_state.DrawRect(30.f, -30.f, 5, 5, 0xFFA500);
}

