#include<glut.h>
#include<GL/gl.h>
#include<GL/GLU.h>

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_TRIANGLES);
		glColor3f(0.0, 1.0, 0.0); // ���
		glVertex3f(-0.5, -0.5, 0.0); // ����1
		glColor3f(0.0, 0.0, 0.0); // ���
		glVertex3f(0.5, -0.5, 0.0); // ����2
		glColor3f(1.0, 0.0, 0.0); // ����
		glVertex3f(0.0, 0.5, 0.0); // ����3
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