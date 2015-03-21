"\
#version 120                                                    \n\
attribute vec3 vertexPosition_modelspace;                       \n\
attribute vec2 vertexUV;                                        \n\
varying vec2 UV;                                                \n\
uniform mat4 MVP;                                               \n\
void main(){                                                    \n\
	gl_Position = MVP*vec4(vertexPosition_modelspace, 1.0);     \n\
	UV = vertexUV;                                              \n\
}                                                               \n\
";