#include "MyGlWindow.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"

static float DEFAULT_VIEW_POINT[3] = { -10, 10, 10 };
static float DEFAULT_VIEW_CENTER[3] = { 0, 10, 0 };
static float DEFAULT_UP_VECTOR[3] = { 0, 1, 0 };

MyGlWindow::MyGlWindow(float w, float h)
{
	m_width = w;
	m_height = h;

	m_color_cube = new ColorCube();
	m_wire_cube = new WireCube();
	m_floor = new CheckeredFloor(50, 16);
	m_line = new RedLine(glm::vec4(0, 0, 0, 1), glm::vec4(0, 10, 0, 1));

	glm::vec3 viewPoint(DEFAULT_VIEW_POINT[0], DEFAULT_VIEW_POINT[1], DEFAULT_VIEW_POINT[2]);
	glm::vec3 viewCenter(DEFAULT_VIEW_CENTER[0], DEFAULT_VIEW_CENTER[1], DEFAULT_VIEW_CENTER[2]);
	glm::vec3 upVector(DEFAULT_UP_VECTOR[0], DEFAULT_UP_VECTOR[1], DEFAULT_UP_VECTOR[2]);

	float aspect = (w / (float)h);
	m_viewer = new Viewer(viewPoint, viewCenter, upVector, 45.0f, aspect);

	setupBuffer();
}

MyGlWindow::~MyGlWindow()
{

}


void MyGlWindow::resize(int width, int height) {
	m_height = height;
	m_width = width;
}

void MyGlWindow::setupBuffer()
{
	m_shaderProgram = new ShaderProgram();
	m_shaderProgram->initFromFiles("simple.vert", "simple.frag");
	
	//add uniform variables
	m_shaderProgram->addUniform("mvp");
}

void MyGlWindow::draw(float rotate, float X_translation, float Y_translation, bool cube_view)
{
	int height = 6;
	glm::mat4 model;
	glm::mat4 mvp;
	glm::vec3 eye;
	glm::vec3 look;
	glm::vec3 up = m_viewer->getUpVector();

	m_shaderProgram->use(); //call our shader

	// view Matrix
	if (cube_view) {
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), rotate * (3.14f/180), glm::vec3(0, 1, 0));
		eye = glm::vec3(2, 2 * height, 0);
		eye += glm::vec3((2 * (height - 2) * X_translation), -(2 * (height - 1) * Y_translation), 0);
		eye = glm::mat3(rotation) * eye;
		look = eye + glm::mat3(rotation) * glm::vec3(5, 0, 0);
		
	} else {
		eye = m_viewer->getViewPoint();
		look = m_viewer->getViewCenter();
	}
	

	glm::mat4 view = lookAt(eye, look, up);
	glm::mat4 projection = glm::perspective(45.0f, m_width / m_height, 0.1f, 500.0f);

	// Draw the Red Line
	m_model.glPushMatrix();
	m_model.glRotate(rotate, 0, 1, 0);
	m_model.glTranslate(2, 2 * height + 1, 0);

	glm::vec4 start = glm::vec4((2 * (height - 2) * X_translation), 0, 0, 1);
	glm::vec4 end = glm::vec4((2 * (height - 2) * X_translation), -(2 * (height - 1) * Y_translation), 0, 1);

	m_line->update(start, end);

	model = m_model.getMatrix();
	mvp = projection * view * model;

	glUniformMatrix4fv(m_shaderProgram->uniform("mvp"), 1, GL_FALSE, glm::value_ptr(mvp));

	m_line->draw();

	m_model.glPopMatrix();

	// Draw the Checkered floor
	m_model.glPushMatrix(); //for saving 

	m_model.glTranslate(0, 1, 0);

	model = m_model.getMatrix();
	mvp = projection * view * model;

	glUniformMatrix4fv(m_shaderProgram->uniform("mvp"), 1, GL_FALSE, glm::value_ptr(mvp));

	m_floor->draw();


	m_model.glPopMatrix();


	// Draw the Wire Cubes for the Crane 
	for (int i = 0; i < height; i++) {
		//model Matrix

		m_model.glPushMatrix();
		m_model.glTranslate(0, 2*(i + 1), 0);
		model = m_model.getMatrix();
		mvp = projection * view * model;

		glUniformMatrix4fv(m_shaderProgram->uniform("mvp"), 1, GL_FALSE, glm::value_ptr(mvp));

		m_wire_cube->draw();

		m_model.glPopMatrix(); //restoring
	}

	// Draw the Boom
	for (int i = -1; i < height ; i++) {
		//model Matrix

		m_model.glPushMatrix();
		m_model.glRotate(rotate, 0, 1, 0);
		m_model.glTranslate(2 * i, 2 * (height + 1), 0);
		model = m_model.getMatrix();
		mvp = projection * view * model;

		glUniformMatrix4fv(m_shaderProgram->uniform("mvp"), 1, GL_FALSE, glm::value_ptr(mvp));

		m_wire_cube->draw();

		m_model.glPopMatrix(); //restoring
	}

	// Draw the Color Cube

	m_model.glPushMatrix();

	m_model.glRotate(rotate, 0, 1, 0);
	m_model.glTranslate(2, 2 * height, 0);
	m_model.glTranslate((2 * (height - 2) * X_translation), -(2 * (height - 1) * Y_translation), 0);

	model = m_model.getMatrix();
	mvp = projection * view * model;

	glUniformMatrix4fv(m_shaderProgram->uniform("mvp"), 1, GL_FALSE, glm::value_ptr(mvp));
	if (!cube_view) {
		m_color_cube->draw();
	}
	m_model.glPopMatrix();

	m_shaderProgram->disable();
}
