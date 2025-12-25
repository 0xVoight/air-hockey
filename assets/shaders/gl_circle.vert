#version 460 core

layout(location = 0) in vec2 aPos; // Позиция вершины из Unit Circle

// Uniform-блок для передачи данных объекта одним вызовом
uniform mat4 uProjection;
uniform vec2 uInstancePos;
uniform float uInstanceRadius;

void main() {
    // Масштабируем и переносим вершину в мировые (игровые) координаты
    vec2 worldPos = aPos * uInstanceRadius + uInstancePos;

    // Умножаем на ортографическую проекцию для перевода в NDC
    gl_Position = uProjection * vec4(worldPos, 0.0, 1.0);
}
