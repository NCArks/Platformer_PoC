#version 330 core

layout (location = 0) in vec3 aPos;

uniform vec2 pos;
uniform float zoom;
uniform float aspect_ratio;

void main() {
    gl_Position = vec4(zoom, aspect_ratio * zoom, 1.0f, 1.0f) * (vec4(aPos.x, aPos.y, aPos.z, 1.0) + vec4(pos, 0.0f, 0.0f));
};
