"\
#version 120                                            \n\
varying vec2 UV;                                        \n\
uniform vec4 frag_color;								\n\
uniform sampler2D myTextureSampler;                     \n\
void main(){                                            \n\
	vec4 texColor = texture2D(myTextureSampler,UV);		\n\
	gl_FragColor = texColor*frag_color;					\n\
}                                                       \n\
";