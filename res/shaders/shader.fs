#version 330 core

in vec3 v_aColor;
in vec2 v_aTexture;

out vec4 FragColor;

uniform sampler2D u_Texture;

void main(){
    vec4 color_texture   = texture(u_Texture, v_aTexture);
    vec4 color_attribute = vec4(v_aColor, 1.0);

    FragColor = color_texture * color_attribute;
}