#version 330
in vec3 i_Position;
uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(i_Position, 1.0);
}
