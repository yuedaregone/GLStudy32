globle_info = {
	width = 300,
	height = 300,
	title = "GLStudy",
}

bg_color = {
    r = 0.0,
    g = 0.0,
    b = 0.0,
    a = 1.0,
}



-------------------------------------------------------------------------------------
local texture_shader = {
	vertex_str = "\
        #version 120                                                    \n\
        attribute vec3 vertexPosition_modelspace;                       \n\
        attribute vec2 vertexUV;                                        \n\
        varying vec2 UV;                                                \n\
        uniform mat4 MVP;                                               \n\
        void main(){                                                    \n\
            gl_Position = MVP*vec4(vertexPosition_modelspace, 1.0);     \n\
            UV = vertexUV;                                              \n\
        }                                                               \n\
    ",
    fragment_str = "\
        #version 120                                            \n\
        varying vec2 UV;                                        \n\
	uniform vec4 frag_color;				\n\
        uniform sampler2D myTextureSampler;                     \n\
        void main(){                                            \n\
            vec4 texColor = texture2D(myTextureSampler,UV);	\n\
	    gl_FragColor = texColor*frag_color;			\n\
        }                                                       \n\
    ",
    fragment_gray_str = "\
        #version 120                                                    \n\
        varying vec2 UV;                                                \n\
        uniform sampler2D myTextureSampler;                             \n\
        void main(){                                                    \n\
            vec4 texColor = texture2D(myTextureSampler,UV);             \n\
            float gay = dot(texColor.rgb, vec3(0.299, 0.587, 0.114));   \n\
            gl_FragColor = vec4(vec3(gay), texColor.a);                 \n\
        }                                                               \n\
    ",    
    --add spark effect
    fragment_str_spark = "\
        #version 120                                            \n\
        varying vec2 UV;                                        \n\
	uniform vec4 frag_color;				\n\
        uniform sampler2D myTextureSampler;                     \n\
	uniform float offset = 0.0;				\n\
	uniform float width = 0.2;				\n\
	uniform vec4 u_color = vec4(1.0, 0.0, 1.0, 1.0);	\n\
        void main(){                                            \n\
            vec4 texColor = texture2D(myTextureSampler,UV);	\n\
	    float dis = abs(UV[0]-UV[1]-offset)/1.414;		\n\
	    dis = 1 - (1/width) * dis;				\n\
	    dis = max(dis, 0);					\n\
	    vec4 color = u_color*dis;				\n\
	    gl_FragColor = frag_color*texColor+color;		\n\
        }                                                       \n\
    ",
    fragment_str_test = "\
        #version 120                                                    \n\
        varying vec2 UV;                                                \n\
        uniform sampler2D myTextureSampler;                             \n\
	float p_offset[9] = {-4, -3, -2, -1, 0, 1, 2, 3, 4};\n\
	float p_weight[9] = {0.05, 0.09, 0.12, 0.15, 0.16, 0.15, 0.12, 0.09, 0.05};\n\
        void main(){                                                    \n\
	    vec4 samplerColorX = vec4(0, 0, 0, 0);			\n\
	    for (int i = 0; i < 9; ++i) {				\n\
		vec2 uvPos = UV - vec2(p_offset[i] * 0.02, 0);			\n\
		vec4 texColor = texture2D(myTextureSampler,uvPos);	\n\
		samplerColorX += texColor*p_weight[i];			\n\
	    }								\n\
	    vec4 samplerColorY = vec4(0, 0, 0, 0);			\n\
	    for (int i = 0; i < 9; ++i) {				\n\
		vec2 uvPos = UV - vec2(0,p_offset[i] * 0.02);		\n\
		vec4 texColor = texture2D(myTextureSampler,uvPos);	\n\
		samplerColorY += texColor*p_weight[i];			\n\
	    }								\n\
	    gl_FragColor = (samplerColorX+samplerColorY)*0.5;				\n\
        }                                                               \n\
    ",
}

function getVertexShader()
    return texture_shader.vertex_str
end

function getFragmentShader()
    return texture_shader.fragment_str_test
end