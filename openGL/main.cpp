//https://heinleinsgame.tistory.com/8
// sample.cpp
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stdlib.h>
#include "glm/gtc/matrix_transform.hpp"
#include "include/GL/glew.h"		
#include "include/GLFW/glfw3.h" 
#include "glm/glm.hpp"

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib-vc2017/glew32.lib")
#pragma comment(lib, "lib-vc2017/glfw3.lib")

GLFWwindow* window;

using namespace glm;
using namespace std;

GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path) {

	// 쉐이더들 생성
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// 버텍스 쉐이더 코드를 파일에서 읽기
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else {
		printf("파일 %s 를 읽을 수 없음. 정확한 디렉토리를 사용 중입니까 ? FAQ 를 우선 읽어보는 걸 잊지 마세요!\n", vertex_file_path);
		getchar();
		return 0;
	}

	// 프래그먼트 쉐이더 코드를 파일에서 읽기
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;


	// 버텍스 쉐이더를 컴파일
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// 버텍스 쉐이더를 검사
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// 프래그먼트 쉐이더를 컴파일
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// 프래그먼트 쉐이더를 검사
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// 프로그램에 링크
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// 프로그램 검사
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}



int main(void)
{
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(1024, 768, "Tutorial 04 - Colored Cube", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders("vs.shader", "fs.shader");

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 0, -20), // Camera is at (4,3,-3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 Model1 = glm::mat4(1.0f);

	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around
	glm::mat4 MVP1 = Projection * View * Model1;


	FILE* Sun_fp;
	FILE* Moon_fp;
	FILE* Color_fp;

	GLfloat Sun[36 * 3] = { 0 };
	GLfloat Moon[36 * 3] = { 0 };
	GLfloat Color[36 * 3] = { 0 };

	fopen_s(&Sun_fp, "sun.txt", "r");
	fopen_s(&Moon_fp, "moon.txt", "r");
	fopen_s(&Color_fp, "color.txt", "r");


	//if (Sun_fp == NULL)
	//{
	//	fprintf(stdout, "파일을 열지 못했습니다.");
	//	exit(1);
	//}

	for (int i = 0; i < 36 * 3; ++i)
	{
		fscanf_s(Moon_fp, "%f", &Moon[i]);
		fscanf_s(Color_fp, "%f", &Color[i]);
		fscanf_s(Sun_fp, "%f", &Sun[i]);
	}

	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	//static const GLfloat Sun[] = {
	//	-1.0f,-1.0f,-1.0f,
	//	-1.0f,-1.0f, 1.0f,
	//	-1.0f, 1.0f, 1.0f,
	//	 1.0f, 1.0f,-1.0f,
	//	-1.0f,-1.0f,-1.0f,
	//	-1.0f, 1.0f,-1.0f,
	//	 1.0f,-1.0f, 1.0f,
	//	-1.0f,-1.0f,-1.0f,
	//	 1.0f,-1.0f,-1.0f,
	//	 1.0f, 1.0f,-1.0f,
	//	 1.0f,-1.0f,-1.0f,
	//	-1.0f,-1.0f,-1.0f,
	//	-1.0f,-1.0f,-1.0f,
	//	-1.0f, 1.0f, 1.0f,
	//	-1.0f, 1.0f,-1.0f,
	//	 1.0f,-1.0f, 1.0f,
	//	-1.0f,-1.0f, 1.0f,
	//	-1.0f,-1.0f,-1.0f,
	//	-1.0f, 1.0f, 1.0f,
	//	-1.0f,-1.0f, 1.0f,
	//	 1.0f,-1.0f, 1.0f,
	//	 1.0f, 1.0f, 1.0f,
	//	 1.0f,-1.0f,-1.0f,
	//	 1.0f, 1.0f,-1.0f,
	//	 1.0f,-1.0f,-1.0f,
	//	 1.0f, 1.0f, 1.0f,
	//	 1.0f,-1.0f, 1.0f,
	//	 1.0f, 1.0f, 1.0f,
	//	 1.0f, 1.0f,-1.0f,
	//	-1.0f, 1.0f,-1.0f,
	//	 1.0f, 1.0f, 1.0f,
	//	-1.0f, 1.0f,-1.0f,
	//	-1.0f, 1.0f, 1.0f,
	//	 1.0f, 1.0f, 1.0f,
	//	-1.0f, 1.0f, 1.0f,
	//	 1.0f,-1.0f, 1.0f
	//};

	//static const GLfloat Moon[] = {
	//	5.0f ,-1.0f,-1.0f,
	//	5.0f ,-1.0f, 1.0f,
	//	5.0f , 1.0f, 1.0f,
	//	7.0f , 1.0f,-1.0f,
	//	5.0f ,-1.0f,-1.0f,
	//	5.0f , 1.0f,-1.0f,
	//	7.0f ,-1.0f, 1.0f,
	//	5.0f ,-1.0f,-1.0f,
	//	7.0f ,-1.0f,-1.0f,
	//	7.0f , 1.0f,-1.0f,
	//	7.0f ,-1.0f,-1.0f,
	//	5.0f ,-1.0f,-1.0f,
	//	5.0f ,-1.0f,-1.0f,
	//	5.0f , 1.0f, 1.0f,
	//	5.0f , 1.0f,-1.0f,
	//	7.0f ,-1.0f, 1.0f,
	//	5.0f ,-1.0f, 1.0f,
	//	5.0f ,-1.0f,-1.0f,
	//	5.0f , 1.0f, 1.0f,
	//	5.0f ,-1.0f, 1.0f,
	//	7.0f ,-1.0f, 1.0f,
	//	7.0f , 1.0f, 1.0f,
	//	7.0f ,-1.0f,-1.0f,
	//	7.0f , 1.0f,-1.0f,
	//	7.0f ,-1.0f,-1.0f,
	//	7.0f , 1.0f, 1.0f,
	//	7.0f ,-1.0f, 1.0f,
	//	7.0f , 1.0f, 1.0f,
	//	7.0f , 1.0f,-1.0f,
	//	5.0f , 1.0f,-1.0f,
	//	7.0f , 1.0f, 1.0f,
	//	5.0f , 1.0f,-1.0f,
	//	5.0f , 1.0f, 1.0f,
	//	7.0f , 1.0f, 1.0f,
	//	5.0f , 1.0f, 1.0f,
	//	7.0f ,-1.0f, 1.0f
	//};

	// One color for each vertex. They were generated randomly.
	//static const GLfloat Color[] = {
	//	0.583f,  0.771f,  0.014f,
	//	0.609f,  0.115f,  0.436f,
	//	0.327f,  0.483f,  0.844f,
	//	0.822f,  0.569f,  0.201f,
	//	0.435f,  0.602f,  0.223f,
	//	0.310f,  0.747f,  0.185f,
	//	0.597f,  0.770f,  0.761f,
	//	0.559f,  0.436f,  0.730f,
	//	0.359f,  0.583f,  0.152f,
	//	0.483f,  0.596f,  0.789f,
	//	0.559f,  0.861f,  0.639f,
	//	0.195f,  0.548f,  0.859f,
	//	0.014f,  0.184f,  0.576f,
	//	0.771f,  0.328f,  0.970f,
	//	0.406f,  0.615f,  0.116f,
	//	0.676f,  0.977f,  0.133f,
	//	0.971f,  0.572f,  0.833f,
	//	0.140f,  0.616f,  0.489f,
	//	0.997f,  0.513f,  0.064f,
	//	0.945f,  0.719f,  0.592f,
	//	0.543f,  0.021f,  0.978f,
	//	0.279f,  0.317f,  0.505f,
	//	0.167f,  0.620f,  0.077f,
	//	0.347f,  0.857f,  0.137f,
	//	0.055f,  0.953f,  0.042f,
	//	0.714f,  0.505f,  0.345f,
	//	0.783f,  0.290f,  0.734f,
	//	0.722f,  0.645f,  0.174f,
	//	0.302f,  0.455f,  0.848f,
	//	0.225f,  0.587f,  0.040f,
	//	0.517f,  0.713f,  0.338f,
	//	0.053f,  0.959f,  0.120f,
	//	0.393f,  0.621f,  0.362f,
	//	0.673f,  0.211f,  0.457f,
	//	0.820f,  0.883f,  0.371f,
	//	0.982f,  0.099f,  0.879f
	//};

	GLuint Sun_vertexbuffer;
	glGenBuffers(1, &Sun_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, Sun_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Sun), Sun, GL_STATIC_DRAW);

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Color), Color, GL_STATIC_DRAW);

	GLuint Moon_vertexbuffer;
	glGenBuffers(1, &Moon_vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, Moon_vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Moon), Moon, GL_STATIC_DRAW);

	do {
		//Model = glm::translate(Model, glm::vec3(0.1f, 0.f, 0.1f));//I = T * I
		Model = glm::rotate(Model, glm::radians(1.f), glm::vec3(0.f, 3.f, 0.f));//I = R * T * I
		MVP = Projection * View * Model;//MVP행렬 = P * V * (R * T * I)

		//Model1 = glm::translate(Model1, glm::vec3(0.1f, 0.f, 0.1f));//I = T * I
		Model1 = glm::rotate(Model1, glm::radians(1.f), glm::vec3(0.f, 3.f, 0.f));//I = R * T * I
		MVP1 = Projection * View * Model1;//MVP행렬 = P * V * (R * T * I)


		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP1[0][0]);


		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, Sun_vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, Moon_vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	// Cleanup VBO and shader
	glDeleteBuffers(1, &Sun_vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
	glDeleteBuffers(1, &Moon_vertexbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}