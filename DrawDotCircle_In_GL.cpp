#include<glut.h>
#include<GL/gl.h>
#include<GL/GLU.h>
#include<math.h>
#define Pi 3.1415

void MyDisplay() {
	GLfloat Size[2];
	GLfloat Angle;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glGetFloatv(GL_POINT_SIZE_RANGE, Size);
	glPointSize(Size[0] * 10);
	glBegin(GL_POINTS);
	for (Angle = 0.0; Angle <= 2.0 * Pi; Angle += Pi / 20.0)
		glVertex3f(0.5 * cos(Angle), 0.5 * sin(Angle), 0.0);
	glEnd();
	glFlush();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Drawing Example");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}