"																\n\
#version 120													\n\
attribute vec3 vertexPosition_modelspace;						\n\
attribute vec3 vertexColor;										\n\
varying vec3 fragmentColor;										\n\
uniform mat4 MVP;												\n\
void main(){													\n\
	gl_Position = MVP*vec4(vertexPosition_modelspace, 1.0);		\n\
	fragmentColor = vertexColor;								\n\
}																\n\
";