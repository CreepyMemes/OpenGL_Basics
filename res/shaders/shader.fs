#version 330 core

out vec4 FragColor;
in vec3 ourColor;

in vec2 v_aTexture;
uniform sampler2D u_Texture;

void main(){
    vec4 texColor = texture(u_Texture, v_aTexture);
    vec4 colColor = vec4(ourColor, 1.0);
    FragColor = texColor * colColor;
}