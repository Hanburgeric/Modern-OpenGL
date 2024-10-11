#include "GL/freeglut.h"

#include "Simulator.h"

//OpenGL callback functions
void motion(int x, int y);
void mouse(int mouseEvent, int mouseState, int x, int y);
void keyboard(unsigned char key, int x, int y);
void specialFunc(int key, int x, int y);
void update(int value);
void render();
void reshape(int width, int height);

//Simulator
Simulator* glSimulator = nullptr;

int main(int argc, char* argv[])
{
	//Initializes gl
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1080) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 720) / 2);
	glutInitWindowSize(1080, 720);
	glutCreateWindow("Particle Test Simulation");
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	//Allocates and initializes simulator
	glSimulator = new Simulator();
	glSimulator->init();

	//Main loop
	glutMotionFunc(motion);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialFunc);
	glutTimerFunc(16, update, 16);
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutMainLoop();

	//Cleans up and deallocates simulator
	delete glSimulator;
	glSimulator = nullptr;

	return 0;
}

void motion(int x, int y)
{
	glSimulator->motion(x, y);
}

void mouse(int mouseEvent, int mouseState, int x, int y)
{
	glSimulator->mouse(mouseEvent, mouseState, x, y);
}

void keyboard(unsigned char key, int x, int y)
{
	glSimulator->keyboard(key, x, y);
}

void specialFunc(int key, int x, int y)
{
	glSimulator->specialFunc(key, x, y);
}

void update(int value)
{
	glSimulator->update(value);
	glutPostRedisplay();
	glutTimerFunc(16, update, 16);
}

void render()
{
	glSimulator->render();
}

void reshape(int width, int height)
{
	glSimulator->reshape(width, height);
}
