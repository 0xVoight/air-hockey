#version 460 core

out vec4 FragColor;
in vec2 vTexCoord;

uniform sampler2D uTexture;
uniform float uBrightness = 1.0; // Коэффициент яркости

void main() {
    vec4 texColor = texture(uTexture, vTexCoord);

    // Делаем лед чуть более холодным и регулируем яркость
    vec3 iceColor = texColor.rgb * vec3(0.9, 0.95, 1.0);
    FragColor = vec4(iceColor * uBrightness, texColor.a);
}
