#pragma once
GLfloat axes[4][2];
GLfloat axes_color[3] = { 0.0f, 0.0f, 0.0f };
GLuint VBO_axes, VAO_axes;

void prepare_axes(void) { // Draw axes in their MC.
	axes[0][0] = -win_width / 2.5f; axes[0][1] = 0.0f;
	axes[1][0] = win_width / 2.5f; axes[1][1] = 0.0f;
	axes[2][0] = 0.0f; axes[2][1] = -win_height / 2.5f;
	axes[3][0] = 0.0f; axes[3][1] = win_height / 2.5f;

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_axes);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_axes);
	glBufferData(GL_ARRAY_BUFFER, sizeof(axes), axes, GL_STATIC_DRAW);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_axes);
	glBindVertexArray(VAO_axes);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_axes);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void update_axes(void) {
	axes[0][0] = -win_width / 3.0f; axes[1][0] = win_width / 3.0f;
	axes[2][1] = -win_height / 3.0f;
	axes[3][1] = win_height / 3.0f;

	glBindBuffer(GL_ARRAY_BUFFER, VBO_axes);
	glBufferData(GL_ARRAY_BUFFER, sizeof(axes), axes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void draw_axes(void) {
	glUniform3fv(loc_primitive_color, 1, axes_color);
	glBindVertexArray(VAO_axes);
	glDrawArrays(GL_LINES, 0, 4);
	glBindVertexArray(0);
}

#define AIRPLANE_BIG_WING 0
#define AIRPLANE_SMALL_WING 1
#define AIRPLANE_BODY 2
#define AIRPLANE_BACK 3
#define AIRPLANE_SIDEWINDER1 4
#define AIRPLANE_SIDEWINDER2 5
#define AIRPLANE_CENTER 6
GLfloat big_wing[6][2] = { { 0.0, 0.0 }, { -20.0, 15.0 }, { -20.0, 20.0 }, { 0.0, 23.0 }, { 20.0, 20.0 }, { 20.0, 15.0 } };
GLfloat small_wing[6][2] = { { 0.0, -18.0 }, { -11.0, -12.0 }, { -12.0, -7.0 }, { 0.0, -10.0 }, { 12.0, -7.0 }, { 11.0, -12.0 } };
GLfloat body[5][2] = { { 0.0, -25.0 }, { -6.0, 0.0 }, { -6.0, 22.0 }, { 6.0, 22.0 }, { 6.0, 0.0 } };
GLfloat back[5][2] = { { 0.0, 25.0 }, { -7.0, 24.0 }, { -7.0, 21.0 }, { 7.0, 21.0 }, { 7.0, 24.0 } };
GLfloat sidewinder1[5][2] = { { -20.0, 10.0 }, { -18.0, 3.0 }, { -16.0, 10.0 }, { -18.0, 20.0 }, { -20.0, 20.0 } };
GLfloat sidewinder2[5][2] = { { 20.0, 10.0 }, { 18.0, 3.0 }, { 16.0, 10.0 }, { 18.0, 20.0 }, { 20.0, 20.0 } };
GLfloat center[1][2] = { { 0.0, 0.0 } };
GLfloat airplane_color[7][3] = {
	{ 150 / 255.0f, 129 / 255.0f, 183 / 255.0f },  // big_wing
	{ 245 / 255.0f, 211 / 255.0f,   0 / 255.0f },  // small_wing
	{ 111 / 255.0f,  85 / 255.0f, 157 / 255.0f },  // body
	{ 150 / 255.0f, 129 / 255.0f, 183 / 255.0f },  // back
	{ 245 / 255.0f, 211 / 255.0f,   0 / 255.0f },  // sidewinder1
	{ 245 / 255.0f, 211 / 255.0f,   0 / 255.0f },  // sidewinder2
	{ 255 / 255.0f,   0 / 255.0f,   0 / 255.0f }   // center
};

GLuint VBO_airplane, VAO_airplane;

#define AIRPLANE_ROTATION_RADIUS 200.0f
float airplane_s_factor = 1.0f;

void prepare_airplane() {
	GLsizeiptr buffer_size = sizeof(big_wing) + sizeof(small_wing) + sizeof(body) + sizeof(back)
		+ sizeof(sidewinder1) + sizeof(sidewinder2) + sizeof(center);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_airplane);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_airplane);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(big_wing), big_wing);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(big_wing), sizeof(small_wing), small_wing);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(big_wing) + sizeof(small_wing), sizeof(body), body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(big_wing) + sizeof(small_wing) + sizeof(body), sizeof(back), back);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(big_wing) + sizeof(small_wing) + sizeof(body) + sizeof(back),
		sizeof(sidewinder1), sidewinder1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(big_wing) + sizeof(small_wing) + sizeof(body) + sizeof(back)
		+ sizeof(sidewinder1), sizeof(sidewinder2), sidewinder2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(big_wing) + sizeof(small_wing) + sizeof(body) + sizeof(back)
		+ sizeof(sidewinder1) + sizeof(sidewinder2), sizeof(center), center);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_airplane);
	glBindVertexArray(VAO_airplane);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_airplane);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_airplane() { // Draw airplane in its MC.
	glBindVertexArray(VAO_airplane);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_BIG_WING]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_SMALL_WING]);
	glDrawArrays(GL_TRIANGLE_FAN, 6, 6);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 5);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_BACK]);
	glDrawArrays(GL_TRIANGLE_FAN, 17, 5);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_SIDEWINDER1]);
	glDrawArrays(GL_TRIANGLE_FAN, 22, 5);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_SIDEWINDER2]);
	glDrawArrays(GL_TRIANGLE_FAN, 27, 5);

	glUniform3fv(loc_primitive_color, 1, airplane_color[AIRPLANE_CENTER]);
	glPointSize(5.0);
	glDrawArrays(GL_POINTS, 32, 1);
	glPointSize(1.0);
	glBindVertexArray(0);
}

//house
#define HOUSE_ROOF 0
#define HOUSE_BODY 1
#define HOUSE_CHIMNEY 2
#define HOUSE_DOOR 3
#define HOUSE_WINDOW 4

GLfloat roof[3][2] = { { -12.0, 0.0 },{ 0.0, 12.0 },{ 12.0, 0.0 } };
GLfloat house_body[4][2] = { { -12.0, -14.0 },{ -12.0, 0.0 },{ 12.0, 0.0 },{ 12.0, -14.0 } };
GLfloat chimney[4][2] = { { 6.0, 6.0 },{ 6.0, 14.0 },{ 10.0, 14.0 },{ 10.0, 2.0 } };
GLfloat door[4][2] = { { -8.0, -14.0 },{ -8.0, -8.0 },{ -4.0, -8.0 },{ -4.0, -14.0 } };
GLfloat window[4][2] = { { 4.0, -6.0 },{ 4.0, -2.0 },{ 8.0, -2.0 },{ 8.0, -6.0 } };

GLfloat house_color[5][3] = {
	{ 200 / 255.0f, 39 / 255.0f, 42 / 255.0f },
	{ 235 / 255.0f, 225 / 255.0f, 196 / 255.0f },
	{ 255 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 233 / 255.0f, 113 / 255.0f, 23 / 255.0f },
	{ 44 / 255.0f, 180 / 255.0f, 49 / 255.0f }
};

GLuint VBO_house, VAO_house;
void prepare_house() {
	GLsizeiptr buffer_size = sizeof(roof) + sizeof(house_body) + sizeof(chimney) + sizeof(door)
		+ sizeof(window);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_house);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_house);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(roof), roof);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(roof), sizeof(house_body), house_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(roof) + sizeof(house_body), sizeof(chimney), chimney);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(roof) + sizeof(house_body) + sizeof(chimney), sizeof(door), door);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(roof) + sizeof(house_body) + sizeof(chimney) + sizeof(door),
		sizeof(window), window);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_house);
	glBindVertexArray(VAO_house);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_house);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_house() {
	glBindVertexArray(VAO_house);

	glUniform3fv(loc_primitive_color, 1, house_color[HOUSE_ROOF]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3);

	glUniform3fv(loc_primitive_color, 1, house_color[HOUSE_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 3, 4);

	glUniform3fv(loc_primitive_color, 1, house_color[HOUSE_CHIMNEY]);
	glDrawArrays(GL_TRIANGLE_FAN, 7, 4);

	glUniform3fv(loc_primitive_color, 1, house_color[HOUSE_DOOR]);
	glDrawArrays(GL_TRIANGLE_FAN, 11, 4);

	glUniform3fv(loc_primitive_color, 1, house_color[HOUSE_WINDOW]);
	glDrawArrays(GL_TRIANGLE_FAN, 15, 4);

	glBindVertexArray(0);
}

//car
#define CAR_BODY 0
#define CAR_FRAME 1
#define CAR_WINDOW 2
#define CAR_LEFT_LIGHT 3
#define CAR_RIGHT_LIGHT 4
#define CAR_LEFT_WHEEL 5
#define CAR_RIGHT_WHEEL 6

GLfloat car_body[4][2] = { { -16.0, -8.0 },{ -16.0, 0.0 },{ 16.0, 0.0 },{ 16.0, -8.0 } };
GLfloat car_frame[4][2] = { { -10.0, 0.0 },{ -10.0, 10.0 },{ 10.0, 10.0 },{ 10.0, 0.0 } };
GLfloat car_window[4][2] = { { -8.0, 0.0 },{ -8.0, 8.0 },{ 8.0, 8.0 },{ 8.0, 0.0 } };
GLfloat car_left_light[4][2] = { { -9.0, -6.0 },{ -10.0, -5.0 },{ -9.0, -4.0 },{ -8.0, -5.0 } };
GLfloat car_right_light[4][2] = { { 9.0, -6.0 },{ 8.0, -5.0 },{ 9.0, -4.0 },{ 10.0, -5.0 } };
GLfloat car_left_wheel[4][2] = { { -10.0, -12.0 },{ -10.0, -8.0 },{ -6.0, -8.0 },{ -6.0, -12.0 } };
GLfloat car_right_wheel[4][2] = { { 6.0, -12.0 },{ 6.0, -8.0 },{ 10.0, -8.0 },{ 10.0, -12.0 } };

GLfloat car_color[7][3] = {
	{ 0 / 255.0f, 149 / 255.0f, 159 / 255.0f },
	{ 0 / 255.0f, 149 / 255.0f, 159 / 255.0f },
	{ 216 / 255.0f, 208 / 255.0f, 174 / 255.0f },
	{ 249 / 255.0f, 244 / 255.0f, 0 / 255.0f },
	{ 249 / 255.0f, 244 / 255.0f, 0 / 255.0f },
	{ 21 / 255.0f, 30 / 255.0f, 26 / 255.0f },
	{ 21 / 255.0f, 30 / 255.0f, 26 / 255.0f }
};

GLuint VBO_car, VAO_car;
void prepare_car() {
	GLsizeiptr buffer_size = sizeof(car_body) + sizeof(car_frame) + sizeof(car_window) + sizeof(car_left_light)
		+ sizeof(car_right_light) + sizeof(car_left_wheel) + sizeof(car_right_wheel);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_car);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_car);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(car_body), car_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car_body), sizeof(car_frame), car_frame);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car_body) + sizeof(car_frame), sizeof(car_window), car_window);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car_body) + sizeof(car_frame) + sizeof(car_window), sizeof(car_left_light), car_left_light);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car_body) + sizeof(car_frame) + sizeof(car_window) + sizeof(car_left_light),
		sizeof(car_right_light), car_right_light);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car_body) + sizeof(car_frame) + sizeof(car_window) + sizeof(car_left_light)
		+ sizeof(car_right_light), sizeof(car_left_wheel), car_left_wheel);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car_body) + sizeof(car_frame) + sizeof(car_window) + sizeof(car_left_light)
		+ sizeof(car_right_light) + sizeof(car_left_wheel), sizeof(car_right_wheel), car_right_wheel);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_car);
	glBindVertexArray(VAO_car);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_car);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_car() {
	glBindVertexArray(VAO_car);

	glUniform3fv(loc_primitive_color, 1, car_color[CAR_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUniform3fv(loc_primitive_color, 1, car_color[CAR_FRAME]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

	glUniform3fv(loc_primitive_color, 1, car_color[CAR_WINDOW]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);

	glUniform3fv(loc_primitive_color, 1, car_color[CAR_LEFT_LIGHT]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);

	glUniform3fv(loc_primitive_color, 1, car_color[CAR_RIGHT_LIGHT]);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);

	glUniform3fv(loc_primitive_color, 1, car_color[CAR_LEFT_WHEEL]);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);

	glUniform3fv(loc_primitive_color, 1, car_color[CAR_RIGHT_WHEEL]);
	glDrawArrays(GL_TRIANGLE_FAN, 24, 4);

	glBindVertexArray(0);
}

//draw car2
#define CAR2_BODY 0
#define CAR2_FRONT_WINDOW 1
#define CAR2_BACK_WINDOW 2
#define CAR2_FRONT_WHEEL 3
#define CAR2_BACK_WHEEL 4
#define CAR2_LIGHT1 5
#define CAR2_LIGHT2 6

GLfloat car2_body[8][2] = { { -18.0, -7.0 },{ -18.0, 0.0 },{ -13.0, 0.0 },{ -10.0, 8.0 },{ 10.0, 8.0 },{ 13.0, 0.0 },{ 18.0, 0.0 },{ 18.0, -7.0 } };
GLfloat car2_front_window[4][2] = { { -10.0, 0.0 },{ -8.0, 6.0 },{ -2.0, 6.0 },{ -2.0, 0.0 } };
GLfloat car2_back_window[4][2] = { { 0.0, 0.0 },{ 0.0, 6.0 },{ 8.0, 6.0 },{ 10.0, 0.0 } };
GLfloat car2_front_wheel[8][2] = { { -11.0, -11.0 },{ -13.0, -8.0 },{ -13.0, -7.0 },{ -11.0, -4.0 },{ -7.0, -4.0 },{ -5.0, -7.0 },{ -5.0, -8.0 },{ -7.0, -11.0 } };
GLfloat car2_back_wheel[8][2] = { { 7.0, -11.0 },{ 5.0, -8.0 },{ 5.0, -7.0 },{ 7.0, -4.0 },{ 11.0, -4.0 },{ 13.0, -7.0 },{ 13.0, -8.0 },{ 11.0, -11.0 } };
GLfloat car2_light1[3][2] = { { -18.0, -1.0 },{ -17.0, -2.0 },{ -18.0, -3.0 } };
GLfloat car2_light2[3][2] = { { -18.0, -4.0 },{ -17.0, -5.0 },{ -18.0, -6.0 } };

GLfloat car2_color[7][3] = {
	{ 100 / 255.0f, 141 / 255.0f, 159 / 255.0f },
	{ 235 / 255.0f, 219 / 255.0f, 208 / 255.0f },
	{ 235 / 255.0f, 219 / 255.0f, 208 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 249 / 255.0f, 244 / 255.0f, 0 / 255.0f },
	{ 249 / 255.0f, 244 / 255.0f, 0 / 255.0f }
};

GLuint VBO_car2, VAO_car2;
void prepare_car2() {
	GLsizeiptr buffer_size = sizeof(car2_body) + sizeof(car2_front_window) + sizeof(car2_back_window) + sizeof(car2_front_wheel)
		+ sizeof(car2_back_wheel) + sizeof(car2_light1) + sizeof(car2_light2);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_car2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_car2);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(car2_body), car2_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car2_body), sizeof(car2_front_window), car2_front_window);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car2_body) + sizeof(car2_front_window), sizeof(car2_back_window), car2_back_window);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car2_body) + sizeof(car2_front_window) + sizeof(car2_back_window), sizeof(car2_front_wheel), car2_front_wheel);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car2_body) + sizeof(car2_front_window) + sizeof(car2_back_window) + sizeof(car2_front_wheel),
		sizeof(car2_back_wheel), car2_back_wheel);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car2_body) + sizeof(car2_front_window) + sizeof(car2_back_window) + sizeof(car2_front_wheel)
		+ sizeof(car2_back_wheel), sizeof(car2_light1), car2_light1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(car2_body) + sizeof(car2_front_window) + sizeof(car2_back_window) + sizeof(car2_front_wheel)
		+ sizeof(car2_back_wheel) + sizeof(car2_light1), sizeof(car2_light2), car2_light2);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_car2);
	glBindVertexArray(VAO_car2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_car2);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_car2() {
	glBindVertexArray(VAO_car2);

	glUniform3fv(loc_primitive_color, 1, car2_color[CAR2_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 8);

	glUniform3fv(loc_primitive_color, 1, car2_color[CAR2_FRONT_WINDOW]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);

	glUniform3fv(loc_primitive_color, 1, car2_color[CAR2_BACK_WINDOW]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);

	glUniform3fv(loc_primitive_color, 1, car2_color[CAR2_FRONT_WHEEL]);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 8);

	glUniform3fv(loc_primitive_color, 1, car2_color[CAR2_BACK_WHEEL]);
	glDrawArrays(GL_TRIANGLE_FAN, 24, 8);

	glUniform3fv(loc_primitive_color, 1, car2_color[CAR2_LIGHT1]);
	glDrawArrays(GL_TRIANGLE_FAN, 32, 3);

	glUniform3fv(loc_primitive_color, 1, car2_color[CAR2_LIGHT2]);
	glDrawArrays(GL_TRIANGLE_FAN, 35, 3);

	glBindVertexArray(0);
}

// hat
#define HAT_LEAF 0
#define HAT_BODY 1
#define HAT_STRIP 2
#define HAT_BOTTOM 3

GLfloat hat_leaf[4][2] = { { 3.0, 20.0 },{ 3.0, 28.0 },{ 9.0, 32.0 },{ 9.0, 24.0 } };
GLfloat hat_body[4][2] = { { -19.5, 2.0 },{ 19.5, 2.0 },{ 15.0, 20.0 },{ -15.0, 20.0 } };
GLfloat hat_strip[4][2] = { { -20.0, 0.0 },{ 20.0, 0.0 },{ 19.5, 2.0 },{ -19.5, 2.0 } };
GLfloat hat_bottom[4][2] = { { 25.0, 0.0 },{ -25.0, 0.0 },{ -25.0, -4.0 },{ 25.0, -4.0 } };

GLfloat hat_color[4][3] = {
	{ 167 / 255.0f, 255 / 255.0f, 55 / 255.0f },
{ 255 / 255.0f, 144 / 255.0f, 32 / 255.0f },
{ 255 / 255.0f, 40 / 255.0f, 33 / 255.0f },
{ 255 / 255.0f, 144 / 255.0f, 32 / 255.0f }
};

GLuint VBO_hat, VAO_hat;

void prepare_hat() {
	GLsizeiptr buffer_size = sizeof(hat_leaf) + sizeof(hat_body) + sizeof(hat_strip) + sizeof(hat_bottom);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_hat);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_hat);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(hat_leaf), hat_leaf);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(hat_leaf), sizeof(hat_body), hat_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(hat_leaf) + sizeof(hat_body), sizeof(hat_strip), hat_strip);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(hat_leaf) + sizeof(hat_body) + sizeof(hat_strip), sizeof(hat_bottom), hat_bottom);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_hat);
	glBindVertexArray(VAO_hat);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_hat);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_hat() {
	glBindVertexArray(VAO_hat);

	glUniform3fv(loc_primitive_color, 1, hat_color[HAT_LEAF]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUniform3fv(loc_primitive_color, 1, hat_color[HAT_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

	glUniform3fv(loc_primitive_color, 1, hat_color[HAT_STRIP]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);

	glUniform3fv(loc_primitive_color, 1, hat_color[HAT_BOTTOM]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);

	glBindVertexArray(0);
}

// cake
#define CAKE_FIRE 0
#define CAKE_CANDLE 1
#define CAKE_BODY 2
#define CAKE_BOTTOM 3
#define CAKE_DECORATE 4

GLfloat cake_fire[4][2] = { { -0.5, 14.0 },{ -0.5, 13.0 },{ 0.5, 13.0 },{ 0.5, 14.0 } };
GLfloat cake_candle[4][2] = { { -1.0, 8.0 } ,{ -1.0, 13.0 },{ 1.0, 13.0 },{ 1.0, 8.0 } };
GLfloat cake_body[4][2] = { { 8.0, 5.0 },{ -8.0, 5.0 } ,{ -8.0, 8.0 },{ 8.0, 8.0 } };
GLfloat cake_bottom[4][2] = { { -10.0, 1.0 },{ -10.0, 5.0 },{ 10.0, 5.0 },{ 10.0, 1.0 } };
GLfloat cake_decorate[4][2] = { { -10.0, 0.0 },{ -10.0, 1.0 },{ 10.0, 1.0 },{ 10.0, 0.0 } };

GLfloat cake_color[5][3] = {
	{ 255 / 255.0f, 0 / 255.0f, 0 / 255.0f },
{ 255 / 255.0f, 204 / 255.0f, 0 / 255.0f },
{ 255 / 255.0f, 102 / 255.0f, 255 / 255.0f },
{ 255 / 255.0f, 102 / 255.0f, 255 / 255.0f },
{ 102 / 255.0f, 51 / 255.0f, 0 / 255.0f }
};

GLuint VBO_cake, VAO_cake;

void prepare_cake() {
	int size = sizeof(cake_fire);
	GLsizeiptr buffer_size = sizeof(cake_fire) * 5;

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_cake);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_cake);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, size, cake_fire);
	glBufferSubData(GL_ARRAY_BUFFER, size, size, cake_candle);
	glBufferSubData(GL_ARRAY_BUFFER, size * 2, size, cake_body);
	glBufferSubData(GL_ARRAY_BUFFER, size * 3, size, cake_bottom);
	glBufferSubData(GL_ARRAY_BUFFER, size * 4, size, cake_decorate);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_cake);
	glBindVertexArray(VAO_cake);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_cake);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_cake() {
	glBindVertexArray(VAO_cake);

	glUniform3fv(loc_primitive_color, 1, cake_color[CAKE_FIRE]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUniform3fv(loc_primitive_color, 1, cake_color[CAKE_CANDLE]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

	glUniform3fv(loc_primitive_color, 1, cake_color[CAKE_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);

	glUniform3fv(loc_primitive_color, 1, cake_color[CAKE_BOTTOM]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);

	glUniform3fv(loc_primitive_color, 1, cake_color[CAKE_DECORATE]);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);

	glBindVertexArray(0);
}

// sword

#define SWORD_BODY 0
#define SWORD_BODY2 1
#define SWORD_HEAD 2
#define SWORD_HEAD2 3
#define SWORD_IN 4
#define SWORD_DOWN 5
#define SWORD_BODY_IN 6

GLfloat sword_body[4][2] = { { -6.0, 0.0 },{ -6.0, -4.0 },{ 6.0, -4.0 },{ 6.0, 0.0 } };
GLfloat sword_body2[4][2] = { { -2.0, -4.0 },{ -2.0, -6.0 } ,{ 2.0, -6.0 },{ 2.0, -4.0 } };
GLfloat sword_head[4][2] = { { -2.0, 0.0 },{ -2.0, 16.0 } ,{ 2.0, 16.0 },{ 2.0, 0.0 } };
GLfloat sword_head2[3][2] = { { -2.0, 16.0 },{ 0.0, 19.46 } ,{ 2.0, 16.0 } };
GLfloat sword_in[4][2] = { { -0.3, 0.7 },{ -0.3, 15.3 } ,{ 0.3, 15.3 },{ 0.3, 0.7 } };
GLfloat sword_down[4][2] = { { -2.0, -6.0 } ,{ 2.0, -6.0 },{ 4.0, -8.0 },{ -4.0, -8.0 } };
GLfloat sword_body_in[4][2] = { { 0.0, -1.0 } ,{ 1.0, -2.732 },{ 0.0, -4.464 },{ -1.0, -2.732 } };

GLfloat sword_color[7][3] = {
	{ 139 / 255.0f, 69 / 255.0f, 19 / 255.0f },
{ 139 / 255.0f, 69 / 255.0f, 19 / 255.0f },
{ 155 / 255.0f, 155 / 255.0f, 155 / 255.0f },
{ 155 / 255.0f, 155 / 255.0f, 155 / 255.0f },
{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
{ 139 / 255.0f, 69 / 255.0f, 19 / 255.0f },
{ 255 / 255.0f, 0 / 255.0f, 0 / 255.0f }
};

GLuint VBO_sword, VAO_sword;

void prepare_sword() {
	GLsizeiptr buffer_size = sizeof(sword_body) + sizeof(sword_body2) + sizeof(sword_head) + sizeof(sword_head2) + sizeof(sword_in) + sizeof(sword_down) + sizeof(sword_body_in);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_sword);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_sword);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(sword_body), sword_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(sword_body), sizeof(sword_body2), sword_body2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(sword_body) + sizeof(sword_body2), sizeof(sword_head), sword_head);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(sword_body) + sizeof(sword_body2) + sizeof(sword_head), sizeof(sword_head2), sword_head2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(sword_body) + sizeof(sword_body2) + sizeof(sword_head) + sizeof(sword_head2), sizeof(sword_in), sword_in);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(sword_body) + sizeof(sword_body2) + sizeof(sword_head) + sizeof(sword_head2) + sizeof(sword_in), sizeof(sword_down), sword_down);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(sword_body) + sizeof(sword_body2) + sizeof(sword_head) + sizeof(sword_head2) + sizeof(sword_in) + sizeof(sword_down), sizeof(sword_body_in), sword_body_in);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_sword);
	glBindVertexArray(VAO_sword);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_sword);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_sword() {
	glBindVertexArray(VAO_sword);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_BODY2]);
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_HEAD]);
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_HEAD2]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 3);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_IN]);
	glDrawArrays(GL_TRIANGLE_FAN, 15, 4);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_DOWN]);
	glDrawArrays(GL_TRIANGLE_FAN, 19, 4);

	glUniform3fv(loc_primitive_color, 1, sword_color[SWORD_BODY_IN]);
	glDrawArrays(GL_TRIANGLE_FAN, 23, 4);

	glBindVertexArray(0);
}

// new object1
#define STAR_1 0
#define STAR_2 1
#define STAR_3 2
#define STAR_4 3
#define STAR_5 4
#define STAR_BODY 5

GLfloat star_1[3][2] = { { -3.0, 3.0 },{ 0.0, 10.0 },{ 3.0, 3.0 } };
GLfloat star_2[3][2] = { { 3.0, 3.0 },{ 9.0, 3.0 },{ 3.0, -1.5 } };
GLfloat star_3[3][2] = { { 3.0, -1.5 },{ 6.0, -8.0 },{ 0.0, -4.0 } };
GLfloat star_4[3][2] = { { 0.0, -4.0 },{ -6.0, -8.0 },{ -3.0, -1.5 } };
GLfloat star_5[3][2] = { { -3.0, -1.5 },{ -9.0, 3.0 },{ -3.0, 3.0 } };
GLfloat star_body[5][2] = { { 3.0, 3.0 },{ 3.0, -1.5 },{ 0.0, -4.0 },{ -3.0, -1.5 },{ -3.0, 3.0 } };

GLfloat star_color[6][3] = {
	{ 255 / 255.0f, 255 / 255.0f, 0 / 255.0f },
	{ 255 / 255.0f, 255 / 255.0f, 0 / 255.0f },
	{ 255 / 255.0f, 255 / 255.0f, 0 / 255.0f },
	{ 255 / 255.0f, 255 / 255.0f, 0 / 255.0f },
	{ 255 / 255.0f, 255 / 255.0f, 0 / 255.0f },
	{ 255 / 255.0f, 255 / 255.0f, 0 / 255.0f }
};

GLuint VBO_star, VAO_star;
void prepare_star() {
	GLsizeiptr buffer_size = sizeof(star_1) + sizeof(star_2) + sizeof(star_3) + sizeof(star_4) + sizeof(star_5)
		+ sizeof(star_body);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_star);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_star);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(star_1), star_1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(star_1), sizeof(star_2), star_2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(star_1) + sizeof(star_2), sizeof(star_3), star_3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(star_1) + sizeof(star_2) + sizeof(star_3), sizeof(star_4), star_4);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(star_1) + sizeof(star_2) + sizeof(star_3) + sizeof(star_4), sizeof(star_5), star_5);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(star_1) + sizeof(star_2) + sizeof(star_3) + sizeof(star_4) + sizeof(star_5),
		sizeof(star_body), star_body);
	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_star);
	glBindVertexArray(VAO_star);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_star);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_star() {
	glBindVertexArray(VAO_star);

	glUniform3fv(loc_primitive_color, 1, star_color[STAR_1]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3);

	glUniform3fv(loc_primitive_color, 1, star_color[STAR_2]);
	glDrawArrays(GL_TRIANGLE_FAN, 3, 3);

	glUniform3fv(loc_primitive_color, 1, star_color[STAR_3]);
	glDrawArrays(GL_TRIANGLE_FAN, 6, 3);

	glUniform3fv(loc_primitive_color, 1, star_color[STAR_4]);
	glDrawArrays(GL_TRIANGLE_FAN, 9, 3);

	glUniform3fv(loc_primitive_color, 1, star_color[STAR_5]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 3);

	glUniform3fv(loc_primitive_color, 1, star_color[STAR_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 15, 5);

	glBindVertexArray(0);
}

// new object2
#define GROOT_HEAD1 0
#define GROOT_HEAD2 1
#define GROOT_HEAD3 2
#define GROOT_HEAD4 3
#define GROOT_HEAD5 4
#define GROOT_HEAD_MAIN 5

#define GROOT_BODY1 6
#define GROOT_BODY2 7
#define GROOT_BODY3 8
#define GROOT_BODY4 9
#define GROOT_BODY5 10

#define GROOT_EYEBROW1 11
#define GROOT_EYEBROW2 12
#define GROOT_MOUTH 13
#define GROOT_EYE1_1 14
#define GROOT_EYE1_2 15
#define GROOT_EYE2_1 16
#define GROOT_EYE2_2 17

#define GROOT_HAIR1 18
#define GROOT_HAIR2 19
#define GROOT_HAIR3 20
#define GROOT_HAIR4 21

GLfloat groot_head1[3][2] = { { -18.0, -20.0 },{ -20.0, 13.0 },{ -14.0, 10.0 } };
GLfloat groot_head2[3][2] = { { -14.0, 10.0 },{ -9.0, 13.0 },{ -5.0, 11.5 } };
GLfloat groot_head3[3][2] = { { -5.0, 11.5 },{ 0.0, 15.0 },{ 5.0, 11.5 } };
GLfloat groot_head4[3][2] = { { 5.0, 11.5 },{ 9.0, 13.0 },{ 14.0, 10.0 } };
GLfloat groot_head5[3][2] = { { 14.0, 10.0 },{ 20.0, 13.0 },{ 18.0, -20.0 } };
GLfloat groot_head_main[8][2] = { { -18.0, -20.0 },{ -14.0, 10.0 },{ -5.0, 11.5 },{ 5.0, 11.5 },{ 14.0, 10.0 },{ 18.0, -20.0 },{ 9.0, -22.0 },{ -9.0, -22.0 } };

GLfloat groot_body1[4][2] = { { -15.0, -22.0 },{ -26.0, -42.0 },{ -21.0, -46.0 },{ -13.0, -36.0 } };
GLfloat groot_body2[4][2] = { { -13.0, -36.0 },{ -12.0, -64.0 },{ -3.0, -64.0 },{ 0.0, -49.0 } };
GLfloat groot_body3[4][2] = { { 0.0, -49.0 },{ 3.0, -64.0 },{ 12.0, -64.0 },{ 13.0, -36.0 } };
GLfloat groot_body4[4][2] = { { 13.0, -36.0 },{ 21.0, -46.0 },{ 26.0, -42.0 },{ 15.0, -22.0 } };
GLfloat groot_body5[5][2] = { { -15.0, -22.0 },{ -13.0, -36.0 },{ 0.0, -49.0 },{ 13.0, -36.0 },{ 15.0, -22.0 } };

GLfloat groot_eyebrow1[4][2] = { { -13.9, 1.3 },{ -14.0, 0.8 },{ -4.8, -3.1 },{ -4.7, -2.5 } };
GLfloat groot_eyebrow2[4][2] = { { 13.9, 1.3 },{ 14.0, 0.8 },{ 4.8, -3.1 },{ 4.7, -2.5 } };
GLfloat groot_mouth[8][2] = { { -3.3, -17.0 },{ -3.1, -17.1 },{ -1.8, -15.4 },{ -1.8, -16.0 },
								{ 1.8, -15.4 },{ 1.8, -16.0 },{ 3.3, -17.0 },{ 3.1, -17.1 } };
GLfloat groot_eye1_1[4][2] = { { -14.0, -1.2 },{ -13.3, -9.0 },{ -7.0, -10.4 },{ -4.8, -5.3 } };
GLfloat groot_eye1_2[4][2] = { { -12.8, -3.4 },{ -12.2, -8.1 },{ -7.8, -9.2 },{ -6.0, -5.0 } };
GLfloat groot_eye2_1[4][2] = { { 14.0, -1.2 },{ 13.3, -9.0 },{ 7.0, -10.4 },{ 4.8, -5.3 } };
GLfloat groot_eye2_2[4][2] = { { 12.8, -3.4 },{ 12.2, -8.1 },{ 7.8, -9.2 },{ 6.0, -5.0 } };

GLfloat groot_hair1[4][2] = { { -14.3, 5.7 },{ -13.7, 5.7 },{ -13.7, 10.0 },{ -14.3, 10.0 } };
GLfloat groot_hair2[4][2] = { { -9.3, 5.7 },{ -8.7, 5.7 },{ -8.7, 13.0 },{ -9.3, 13.0 } };
GLfloat groot_hair3[4][2] = { { 14.3, 5.7 },{ 13.7, 5.7 },{ 13.7, 10.0 },{ 14.3, 10.0 } };
GLfloat groot_hair4[4][2] = { { 9.3, 5.7 },{ 8.7, 5.7 },{ 8.7, 13.0 },{ 9.3, 13.0 } };

GLfloat groot_color[22][3] = {
	{ 143 / 255.0f, 120 / 255.0f, 75 / 255.0f }, // head { 210 / 255.0f, 180 / 255.0f, 140 / 255.0f }
	{ 143 / 255.0f, 120 / 255.0f, 75 / 255.0f },
	{ 143 / 255.0f, 120 / 255.0f, 75 / 255.0f },
	{ 143 / 255.0f, 120 / 255.0f, 75 / 255.0f },
	{ 143 / 255.0f, 120 / 255.0f, 75 / 255.0f },
	{ 143 / 255.0f, 120 / 255.0f, 75 / 255.0f },
	{ 143 / 255.0f, 120 / 255.0f, 75 / 255.0f }, // body { 143 / 255.0f, 120 / 255.0f, 75 / 255.0f }
	{ 143 / 255.0f, 120 / 255.0f, 75 / 255.0f },
	{ 143 / 255.0f, 120 / 255.0f, 75 / 255.0f },
	{ 143 / 255.0f, 120 / 255.0f, 75 / 255.0f },
	{ 143 / 255.0f, 120 / 255.0f, 75 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f }, // eyebrow1
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 150 / 255.0f, 70 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 150 / 255.0f, 70 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f }, // hair1
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f }
};

GLuint VBO_groot, VAO_groot;
void prepare_groot() {
	GLsizeiptr buffer_size = sizeof(groot_head1) + sizeof(groot_head2) + sizeof(groot_head3) + sizeof(groot_head4) + sizeof(groot_head5)
		+ sizeof(groot_head_main) + sizeof(groot_body1) + sizeof(groot_body2) + sizeof(groot_body3) + sizeof(groot_body4)
		+ sizeof(groot_body5) + sizeof(groot_eyebrow1) + sizeof(groot_eyebrow2) + sizeof(groot_mouth) + sizeof(groot_eye1_1)
		+ sizeof(groot_eye1_2) + sizeof(groot_eye2_1) + sizeof(groot_eye2_2) + sizeof(groot_hair1) + sizeof(groot_hair2)
		+ sizeof(groot_hair3) + sizeof(groot_hair4);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_groot);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_groot);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(groot_head1), groot_head1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(groot_head1), sizeof(groot_head2), groot_head2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(groot_head1) + sizeof(groot_head2), sizeof(groot_head3), groot_head3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(groot_head1) + sizeof(groot_head2) + sizeof(groot_head3), sizeof(groot_head4), groot_head4);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(groot_head1) + sizeof(groot_head2) + sizeof(groot_head3) + sizeof(groot_head4), sizeof(groot_head5), groot_head5);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(groot_head1) + sizeof(groot_head2) + sizeof(groot_head3) + sizeof(groot_head4) + sizeof(groot_head5),
		sizeof(groot_head_main), groot_head_main);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(groot_head1) + sizeof(groot_head2) + sizeof(groot_head3) + sizeof(groot_head4) + sizeof(groot_head5)
		+ sizeof(groot_head_main), sizeof(groot_body1), groot_body1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(groot_head1) + sizeof(groot_head2) + sizeof(groot_head3) + sizeof(groot_head4) + sizeof(groot_head5)
		+ sizeof(groot_head_main) + sizeof(groot_body1), sizeof(groot_body2), groot_body2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(groot_head1) + sizeof(groot_head2) + sizeof(groot_head3) + sizeof(groot_head4) + sizeof(groot_head5)
		+ sizeof(groot_head_main) + sizeof(groot_body1) + sizeof(groot_body2), sizeof(groot_body3), groot_body3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(groot_head1) + sizeof(groot_head2) + sizeof(groot_head3) + sizeof(groot_head4) + sizeof(groot_head5)
		+ sizeof(groot_head_main) + sizeof(groot_body1) + sizeof(groot_body2) + sizeof(groot_body3), sizeof(groot_body4), groot_body4);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(groot_head1) + sizeof(groot_head2) + sizeof(groot_head3) + sizeof(groot_head4) + sizeof(groot_head5)
		+ sizeof(groot_head_main) + sizeof(groot_body1) + sizeof(groot_body2) + sizeof(groot_body3) + sizeof(groot_body4),
		sizeof(groot_body5), groot_body5);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(groot_head1) + sizeof(groot_head2) + sizeof(groot_head3) + sizeof(groot_head4) + sizeof(groot_head5)
		+ sizeof(groot_head_main) + sizeof(groot_body1) + sizeof(groot_body2) + sizeof(groot_body3) + sizeof(groot_body4)
		+ sizeof(groot_body5), sizeof(groot_eyebrow1), groot_eyebrow1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(groot_head1) + sizeof(groot_head2) + sizeof(groot_head3) + sizeof(groot_head4) + sizeof(groot_head5)
		+ sizeof(groot_head_main) + sizeof(groot_body1) + sizeof(groot_body2) + sizeof(groot_body3) + sizeof(groot_body4)
		+ sizeof(groot_body5) + sizeof(groot_eyebrow1), sizeof(groot_eyebrow2), groot_eyebrow2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(groot_head1) + sizeof(groot_head2) + sizeof(groot_head3) + sizeof(groot_head4) + sizeof(groot_head5)
		+ sizeof(groot_head_main) + sizeof(groot_body1) + sizeof(groot_body2) + sizeof(groot_body3) + sizeof(groot_body4)
		+ sizeof(groot_body5) + sizeof(groot_eyebrow1) + sizeof(groot_eyebrow2), sizeof(groot_mouth), groot_mouth);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(groot_head1) + sizeof(groot_head2) + sizeof(groot_head3) + sizeof(groot_head4) + sizeof(groot_head5)
		+ sizeof(groot_head_main) + sizeof(groot_body1) + sizeof(groot_body2) + sizeof(groot_body3) + sizeof(groot_body4)
		+ sizeof(groot_body5) + sizeof(groot_eyebrow1) + sizeof(groot_eyebrow2) + sizeof(groot_mouth), sizeof(groot_eye1_1), groot_eye1_1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(groot_head1) + sizeof(groot_head2) + sizeof(groot_head3) + sizeof(groot_head4) + sizeof(groot_head5)
		+ sizeof(groot_head_main) + sizeof(groot_body1) + sizeof(groot_body2) + sizeof(groot_body3) + sizeof(groot_body4)
		+ sizeof(groot_body5) + sizeof(groot_eyebrow1) + sizeof(groot_eyebrow2) + sizeof(groot_mouth) + sizeof(groot_eye1_1)
		, sizeof(groot_eye1_2), groot_eye1_2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(groot_head1) + sizeof(groot_head2) + sizeof(groot_head3) + sizeof(groot_head4) + sizeof(groot_head5)
		+ sizeof(groot_head_main) + sizeof(groot_body1) + sizeof(groot_body2) + sizeof(groot_body3) + sizeof(groot_body4)
		+ sizeof(groot_body5) + sizeof(groot_eyebrow1) + sizeof(groot_eyebrow2) + sizeof(groot_mouth) + sizeof(groot_eye1_1) + sizeof(groot_eye1_2)
		, sizeof(groot_eye2_1), groot_eye2_1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(groot_head1) + sizeof(groot_head2) + sizeof(groot_head3) + sizeof(groot_head4) + sizeof(groot_head5)
		+ sizeof(groot_head_main) + sizeof(groot_body1) + sizeof(groot_body2) + sizeof(groot_body3) + sizeof(groot_body4)
		+ sizeof(groot_body5) + sizeof(groot_eyebrow1) + sizeof(groot_eyebrow2) + sizeof(groot_mouth) + sizeof(groot_eye1_1) + sizeof(groot_eye1_2)
		+ sizeof(groot_eye2_1), sizeof(groot_eye2_2), groot_eye2_2);

	glBufferSubData(GL_ARRAY_BUFFER, sizeof(groot_head1) + sizeof(groot_head2) + sizeof(groot_head3) + sizeof(groot_head4) + sizeof(groot_head5)
		+ sizeof(groot_head_main) + sizeof(groot_body1) + sizeof(groot_body2) + sizeof(groot_body3) + sizeof(groot_body4)
		+ sizeof(groot_body5) + sizeof(groot_eyebrow1) + sizeof(groot_eyebrow2) + sizeof(groot_mouth) + sizeof(groot_eye1_1) + sizeof(groot_eye1_2)
		+ sizeof(groot_eye2_1) + sizeof(groot_eye2_2), sizeof(groot_hair1), groot_hair1);

	glBufferSubData(GL_ARRAY_BUFFER, sizeof(groot_head1) + sizeof(groot_head2) + sizeof(groot_head3) + sizeof(groot_head4) + sizeof(groot_head5)
		+ sizeof(groot_head_main) + sizeof(groot_body1) + sizeof(groot_body2) + sizeof(groot_body3) + sizeof(groot_body4)
		+ sizeof(groot_body5) + sizeof(groot_eyebrow1) + sizeof(groot_eyebrow2) + sizeof(groot_mouth) + sizeof(groot_eye1_1) + sizeof(groot_eye1_2)
		+ sizeof(groot_eye2_1) + sizeof(groot_eye2_2) + sizeof(groot_hair1), sizeof(groot_hair2), groot_hair2);

	glBufferSubData(GL_ARRAY_BUFFER, sizeof(groot_head1) + sizeof(groot_head2) + sizeof(groot_head3) + sizeof(groot_head4) + sizeof(groot_head5)
		+ sizeof(groot_head_main) + sizeof(groot_body1) + sizeof(groot_body2) + sizeof(groot_body3) + sizeof(groot_body4)
		+ sizeof(groot_body5) + sizeof(groot_eyebrow1) + sizeof(groot_eyebrow2) + sizeof(groot_mouth) + sizeof(groot_eye1_1) + sizeof(groot_eye1_2)
		+ sizeof(groot_eye2_1) + sizeof(groot_eye2_2) + sizeof(groot_hair1) + sizeof(groot_hair2), sizeof(groot_hair3), groot_hair3);

	glBufferSubData(GL_ARRAY_BUFFER, sizeof(groot_head1) + sizeof(groot_head2) + sizeof(groot_head3) + sizeof(groot_head4) + sizeof(groot_head5)
		+ sizeof(groot_head_main) + sizeof(groot_body1) + sizeof(groot_body2) + sizeof(groot_body3) + sizeof(groot_body4)
		+ sizeof(groot_body5) + sizeof(groot_eyebrow1) + sizeof(groot_eyebrow2) + sizeof(groot_mouth) + sizeof(groot_eye1_1) + sizeof(groot_eye1_2)
		+ sizeof(groot_eye2_1) + sizeof(groot_eye2_2) + sizeof(groot_hair1) + sizeof(groot_hair2) + sizeof(groot_hair3),
		sizeof(groot_hair4), groot_hair4);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_groot);
	glBindVertexArray(VAO_groot);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_groot);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_groot() {
	glBindVertexArray(VAO_groot);

	glUniform3fv(loc_primitive_color, 1, groot_color[GROOT_HEAD1]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 3);

	glUniform3fv(loc_primitive_color, 1, groot_color[GROOT_HEAD2]);
	glDrawArrays(GL_TRIANGLE_FAN, 3, 3);

	glUniform3fv(loc_primitive_color, 1, groot_color[GROOT_HEAD3]);
	glDrawArrays(GL_TRIANGLE_FAN, 6, 3);

	glUniform3fv(loc_primitive_color, 1, groot_color[GROOT_HEAD4]);
	glDrawArrays(GL_TRIANGLE_FAN, 9, 3);

	glUniform3fv(loc_primitive_color, 1, groot_color[GROOT_HEAD5]);
	glDrawArrays(GL_TRIANGLE_FAN, 12, 3);

	glUniform3fv(loc_primitive_color, 1, groot_color[GROOT_HEAD_MAIN]);
	glDrawArrays(GL_TRIANGLE_FAN, 15, 8);

	glUniform3fv(loc_primitive_color, 1, groot_color[GROOT_BODY1]);
	glDrawArrays(GL_TRIANGLE_FAN, 23, 4);

	glUniform3fv(loc_primitive_color, 1, groot_color[GROOT_BODY2]);
	glDrawArrays(GL_TRIANGLE_FAN, 27, 4);

	glUniform3fv(loc_primitive_color, 1, groot_color[GROOT_BODY3]);
	glDrawArrays(GL_TRIANGLE_FAN, 31, 4);

	glUniform3fv(loc_primitive_color, 1, groot_color[GROOT_BODY4]);
	glDrawArrays(GL_TRIANGLE_FAN, 35, 4);

	glUniform3fv(loc_primitive_color, 1, groot_color[GROOT_BODY5]);
	glDrawArrays(GL_TRIANGLE_FAN, 39, 5);

	glUniform3fv(loc_primitive_color, 1, groot_color[GROOT_EYEBROW1]);
	glDrawArrays(GL_TRIANGLE_FAN, 44, 4);

	glUniform3fv(loc_primitive_color, 1, groot_color[GROOT_EYEBROW2]);
	glDrawArrays(GL_TRIANGLE_FAN, 48, 4);

	glUniform3fv(loc_primitive_color, 1, groot_color[GROOT_MOUTH]);
	glDrawArrays(GL_TRIANGLE_STRIP, 52, 8);

	glUniform3fv(loc_primitive_color, 1, groot_color[GROOT_EYE1_1]);
	glDrawArrays(GL_TRIANGLE_FAN, 60, 4);

	glUniform3fv(loc_primitive_color, 1, groot_color[GROOT_EYE1_2]);
	glDrawArrays(GL_TRIANGLE_FAN, 64, 4);

	glUniform3fv(loc_primitive_color, 1, groot_color[GROOT_EYE2_1]);
	glDrawArrays(GL_TRIANGLE_FAN, 68, 4);

	glUniform3fv(loc_primitive_color, 1, groot_color[GROOT_EYE2_2]);
	glDrawArrays(GL_TRIANGLE_FAN, 72, 4);

	glUniform3fv(loc_primitive_color, 1, groot_color[GROOT_HAIR1]);
	glDrawArrays(GL_TRIANGLE_FAN, 76, 4);

	glUniform3fv(loc_primitive_color, 1, groot_color[GROOT_HAIR2]);
	glDrawArrays(GL_TRIANGLE_FAN, 80, 4);

	glUniform3fv(loc_primitive_color, 1, groot_color[GROOT_HAIR3]);
	glDrawArrays(GL_TRIANGLE_FAN, 84, 4);

	glUniform3fv(loc_primitive_color, 1, groot_color[GROOT_HAIR4]);
	glDrawArrays(GL_TRIANGLE_FAN, 88, 4);

	glBindVertexArray(0);
}

// new object3
#define LEAF_BODY 0
#define LEAF_LINE1 1
#define LEAF_LINE2 2
#define LEAF_LINE3 3
#define LEAF_LINE4 4

GLfloat leaf_body[16][2] = { { 0.0, 0.0 },{ -9.6, 9.8 },{ -15.7, 20.7 },{ -18.9, 32.3 },{ -18.9, 46.6 }
							,{ -15.7, 58.2 } ,{ -9.8, 68.9 } ,{ 0.0, 78.9 } ,{ 12.5, 85.9 } ,{ 19.4, 78.9 } 
							,{ 25.4, 69.7 } ,{ 29.6, 58.2 } ,{ 30.9, 45.8 } ,{ 28.5, 31.3 } ,{ 23.7, 20.6 } ,{ 16.0, 10.7 } };
GLfloat leaf_line1[4][2] = { { 0.4, 0.0 },{ 12.9, 85.9 },{ 12.1, 85.9 },{ -0.4, 0.0 } };
GLfloat leaf_line2[4][2] = { { 2.3, 18.9 },{ 25.4, 40.0 },{ 26.6, 40.0 },{ 3.1, 18.9 } };
GLfloat leaf_line3[4][2] = { { 6.1, 42.3 },{ -8.5, 63.5 },{ -7.5, 63.5 },{ 5.3, 42.3 } };
GLfloat leaf_line4[4][2] = { { 20.6, 73.3 },{ 8.4, 60.9 },{ 9.2, 60.9 },{ 21.4, 73.3 } };

GLfloat leaf_color[5][3] = {
	{ 56 / 255.0f, 188 / 255.0f, 28 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f },
	{ 0 / 255.0f, 0 / 255.0f, 0 / 255.0f }
	/*{ 56 / 255.0f, 188 / 255.0f, 28 / 255.0f },
	{ 101 / 255.0f, 67 / 255.0f, 33 / 255.0f },
	{ 101 / 255.0f, 67 / 255.0f, 33 / 255.0f },
	{ 101 / 255.0f, 67 / 255.0f, 33 / 255.0f },
	{ 101 / 255.0f, 67 / 255.0f, 33 / 255.0f }*/
};

GLuint VBO_leaf, VAO_leaf;
void prepare_leaf() {
	GLsizeiptr buffer_size = sizeof(leaf_body) + sizeof(leaf_line1) + sizeof(leaf_line2) + sizeof(leaf_line3) + sizeof(leaf_line4);

	// Initialize vertex buffer object.
	glGenBuffers(1, &VBO_leaf);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_leaf);
	glBufferData(GL_ARRAY_BUFFER, buffer_size, NULL, GL_STATIC_DRAW); // allocate buffer object memory

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(leaf_body), leaf_body);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(leaf_body), sizeof(leaf_line1), leaf_line1);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(leaf_body) + sizeof(leaf_line1), sizeof(leaf_line2), leaf_line2);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(leaf_body) + sizeof(leaf_line1) + sizeof(leaf_line2), sizeof(leaf_line3), leaf_line3);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(leaf_body) + sizeof(leaf_line1) + sizeof(leaf_line2) + sizeof(leaf_line3), sizeof(leaf_line4), leaf_line4);

	// Initialize vertex array object.
	glGenVertexArrays(1, &VAO_leaf);
	glBindVertexArray(VAO_leaf);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_leaf);
	glVertexAttribPointer(LOC_VERTEX, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void draw_leaf() {
	glBindVertexArray(VAO_leaf);

	glUniform3fv(loc_primitive_color, 1, leaf_color[LEAF_BODY]);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 16);

	glUniform3fv(loc_primitive_color, 1, leaf_color[LEAF_LINE1]);
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);

	glUniform3fv(loc_primitive_color, 1, leaf_color[LEAF_LINE2]);
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);

	glUniform3fv(loc_primitive_color, 1, leaf_color[LEAF_LINE3]);
	glDrawArrays(GL_TRIANGLE_FAN, 24, 4);

	glUniform3fv(loc_primitive_color, 1, leaf_color[LEAF_LINE4]);
	glDrawArrays(GL_TRIANGLE_FAN, 28, 4);

	glBindVertexArray(0);
}