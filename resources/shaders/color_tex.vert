in vec3 v_Position;
in vec2 v_TexCoord;

out vec2 f_TexCoord;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * vec4(v_Position, 1.0);
    f_TexCoord = v_TexCoord;
}
