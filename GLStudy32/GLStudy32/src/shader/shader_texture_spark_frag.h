"\
#version 120                                            \n\
varying vec2 UV;                                        \n\
uniform vec4 frag_color;								\n\
uniform sampler2D myTextureSampler;                     \n\
uniform float offset = 0.0;								\n\
uniform float width = 0.2;								\n\
uniform vec4 u_color = vec4(1.0, 0.0, 1.0, 1.0);		\n\
void main(){                                            \n\
	vec4 texColor = texture2D(myTextureSampler,UV);		\n\
	float dis = abs(UV[0]-UV[1]-offset)/1.414;			\n\
	dis = 1 - (1/width) * dis;							\n\
	dis = max(dis, 0);									\n\
	vec4 color = u_color*dis;							\n\
	gl_FragColor = frag_color*texColor+color;			\n\
}                                                       \n\
";