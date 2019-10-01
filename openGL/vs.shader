// vs.shader

// opengl 3을 사용할 것.
/*#version 330 core

// 프로그램으로부터 입력 받을 데이터에 대한 정보
layout(location = 0) in vec3 vertexPosition_modelspace;

void main()
{
  // 정점의 위치(xyz)를 결정.
	gl_Position.xyz = vertexPosition_modelspace;

  // 특별한 이유가 없으면 일단 1.0
	gl_Position.w = 1.0;
}*/
#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1 );
	//회전 - v랑 p는 건들면 안됨
	//m을 프레임별로 위치를 변경함 - m행렬을 만져야함
	//cpp파일만 건듬
}
