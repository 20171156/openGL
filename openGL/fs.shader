//#version 330 core
//
//out vec3 color;
//
//void main()
//{
//	color = vec3(1, 0, 0);
//}

#version 330 core

// Interpolated values from the vertex shaders
in vec3 fragmentColor;

// Ouput data
out vec3 color;

void main() {

	// Output color = color specified in the vertex shader, 
	// interpolated between all 3 surrounding vertices
	color = fragmentColor;//정점 색깔 그대로 출력하겠다는 의미 / + (컬러)이런식이 되면 컬러 빛을 더 비슷하게 띄고 출력됨

}