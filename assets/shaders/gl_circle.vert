#version 460 core

layout(location = 0) in vec2 aPos;

uniform mat4 uProjection;
uniform vec2 uInstancePos;
uniform float uInstanceRadius;

void main() {
    vec2 worldPos = aPos * uInstanceRadius + uInstancePos;

    gl_Position = uProjection * vec4(worldPos, 0.0, 1.0);
}
