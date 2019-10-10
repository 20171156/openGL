//#version 330 core
//
//layout(location = 0) in vec3 vertexPosition_modelspace;//정점 하나당 정의를 받아서 값이 들어감
//uniform mat4 MVP;//정점에 포함된 정보가 아님
////정점 당 색상정보는 위의 방식으로 넘겨야 함 - >그래서 셰이더 코드도 바뀌어야함
//
//void main()
//{
//	gl_Position = MVP * vec4(vertexPosition_modelspace, 1 );
//	//회전 - v랑 p는 건들면 안됨
//	//m을 프레임별로 위치를 변경함 - m행렬을 만져야함
//	//cpp파일만 건듬
//}

#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;

// Output data ; will be interpolated for each fragment.
out vec3 fragmentColor;//버텍스 셰이더 다음 프래그먼트 셰이더(정점 -> 색상정보 셰이더 출력) / 셰이더에서 나가는 변수이므로 out, 프래그먼트 셰이더 출력 위한 코드
// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main() {

	// Output position of the vertex, in clip space : MVP * position
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

	// The color of each vertex will be interpolated
	// to produce the color of each fragment
	fragmentColor = vertexColor;
}
