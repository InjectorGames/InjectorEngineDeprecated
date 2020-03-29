in vec3 v_Position;
in vec3 v_Normal;

out vec3 f_Normal;

uniform mat4 u_MVP;
uniform mat3 u_Normal;

void main()
{
    gl_Position = u_MVP * vec4(v_Position, 1.0);
    f_Normal = u_Normal * v_Normal;
}
