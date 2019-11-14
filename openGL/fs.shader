#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;

//float delta = 0.0f;

void main() {

	..delta += 0.00lf;

	// Output color = color of the texture at the specified UV
	color = texture(myTextureSampler, UV /** 0.5*/).rgb;
}

//런타임 중에 컴파일을 할 수 있지만 이 방법은 비효율적
//.cpp에서 vs로 값을 하나 더 넘겨주면 해결(uv * delta)