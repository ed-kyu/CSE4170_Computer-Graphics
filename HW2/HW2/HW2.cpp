#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include "Shaders/LoadShaders.h"
GLuint h_ShaderProgram; // handle to shader program
GLint loc_ModelViewProjectionMatrix, loc_primitive_color; // indices of uniform variables
GLfloat ClickLeftX, ClickLeftY, ClickRightX, ClickRightY;

// include glm/*.hpp only if necessary
//#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> //translate, rotate, scale, ortho, etc.
glm::mat4 ModelViewProjectionMatrix;
glm::mat4 ViewMatrix, ProjectionMatrix, ViewProjectionMatrix;

#define TO_RADIAN 0.01745329252f  
#define TO_DEGREE 57.295779513f
#define BUFFER_OFFSET(offset) ((GLvoid *) (offset))
#define GRAVITY 4.0f
#define LOC_VERTEX 0

int win_width = 0, win_height = 0;
float centerx = 0.0f, centery = 0.0f;
GLfloat xrot, yrot; GLfloat star_posx = 0.0f, star_posy = 0.0f, star_velx = 0.0f, star_vely = 0.0f, dt = 1.0f;
GLfloat posx = -200.0f, posy = 0.0f, xdt = 1.0, ydt = 1.0, velx = 3.0, vely = 3.0;
GLfloat plane_posx = -100.0f, plane_posy = -200.0f, plane_dt = 1.0, plane_velx = 1.0, plane_vely = 1.0;
GLfloat house_posx = 200.0f, house_posy = 200.0f, house_dt = 0.1, house_velx = 20.0, house_vely = -1.0;
GLfloat house_posx2 = 300.0f, house_posy2 = 200.0f, house_velx2 = -100.0, house_vely2 = -1.0;
GLfloat hat_pos = -300.0f;
int leftbuttonpressed = 0; int shootbutton = 0;
int rightbuttonpressed = 0;
double trans_left = 0, trans_up = 0;
GLfloat rotx = 0, roty = 0;


// 2D 물체 정의 부분은 objects.h 파일로 분리
// 새로운 물체 추가 시 prepare_scene() 함수에서 해당 물체에 대한 prepare_***() 함수를 수행함.
// (필수는 아니나 올바른 코딩을 위하여) cleanup() 함수에서 해당 resource를 free 시킴.
#include "objects.h"
#include <ctime>
#include <algorithm>

float makeRandomnum() {
	float num;
	srand((unsigned int)time(NULL));
	num = std::min(rand() % win_width / 2, rand() % win_height / 2);
	return num;
}

unsigned int timestamp = 0;
unsigned int timestamp_clicked = 0;
void timer(int value) {
	timestamp = (timestamp + 1) % UINT_MAX;
	posx += velx * xdt;
	posy += vely * ydt;

	plane_posx += plane_velx * plane_dt;
	plane_posy += plane_vely * plane_dt;

	house_posx += house_velx * house_dt;
	house_posy += house_vely * house_dt;
	house_vely += -GRAVITY * house_dt;
	house_posx2 += house_velx2 * house_dt;
	house_posy2 += house_vely2 * house_dt;
	house_vely2 += -GRAVITY * house_dt;

	star_posx += star_velx * dt;
	star_posy += star_vely * dt;
	glutPostRedisplay();
	glutTimerFunc(10, timer, 0);
}

void display(void) {
	glm::mat4 ModelMatrix;

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(211 / 255.0f, 211 / 255.0f, 211 / 255.0f, 1.0); // 배경 색

	ModelMatrix = glm::mat4(1.0f);
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_axes();


	int sword_clock = (timestamp % 1442) / 2 - 360; // -360 <= sword_clock <= 360 
	float rotation_angle_sword = atanf(100.0f * TO_RADIAN * cosf(sword_clock * TO_RADIAN));
	rotation_angle_sword = 50 * sword_clock * TO_RADIAN;
	// 0. groot + star
	int star_clock = (timestamp % 1440) - 720; // -720 <= star_clock <= 720 
	float rotation_angle_star = atanf(100.0f * TO_RADIAN * cosf(star_clock * TO_RADIAN));
	GLfloat start_pointx = -200.0f, start_pointy = -200.0f;
	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(start_pointx - 20.0f + trans_left, start_pointy + trans_up, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.5f, 0.5f, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_leaf();
	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(start_pointx + trans_left, start_pointy + trans_up, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2.0f, 2.0f, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_groot();
	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(start_pointx + 40.0f + trans_left, start_pointy - 80.0f + trans_up, 0.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2.0f, 2.0f, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_sword();
	// 1. sword
	for (int i = 1; i < 10; i++) {
		ModelMatrix = glm::mat4(1.0f);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(start_pointx + trans_left, start_pointy + trans_up, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, -i * star_clock / 2 * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(150.0f, 0.0f, 0.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.6f, 0.6f, 1.0f)); // 0.4f * i, 0.4f * i, 1.0f
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_sword();
	}

	// 2. hat
	int hat_clock = (timestamp % 1440) - 720;
	ModelMatrix = glm::mat4(1.0f);
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(hat_pos, 0.0f, 0.0f));
	ModelMatrix = glm::rotate(ModelMatrix, 45.0f * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
	ModelMatrix = glm::translate(ModelMatrix, glm::vec3(hat_clock, 20.0f * sinf(hat_clock * TO_RADIAN), 0.0f));
	ModelMatrix = glm::rotate(ModelMatrix, hat_clock * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2.0f * sinf(hat_clock * TO_RADIAN), 2.0f * sinf(hat_clock * TO_RADIAN), 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_hat();



	// 3. car
	int car_clock = (timestamp % 720);
	float new_xdt = 1.0;
	float new_ydt = 1.0;
	if (posy > win_height / 2.0f) {
		ydt = -new_ydt;
		rotx -= 90.0f;
	}
	else if (posx > win_width / 2.0f) {
		xdt = -new_xdt;
		rotx += 90.0f;
	}
	else if (posy < -win_height / 2.0f) {
		ydt = new_ydt;
		rotx += 90.0f;
	}
	else if (posx < -win_width / 2.0f) {
		xdt = new_xdt;
		rotx -= 90.0f;
	}
	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(posx, posy, 0.0f));
	ModelMatrix = glm::rotate(ModelMatrix, rotx, glm::vec3(0.0f, 0.0f, 1.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2.0f, 2.0f, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_car();



	// 4. house 물리엔진 구현(중력, 마찰, 반발)
	int house_clock = (timestamp % 720);
	float house_rotx = 0.0f * TO_RADIAN;
	const float coef_res = 0.85f; // 반발계수
	const float friction = 0.9f; // 마찰
	const float coef_res2 = 0.9f; // 반발계수
	const float friction2 = 0.9f; // 마찰
	if (house_posy < -win_height / 2.0f + 20.0f) {
		if (house_vely <= 0.0f)
			house_vely *= -1.0f * coef_res;
		house_velx *= friction;
	}
	if (house_posy > win_height / 2.0f - 20.0f) {
		if (house_vely >= 0.0f)
			house_vely *= -1.0f * coef_res;
	}
	if (house_posx > win_width / 2.0f - 15.0f) {
		if (house_velx >= 0.0f)
			house_velx *= -1.0f * coef_res;
	}
	if (house_posx < -win_width / 2.0f + 15.0f) {
		if (house_velx <= 0.0f)
			house_velx *= -1.0f * coef_res;
	}
	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(house_posx, house_posy, 0.0f));
	ModelMatrix = glm::rotate(ModelMatrix, house_rotx, glm::vec3(0.0f, 0.0f, 1.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2.0f, 2.0f, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_house();
	if (house_posy2 < -win_height / 2.0f + 20.0f) {
		if (house_vely2 <= 0.0f)
			house_vely2 *= -1.0f * coef_res2;
		house_velx2 *= friction2;
	}
	if (house_posy2 > win_height / 2.0f - 20.0f) {
		if (house_vely2 >= 0.0f)
			house_vely2 *= -1.0f * coef_res2;
	}
	if (house_posx2 > win_width / 2.0f - 15.0f) {
		if (house_velx2 >= 0.0f)
			house_velx2 *= -1.0f * coef_res2;
	}
	if (house_posx2 < -win_width / 2.0f + 15.0f) {
		if (house_velx2 <= 0.0f)
			house_velx2 *= -1.0f * coef_res2;
	}
	ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(house_posx2, house_posy2, 0.0f));
	ModelMatrix = glm::rotate(ModelMatrix, house_rotx, glm::vec3(0.0f, 0.0f, 1.0f));
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2.0f, 2.0f, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_house();

	// 5. airplane 
	int airplane_clock = timestamp % 720; // 0 <= airplane_clock <= 719 
	float airplane_rotate_angle = 0;
	if (ClickRightX != win_width / 2.0f) {
		if (ClickRightX < win_width / 2.0f) {
			airplane_rotate_angle = 90.0f * TO_RADIAN + atanf(-(ClickRightY - win_height / 2.0f) / (float)(ClickRightX - win_width / 2.0f));
		}
		else {
			airplane_rotate_angle = -90.0f * TO_RADIAN + atanf(-(ClickRightY - win_height / 2.0f) / (float)(ClickRightX - win_width / 2.0f));
		}
	}
	else {
		if (ClickRightY >= win_height / 2.0f) {
			airplane_rotate_angle = 180.0f * TO_RADIAN;
		}
		else {
			airplane_rotate_angle = 0.0f * TO_RADIAN;
		}
	}
	ModelMatrix = glm::mat4(1.0f);
	ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2.0f, 2.0f, 1.0f));
	ModelMatrix = glm::rotate(ModelMatrix, airplane_rotate_angle, glm::vec3(0.0f, 0.0f, 1.0f));
	ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
	glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
	draw_airplane();
	float angle = airplane_rotate_angle - 90.0f * TO_RADIAN;
	int star_clock2 = (timestamp % 360);
	if (shootbutton == 1) {
		if (rightbuttonpressed == 0) {
			angle = airplane_rotate_angle - 90.0f * TO_RADIAN;
		}
		star_velx = 7.0f * cosf(angle);  // star x속도 설정
		star_vely = 7.0f * sinf(angle);  // star y속도 설정
		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(star_posx, star_posy, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, angle, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(55.0f, 0.0f, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, 10 * star_clock2 * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2.0f, 2.0f, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_star();
		if (abs(star_posx) > win_width / 2.0f + 10.0f || abs(star_posy) > win_height / 2.0f + 10.0f) {
			shootbutton = 0;
			star_posx = 0;
			star_posy = 0;
			star_velx = 0.0f;
			star_vely = 0.0f;
		}

	}
	float distance1 = sqrt(pow(house_posx - star_posx, 2) + pow(house_posy - star_posy, 2));
	float distance2 = sqrt(pow(house_posx2 - star_posx, 2) + pow(house_posy2 - star_posy, 2));
	if (distance1 <= 25.0f) {
		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(house_posx, house_posy, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, house_rotx, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2.0f, 2.0f, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_star();
		//house_posx = -100.0f, house_posy = 200.0f;
		float num = makeRandomnum();
		house_posx = num * pow(-1, num), house_posy = num * pow(-1, num);
		house_velx = 20.0, house_vely = -1.0;
	}
	if (distance2 <= 25.0f) {
		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(house_posx2, house_posy2, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, house_rotx, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2.0f, 2.0f, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_star();
		float num = makeRandomnum();
		house_posx2 = num * pow(-1, num), house_posy2 = num * pow(-1, num);
		house_velx2 = 100.0, house_vely2 = -1.0;
	}
	float distance3 = sqrt(pow(posx - star_posx, 2) + pow(posy - star_posy, 2));
	if (distance3 <= 50.0f) {
		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(house_posx2, house_posy2, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, house_rotx, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2.0f, 2.0f, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_star();
		float num = makeRandomnum();
		posx = num * pow(-1, num), posy = num * pow(-1, num);
	}
	float distance4 = sqrt(pow(hat_pos - star_posx, 2) + pow(0.0f - star_posy, 2));
	if (distance4 <= 20.0f) {
		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(hat_pos, 0.0f, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, house_rotx, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(2.0f, 2.0f, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_star();
		float num = makeRandomnum();
		hat_pos = num * pow(-1, num);
	}
	// 6. leaf
	int leaf_clock = (timestamp % 1440) - 720;
	for (int i = 0; i < 5; i++) {
		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(i * 70.0f + 200.0f, 0.0f, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, -90.0f * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3((leaf_clock + i * 30), 100.0f * (i + 1) / 20 * pow(-1, i) * sinf((leaf_clock + i * 30) * TO_RADIAN * (i + 1) + i * 100.0f), 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, -30.0f * TO_RADIAN * i, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.5f, 0.5f, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_leaf();
	}
	for (int i = 1; i < 6; i++) {
		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(i * 70.0f, 0.0f, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, -90.0f * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3((double)leaf_clock + i * 20, (double)(100.0f * (i + 1) / 20 * pow(-1, i) * (sinf((leaf_clock + i * 20) * TO_RADIAN) + cosf((leaf_clock + i * 20.0f) * TO_RADIAN * (i + 1)))), 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, -30.0f * TO_RADIAN * i, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.5f, 0.5f, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_leaf();
	}
	for (int i = 0; i < 5; i++) {
		ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(i * 30.0f, 0.0f, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, -90.0f * TO_RADIAN, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3((leaf_clock + i * 50), 100.0f * (i + 1) / 20 * pow(-1, i) * sinf((leaf_clock + i * 50) * TO_RADIAN * (i + 1) + i * 100.0f), 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, -20.0f * TO_RADIAN * i, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.5f, 0.5f, 1.0f));
		ModelViewProjectionMatrix = ViewProjectionMatrix * ModelMatrix;
		glUniformMatrix4fv(loc_ModelViewProjectionMatrix, 1, GL_FALSE, &ModelViewProjectionMatrix[0][0]);
		draw_leaf();
	}

	glFlush();
}


void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: // ESC key
		glutLeaveMainLoop(); // Incur destuction callback for cleanups.
		break;
	case 's':
		shootbutton = 1;
		glutPostRedisplay();
		break;
	}
}

void MySpecialKey(int Key, int X, int Y)
{
	switch (Key) {
	case GLUT_KEY_LEFT&& GLUT_KEY_UP:
		trans_left = trans_left - 5.0;
		trans_up = trans_up + 5.0;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:     //왼쪽 키
		trans_left = trans_left - 5.0;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:     //오른쪽 키
		trans_left = trans_left + 5.0;
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:      //위 키
		trans_up = trans_up + 5.0;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:      //아래 키
		trans_up = trans_up - 5.0;
		glutPostRedisplay();
		break;
	}

}

void mouse(int button, int state, int x, int y) {
	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
		leftbuttonpressed = 1;
		ClickLeftX = x - win_width / 2.0f, ClickLeftY = -(y - win_height / 2.0f);
	}
	else if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP)) {
		leftbuttonpressed = 0;
	}
	else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN))
		rightbuttonpressed = 1;
	else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_UP)) {
		rightbuttonpressed = 0;
	}
}

void motion(int x, int y) {
	if (leftbuttonpressed) {
		centerx = x - win_width / 2.0f, centery = (win_height - y) - win_height / 2.0f;
		//ClickLeftX = x, ClickLeftY = y,
		glutPostRedisplay();
	}
	if (rightbuttonpressed) {
		ClickRightX = x, ClickRightY = y;
		glutPostRedisplay();
	}

}

void reshape(int width, int height) {
	win_width = width, win_height = height;

	glViewport(0, 0, win_width, win_height);
	ProjectionMatrix = glm::ortho(-win_width / 2.0, win_width / 2.0,
		-win_height / 2.0, win_height / 2.0, -1000.0, 1000.0);
	ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;

	update_axes();

	glutPostRedisplay();
}

void cleanup(void) {
	glDeleteVertexArrays(1, &VAO_axes);
	glDeleteBuffers(1, &VBO_axes);

	glDeleteVertexArrays(1, &VAO_airplane);
	glDeleteBuffers(1, &VBO_airplane);

	glDeleteVertexArrays(1, &VAO_house);
	glDeleteBuffers(1, &VBO_house);

	glDeleteVertexArrays(1, &VAO_sword);
	glDeleteBuffers(1, &VBO_sword);

	glDeleteVertexArrays(1, &VAO_star);
	glDeleteBuffers(1, &VBO_star);

	glDeleteVertexArrays(1, &VAO_groot);
	glDeleteBuffers(1, &VBO_groot);

	glDeleteVertexArrays(1, &VAO_car);
	glDeleteBuffers(1, &VBO_car);

	glDeleteVertexArrays(1, &VAO_car2);
	glDeleteBuffers(1, &VBO_car2);

	glDeleteVertexArrays(1, &VAO_leaf);
	glDeleteBuffers(1, &VBO_leaf);

	glDeleteVertexArrays(1, &VAO_hat);
	glDeleteBuffers(1, &VBO_hat);
}

void register_callbacks(void) {
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutReshapeFunc(reshape);
	glutTimerFunc(10, timer, 0);
	glutCloseFunc(cleanup);
	glutSpecialFunc(MySpecialKey);
}

void prepare_shader_program(void) {
	ShaderInfo shader_info[3] = {
		{ GL_VERTEX_SHADER, "Shaders/simple.vert" },
		{ GL_FRAGMENT_SHADER, "Shaders/simple.frag" },
		{ GL_NONE, NULL }
	};

	h_ShaderProgram = LoadShaders(shader_info);
	glUseProgram(h_ShaderProgram);

	loc_ModelViewProjectionMatrix = glGetUniformLocation(h_ShaderProgram, "u_ModelViewProjectionMatrix");
	loc_primitive_color = glGetUniformLocation(h_ShaderProgram, "u_primitive_color");
}

void initialize_OpenGL(void) {
	glEnable(GL_MULTISAMPLE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glClearColor(44 / 255.0f, 180 / 255.0f, 49 / 255.0f, 1.0f);
	ViewMatrix = glm::mat4(1.0f);
}

void prepare_scene(void) {
	prepare_axes();
	prepare_airplane();
	prepare_house();
	prepare_sword();
	prepare_star();
	prepare_groot();
	prepare_car();
	prepare_car2();
	prepare_leaf();
	prepare_hat();
}

void initialize_renderer(void) {
	register_callbacks();
	prepare_shader_program();
	initialize_OpenGL();
	prepare_scene();
}

void initialize_glew(void) {
	GLenum error;

	glewExperimental = GL_TRUE;

	error = glewInit();
	if (error != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(error));
		exit(-1);
	}
	fprintf(stdout, "*********************************************************\n");
	fprintf(stdout, " - GLEW version supported: %s\n", glewGetString(GLEW_VERSION));
	fprintf(stdout, " - OpenGL renderer: %s\n", glGetString(GL_RENDERER));
	fprintf(stdout, " - OpenGL version supported: %s\n", glGetString(GL_VERSION));
	fprintf(stdout, "*********************************************************\n\n");
}

void greetings(char* program_name, char messages[][256], int n_message_lines) {
	fprintf(stdout, "**************************************************************\n\n");
	fprintf(stdout, "  PROGRAM NAME: %s\n\n", program_name);
	fprintf(stdout, "    This program was coded for CSE4170 students\n");
	fprintf(stdout, "      of Dept. of Comp. Sci. & Eng., Sogang University.\n\n");

	for (int i = 0; i < n_message_lines; i++)
		fprintf(stdout, "%s\n", messages[i]);
	fprintf(stdout, "\n**************************************************************\n\n");

	initialize_glew();
}

#define N_MESSAGE_LINES 2
int main(int argc, char* argv[]) {
	char program_name[64] = "Sogang CSE4170 Homework2 Project";
	char messages[N_MESSAGE_LINES][256] = {
		"    - Keys used: 'ESC'"
		"    - Keyboard 방향키 used: Moving Groot"
		"    - s used: Shoot star"
	};

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitWindowSize(1200, 800);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow(program_name);

	greetings(program_name, messages, N_MESSAGE_LINES);
	initialize_renderer();

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutMainLoop();
}


