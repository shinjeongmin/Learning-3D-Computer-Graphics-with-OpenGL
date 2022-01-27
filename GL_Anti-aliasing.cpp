#include<glut.h>
#include<GL/gl.h>
#include<GL/GLU.h>

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glPointSize(12);
	glBegin(GL_POINTS);
		glVertex3f(-0.9, -0.65, 0);
	glEnd();
	glDisable(GL_POINT_SMOOTH);

	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glBegin(GL_LINES);
		glVertex3f(-1.0, -0.6, 0.0);
		glVertex3f(1.0, -0.2, 0.0);
		glVertex3f(-1.0, -0.6, 0.0);
		glVertex3f(0.75, 1.0, 0.0);
		glVertex3f(-1.0, -0.6, 0.0);
		glVertex3f(-0.75, 1.0, 0.0);
	glEnd();
	glDisable(GL_LINE_SMOOTH);
	
	glDisable(GL_BLEND);
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