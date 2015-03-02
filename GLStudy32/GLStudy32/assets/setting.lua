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
        uniform sampler2D myTextureSampler;                     \n\
        void main(){                                            \n\
            gl_FragColor = texture2D(myTextureSampler,UV);      \n\
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
    fragment_red_str = "\
        #version 120                                                    \n\
        varying vec2 UV;                                                \n\
        uniform sampler2D myTextureSampler;                             \n\
        void main(){                                                    \n\
            vec4 texColor = texture2D(myTextureSampler,UV);             \n\            
            gl_FragColor = vec4(1.0,texColor.g,texColor.b,texColor.a);  \n\
        }                                                               \n\
    ",
}

function getVertexShader()
    return texture_shader.vertex_str
end

function getFragmentShader()
    return texture_shader.fragment_gray_str
end