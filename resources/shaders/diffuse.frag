in vec3 f_Normal;
out vec4 o_Color;

uniform vec4 u_Color;
uniform vec4 u_AmbientColor;
uniform vec4 u_LightColor;
uniform vec3 u_LightDirection;

void main()
{
    vec4 diffuseColor = u_LightColor * max(dot(f_Normal, u_LightDirection), 0.0);
    o_Color = (u_AmbientColor + diffuseColor) * u_Color;
}
