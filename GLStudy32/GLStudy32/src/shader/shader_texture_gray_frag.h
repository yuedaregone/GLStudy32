"\
#version 120                                                    \n\
varying vec2 UV;                                                \n\
uniform sampler2D myTextureSampler;                             \n\
void main(){                                                    \n\
	vec4 texColor = texture2D(myTextureSampler,UV);             \n\
	float gay = dot(texColor.rgb, vec3(0.299, 0.587, 0.114));   \n\
	gl_FragColor = vec4(vec3(gay), texColor.a);                 \n\
}                                                               \n\
";