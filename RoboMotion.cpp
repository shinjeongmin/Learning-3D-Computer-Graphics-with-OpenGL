#include <Windows.h> // 필수 헤더 파일들
#include <mmsystem.h>
#include <glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

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
GLfloat R_leg_y = 0; // 오른쪽 종아리
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

