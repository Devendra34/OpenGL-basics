#shader vertex
#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_texCoord;

void main() {
   gl_Position = vec4(position, 0.0, 1.0);
   v_texCoord = texCoord;
}


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_texCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main() {
	vec4 textColor = texture(u_Texture, v_texCoord);
	color = textColor;
}