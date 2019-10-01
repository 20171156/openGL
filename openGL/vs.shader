// vs.shader

// opengl 3�� ����� ��.
/*#version 330 core

// ���α׷����κ��� �Է� ���� �����Ϳ� ���� ����
layout(location = 0) in vec3 vertexPosition_modelspace;

void main()
{
  // ������ ��ġ(xyz)�� ����.
	gl_Position.xyz = vertexPosition_modelspace;

  // Ư���� ������ ������ �ϴ� 1.0
	gl_Position.w = 1.0;
}*/
#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1 );
	//ȸ�� - v�� p�� �ǵ�� �ȵ�
	//m�� �����Ӻ��� ��ġ�� ������ - m����� ��������
	//cpp���ϸ� �ǵ�
}
