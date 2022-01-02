#include <windows.h> // �ʼ� ��� ���ϵ�
#include <MMSystem.h>
#include <glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#include <cmath>

static double time = 0; // Run_time ����
static double time2 = 0; // Jap_time ����
static double time3 = 0; // Rocket_time ����
static double time4 = 0; // ground_time ����
static double time6 = 0; // exit_time ����

GLfloat R_Arm_x = 0; // ������ ���
GLfloat R_Arm_y = 0; // ���� ��
GLfloat L_Arm_x = 0; // ���� ���
GLfloat L_Arm_y = 0; // ����
GLfloat R_Leg_x = 0; // ������ �����
GLfloat R_Leg_y = 0; // ������ ���Ƹ�
GLfloat L_Leg_x = 0; // ���� �����
GLfloat L_Leg_y = 0; // ���� ���Ƹ�
GLfloat R = 0; // ���� ���� ��ġ ������ ����
GLfloat R2 = 0; // ������ ���� ��ġ ������ ����

GLUquadricObj* cyl; // �Ǹ��� ��ü ����

int a = 0; // x�� ����(���� 1�� �� x���� �������� ȸ��)
int b = 0; // y�� ����(���� 1�� �� y���� �������� ȸ��)
int c = 0; // z�� ����(���� 1�� �� z���� �������� ȸ��)

static int flag = 0; // wireframe ���� solid rendering ��� ���� ����
static int key = 0; // ���� ���� ���� ���� ����

#define RUN			1
#define JAP			2
#define ROCKET		3
#define YUNA		4
#define EXIT		6

void glInit(void) { // ���� �ʱ�ȭ �Լ�
	glEnable(GL_DEPTH_TEST); // ���� �׽��� ���
	glEnable(GL_NORMALIZE); // ����ȭ
	glEnable(GL_SMOOTH); // �� ������ ������ �ε巴�� �����Ͽ� ĥ��������
	glEnable(GL_LIGHTING); // ���� ����, ���� �޴� ������ ���� �κ� ������ ��ȭ
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
	glClearColor(1.0, 1.0, 1.0, 1.0); // ����� ������
	glMatrixMode(GL_PROJECTION); // ��� ����
	glLoadIdentity(); // CTM �� �ʱ�ȭ
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // ���� ���� ����
}

void Draw_Color(int i) { // ������ �׸��� �Լ�
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

void Change_Wire_Or_Solid(int i) { // �ָ���, ���̾� ����
	if (flag == 1)
		gluQuadricDrawStyle(cyl, GLU_LINE); // ��Ÿ���� ���̾�� ����
}

// �κ� ������ �׸��� �Լ�
void DrawL_Arm(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key); // �� ����
	cyl = gluNewQuadric(); // �Ǹ��� ��ü ����
	glRotatef(x, a, b, c); // �Ķ���� ����ŭ ȸ��
	glRotatef(90.0, 1.0, 1.0, 0.0); // �Ǹ����� x�� �������� 90�� ȸ�� 
	// (�Ǹ��� ���� �� ���� ������ ����)
	glTranslatef(0.25, 0.0, 0.0); // ���� ����� ���������� �̵�
	glRotatef(15.0, 0.0, 1.0, 0.0); // ���� ����� y�� �������� 15�� ȸ��
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // �Ǹ����� �׸�
}

// �κ� �޼��� �׸����Լ�
void DrawL_Hand(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key); // �� ����
	cyl = gluNewQuadric(); // �Ǹ��� ��ü ����
	glTranslatef(0.0, 0.0, 0.22); // �޼� ������
	glRotatef(y, a, b, c); // �Ķ���� ����ŭ ȸ��
	Change_Wire_Or_Solid(flag);
	if (key == YUNA) gluCylinder(cyl, 0.05, 0.02, 0.2, 15, 1); // �򶧱� ��� �Ǹ����� �׸�
	else gluCylinder(cyl, 0.05, 0.05, 0.2, 15, 1); // �Ǹ����� �׸�
	glPopMatrix();
}

// �κ� ���� �ָ�
void DrawL_HandRocket() {
	glPushMatrix();
	Draw_Color(key); // �� ����
	cyl = gluNewQuadric(); // �Ǹ��� ��ü ����
	glTranslatef(0, 0, R); // ���� �ָ� ��ġ�� �Ķ���͸�ŭ �̵�
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // �Ǹ����� �׸�
	glPopMatrix();
}

// �κ� �������� �׸��� �Լ�
void DrawR_Arm(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key); // �� ����
	cyl = gluNewQuadric(); // �Ǹ��� ��ü ����
	glRotatef(x, a, b, c); // �Ķ���� ����ŭ ȸ��
	glRotatef(90.0, 1.0, 0.0, 0.0); // �Ǹ����� x�� �������� 90�� ȸ�� 
	// (�Ƿ��� ���� �� ���� ������ ����)
	glTranslatef(-0.25, 0.0, 0.0); // ������ ��� ���������� �̵�
	glRotatef(-15.0, 0.0, 1.0, 0.0); // ������ ����� y������ -15�� ȸ��
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // �Ǹ����� �׸�
}

// �κ� �������� �׸��� �Լ�
void DrawR_Hand(int y, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric(); // �Ǹ��� ��ü ����
	glTranslatef(0.0, 0.0, 0.22); // ������ ������
	glRotatef(y, a, b, c); // �Ķ���� ����ŭ ȸ��
	Change_Wire_Or_Solid(flag);
	if (key == YUNA) gluCylinder(cyl, 0.05, 0.02, 0.2, 50, 1); // �򶧱� ��� �Ǹ����� �׸�
	else gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // �Ǹ����� �׸�
	glPopMatrix();
}

// �κ� ������ ���� �Լ�
void DrawR_HandRocket() {
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric(); // �Ǹ��� ��ü ����
	glTranslatef(0, 0, R2); // ������ �ָ� ��ġ�� �Ķ���͸�ŭ �̵�
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.05, 0.05, 0.2, 50, 1); // �Ǹ����� �׸�
	glPopMatrix();
}

// �κ� ��ü�� �׸��� �Լ�
void DrawBody(int x, int a, int b, int c) {
	glPushMatrix();
	Draw_Color(key);
	cyl = gluNewQuadric(); // �Ǹ��� ��ü ����
	glRotatef(90.0, 1.0, 0.0, 0.0); // �Ǹ����� x�� �������� 90�� ȸ��
	// (�Ǹ��� ���� �� ���� ������ ����)
	glRotatef(x, a, b, c); // �Ķ���� ����ŭ ȸ��
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.2, 0.2, 0.45, 50, 1); // �Ǹ����� �׸�
	glPopMatrix();
}

// �κ� ���� ������� �׸��� �Լ�
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

// �κ� ���� ���Ƹ��� �׸��� �Լ�
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

// �κ� ������ ������� �׸��� �Լ�
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

// �κ� ������ ���Ƹ��� �׸��� �Լ�
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

// �κ� ���� �׸��� �Լ�
void DrawNeck() {
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0); // �� ����(���)
	cyl = gluNewQuadric(); // �Ǹ��� ��ü ����
	glRotatef(90.0, 1.0, 0.0, 0.0); // �Ǹ����� x�� �������� 9�� ȸ��
	// (�Ǹ��� ���� �� ���� ������ ����)
	glTranslatef(0.0, 0.0, -0.045); // �� ������
	Change_Wire_Or_Solid(flag);
	gluCylinder(cyl, 0.2, 0.2, 0.025, 100, 1); // �Ǹ����� �׸�
	glPopMatrix();
}

// ������ �׸��� �Լ�, �̴� Ŀ�ٶ� ���� �����Ͽ����� ������ �ð��� ���� 
// ȸ���Ͽ� ��ġ �κ��� ������ �پ�� ������ �鵵�� ��.
void DrawGround() {
	Draw_Color(flag); // ���� ����
	glTranslatef(0.0, -2.73, 0.0); // ���� ������
	glRotatef(45.0, 0, 1, 0); // 45�� ��ŭ y���� �������� ȸ��
	glRotatef(0.0 + time4 - 15, 0.0, 0.0, 1); // z���� �������� time4 ��ŭ ������ ȸ��
	Change_Wire_Or_Solid(flag);
	gluSphere(cyl, 2.5, 30, 90);
}

// �κ� �Ӹ��� �׸��� �Լ�, �Ӹ��� �޸� �԰� �κ��� ���� ������
void DrawHead() {
	glTranslatef(0.0, 0.02, 0.0); // �Ӹ� ������
	glPushMatrix(); // ���� ���� ��ǥ�� �ٽ� ����
	cyl = gluNewQuadric();
	Change_Wire_Or_Solid(flag);
	Draw_Color(key); // ���� ����
	gluSphere(cyl, 0.20, 30, 10); //�Ӹ� �׸���

	// ���� �� �׸���
	glRotatef(90.0, 1.0, 0.0, 0.0); // �Ǹ��� 90�� x���� �������� ȸ��
	// (�Ǹ��� ���� �� ���� ������ ����)
	glTranslatef(-0.16, 0.0, -0.22); // ���� �� ������
	glRotatef(35.0, 0.0, 1.0, 0.0); // 35�� y���� �������� ȸ��
	gluCylinder(cyl, 0.005, 0.008, 0.1, 3, 1); // �Ǹ����� �׸�
	glPopMatrix(); // ���� ���� ��ǥ�踦 ���ư�.
	glPushMatrix(); // ���� ���� ��ǥ�� �ٽ� ����

	// ������ �� �׸���
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.16, 0.0, -0.22);
	glRotatef(-35.0, 0.0, 1.0, 0.0);
	gluCylinder(cyl, 0.005, 0.008, 0.1, 3, 1);
	glPopMatrix();
	glPushMatrix();

	// ���� �� �׸���
	glTranslatef(0.1, 0.1, 0.13); // ���� �� ������
	glColor3f(0.0, 0.0, 0.0); // �� �÷� ����(���)
	gluSphere(cyl, 0.03, 10, 10);
	glPopMatrix(); // ���� ���� ��ǥ��� ���ư�
	glPushMatrix(); // ���� ���� ��ǥ�� �ٽ� ����

	// ������ �� �׸��� 
	glTranslatef(0.1, 0.1, 0.13); // ������ �� ������
	gluSphere(cyl, 0.03, 10, 10);
	glPopMatrix(); // ���� ���� ��ǥ�� �ٽ� ����
}

// �κ� ��ü ����� �׸��� �Լ�
void DrawAndroid() {
	DrawBody(0, 0, 0, 0); // ���� �Լ� ȣ��
	DrawNeck(); // �� �Լ� ȣ��
	DrawHead(); // �Ӹ� ȣ��
	DrawR_Arm(R_Arm_x, 1, 0, 0); // ������
	if (key == ROCKET) DrawR_HandRocket(); // ���ϸ���� �� ������ ���� ȣ��
	else DrawR_Hand(R_Arm_y, 1, 0, 0); // ������

	DrawL_Arm(L_Arm_x, 1, 0, 0); // ����
	if (key == ROCKET) DrawL_HandRocket(); // ���� ����� �� ������ ���� ȣ��
	else DrawL_Hand(L_Arm_y, 1, 0, 0); // �޼�
	DrawL_Legs(L_Leg_x, 1, 0, 0); // ���� �ٸ�
	DrawL_foot(L_Leg_y, 1, 0, 0); // ���� ��
	DrawR_Legs(R_Leg_x, 1, 0, 0); // ������ �ٸ�
	DrawR_foot(R_Leg_y, 1, 0, 0); // ������ ��
}

// �κ��� �޸��� ���� ǥ���� �Լ�, �κ��� ���� �������� ǥ���߰�, 
// �κ��� �޸��鼭 ��, ��, ��, ��� �����̴� ����� ǥ����.
// �⺻���� �κ� �������� ���ӵ��� sin() �Լ��� ���� ǥ���Ͽ�����, 
// ���� �������� ���� ������ �����Ͽ� abs() �Լ��� ���� ������ �������� ������.
void Run() {
	sndPlaySound(TEXT("C:\\sample1.wav"), SND_ASYNC | SND_NOSTOP);
	glLoadIdentity(); // CTM �ʱ�ȭ
	L_Arm_x = sin(time) * 80; // ������ 80������ �����̵� sin()���� �ֱ����� ������ ����
	R_Arm_x = -L_Arm_x; // �������� ���� �ݴ� ���� 80�� ��������
	R_Arm_y = -abs(sin(time) * 60 + 50); // ������ ���� ����(������ �����ν� ���� �ڷ� ������ ����.)
	L_Arm_y = -abs(-sin(time) * 60 + 50); // ���� ���� ����
	R_Leg_y = -abs(-sin(time) * 60 + 50); //  ������ ���Ƹ� ���� ����
	L_Leg_y = abs(sin(time) * 30 - 30); // ���� ���Ƹ� ���� ����
	R_Leg_x = sin(time) * 60; // ������ �ٸ��� 60������ �����̵� sin()���� �ֱ����� ������ ����
	L_Leg_x = -R_Leg_x; // ���� �ٸ��� ������ �ٸ� �ݴ��

	cyl = gluNewQuadric(); // �Ǹ��� ��ü ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // �ʱ�ȭ
	glMatrixMode(GL_MODELVIEW); // ��� ����

	DrawGround(); // ������ �׸�
	glLoadIdentity(); // CTM �ʱ�ȭ

	// �κ��� �޸��鼭 ��, �ڷ� �ڶװŸ��� ���� Ʋ������ ���� ǥ��
	glRotatef(-230.0, 0, 1, 0); // y���� �������� ȸ��
	glRotatef(abs(sin(time) * 16), 1, 0, 0); // x���� �������� 16������ ������ Ʋ����.
	glRotatef(sin(time) * 16, 0, 1, 0); // y���� �������� 16������ ������ Ʋ����, 
	// sin() �Լ��� �ֱ����� ������ ����

	// �κ��� �޸��鼭 ���Ϸ� �����̴� ���� ǥ��
	float i = 0;
	i = abs(sin(time) * 0.08); // i ���� �� ����
	glPushMatrix(); // ���� ���� ��ǥ�� �ٽ� ����
	glTranslatef(0.0, i, 0); // �κ��� ��ü�� y�� �������� ���� i��ŭ �̵�
	glTranslatef(0.0, 0.5, 0.0); // �κ��� ���� ��ġ
	DrawAndroid();
	glutSwapBuffers();
}

// �κ��� ���� ������ ������ ǥ���� �Լ�
void Jap() {
	sndPlaySound(TEXT("C:\\sample3.wav"), SND_ASYNC | SND_NOSTOP);
	glLoadIdentity();
	L_Arm_x = (-40) + sin(time2) * 60; // ���� ����� ���� ������ -40 ���¿��� sin() �Լ��� �ֱ����� ������ ����
	R_Arm_x = (-80) - L_Arm_x; // ������ ����� ���� ������ -80 ���¿��� ���� ��� �������� �ݴ�� ����
	R_Arm_y = -abs(cos(time2) * 80); // ���� �� ���� ����
	// ���� ���� ������ ǥ���� ���� ����� sin() �Լ��� �ݴ��� cos() �Լ� ���
	L_Arm_y = -abs(-cos(time2) * 80); // ���� ���� ����
	R_Leg_y = abs(-sin(time) * 30 - 20); // ������ ���Ƹ� ���� ����(������ ����� ������ ������ �ʰ�)
	L_Leg_y = abs(sin(time) * 30 - 20); // ���� ���Ƹ� ���� ����
	R_Leg_x = sin(time) * 30; // ������ �ٸ��� 30������. sin() �Լ��� �ֱ����� ������ ����
	L_Leg_x = -R_Leg_x; // ���� �ٸ��� ������ �ٸ� �ݴ��

	cyl = gluNewQuadric(); // �Ǹ��� ��ü ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // �ʱ�ȭ
	glMatrixMode(GL_MODELVIEW); // ��� ����

	DrawGround(); // ������ �׸�
	glLoadIdentity(); // CTM �ʱ�ȭ
	glRotatef(-230.0, 0, 1, 0); // y���� �������� ȸ��
	glRotatef(sin(time) * 10, 0, 0, 1); // �κ��� �¿� �ݵ� ǥ�� (�¿�� 10����ŭ �ֱ����� ������ ����)

	// �κ��� ���� �����鼭 ���Ϸ� �����̴� ���� ǥ��
	float j = 0;
	j = abs(sin(time2) * 0.085); // j�� ����
	glPushMatrix(); // ���� ���� ��ǥ�� �ٽ� ����
	glTranslatef(0.0, j, 0); // ���� j��ŭ �κ��� ��ü�� y���� �������� ������
	glTranslatef(0.0, 0.5, 0.0); // ���� ��ġ
	DrawAndroid();
	glutSwapBuffers();
}

// �κ��� ������ �� ũ�� ��ȯ�� ǥ���� �Լ�
void ex() {
	sndPlaySound(TEXT("C:\\sample5.wav"), SND_ASYNC | SND_NOSTOP);
	glLoadIdentity(); // CTM �ʱ�ȭ

	L_Arm_x = (-40) + sin(time2) * 60;
	R_Arm_x = (-80) - L_Arm_x;
	R_Arm_y = -abs(cos(time2) * 10);
	L_Arm_y = -abs(-cos(time2) * 10);
	R_Leg_y = abs(-sin(time) * 30 - 30);
	L_Leg_y = abs(sin(time) * 30 - 30);
	R_Leg_x = sin(time) * 60;
	L_Leg_x = -R_Leg_x;

	cyl = gluNewQuadric(); // �Ǹ��� ��ü ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // �ʱ�ȭ
	glMatrixMode(GL_MODELVIEW); // ��� ����

	glLoadIdentity(); // CTM�� �ʱ�ȭ
	glRotatef(-180, 0, 1, 0); // y���� �������� ȸ��
	glRotatef(time6, 0, 0, 1); // time6 ������ŭ z���� �������� ȸ��
	glScalef(0.4 / (sin(time3)), 0.4 / (sin(time3)), 0.4 / (sin(time3)));
	// 0.4�� ũ�⿡�� sin()�� ����Ͽ� ũ�� ������ �ֱ������� ����
	glPushMatrix(); // ���� ���� ��ǥ�� �ٽ� ����
	glTranslatef(0.0, 0.5, 0.0); // ���� ��ġ
	DrawAndroid();
	glutSwapBuffers();
}

// �������� ������ ǥ���� �Լ�
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

	// ����. �κ��� �ǰ� ���� �� ���� Ʋ������ ���� ǥ��
	glRotatef(sin(time) * 7, 0, 0, 1); // z���� �������� 7������ Ʋ����. sin() �Լ��� �ֱ����� ������ ����
	glRotatef(sin(time) * 7, 0, 1, 0); // y���� �������� 7������ Ʋ����. sin() �Լ��� �ֱ����� ������ ����

	glTranslatef(0.0, 0.18, 0.0); // y�� �������� �̵�
	glRotatef(80, 1, 0, 0); // x���� �������� ȸ��
	glTranslatef(0.0, 0.5, 0.0); // ���� ��ġ
	glPushMatrix(); // ���� ��ġ ����
	DrawBody(0, 0, 0, 0); // ���� �׸���
	glPopMatrix(); // ���� ��ġ ��ǥ��� �ǵ��ư�.
	glPushMatrix(); // ���� ��ġ ��ǥ�� �ٽ� ����.

	// ��
	DrawNeck(); // �� �׸���
	glPopMatrix(); // ���� ��ġ ��ǥ��� �ǵ��ư�.
	glPushMatrix(); // ���� ��ġ ��ǥ�� �ٽ� ����.

	// �Ӹ�
	glRotatef(-75, 1, 0, 0); // x���� �������� ȸ��(�Ӹ��� �������� ������)
	glTranslatef(0.0, -0.02, 0.0); // y�� �������� �̵�(�Ӹ� ������)
	DrawHead(); // �Ӹ��� �׸�
	glPopMatrix(); // ���� ���� ��ǥ��� �ǵ��ư�.
	glPushMatrix(); // ���� ��ġ ��ǥ�� �ٽ� ����.

	// �����Ȱ� ������
	DrawR_Arm((R_Arm_y + 30), 1, 0, 0); // �������� �׸�
	DrawR_Hand(-(R_Arm_y - 15), 1, 0, 0); // �������� �׸�
	glPopMatrix(); // ���� ���� ��ǥ��� �ǵ��ư�.
	glPushMatrix(); // ���� ��ġ ��ǥ�� �ٽ� ����.

	// ���Ȱ� �޼�
	glTranslatef(0.0, -0.16, -0.04); // y��, z������ �̵�(���� ������)
	glRotatef(40, 0, 0, 1); // z���� �������� ȸ��
	DrawL_Arm((L_Arm_y + 30), 1, 0, 0); // ������ �׸�.
	DrawL_Hand(-(L_Arm_y - 15), 1, 0, 0); // �޼��� �׸�.
	glPopMatrix(); // ���� ���� ��ǥ��� �ǵ��ư�.
	glPushMatrix(); // ���� ��ġ ��ǥ�� �ٽ� ����.

	// ���� �ٸ��� ���� ���Ƹ�
	glTranslatef(0.0, -0.45, -0.25); // y��, z������ �̵�(���� �ٸ� ������)
	glRotatef(-90, 1, 0, 0); // x���� �������� ȸ��
	DrawL_Legs(-30, 1, 0, 0); // ���� �ٸ�
	DrawL_foot(10, 1, 0, 0); // ���� ���Ƹ�
	glPopMatrix(); // ���� ���� ��ǥ��� �ǵ��ư�.
	glPushMatrix(); // ���� ��ġ ��ǥ�� �ٽ� ����.

	// ������ �ٸ��� ������ ���Ƹ�
	glTranslatef(0.0, -0.5, -0.5); // y��, z������ �̵�(������ �ٸ� ������)
	glRotatef(-90, 1, 0, 0); // x���� �������� ȸ��
	DrawR_Legs(160, 1, 0, 0); // ������ �ٸ�
	DrawR_foot(R_Leg_y, 1, 0, 0); // ������ ���Ƹ�
	glPopMatrix(); // ���� ���� ��ǥ��� �ǵ��ư�.
	glutSwapBuffers(); // ���� ���۸�
}

// �κ��� ������ �߻��ϴ� ����� ǥ���� �Լ�
void Rocket() {
	sndPlaySound(TEXT("C:\\sample2.wav"), SND_ASYNC | SND_NOSTOP);
	glLoadIdentity();
	L_Arm_x = -90; // 90�� ������ ���� ������ ����.
	R_Arm_x = -90;
	R = 2 * abs(-sin(time2) * 0.2 - 0.2) + 0.2;
	// ������ ���� ������ ����. ������ ����� ������ �������� ������ ����.
	// +0.2�� ���� ������ ���� ��ġ ����. 2*�� ���� ������ ������ �Ÿ� ����. 
	// sin() �Լ��� �ֱ����� ������ ����

	R2 = 2 * abs(sin(time2) * 0.2 - 0.2) + 0.2; // ���� ���� ������ ����
	R_Leg_y = abs(-sin(time) * 30 - 30); // ������ ���Ƹ� ���� ����
	L_Leg_y = abs(sin(time) * 30 - 30); // ���� ���Ƹ� ���� ����
	R_Leg_x = sin(time) * 60;
	L_Leg_x = -R_Leg_x;

	cyl = gluNewQuadric(); // �Ǹ��� ��ü ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // �ʱ�ȭ
	glMatrixMode(GL_MODELVIEW); // ��� ����

	DrawGround(); // ������ �׸�
	glLoadIdentity();
	glPushMatrix();
	glRotatef(-230.0, 0, 1, 0);

	// ������ �� �� �����¿�� ���� Ʈ�� ����� ����
	glRotatef(-abs(sin(time) * 8), 1, 0, 0); // x���� �������� 8������ Ʋ����
	glRotatef(sin(time) * 7, 0, 0, 1); // z���� �������� 7������ Ʋ����
	// ������ ��� ���� ƨ��� ����� ǥ��
	float i = 0;
	i = abs(sin(time) * 0.08);
	glTranslatef(0.0, i, 0);
	glTranslatef(0.0, 0.5, 0.0);
	DrawAndroid();
	glutSwapBuffers();
}

// Ű���� �ݹ�. w�� ������ writeframe ����, s�� ������ solid rendering ����, q�� ������ ����
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

// ��麰�� Ű ���� �ο��Ǹ� �̿� ���� �뷡�� ���ֵ�. �뷡 ����� sndPlaySound() �Լ��� ����Ͽ�����
// �̸� ���� ������ ���� ������ �ʿ���. ��� ������ sndPlaySound(TEXT("���� ���� ���"))
void MyDisplay() {
	if (key == RUN) { // �޸���
		Run();
		glPopMatrix();
	}
	else if (key == JAP) { // ���� ���� ��
		Jap();
		glPopMatrix();
	}
	else if(key == ROCKET){ // ������ �߻��� ��
		Rocket();
		glPopMatrix();
	}
	else if (key == YUNA) { // �ǰ� ������ ���� ��
		Show();
		glPopMatrix();
	}
	else if (key == 5) { // ������ ���õǾ��� ��
		sndPlaySound(NULL, SND_ASYNC);
	}
	else if(key==EXIT) { // ���ᰡ ���õǾ��� ��
		ex();
		glPopMatrix();
	}
}

// Ÿ�̸� �Լ�, �� ��鸶�� ���� ǥ���� �ٸ��� �ϱ� ���� ������ �ð� ������ �����.
void MyTimer(int Value) {
	time = time + 0.1; // �޸� �� ���� Ÿ�̸� ����
	time2 = time2 + 0.5; // ���� ���� �� ���� Ÿ�̸� ����
	time3 = time3 + 0.01; // ������ �߻��� �� ���� Ÿ�̸� ����
	// ����� �κ��� ��۹�� ���ư��� �ϴ� �� ���� Ÿ�̸� ����
	time4 = time4 + 1.0; // �ǰ� ������ ���� �� ���� Ÿ�̸� ����
	glutPostRedisplay();
	glutTimerFunc(40, MyTimer, 1);
}

// ���콺 ������ Ŭ������ �޴��� ������ �� ����Ǵ� �Լ�. �⺻������ ���콺 �ݹ��� �̿��� ����� ��ȯ �ǵ��� ����
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
	glutAddMenuEntry("Run", 1); // �κ��� �޸��� ���� �޴� �߰�
	glutAddMenuEntry("Jap", 2); // �κ��� ���� ������ ���� �޴� �߰�
	glutAddMenuEntry("Shoot", 3); // �κ��� ���� ��ġ�� �߻��ϴ� ���� �޴� �߰�
	glutAddMenuEntry("Skate", 4); // �κ��� ���� ���������� �ϴ� ���� �޴� �߰�
	glutAddMenuEntry("����", 5); // �κ��� �ϴ� ���� ���߰� �ϴ� �޴� �߰�
	glutAttachMenu(GLUT_RIGHT_BUTTON); // ���콺 ������ ��ư�� Ŭ���ϸ� �޴� �˾�
	glutKeyboardFunc(MyKeyboard);
	glutTimerFunc(40, MyTimer, 1);
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}