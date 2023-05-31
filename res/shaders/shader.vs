#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexture;

out vec3 v_aColor;
out vec2 v_aTexture;

uniform float xoffset;
uniform float yoffset;

void main(){
    gl_Position = vec4(aPos.x + xoffset, aPos.y + yoffset, aPos.z, 1.0);
    v_aColor    = aColor;
    v_aTexture  = aTexture;
}