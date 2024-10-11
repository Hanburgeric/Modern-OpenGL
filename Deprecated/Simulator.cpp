#include "GL/freeglut.h"
#include <stdio.h>

#include "Cube.h"
#include "Simulator.h"

Simulator::Simulator()
{
	printf("==================================================\n");
	printf("1: Toggle Points\n");
	printf("2: Toggle Lines\n");
	printf("3: Toggle Faces\n");
	printf("4: Toggle Face Normals\n");
	printf("5: Toggle Vertex Normals\n");
	printf("==================================================\n");
	printf("[: Rotate Around Individual Axes\n");
	printf("]: Rotate Around World Axes\n");
	printf("==================================================\n");

	//Initializes camera settings (these do not reset when the simulation is restarted)
	m_translate.x = 14.5f;
	m_translate.y = 5.0f;
	m_translate.z = 50.0f;

	m_rotate.x = 0.0f;
	m_rotate.y = 0.0f;
}

Simulator::~Simulator()
{
	cleanup();
}

void Simulator::init()
{
	//Initializes simulator (these reset when the simulation is restarted)
	m_start[0] = false;
	m_start[1] = false;

	m_mousePos.x = 0;
	m_mousePos.y = 0;

	m_mouseEvent[0] = false;
	m_mouseEvent[1] = false;

	//한
	m_cubes.push_back(Cube(glm::vec3(), 1.0f));
	m_cubes[0].m_mesh.scale(glm::vec3(1.0f, 1.5f, 1.0f));
	m_cubes[0].m_mesh.translate(glm::vec3(2.5f, 9.25f, 0.0f));

	m_cubes.push_back(Cube(glm::vec3(), 1.0f));
	m_cubes[1].m_mesh.scale(glm::vec3(5.0f, 1.0f, 1.0f));
	m_cubes[1].m_mesh.translate(glm::vec3(2.5f, 8.0f, 0.0f));

	m_toruses.push_back(Torus(glm::vec3(), 1.5f, 0.5f, 36, 12));
	m_toruses[0].m_mesh.scale(glm::vec3(1.25f, 1.0f, 1.0f));
	m_toruses[0].m_mesh.rotate(90.0f, glm::vec3(), glm::vec3(1.0f, 0.0f, 0.0f));
	m_toruses[0].m_mesh.translate(glm::vec3(2.5f, 5.0f, 0.0f));

	m_cubes.push_back(Cube(glm::vec3(), 1.0f));
	m_cubes[2].m_mesh.scale(glm::vec3(1.0f, 7.5f, 1.0f));
	m_cubes[2].m_mesh.translate(glm::vec3(6.5f, 6.25f, 0.0f));

	m_cubes.push_back(Cube(glm::vec3(), 1.0f));
	m_cubes[3].m_mesh.scale(glm::vec3(1.5f, 1.0f, 1.0f));
	m_cubes[3].m_mesh.translate(glm::vec3(7.75f, 6.5f, 0.0f));

	m_cubes.push_back(Cube(glm::vec3(), 1.0f));
	m_cubes[4].m_mesh.scale(glm::vec3(1.0f, 2.5f, 1.0f));
	m_cubes[4].m_mesh.translate(glm::vec3(1.5f, 1.25f, 0.0f));

	m_cubes.push_back(Cube(glm::vec3(), 1.0f));
	m_cubes[5].m_mesh.scale(glm::vec3(5.0f, 1.0f, 1.0f));
	m_cubes[5].m_mesh.translate(glm::vec3(4.5f, 0.5f, 0.0f));

	//원
	m_toruses.push_back(Torus(glm::vec3(), 1.5f, 0.5f, 36, 12));
	m_toruses[1].m_mesh.scale(glm::vec3(1.25f, 1.0f, 1.0f));
	m_toruses[1].m_mesh.rotate(90.0f, glm::vec3(), glm::vec3(1.0f, 0.0f, 0.0f));
	m_toruses[1].m_mesh.translate(glm::vec3(13.5f, 8.0f, 0.0f));

	m_cubes.push_back(Cube(glm::vec3(), 1.0f));
	m_cubes[6].m_mesh.scale(glm::vec3(5.5f, 1.0f, 1.0f));
	m_cubes[6].m_mesh.translate(glm::vec3(13.75f, 5.0f, 0.0f));

	m_cubes.push_back(Cube(glm::vec3(), 1.0f));
	m_cubes[7].m_mesh.scale(glm::vec3(1.0f, 2.0f, 1.0f));
	m_cubes[7].m_mesh.translate(glm::vec3(13.5f, 3.5f, 0.0f));

	m_cubes.push_back(Cube(glm::vec3(), 1.0f));
	m_cubes[8].m_mesh.scale(glm::vec3(3.0f, 1.0f, 1.0f));
	m_cubes[8].m_mesh.translate(glm::vec3(16.0f, 3.5f, 0.0f));

	m_cubes.push_back(Cube(glm::vec3(), 1.0f));
	m_cubes[9].m_mesh.scale(glm::vec3(1.0f, 7.5f, 1.0f));
	m_cubes[9].m_mesh.translate(glm::vec3(18.0f, 6.25f, 0.0f));

	m_cubes.push_back(Cube(glm::vec3(), 1.0f));
	m_cubes[10].m_mesh.scale(glm::vec3(1.0f, 2.5f, 1.0f));
	m_cubes[10].m_mesh.translate(glm::vec3(12.0f, 1.25f, 0.0f));

	m_cubes.push_back(Cube(glm::vec3(), 1.0f));
	m_cubes[11].m_mesh.scale(glm::vec3(6.0f, 1.0f, 1.0f));
	m_cubes[11].m_mesh.translate(glm::vec3(15.5f, 0.5f, 0.0f));

	//진
	m_cubes.push_back(Cube(glm::vec3(), 1.0f));
	m_cubes[12].m_mesh.scale(glm::vec3(6.0f, 1.0f, 1.0f));
	m_cubes[12].m_mesh.translate(glm::vec3(24.0f, 9.5f, 0.0f));

	m_cubes.push_back(Cube(glm::vec3(), 1.0f));
	m_cubes[13].m_mesh.scale(glm::vec3(6.0f, 1.0f, 1.0f));
	m_cubes[13].m_mesh.rotate(60.0f, glm::vec3(), glm::vec3(0.0f, 0.0f, 1.0f));
	m_cubes[13].m_mesh.translate(glm::vec3(22.875f, 7.125f, 0.0f));

	m_cubes.push_back(Cube(glm::vec3(), 1.0f));
	m_cubes[14].m_mesh.scale(glm::vec3(6.0f, 1.0f, 1.0f));
	m_cubes[14].m_mesh.rotate(120.0f, glm::vec3(), glm::vec3(0.0f, 0.0f, 1.0f));
	m_cubes[14].m_mesh.translate(glm::vec3(25.125f, 7.125f, 0.0f));

	m_cubes.push_back(Cube(glm::vec3(), 1.0f));
	m_cubes[15].m_mesh.scale(glm::vec3(1.0f, 7.5f, 1.0f));
	m_cubes[15].m_mesh.translate(glm::vec3(28.5f, 6.25f, 0.0f));

	m_cubes.push_back(Cube(glm::vec3(), 1.0f));
	m_cubes[16].m_mesh.scale(glm::vec3(1.0f, 2.5f, 1.0f));
	m_cubes[16].m_mesh.translate(glm::vec3(22.5f, 1.25f, 0.0f));

	m_cubes.push_back(Cube(glm::vec3(), 1.0f));
	m_cubes[17].m_mesh.scale(glm::vec3(6.0f, 1.0f, 1.0f));
	m_cubes[17].m_mesh.translate(glm::vec3(26.0f, 0.5f, 0.0f));
}

void Simulator::cleanup()
{
	m_toruses.clear();
	m_cubes.clear();
}

void Simulator::motion(int x, int y)
{
	//Calculates the difference between the current and previous mouse positions
	int deltaX = x - m_mousePos.x;
	int deltaY = y - m_mousePos.y;

	//Updates the current mouse position
	m_mousePos.x = x;
	m_mousePos.y = y;

	//Translates the camera
	if (m_mouseEvent[0])
	{
		m_translate[0] -= 0.1f * (float)deltaX;
		m_translate[1] += 0.1f * (float)deltaY;
	}

	//Rotates the camera
	else if (m_mouseEvent[1])
	{
		m_rotate[0] += 0.1f * (float)deltaY;
		m_rotate[1] += 0.1f * (float)deltaX;
	}

	glutPostRedisplay();
}

void Simulator::mouse(int mouseEvent, int mouseState, int x, int y)
{
	//Updates the mouse position
	m_mousePos.x = x;
	m_mousePos.y = y;

	switch (mouseEvent)
	{
	case GLUT_LEFT_BUTTON:
	{
		if (GLUT_DOWN == mouseState)
		{
			m_mouseEvent[0] = true;
		}
		else
		{
			m_mouseEvent[0] = false;
		}
		break;
	}
	case GLUT_RIGHT_BUTTON:
	{
		if (GLUT_DOWN == mouseState)
		{
			m_mouseEvent[1] = true;
		}
		else
		{
			m_mouseEvent[1] = false;
		}
		break;
	}
	case 3:
	{
		m_translate.z -= 2.5f;
		break;
	}
	case 4:
	{
		m_translate.z += 2.5f;
		break;
	}
	default:
	{
		break;
	}
	}

	glutPostRedisplay();
}

void Simulator::keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ' ':
	{
		m_start[0] = !m_start[0];
		m_start[1] = !m_start[1];
		break;
	}
	case '[':
	{
		m_start[0] = !m_start[0];
		break;
	}
	case ']':
	{
		m_start[1] = !m_start[1];
		break;
	}
	case 'r':
	{
		cleanup();
		init();
		break;
	}
	case '1':
	{
		for (int i = 0; i < m_cubes.size(); i++)
		{
			m_cubes[i].m_mesh.toggleDisplay[0] = !m_cubes[i].m_mesh.toggleDisplay[0];
		}
		for (int i = 0; i < m_toruses.size(); i++)
		{
			m_toruses[i].m_mesh.toggleDisplay[0] = !m_toruses[i].m_mesh.toggleDisplay[0];
		}
		break;
	}
	case '2':
	{
		for (int i = 0; i < m_cubes.size(); i++)
		{
			m_cubes[i].m_mesh.toggleDisplay[1] = !m_cubes[i].m_mesh.toggleDisplay[1];
		}
		for (int i = 0; i < m_toruses.size(); i++)
		{
			m_toruses[i].m_mesh.toggleDisplay[1] = !m_toruses[i].m_mesh.toggleDisplay[1];
		}
		break;
	}
	case '3':
	{
		for (int i = 0; i < m_cubes.size(); i++)
		{
			m_cubes[i].m_mesh.toggleDisplay[2] = !m_cubes[i].m_mesh.toggleDisplay[2];
		}
		for (int i = 0; i < m_toruses.size(); i++)
		{
			m_toruses[i].m_mesh.toggleDisplay[2] = !m_toruses[i].m_mesh.toggleDisplay[2];
		}
		break;
	}
	case '4':
	{
		for (int i = 0; i < m_cubes.size(); i++)
		{
			m_cubes[i].m_mesh.toggleDisplay[3] = !m_cubes[i].m_mesh.toggleDisplay[3];
		}
		for (int i = 0; i < m_toruses.size(); i++)
		{
			m_toruses[i].m_mesh.toggleDisplay[3] = !m_toruses[i].m_mesh.toggleDisplay[3];
		}
		break;
	}
	case '5':
	{
		for (int i = 0; i < m_cubes.size(); i++)
		{
			m_cubes[i].m_mesh.toggleDisplay[4] = !m_cubes[i].m_mesh.toggleDisplay[4];
		}
		for (int i = 0; i < m_toruses.size(); i++)
		{
			m_toruses[i].m_mesh.toggleDisplay[4] = !m_toruses[i].m_mesh.toggleDisplay[4];
		}
	}
	default:
	{
		break;
	}
	}

	glutPostRedisplay();
}

void Simulator::specialFunc(int key, int x, int y)
{
	switch (key)
	{
	default:
	{
		break;
	}
	}

	glutPostRedisplay();
}

void Simulator::update(int value)
{
	if (m_start[0])
	{
		//X rotation
		m_cubes[1].m_mesh.rotate(3.0f, glm::vec3(m_cubes[1].m_mesh.m_position), m_cubes[1].m_mesh.m_v_vn[4].first - m_cubes[1].m_mesh.m_v_vn[0].first);
		m_cubes[3].m_mesh.rotate(3.0f, glm::vec3(m_cubes[3].m_mesh.m_position), m_cubes[3].m_mesh.m_v_vn[4].first - m_cubes[3].m_mesh.m_v_vn[0].first);
		m_cubes[5].m_mesh.rotate(3.0f, glm::vec3(m_cubes[5].m_mesh.m_position), m_cubes[5].m_mesh.m_v_vn[4].first - m_cubes[5].m_mesh.m_v_vn[0].first);
		m_cubes[6].m_mesh.rotate(3.0f, glm::vec3(m_cubes[6].m_mesh.m_position), m_cubes[6].m_mesh.m_v_vn[4].first - m_cubes[6].m_mesh.m_v_vn[0].first);
		m_cubes[8].m_mesh.rotate(3.0f, glm::vec3(m_cubes[8].m_mesh.m_position), m_cubes[8].m_mesh.m_v_vn[4].first - m_cubes[8].m_mesh.m_v_vn[0].first);
		m_cubes[11].m_mesh.rotate(3.0f, glm::vec3(m_cubes[11].m_mesh.m_position), m_cubes[11].m_mesh.m_v_vn[4].first - m_cubes[11].m_mesh.m_v_vn[0].first);
		m_cubes[12].m_mesh.rotate(3.0f, glm::vec3(m_cubes[12].m_mesh.m_position), m_cubes[12].m_mesh.m_v_vn[4].first - m_cubes[12].m_mesh.m_v_vn[0].first);
		m_cubes[13].m_mesh.rotate(3.0f, glm::vec3(m_cubes[13].m_mesh.m_position), m_cubes[13].m_mesh.m_v_vn[4].first - m_cubes[13].m_mesh.m_v_vn[0].first);
		m_cubes[14].m_mesh.rotate(3.0f, glm::vec3(m_cubes[14].m_mesh.m_position), m_cubes[14].m_mesh.m_v_vn[4].first - m_cubes[14].m_mesh.m_v_vn[0].first);
		m_cubes[17].m_mesh.rotate(3.0f, glm::vec3(m_cubes[17].m_mesh.m_position), m_cubes[17].m_mesh.m_v_vn[4].first - m_cubes[17].m_mesh.m_v_vn[0].first);

		//Y rotation
		m_cubes[0].m_mesh.rotate(3.0f, glm::vec3(m_cubes[0].m_mesh.m_position), m_cubes[0].m_mesh.m_v_vn[2].first - m_cubes[0].m_mesh.m_v_vn[0].first);
		m_cubes[2].m_mesh.rotate(3.0f, glm::vec3(m_cubes[2].m_mesh.m_position), m_cubes[2].m_mesh.m_v_vn[2].first - m_cubes[2].m_mesh.m_v_vn[0].first);
		m_cubes[4].m_mesh.rotate(3.0f, glm::vec3(m_cubes[4].m_mesh.m_position), m_cubes[4].m_mesh.m_v_vn[2].first - m_cubes[4].m_mesh.m_v_vn[0].first);
		m_cubes[7].m_mesh.rotate(3.0f, glm::vec3(m_cubes[7].m_mesh.m_position), m_cubes[7].m_mesh.m_v_vn[2].first - m_cubes[7].m_mesh.m_v_vn[0].first);
		m_cubes[9].m_mesh.rotate(3.0f, glm::vec3(m_cubes[9].m_mesh.m_position), m_cubes[9].m_mesh.m_v_vn[2].first - m_cubes[9].m_mesh.m_v_vn[0].first);
		m_cubes[10].m_mesh.rotate(3.0f, glm::vec3(m_cubes[10].m_mesh.m_position), m_cubes[10].m_mesh.m_v_vn[2].first - m_cubes[10].m_mesh.m_v_vn[0].first);
		m_cubes[15].m_mesh.rotate(3.0f, glm::vec3(m_cubes[15].m_mesh.m_position), m_cubes[15].m_mesh.m_v_vn[2].first - m_cubes[15].m_mesh.m_v_vn[0].first);
		m_cubes[16].m_mesh.rotate(3.0f, glm::vec3(m_cubes[16].m_mesh.m_position), m_cubes[16].m_mesh.m_v_vn[2].first - m_cubes[16].m_mesh.m_v_vn[0].first);

		//Torus rotation
		m_toruses[0].m_mesh.rotate(3.0f, m_toruses[0].m_mesh.m_position, glm::vec3(2.0f, 5.0f, 3.0f));
		m_toruses[1].m_mesh.rotate(3.0f, m_toruses[1].m_mesh.m_position, glm::vec3(-13.0f, -11.0f, -7.0f));
	}

	if (m_start[1])
	{
		//한
		for (int i = 0; i < 6; i++)
		{
			m_cubes[i].m_mesh.rotate(3.0f, glm::vec3(), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		m_toruses[0].m_mesh.rotate(3.0f, glm::vec3(), glm::vec3(1.0f, 0.0f, 0.0f));

		//원
		for (int i = 6; i < 12; i++)
		{
			m_cubes[i].m_mesh.rotate(3.0f, glm::vec3(), glm::vec3(0.0f, 1.0f, 0.0f));
		}
		m_toruses[1].m_mesh.rotate(3.0f, glm::vec3(), glm::vec3(0.0f, 1.0f, 0.0f));

		//진
		for (int i = 12; i < 18; i++)
		{
			m_cubes[i].m_mesh.rotate(3.0f, glm::vec3(), glm::vec3(0.0f, 0.0f, 1.0f));
		}
	}
}

void Simulator::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(-m_translate.x, -m_translate.y, -m_translate.z);
	glRotatef(m_rotate.x, 1.0f, 0.0f, 0.0f);
	glRotatef(m_rotate.y, 0.0f, 1.0f, 0.0f);

	//Axes
	glBegin(GL_LINES);
	//X-Axis
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	//Y-Axis
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	//Z-Axis
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();

	//Cubes
	for (int i = 0; i < m_cubes.size(); i++)
	{
		m_cubes[i].render();
	}

	//Toruses
	for (int i = 0; i < m_toruses.size(); i++)
	{
		m_toruses[i].render();
	}

	glutSwapBuffers();
	glutPostRedisplay();
}

void Simulator::reshape(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)width / (float)height, 0.1f, 500.0f);
	glViewport(0.0f, 0.0f, width, height);
}
