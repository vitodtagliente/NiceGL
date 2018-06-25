#shader vertex

#version 330 core

in vec3 in_position;

void main()
{
	gl_Position = vec4(in_position, 1.0);
}

#shader fragment

#version 330 core

out vec4 fragColor;
uniform vec4 u_Color;

void main(){
	fragColor = u_Color;
}