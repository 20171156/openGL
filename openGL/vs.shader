#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
//정점 하나에 들어가는 정보



// Output data ; will be interpolated for each fragment.
out vec3 fragmentColor;//버텍스 셰이더 다음 프래그먼트 셰이더(정점 -> 색상정보 셰이더 출력) / 셰이더에서 나가는 변수이므로 out, 프래그먼트 셰이더 출력 위한 코드
// Values that stay constant for the whole mesh.
uniform mat4 MVP;
//행렬 한개에 들어가는 정보, 정점 하나에 들어가는 정보랑 다르다

void main() {

	// Output position of the vertex, in clip space : MVP * position
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

	// The color of each vertex will be interpolated
	// to produce the color of each fragment
	fragmentColor = vertexColor;
}
