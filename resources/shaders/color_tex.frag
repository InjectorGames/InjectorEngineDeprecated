in vec2 f_TexCoord;
out vec4 o_Color;

uniform vec4 u_Color;
uniform sampler2D u_TextureMap;

void main()
{
    o_Color = texture(u_TextureMap, f_TexCoord) * u_Color;
}
