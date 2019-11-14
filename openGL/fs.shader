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

//��Ÿ�� �߿� �������� �� �� ������ �� ����� ��ȿ����
//.cpp���� vs�� ���� �ϳ� �� �Ѱ��ָ� �ذ�(uv * delta)