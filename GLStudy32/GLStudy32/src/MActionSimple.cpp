#include "MActionSimple.h"
#include <glm/gtc/matrix_transform.hpp>

void MActionSimple::initMatrix()
{
	projection = glm::perspective(45.0f, 1.0f / 1.0f, 0.1f, 100.0f);
	View = glm::lookAt(
		glm::vec3(0, 0, 6), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
	Model = glm::mat4(1.0f);
}

glm::mat4 MActionSimple::getMVP()
{	
	Model = glm::rotate(Model, 0.001f, glm::vec3(1, 1, 1));
	//Model = glm::translate(Model, glm::vec3(0.01f, 0, 0));
	return projection*View*Model;
}
