#version 330 core
layout(location=0) in vec3 pos;
layout(location=1) in vec2 uv;

out vec2 texc;

uniform mat4 PV;
uniform mat4 ModelMat;

void main() {
	texc = uv;
	gl_Position = PV * ModelMat * vec4(pos, 1.0);
}
