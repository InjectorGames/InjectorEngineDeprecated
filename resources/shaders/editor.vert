in vec3 v_Position;
uniform mat4 u_Model;

void main()
{
    gl_Position = u_Model * vec4(v_Position, 1.0);
}
