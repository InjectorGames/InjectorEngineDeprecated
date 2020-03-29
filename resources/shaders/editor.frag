out vec4 o_Color;
uniform vec4 u_Color;

void main()
{
    o_Color = u_Color;
    gl_FragDepth = 0.0f;
}
