#include <Windows.h> // �ʼ� ��� ���ϵ�
#include <mmsystem.h>
#include <glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

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
GLfloat R_leg_y = 0; // ������ ���Ƹ�
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

