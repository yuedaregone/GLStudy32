"\
#version 120																	\n\
varying vec2 UV;																\n\
uniform sampler2D myTextureSampler;												\n\
float p_offset[9] = {-4, -3, -2, -1, 0, 1, 2, 3, 4};							\n\
float p_weight[9] = {0.05, 0.09, 0.12, 0.15, 0.16, 0.15, 0.12, 0.09, 0.05};		\n\
void main(){																	\n\
	vec4 samplerColorX = vec4(0, 0, 0, 0);										\n\
	for (int i = 0; i < 9; ++i) {												\n\
		vec2 uvPos = UV - vec2(p_offset[i] * 0.02, 0);							\n\
		vec4 texColor = texture2D(myTextureSampler,uvPos);						\n\
		samplerColorX += texColor*p_weight[i];									\n\
	}																			\n\
	vec4 samplerColorY = vec4(0, 0, 0, 0);										\n\
	for (int i = 0; i < 9; ++i) {												\n\
		vec2 uvPos = UV - vec2(0,p_offset[i] * 0.02);							\n\
		vec4 texColor = texture2D(myTextureSampler,uvPos);						\n\
		samplerColorY += texColor*p_weight[i];									\n\
	}																			\n\
	gl_FragColor = (samplerColorX+samplerColorY)*0.5;							\n\
	}																			\n\
";