#include <windows.h>
#include <glut.h>

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	//glVertex3f(-0.5, -0.5, 0.0);
	//glVertex3f(0.5, -0.5, 0.0);
	//glVertex3f(0.5, 0.5, 0.0);
	//glVertex3f(-0.5, 0.5, 0.0);
	glutWireTorus(0.2, 0.4, 6, 4);
	glEnd();
	glFlush();
}

int APIENTRY WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow){
	glutCreateWindow("OpenGL Drawing Example");
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}