#shader vertex
#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 aColor;

out vec3 ourColor;

void main() {
   gl_Position = vec4(position, 0.0, 1.0);
   ourColor = aColor;
};


#shader fragment
#version 330 core

out vec4 color;
in vec3 ourColor;

void main() {
   color = vec4(ourColor, 1.0);
};