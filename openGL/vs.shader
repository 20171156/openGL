//#version 330 core
//
//layout(location = 0) in vec3 vertexPosition_modelspace;//���� �ϳ��� ���Ǹ� �޾Ƽ� ���� ��
//uniform mat4 MVP;//������ ���Ե� ������ �ƴ�
////���� �� ���������� ���� ������� �Ѱܾ� �� - >�׷��� ���̴� �ڵ嵵 �ٲ�����
//
//void main()
//{
//	gl_Position = MVP * vec4(vertexPosition_modelspace, 1 );
//	//ȸ�� - v�� p�� �ǵ�� �ȵ�
//	//m�� �����Ӻ��� ��ġ�� ������ - m����� ��������
//	//cpp���ϸ� �ǵ�
//}

#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;

// Output data ; will be interpolated for each fragment.
out vec3 fragmentColor;//���ؽ� ���̴� ���� �����׸�Ʈ ���̴�(���� -> �������� ���̴� ���) / ���̴����� ������ �����̹Ƿ� out, �����׸�Ʈ ���̴� ��� ���� �ڵ�
// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main() {

	// Output position of the vertex, in clip space : MVP * position
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

	// The color of each vertex will be interpolated
	// to produce the color of each fragment
	fragmentColor = vertexColor;
}
