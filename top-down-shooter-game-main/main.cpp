// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW
#include "dependente\glew\glew.h"

// Include GLFW
#include "dependente\glfw\glfw3.h"

// Include GLM
#include "dependente\glm\glm.hpp"
#include "dependente\glm\gtc\matrix_transform.hpp"
#include "dependente\glm\gtc\type_ptr.hpp"

#include "shader.hpp"

//variables
GLFWwindow* window;
const int width = 1024, height = 768;
bool b = false;


//handling mouse input
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {

		b = true;

	}
}
int main(void)
{

	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(width, height, "Lab 4", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		glfwTerminate();
		return -1;
	}

	//specify the size of the rendering window
	glViewport(0, 0, width, height);

	// Background
	glClearColor(0.1f, 0.0f, 0.4f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);


	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");


	//Asteroids
	glm::vec3 asteroidsPos[] = {
		glm::vec3(0.0f,  0.66f,  0),
		glm::vec3(0.2f,  1.3f, 0),
		glm::vec3(-0.9f, 0.7f, 0),
		glm::vec3(-0.64f, 0.87f, 0),
		glm::vec3(0.4f, 0.45f, 0),
		glm::vec3(-0.27f,  1.0f, 0),
		glm::vec3(-0.73f, 0.62f, 0),
		glm::vec3(-0.35f,  0.81f, 0),
		glm::vec3(0.45f,  0.78f, 0),
		glm::vec3(0.8f,  1.1f, 0)
	};

	glm::vec3 initialPos[] = {
		glm::vec3(0.0f,  0.66f,  0),
		glm::vec3(0.2f,  1.3f, 0),
		glm::vec3(-0.9f, 0.7f, 0),
		glm::vec3(-0.64f, 0.87f, 0),
		glm::vec3(0.4f, 0.45f, 0),
		glm::vec3(-0.27f,  1.0f, 0),
		glm::vec3(-0.73f, 0.62f, 0),
		glm::vec3(-0.35f,  0.81f, 0),
		glm::vec3(0.45f,  0.78f, 0),
		glm::vec3(0.8f,  1.1f, 0)
	};

	GLfloat vertices[] = {
		0.05f,  0.05f, 0.0f,  // top right
		0.05f, -0.05f, 0.0f,  // bottom right
		-0.05f, -0.05f, 0.0f,  // bottom left
		-0.05f,  0.05f, 0.0f   // top left 
	};

	GLuint indices[] = {
		0, 3, 1,  // first Triangle
		1, 3, 2,   // second Triangle
	};

	//Ship 
	glm::vec3 shipPos(0.0f, -0.97f, 0.0f);

	float vertices2[] = {
		-0.04f,  -0.02f, 0.0f,  //  right
		0.04f, -0.02f, 0.0f,  //  left
		0.0f, 0.05f, 0.0f,  // top
	};

	unsigned int indices2[] = {
		0,1,2
	};

	//Bullet

	glm::vec3 bulletPos(0.0f, -0.98f, 0.0f);

	float vertices3[] = {
		-0.008f,  0.004f, 0.0f,  //  right
		0.008f, 0.004f, 0.0f,  //  left
		0.0f, -0.02f, 0.0f,  // top
	};

	unsigned int indices3[] = {
		0,1,2
	};


	// A Vertex Array Object (VAO) is an object which contains one or more Vertex Buffer Objects and is designed to store the information for a complete rendered object. 
	//Asteroids 
	GLuint vbo, vao, ibo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	//bind VAO
	glBindVertexArray(vao);

	//bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//bind IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//set attribute pointers
	glVertexAttribPointer(
		0,                  // attribute 0, must match the layout in the shader.
		3,                  // size of each attribute
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		3 * sizeof(float),  // stride
		(void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(0);

	//Ship
	GLuint vbo2, vao2, ibo2;
	glGenVertexArrays(1, &vao2);
	glGenBuffers(1, &vbo2);
	glGenBuffers(1, &ibo2);

	glBindVertexArray(vao2);

	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

	//set attribute pointers
	glVertexAttribPointer(
		0,                  // attribute 0, must match the layout in the shader.
		3,                  // size of each attribute
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		3 * sizeof(float),                  // stride
		(void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(0);

	//Bullet
	GLuint vbo3, vao3, ibo3;
	glGenVertexArrays(1, &vao3);
	glGenBuffers(1, &vbo3);
	glGenBuffers(1, &ibo3);

	glBindVertexArray(vao3);

	glBindBuffer(GL_ARRAY_BUFFER, vbo3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices3), indices3, GL_STATIC_DRAW);

	//set attribute pointers
	glVertexAttribPointer(
		0,                  // attribute 0, must match the layout in the shader.
		3,                  // size of each attribute
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		3 * sizeof(float),                  // stride
		(void*)0            // array buffer offset
	);
	glEnableVertexAttribArray(0);

	//Set Callback
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	// Check if the window was closed
	while (!glfwWindowShouldClose(window))
	{
		//Exit Game
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {

			glfwSetWindowShouldClose(window, true);
		}

		//User input
		//Move right
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			if (shipPos.x <= 0.9f) {
				shipPos.x = shipPos.x + 0.0008f;
				bulletPos.x = bulletPos.x + 0.0008f;
			}
		}

		//Move left
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			if (shipPos.x >= -0.9f) {
				shipPos.x = shipPos.x - 0.0008f;
				bulletPos.x = bulletPos.x - 0.0008f;
			}
		}

		//Move up
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			if (shipPos.y <= 0.9f) {
				shipPos.y = shipPos.y + 0.001f;
				bulletPos.y = bulletPos.y + 0.001f;
			}
		}

		//Move down
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			if (shipPos.y >= -0.9f) {
				shipPos.y = shipPos.y - 0.001f;
				bulletPos.y = bulletPos.y - 0.001f;
			}
		}


		// Swap buffers
		glfwSwapBuffers(window);

		// Check for events
		glfwPollEvents();

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		//bind VAO
		glBindVertexArray(vao);

		//if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		for (int i = 0; i < 10; i++) {

			//Create matrice to transform(asteroids)
			glm::mat4 trans(1.0f);
			trans = glm::translate(trans, asteroidsPos[i]);
			trans = glm::rotate(trans, (float)glfwGetTime() * 150, glm::vec3(1.0f, 0.5f, 0.0f));

			//transform matrix
			unsigned int transformLoc = glGetUniformLocation(programID, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
			

			//color
			unsigned int transformLoc2 = glGetUniformLocation(programID, "color");


			if (glfwGetTime() < 40) {
				glm::vec4 color = glm::vec4(0.2f, 0.2f, 0.2f, 0.0);
				glUniform4fv(transformLoc2, 1, glm::value_ptr(color));
			}


			//Show higher difficulty by asteroids color turning red
			else {
				glm::vec4 color = glm::vec4(0.5f, 0.0f, 0.0f, 0.0);
				glUniform4fv(transformLoc2, 1, glm::value_ptr(color));
			}

			//Computing distance between asteoirds and bullet for collision detection
			float distx2 = asteroidsPos[i].x - bulletPos.x;
			float disty2 = asteroidsPos[i].y - bulletPos.y;
			float distance2 = sqrt(pow(distx2, 2) + pow(disty2, 2));

			//Asteroids coming towards ship
			if (distance2 >= 0.07f) {
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				if (glfwGetTime() < 40) {
					asteroidsPos[i].y = asteroidsPos[i].y - 0.0001f;
				}

				//Higher difficulty after a while
				else {
					asteroidsPos[i].y = asteroidsPos[i].y - 0.0004f;
				}

				//Computing distance between asteoirds and ship for collision detection
				float distx = asteroidsPos[i].x - shipPos.x;
				float disty = asteroidsPos[i].y - shipPos.y;
				float distance = sqrt(pow(distx, 2) + pow(disty, 2));

				//Ship coming back to restart position
				if (distance <= 0.07f) {
					shipPos.y = -0.97f;
					shipPos.x = 0.0f;
					bulletPos.y = -0.98f;
					bulletPos.x = 0.0f;

					//Show message in console
					std::cout << " Ship destroyed!" << std::endl;
					std::cout << " Try again!" << std::endl;

				}


			}

			//Destroy asteroids
			if (distance2 <= 0.05f) {
				b = false;
				bulletPos.y = shipPos.y;
				bulletPos.x = shipPos.x;
				asteroidsPos[i].x = asteroidsPos[i].x + 5.0f;

				//Show message in console
				std::cout << " Damage 100%" << std::endl;
			}

			//Asteroids coming in waves
			if (asteroidsPos[i].y <= -1.5f) {
				asteroidsPos[i] = initialPos[i];
			}

		}

		//Create matrice to transform(ship)
		glm::mat4 model;

		model = glm::translate(model, shipPos);

		unsigned int transformLoc = glGetUniformLocation(programID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Color
		unsigned int transformLoc2 = glGetUniformLocation(programID, "color");
		glUniform4fv(transformLoc2, 1, glm::value_ptr(glm::vec3(0.9f, 0.2f, 0.4)));
		glBindVertexArray(vao2);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		if (b == true) {
			//Create matrice to transform(bullets)
			glm::mat4 model2(1.0f);

			model2 = glm::translate(model2, bulletPos);
			bulletPos.y = bulletPos.y + 0.001f;

			unsigned int transformLoc3 = glGetUniformLocation(programID, "transform");
			glUniformMatrix4fv(transformLoc3, 1, GL_FALSE, glm::value_ptr(model2));

			//Color
			unsigned int transformLoc4 = glGetUniformLocation(programID, "color");
			glUniform4fv(transformLoc4, 1, glm::value_ptr(glm::vec3(0.9f, 0.0f, 0.9)));
			glBindVertexArray(vao3);


			//Bulet recovery
			if (bulletPos.y >= 1.0f) {
				b = false;
				bulletPos.y = shipPos.y;
				bulletPos.x = shipPos.x;

			}
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		}
	}



	// Cleanup
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo2);
	glDeleteBuffers(1, &ibo2);
	glDeleteVertexArrays(1, &vao2);
	glDeleteBuffers(1, &vbo3);
	glDeleteBuffers(1, &ibo3);
	glDeleteVertexArrays(1, &vao3);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}
