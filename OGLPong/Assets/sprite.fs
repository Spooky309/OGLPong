#version 330 core

out vec4 fragColour;
in vec2 texc;
uniform sampler2D tex;

void main() {
	fragColour = texture(tex, texc);
}
