#include "GL/freeglut.h"
#include "glm/gtc/quaternion.hpp"

#include "Mesh.h"

Mesh::Mesh(const glm::vec3& position)
{
	m_position = position;
	toggleDisplay[0] = true;
	toggleDisplay[1] = true;
	toggleDisplay[2] = true;
	toggleDisplay[3] = false;
	toggleDisplay[4] = false;
}

void Mesh::calcNormals()
{
	//Clears previous vertex normal values
	for (int i = 0; i < m_v_vn.size(); i++)
	{
		m_v_vn[i].second = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	//Calculates face normals and vertex normals
	for (int i = 0; i < m_f_fn.size(); i++)
	{
		float v12v13 = glm::acos(glm::dot(glm::normalize(m_v_vn[m_f_fn[i].first.y].first - m_v_vn[m_f_fn[i].first.x].first),
			glm::normalize(m_v_vn[m_f_fn[i].first.z].first - m_v_vn[m_f_fn[i].first.x].first)));
		float v21v23 = glm::acos(glm::dot(glm::normalize(m_v_vn[m_f_fn[i].first.x].first - m_v_vn[m_f_fn[i].first.y].first),
			glm::normalize(m_v_vn[m_f_fn[i].first.z].first - m_v_vn[m_f_fn[i].first.y].first)));
		float v31v32 = glm::acos(glm::dot(glm::normalize(m_v_vn[m_f_fn[i].first.x].first - m_v_vn[m_f_fn[i].first.z].first),
			glm::normalize(m_v_vn[m_f_fn[i].first.y].first - m_v_vn[m_f_fn[i].first.z].first)));

		m_f_fn[i].second = glm::cross(m_v_vn[m_f_fn[i].first.y].first - m_v_vn[m_f_fn[i].first.x].first, m_v_vn[m_f_fn[i].first.z].first - m_v_vn[m_f_fn[i].first.x].first);
		float faceArea = 0.5f * glm::length(m_f_fn[i].second);

		m_v_vn[m_f_fn[i].first.x].second += m_f_fn[i].second * faceArea * v12v13;
		m_v_vn[m_f_fn[i].first.y].second += m_f_fn[i].second * faceArea * v21v23;
		m_v_vn[m_f_fn[i].first.z].second += m_f_fn[i].second * faceArea * v31v32;
	}

	//Normalizes face normals and vertex normals
	for (int i = 0; i < m_f_fn.size(); i++)
	{
		m_f_fn[i].second = glm::normalize(m_f_fn[i].second);
	}

	for (int i = 0; i < m_v_vn.size(); i++)
	{
		m_v_vn[i].second = glm::normalize(m_v_vn[i].second);
	}
}

void Mesh::scale(const glm::vec3& scalingVector)
{
	m_position *= scalingVector;

	for (int i = 0; i < m_v_vn.size(); i++)
	{
		m_v_vn[i].first *= scalingVector;
	}
}

void Mesh::rotate(float angleDeg, const glm::vec3 origin, const glm::vec3& rotationVector)
{
	glm::quat rq = glm::rotate(glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::radians(angleDeg), rotationVector);

	translate(-origin);

	m_position = rq * m_position;

	for (int i = 0; i < m_v_vn.size(); i++)
	{
		m_v_vn[i].first = rq * m_v_vn[i].first;
		m_v_vn[i].second = rq * m_v_vn[i].second;
	}

	for (int i = 0; i < m_f_fn.size(); i++)
	{
		m_f_fn[i].second = rq * m_f_fn[i].second;
	}

	translate(origin);
}

void Mesh::translate(const glm::vec3& translationVector)
{
	m_position += translationVector;

	for (int i = 0; i < m_v_vn.size(); i++)
	{
		m_v_vn[i].first += translationVector;
	}
}

void Mesh::render()
{
	//Renders the points
	if (toggleDisplay[0])
	{
		glBegin(GL_POINTS);
		glColor3f(1.0f, 1.0f, 1.0f);
		for (int i = 0; i < m_v_vn.size(); i++)
		{
			glVertex3f(m_v_vn[i].first.x, m_v_vn[i].first.y, m_v_vn[i].first.z);
		}
		glEnd();
	}

	//Renders the lines
	if (toggleDisplay[1])
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		for (int i = 0; i < m_f_fn.size(); i++)
		{
			glBegin(GL_LINE_LOOP);
			glVertex3f(m_v_vn[m_f_fn[i].first.x].first.x, m_v_vn[m_f_fn[i].first.x].first.y, m_v_vn[m_f_fn[i].first.x].first.z);
			glVertex3f(m_v_vn[m_f_fn[i].first.y].first.x, m_v_vn[m_f_fn[i].first.y].first.y, m_v_vn[m_f_fn[i].first.y].first.z);
			glVertex3f(m_v_vn[m_f_fn[i].first.z].first.x, m_v_vn[m_f_fn[i].first.z].first.y, m_v_vn[m_f_fn[i].first.z].first.z);
			glEnd();
		}
	}

	//Renders the faces
	if (toggleDisplay[2])
	{
		glBegin(GL_TRIANGLES);
		glColor3f(0.5f, 0.5f, 0.5f);
		for (int i = 0; i < m_f_fn.size(); i++)
		{
			glVertex3f(m_v_vn[m_f_fn[i].first.x].first.x, m_v_vn[m_f_fn[i].first.x].first.y, m_v_vn[m_f_fn[i].first.x].first.z);
			glVertex3f(m_v_vn[m_f_fn[i].first.y].first.x, m_v_vn[m_f_fn[i].first.y].first.y, m_v_vn[m_f_fn[i].first.y].first.z);
			glVertex3f(m_v_vn[m_f_fn[i].first.z].first.x, m_v_vn[m_f_fn[i].first.z].first.y, m_v_vn[m_f_fn[i].first.z].first.z);
		}
		glEnd();
	}

	//Renders the face normals
	if (toggleDisplay[3])
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		for (int i = 0; i < m_f_fn.size(); i++)
		{
			float x = (m_v_vn[m_f_fn[i].first.x].first.x + m_v_vn[m_f_fn[i].first.y].first.x + m_v_vn[m_f_fn[i].first.z].first.x) / 3.0f;
			float y = (m_v_vn[m_f_fn[i].first.x].first.y + m_v_vn[m_f_fn[i].first.y].first.y + m_v_vn[m_f_fn[i].first.z].first.y) / 3.0f;
			float z = (m_v_vn[m_f_fn[i].first.x].first.z + m_v_vn[m_f_fn[i].first.y].first.z + m_v_vn[m_f_fn[i].first.z].first.z) / 3.0f;

			glBegin(GL_LINES);
			glVertex3f(x, y, z);
			glVertex3f(x + m_f_fn[i].second.x, y + m_f_fn[i].second.y, z + m_f_fn[i].second.z);
			glEnd();
		}
	}

	//Renders the vertex normals
	if (toggleDisplay[4])
	{
		glColor3f(0.0f, 0.0f, 1.0f);
		for (int i = 0; i < m_v_vn.size(); i++)
		{
			glBegin(GL_LINES);
			glVertex3f(m_v_vn[i].first.x, m_v_vn[i].first.y, m_v_vn[i].first.z);
			glVertex3f(m_v_vn[i].first.x + m_v_vn[i].second.x, m_v_vn[i].first.y + m_v_vn[i].second.y, m_v_vn[i].first.z + m_v_vn[i].second.z);
			glEnd();
		}
	}
}
