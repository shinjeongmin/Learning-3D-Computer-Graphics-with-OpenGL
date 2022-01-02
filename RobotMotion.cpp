#include <windows.h> // 필수 헤더 파일들
#include <MMSystem.h>
#include <glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#include <cmath>

static double time = 0; // Run_time 변수
static double time2 = 0; // Jap_time 변수
static double time3 = 0; // Rocket_time 변수
static double time4 = 0; // ground_time 변수
static double time6 = 0; // exit_time 변수

GLfloat R_Arm_x = 0; // 오른쪽 어깨
GLfloat R_Arm_y = 0; // 오른 팔
GLfloat L_Arm_x = 0; // 왼쪽 어깨
GLfloat L_Arm_y = 0; // 왼팔
GLfloat R_Leg_x = 0; // 오른쪽 허벅지
GLfloat R_Leg_y = 0; // 오른쪽 종아리
GLfloat L_Leg_x = 0; // 왼쪽 허벅지
GLfloat L_Leg_y = 0; // 왼쪽 종아리
GLfloat R = 0; // 왼쪽 로켓 펀치 움직임 변수
GLfloat R2 = 0; // 오른쪽 로켓 펀치 움직임 변수

GLUquadricObj* cyl; // 실린더 객체 선언

int a = 0; // x축 기준(값이 1일 때 x축을 기준으로 회전)
int b = 0; // y축 기준(값이 1일 때 y축을 기준으로 회전)
int c = 0; // z축 기준(값이 1일 때 z축을 기준으로 회전)

static int flag = 0; // wireframe 모드와 solid rendering 모드 구분 변수
static int key = 0; // 동작 모드와 색상 변경 변수

#define RUN			1
#define JAP			2
#define ROCKET		3
#define YUNA		4
#define EXIT		6

void glInit(void) { // 지엘 초기화 함수
	glEnable(GL_DEPTH_TEST); // 깊이 테스팅 사용
	glEnable(GL_NORMALIZE); // 정규화
	glEnable(GL_SMOOTH); // 각 정점의 색상을 부드럽게 연결하여 칠해지도록
	glEnable(GL_LIGHTING); // 지엘 조명, 빛을 받는 각도에 따라 로봇 색상이 변화
	GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 0.1f };
	GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat position[] = { 400.0, 300.0, -700.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glClearColor(1.0, 1.0, 1.0, 1.0); // 배경은 검은색
	glMatrixMode(GL_PROJECTION); // 모드 설정
	glLoadIdentity(); // CTM 값 초기화
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // 가시 범위 설정
}

void Draw_Color(int i) { // 색상을 그리는 함수
	if(i==RUN){
		glColor3f(0.0, 1.0, 0.0);
	}
	else if (i == JAP) {
		glColor3f(1.0, 1.0, 0.0);
	}
	else if (i == ROCKET) {
		glColor3f(0.0, 1.0, 1.0);
	}
	else if (i == YUNA) {
		glColor3f(1.0, 0.0, 1.0);
	}
	else if (i == EXIT) {
		glColor3f(0.2, 0.2, 0.2);
	}
}

void Change_Wire_Or_Solid(int i) { // 솔리드, 와이어 선택
	if (flag == 1)
		gluQuadricDrawStyle(cyl, GLU_LINE); // 스타일을 와이어로 변경
}

// 로봇 왼팔을 그리는 함수
void DrawL_Arm(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key); // 색 설정
	cyl = gluNewQuadric(); // 실린더 객체 생성
	glRotatef(x, a, b, c); // 파라미터 값만큼 회전
	glRotatef(90.0, 1.0, 1.0, 0.0); // 실린더를 x축 기준으로 90도 회전 
	// (실린더 생성 시 각도 변경을 위해)
	glTranslatef(0.25, 0.0, 0.0); // 왼쪽 어깨를 시작점으로 이동
	glRotatef(15.0, 0.0, 1.0, 0.0); // 왼쪽 어깨를 y축 기준으로 15도 회전
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // 실린더를 그림
}

// 로봇 왼손을 그리는함수
void DrawL_Hand(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key); // 색 설정
	cyl = gluNewQuadric(); // 실린더 객체 생성
	glTranslatef(0.0, 0.0, 0.22); // 왼손 시작점
	glRotatef(y, a, b, c); // 파라미터 값만큼 회전
	Change_Wire_Or_Solid(flag);
	if (key == YUNA) gluCylinder(cyl, 0.05, 0.02, 0.2, 15, 1); // 깔때기 모양 실린더를 그림
	else gluCylinder(cyl, 0.05, 0.05, 0.2, 15, 1); // 실린더를 그림
	glPopMatrix();
}

// 로봇 왼쪽 주먹
void DrawL_HandRocket() {
	glPushMatrix();
	Draw_Color(key); // 색 설정
	cyl = gluNewQuadric(); // 실린더 객체 생성
	glTranslatef(0, 0, R); // 왼쪽 주먹 위치를 파라미터만큼 이동
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // 실린더를 그림
	glPopMatrix();
}

// 로봇 오른팔을 그리는 함수
void DrawR_Arm(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key); // 색 설정
	cyl = gluNewQuadric(); // 실린더 객체 생성
	glRotatef(x, a, b, c); // 파라미터 값만큼 회전
	glRotatef(90.0, 1.0, 0.0, 0.0); // 실린더를 x축 기준으로 90도 회전 
	// (실런더 생성 시 각도 변경을 위해)
	glTranslatef(-0.25, 0.0, 0.0); // 오른쪽 어깨 시작점으로 이동
	glRotatef(-15.0, 0.0, 1.0, 0.0); // 오른쪽 어깨를 y축으로 -15도 회전
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // 실린더를 그림
}

// 로봇 오른손을 그리는 함수
void DrawR_Hand(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric(); // 실린더 객체 생성
	glTranslatef(0.0, 0.0, 0.22); // 오른손 시작점
	glRotatef(y, a, b, c); // 파라미터 값만큼 회전
	Change_Wire_Or_Solid(flag);
	if (key == YUNA) gluCylinder(cyl, 0.05, 0.02, 0.2, 50, 1); // 깔때기 모양 실린더를 그림
	else gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // 실린더를 그림
	glPopMatrix();
}

// 로봇 오른쪽 로켓 함수
void DrawR_HandRocket() {
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric(); // 실린더 객체 생성
	glTranslatef(0, 0, R2); // 오른쪽 주먹 위치를 파라미터만큼 이동
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // 실린더를 그림
	glPopMatrix();
}

// 로봇 몸체를 그리는 함수
void DrawBody(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric(); // 실린더 객체 생성
	glRotatef(90.0, 1.0, 0.0, 0.0); // 실린더를 x축 기준으로 90도 회전
	// (실린더 생성 시 각도 변경을 위해)
	glRotatef(x, a, b, c); // 파라미터 값만큼 회전
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.2, 0.2, 0.45, 50, 1); // 실린더를 그림
	glPopMatrix();
}

// 로봇 왼쪽 허벅지를 그리는 함수
void DrawL_Legs(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.1, 0.0, 0.42);
	glRotatef(x, a, b, c);
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.15, 50, 1);
}

// 로봇 왼쪽 종아리를 그리는 함수
void DrawL_foot(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric();
	glTranslatef(0.0, 0.0, 0.18);
	glRotatef(y, a, b, c);
	Change_Wire_Or_Solid(flag);
	if (key == YUNA) gluCylinder(cyl, 0.05, 0.03, 0.2, 50, 1);
	else gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1);
	glPopMatrix();
}

// 로봇 오른쪽 허벅지를 그리는 함수
void DrawR_Legs(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric();
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTranslatef(-0.1, 0.0, 0.42);
	glRotatef(x, a, b, c);
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.15, 50, 1);
}

// 로봇 오른쪽 종아리를 그리는 함수
void DrawR_foot(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric();
	glTranslatef(0.0, 0.0, 0.18);
	glRotatef(y, a, b, c);
	Change_Wire_Or_Solid(flag);
	if (key == YUNA) gluCylinder(cyl, 0.05, 0.03, 0.2, 15, 1);
	else gluCylinder(cyl, 0.05, 0.05, 0.2, 15, 1);
	glPopMatrix();
}

// 로봇 목을 그리는 함수
void DrawNeck() {
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0); // 색 지정(흰색)
	cyl = gluNewQuadric(); // 실린더 객체 생성
	glRotatef(90.0, 1.0, 0.0, 0.0); // 실린더를 x축 기준으로 9도 회전
	// (실린더 생성 시 각도 변경을 위해)
	glTranslatef(0.0, 0.0, -0.045); // 목 시작점
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.2, 0.2, 0.025, 100, 1); // 실린더를 그림
	glPopMatrix();
}

// 지면을 그리는 함수, 이는 커다란 구로 설정하였으며 지면이 시간에 따라 
// 회전하여 마치 로봇이 앞으로 뛰어가는 느낌이 들도록 함.
void DrawGround() {
	Draw_Color(flag); // 색상 설정
	glTranslatef(0.0, -2.73, 0.0); // 지면 시작점
	glRotatef(45.0, 0, 1, 0); // 45도 만큼 y축을 기준으로 회전
	glRotatef(0.0 + time4 - 15, 0.0, 0.0, 1); // z축을 기준으로 time4 만큼 지면이 회전
	Change_Wire_Or_Solid(flag);
	gluSphere(cyl, 2.5, 30, 90);
}

// 로봇 머리를 그리는 함수, 머리에 달린 뿔과 로봇의 눈을 설정함
void DrawHead() {
	glTranslatef(0.0, 0.02, 0.0); // 머리 시작점
	glPushMatrix(); // 최초 저장 좌표계 다시 저장
	cyl = gluNewQuadric();
	Change_Wire_Or_Solid(flag);
	Draw_Color(key); // 색상 설정
	gluSphere(cyl, 0.20, 30, 10); //머리 그리기

	// 왼쪽 뿔 그리기
	glRotatef(90.0, 1.0, 0.0, 0.0); // 실린더 90도 x축을 기준으로 회전
	// (실린더 생성 시 각도 변경을 위해)
	glTranslatef(-0.16, 0.0, -0.22); // 왼쪽 뿔 시작점
	glRotatef(35.0, 0.0, 1.0, 0.0); // 35도 y축을 기준으로 회전
	gluCylinder(cyl, 0.005, 0.008, 0.1, 3, 1); // 실린더를 그림
	glPopMatrix(); // 최초 저장 좌표계를 돌아감.
	glPushMatrix(); // 최초 저장 좌표계 다시 저장

	// 오른쪽 뿔 그리기
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.16, 0.0, -0.22);
	glRotatef(-35.0, 0.0, 1.0, 0.0);
	gluCylinder(cyl, 0.005, 0.008, 0.1, 3, 1);
	glPopMatrix();
	glPushMatrix();

	// 왼쪽 눈 그리기
	glTranslatef(0.1, 0.1, 0.13); // 왼쪽 눈 시작점
	glColor3f(0.0, 0.0, 0.0); // 눈 컬러 설정(흑색)
	gluSphere(cyl, 0.03, 10, 10);
	glPopMatrix(); // 최초 저장 좌표계로 돌아감
	glPushMatrix(); // 최초 저장 좌표계 다시 저장

	// 오른쪽 눈 그리기 
	glTranslatef(0.1, 0.1, 0.13); // 오른쪽 눈 시작점
	gluSphere(cyl, 0.03, 10, 10);
	glPopMatrix(); // 최초 저장 좌표계 다시 저장
}

// 로봇 전체 모습을 그리는 함수
void DrawAndroid() {
	DrawBody(0, 0, 0, 0); // 몸통 함수 호출
	DrawNeck(); // 목 함수 호출
	DrawHead(); // 머리 호출
	DrawR_Arm(R_Arm_x, 1, 0, 0); // 오른팔
	if (key == ROCKET) DrawR_HandRocket(); // 로켓모드일 때 오른쪽 로켓 호출
	else DrawR_Hand(R_Arm_y, 1, 0, 0); // 오른손

	DrawL_Arm(L_Arm_x, 1, 0, 0); // 왼팔
	if (key == ROCKET) DrawL_HandRocket(); // 로켓 모드일 때 오른쪽 로켓 호출
	else DrawL_Hand(L_Arm_y, 1, 0, 0); // 왼속
	DrawL_Legs(L_Leg_x, 1, 0, 0); // 왼쪽 다리
	DrawL_foot(L_Leg_y, 1, 0, 0); // 왼쪽 발
	DrawR_Legs(R_Leg_x, 1, 0, 0); // 오른쪽 다리
	DrawR_foot(R_Leg_y, 1, 0, 0); // 오른쪽 발
}

// 로봇이 달리는 것을 표현한 함수, 로봇의 관절 움직임을 표현했고, 
// 로봇이 달리면서 상, 하, 좌, 우로 움직이는 모습을 표현함.
// 기본적인 로봇 움직임의 가속도는 sin() 함수를 통해 표현하였으며, 
// 관절 움직임의 제한 범위를 생각하여 abs() 함수를 통해 관절의 움직임을 제한함.
void Run() {
	sndPlaySound(TEXT("C:\\sample1.wav"), SND_ASYNC | SND_NOSTOP);
	glLoadIdentity(); // CTM 초기화
	L_Arm_x = sin(time) * 80; // 왼팔은 80도까지 움직이되 sin()으로 주기적인 움직임 설정
	R_Arm_x = -L_Arm_x; // 오른팔은 왼팔 반대 방향 80도 각도까지
	R_Arm_y = -abs(sin(time) * 60 + 50); // 오른팔 각도 조절(절댓값을 줌으로써 팔이 뒤로 꺾이지 않음.)
	L_Arm_y = -abs(-sin(time) * 60 + 50); // 왼팔 각도 조절
	R_Leg_y = -abs(-sin(time) * 60 + 50); //  오른쪽 종아리 각도 조절
	L_Leg_y = abs(sin(time) * 30 - 30); // 왼쪽 종아리 각도 조절
	R_Leg_x = sin(time) * 60; // 오른쪽 다리는 60도까지 움직이되 sin()으로 주기적인 움직임 설정
	L_Leg_x = -R_Leg_x; // 왼쪽 다리는 오른쪽 다리 반대로

	cyl = gluNewQuadric(); // 실린더 객체 생성
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 초기화
	glMatrixMode(GL_MODELVIEW); // 모드 설정

	DrawGround(); // 지면을 그림
	glLoadIdentity(); // CTM 초기화

	// 로봇이 달리면서 앞, 뒤로 뒤뚱거리고 몸이 틀어지는 것을 표현
	glRotatef(-230.0, 0, 1, 0); // y축을 기준으로 회전
	glRotatef(abs(sin(time) * 16), 1, 0, 0); // x축을 기준으로 16도까지 각도가 틀어짐.
	glRotatef(sin(time) * 16, 0, 1, 0); // y축을 기준으로 16도까지 각도가 틀어짐, 
	// sin() 함수로 주기적인 움직임 설정

	// 로봇이 달리면서 상하로 움직이는 것을 표현
	float i = 0;
	i = abs(sin(time) * 0.08); // i 변수 값 설정
	glPushMatrix(); // 최초 저장 좌표계 다시 저장
	glTranslatef(0.0, i, 0); // 로봇의 몸체가 y축 방향으로 변수 i만큼 이동
	glTranslatef(0.0, 0.5, 0.0); // 로봇의 최초 위치
	DrawAndroid();
	glutSwapBuffers();
}

// 로봇이 잽을 날리는 동작을 표현한 함수
void Jap() {
	sndPlaySound(TEXT("C:\\sample3.wav"), SND_ASYNC | SND_NOSTOP);
	glLoadIdentity();
	L_Arm_x = (-40) + sin(time2) * 60; // 왼쪽 어깨의 각도 시작은 -40 상태에서 sin() 함수로 주기적인 움직임 설정
	R_Arm_x = (-80) - L_Arm_x; // 오른쪽 어깨의 각도 시작은 -80 상태에서 왼쪽 어깨 움직임의 반대로 설정
	R_Arm_y = -abs(cos(time2) * 80); // 오른 팔 각도 조절
	// 팔을 뻗는 움직임 표현을 위해 어깨의 sin() 함수와 반대인 cos() 함수 사용
	L_Arm_y = -abs(-cos(time2) * 80); // 왼팔 각도 조절
	R_Leg_y = abs(-sin(time) * 30 - 20); // 오른쪽 종아리 각도 조절(절댓값을 사용해 앞으로 꺾이지 않게)
	L_Leg_y = abs(sin(time) * 30 - 20); // 왼쪽 종아리 각도 조절
	R_Leg_x = sin(time) * 30; // 오른쪽 다리는 30도까지. sin() 함수로 주기적인 움직임 설정
	L_Leg_x = -R_Leg_x; // 왼쪽 다리는 오른쪽 다리 반대로

	cyl = gluNewQuadric(); // 실린더 객체 생성
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 초기화
	glMatrixMode(GL_MODELVIEW); // 모드 설정

	DrawGround(); // 지면을 그림
	glLoadIdentity(); // CTM 초기화
	glRotatef(-230.0, 0, 1, 0); // y축을 기준으로 회전
	glRotatef(sin(time) * 10, 0, 0, 1); // 로봇의 좌우 반동 표현 (좌우로 10도만큼 주기적인 움직임 설정)

	// 로봇이 잽을 날리면서 상하로 움직이는 것을 표현
	float j = 0;
	j = abs(sin(time2) * 0.085); // j값 설정
	glPushMatrix(); // 최초 저장 좌표계 다시 저장
	glTranslatef(0.0, j, 0); // 변수 j만큼 로봇의 몸체가 y축을 기준으로 움직임
	glTranslatef(0.0, 0.5, 0.0); // 최초 위치
	DrawAndroid();
	glutSwapBuffers();
}

// 로봇이 퇴장할 때 크기 변환을 표현한 함수
void ex() {
	sndPlaySound(TEXT("C:\\sample5.wav"), SND_ASYNC | SND_NOSTOP);
	glLoadIdentity(); // CTM 초기화

	L_Arm_x = (-40) + sin(time2) * 60;
	R_Arm_x = (-80) - L_Arm_x;
	R_Arm_y = -abs(cos(time2) * 10);
	L_Arm_y = -abs(-cos(time2) * 10);
	R_Leg_y = abs(-sin(time) * 30 - 30);
	L_Leg_y = abs(sin(time) * 30 - 30);
	R_Leg_x = sin(time) * 60;
	L_Leg_x = -R_Leg_x;

	cyl = gluNewQuadric(); // 실린더 객체 생성
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 초기화
	glMatrixMode(GL_MODELVIEW); // 모드 설정

	glLoadIdentity(); // CTM을 초기화
	glRotatef(-180, 0, 1, 0); // y축을 기준으로 회전
	glRotatef(time6, 0, 0, 1); // time6 변수만큼 z축을 기준으로 회전
	glScalef(0.4 / (sin(time3)), 0.4 / (sin(time3)), 0.4 / (sin(time3)));
	// 0.4의 크기에서 sin()을 사용하여 크기 조절을 주기적으로 가함
	glPushMatrix(); // 최초 저장 좌표계 다시 저장
	glTranslatef(0.0, 0.5, 0.0); // 최초 위치
	DrawAndroid();
	glutSwapBuffers();
}

// 스케이팅 동작을 표현한 함수
void Show() {
	sndPlaySound(TEXT("C:\\sample4.wav"), SND_ASYNC | SND_NOSTOP);
	glLoadIdentity();
	L_Arm_x = (-40) + sin(time2) * 60;
	R_Arm_x = (-80) - L_Arm_x;
	R_Arm_y = -abs(cos(time2) * 10);
	R_Arm_y = -abs(-cos(time2) * 10);
	R_Leg_y = abs(-sin(time) * 30 - 30);
	L_Leg_y = abs(sin(time) * 30 - 30);
	R_Leg_x = sin(time) * 60;
	L_Leg_x = -R_Leg_x;

	cyl = gluNewQuadric();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	DrawGround();
	glLoadIdentity();
	glRotatef(-230.0, 0, 1, 0);

	// 몸통. 로봇의 피겨 동작 시 몸이 틀어지는 것을 표현
	glRotatef(sin(time) * 7, 0, 0, 1); // z축을 기준으로 7도까지 틀어짐. sin() 함수로 주기적인 움직임 설정
	glRotatef(sin(time) * 7, 0, 1, 0); // y축을 기준으로 7도까지 틀어짐. sin() 함수로 주기적인 움직인 설정

	glTranslatef(0.0, 0.18, 0.0); // y축 방향으로 이동
	glRotatef(80, 1, 0, 0); // x축을 기준으로 회전
	glTranslatef(0.0, 0.5, 0.0); // 최초 위치
	glPushMatrix(); // 최초 위치 저장
	DrawBody(0, 0, 0, 0); // 몸통 그리기
	glPopMatrix(); // 최초 위치 좌표계로 되돌아감.
	glPushMatrix(); // 최초 위치 좌표계 다시 저장.

	// 목
	DrawNeck(); // 목 그리기
	glPopMatrix(); // 최초 위치 좌표계로 되돌아감.
	glPushMatrix(); // 최초 위치 좌표계 다시 저장.

	// 머리
	glRotatef(-75, 1, 0, 0); // x축을 기준으로 회전(머리를 위쪽으로 돌리기)
	glTranslatef(0.0, -0.02, 0.0); // y축 방향으로 이동(머리 시작점)
	DrawHead(); // 머리를 그림
	glPopMatrix(); // 최초 저장 좌표계로 되돌아감.
	glPushMatrix(); // 최초 위치 좌표계 다시 저장.

	// 오른팔과 오른손
	DrawR_Arm((R_Arm_y + 30), 1, 0, 0); // 오른팔을 그림
	DrawR_Hand(-(R_Arm_y - 15), 1, 0, 0); // 오른손을 그림
	glPopMatrix(); // 최초 저장 좌표계로 되돌아감.
	glPushMatrix(); // 최초 위치 좌표계 다시 저장.

	// 왼팔과 왼손
	glTranslatef(0.0, -0.16, -0.04); // y축, z축으로 이동(왼팔 시작점)
	glRotatef(40, 0, 0, 1); // z축을 기준으로 회전
	DrawL_Arm((L_Arm_y + 30), 1, 0, 0); // 왼팔을 그림.
	DrawL_Hand(-(L_Arm_y - 15), 1, 0, 0); // 왼손을 그림.
	glPopMatrix(); // 최초 저장 좌표계로 되돌아감.
	glPushMatrix(); // 최초 위치 좌표계 다시 저장.

	// 왼족 다리와 왼쪽 종아리
	glTranslatef(0.0, -0.45, -0.25); // y축, z축으로 이동(왼쪽 다리 시작점)
	glRotatef(-90, 1, 0, 0); // x축을 기준으로 회전
	DrawL_Legs(-30, 1, 0, 0); // 왼쪽 다리
	DrawL_foot(10, 1, 0, 0); // 왼쪽 종아리
	glPopMatrix(); // 최초 저장 좌표계로 되돌아감.
	glPushMatrix(); // 최초 위치 좌표계 다시 저장.

	// 오른쪽 다리와 오른쪽 종아리
	glTranslatef(0.0, -0.5, -0.5); // y축, z축으로 이동(오른쪽 다리 시작점)
	glRotatef(-90, 1, 0, 0); // x축을 기준으로 회전
	DrawR_Legs(160, 1, 0, 0); // 오른쪽 다리
	DrawR_foot(R_Leg_y, 1, 0, 0); // 오른쪽 종아리
	glPopMatrix(); // 최초 저장 좌표계로 되돌아감.
	glutSwapBuffers(); // 더블 버퍼링
}

// 로봇이 로켓을 발사하는 모습을 표현한 함수
void Rocket() {
	sndPlaySound(TEXT("C:\\sample2.wav"), SND_ASYNC | SND_NOSTOP);
	glLoadIdentity();
	L_Arm_x = -90; // 90도 각도로 팔을 앞으로 내밈.
	R_Arm_x = -90;
	R = 2 * abs(-sin(time2) * 0.2 - 0.2) + 0.2;
	// 오른쪽 로켓 움직임 설정. 절댓값을 사용해 로켓이 앞쪽으로 나가게 설정.
	// +0.2를 통해 로켓의 최초 위치 조절. 2*를 통해 로켓이 나가는 거리 조절. 
	// sin() 함수로 주기적인 움직임 설정

	R2 = 2 * abs(sin(time2) * 0.2 - 0.2) + 0.2; // 왼쪽 로켓 움직임 설정
	R_Leg_y = abs(-sin(time) * 30 - 30); // 오른쪽 종아리 각도 조절
	L_Leg_y = abs(sin(time) * 30 - 30); // 왼쪽 종아리 각도 조절
	R_Leg_x = sin(time) * 60;
	L_Leg_x = -R_Leg_x;

	cyl = gluNewQuadric(); // 실린더 객체 생성
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 초기화
	glMatrixMode(GL_MODELVIEW); // 모드 설정

	DrawGround(); // 지면을 그림
	glLoadIdentity();
	glPushMatrix();
	glRotatef(-230.0, 0, 1, 0);

	// 로켓을 쏠 때 상하좌우로 몸을 트는 모습을 설정
	glRotatef(-abs(sin(time) * 8), 1, 0, 0); // x축을 기준으로 8도까지 틀어짐
	glRotatef(sin(time) * 7, 0, 0, 1); // z축을 기준으로 7도까지 틀어짐
	// 로켓을 쏘며 몸을 튕기는 모습을 표현
	float i = 0;
	i = abs(sin(time) * 0.08);
	glTranslatef(0.0, i, 0);
	glTranslatef(0.0, 0.5, 0.0);
	DrawAndroid();
	glutSwapBuffers();
}

// 키보드 콜백. w를 누르면 writeframe 모드로, s를 누르면 solid rendering 모드로, q를 누르면 종료
void MyKeyboard(unsigned char KeyPressed, int x, int y) {
	switch (KeyPressed) {
	case 'w':
		flag = 1;
		break;
	case 's':
		flag = 0;
		break;
	case 'q':
		key = 6;
		break;
	}
}

// 장면별로 키 값이 부여되며 이에 따라 노래가 연주됨. 노래 재생은 sndPlaySound() 함수를 사용하였으며
// 이를 위해 별도의 음악 파일이 필요함. 경로 설정은 sndPlaySound(TEXT("음악 파일 경로"))
void MyDisplay() {
	if (key == RUN) { // 달릴때
		Run();
		glPopMatrix();
	}
	else if (key == JAP) { // 잽을 날릴 때
		Jap();
		glPopMatrix();
	}
	else if(key == ROCKET){ // 로켓을 발사할 때
		Rocket();
		glPopMatrix();
	}
	else if (key == YUNA) { // 피겨 동작을 취할 때
		Show();
		glPopMatrix();
	}
	else if (key == 5) { // 중지가 선택되었을 때
		sndPlaySound(NULL, SND_ASYNC);
	}
	else if(key==EXIT) { // 종료가 선택되었을 때
		ex();
		glPopMatrix();
	}
}

// 타이머 함수, 각 장면마다 상태 표현을 다르게 하기 위해 별도의 시간 변수를 사용함.
void MyTimer(int Value) {
	time = time + 0.1; // 달릴 때 쓰인 타이머 변수
	time2 = time2 + 0.5; // 잽을 날릴 때 쓰인 타이머 변수
	time3 = time3 + 0.01; // 로켓을 발사할 때 쓰인 타이머 변수
	// 종료시 로봇이 뱅글뱅글 돌아가게 하는 데 쓰인 타이머 변수
	time4 = time4 + 1.0; // 피겨 동작을 취할 때 쓰인 타이머 변수
	glutPostRedisplay();
	glutTimerFunc(40, MyTimer, 1);
}

// 마우스 오른쪽 클릭으로 메뉴를 선택할 때 실행되는 함수. 기본적으로 마우스 콜백을 이용해 장면이 변환 되도록 설정
void MyMainMenu(int entryID) {
	key = entryID;
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Catch Me If You Can");
	glInit();
	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
	glutAddMenuEntry("Run", 1); // 로봇이 달리는 동작 메뉴 추가
	glutAddMenuEntry("Jap", 2); // 로봇이 잽을 날리는 동작 메뉴 추가
	glutAddMenuEntry("Shoot", 3); // 로봇이 로켓 펀치를 발사하는 동작 메뉴 추가
	glutAddMenuEntry("Skate", 4); // 로봇이 피켜 스케이팅을 하는 동작 메뉴 추가
	glutAddMenuEntry("중지", 5); // 로봇이 하는 일을 멈추게 하는 메뉴 추가
	glutAttachMenu(GLUT_RIGHT_BUTTON); // 마우스 오른쪽 버튼을 클릭하면 메뉴 팝업
	glutKeyboardFunc(MyKeyboard);
	glutTimerFunc(40, MyTimer, 1);
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}