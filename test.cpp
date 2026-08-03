#include "scop.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

const char *vertexShaderSource =
	R"(#version 330 core
		layout (location = 0) in vec3 aPos;
		layout (location = 1) in vec3 aColor;

		out vec3 vertexColor;

		void main()
		{
		   gl_Position = vec4(aPos, 1.0);
		   vertexColor = aColor;
		})";

const char *fragmentShaderSource =
	R"(#version 330 core
		in vec3 vertexColor;
		out vec4 FragColor;

		void main()
		{
		   FragColor = vec4(vertexColor, 1);
		})";

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
}

void makeTriangle(unsigned int *VBO, unsigned int *VAO)
{
	// Create Triangle vertecies
	float vertices[] = {
		// positions        // colors
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f	  // top
	};

	glGenBuffers(1, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	/*	GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
		GL_STATIC_DRAW: the data is set only once and used many times.
		GL_DYNAMIC_DRAW: the data is changed a lot and used many times.	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, VAO);
	// 1. bind Vertex Array Object
	glBindVertexArray(*VAO);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. then set our vertex attributes pointers
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void makeRectangle(unsigned int *VBO, unsigned int *VAO, unsigned int *EBO)
{
	float vertices[] = {
		// positions        // colors         // texture coords
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,	  // top right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f	  // top left
	};
	unsigned int indices[] = {
		// note that we start from 0!
		0, 1, 3, // first Triangle
		1, 2, 3	 // second Triangle
	};

	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	glGenBuffers(1, EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(*VAO);

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
	(void)window;
}

int main(void)
{
	GLFWwindow *window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Penis Arsch®", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	unsigned int VBO; // VBO - vertex buffer object
	unsigned int VAO; // VAO - vertex array object
	unsigned int EBO; // EBO - element buffer object

	// makeTriangle(&VBO, &VAO);
	makeRectangle(&VBO, &VAO, &EBO);

	unsigned int texture1 = loadTex("resources/mine/lank.png", GL_RGB);
	unsigned int texture2 = loadTex("resources/mine/genon.png", GL_RGBA);

	Shader shaders("./shaders/shader.vs", GL_VERTEX_SHADER);
	shaders.addShader("./shaders/shader.fs", GL_FRAGMENT_SHADER);
	shaders.use();													   // don't forget to activate the shader before setting uniforms!
	glUniform1i(glGetUniformLocation(shaders.getId(), "texture1"), 0); // set it manually
	shaders.setInt("texture2", 1);									   // or with shader class

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		/* Render here */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::rotate(trans, (float)glm::radians(90.0f) * (float)glfwGetTime(), glm::vec3(0, 0, 1));

		auto bind = glGetUniformLocation(shaders.getId(), "transform");
		glUniformMatrix4fv(bind, 1, 0, glm::value_ptr(trans));

		// float timeValue = glfwGetTime();
		// float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		// int vertexColorLocation = glGetUniformLocation(shaders.getId(), "vertexColor");
		// glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		// draw triangle
		// glBindVertexArray(VAO);
		// glDrawArrays(GL_TRIANGLES, 0, 3);

		// draw rectangle

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	// glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}