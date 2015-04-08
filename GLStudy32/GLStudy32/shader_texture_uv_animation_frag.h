"\
#version 120                                            \n\
varying vec2 UV;                                        \n\
uniform vec4 frag_color;                                \n\
uniform sampler2D myTextureSampler;                     \n\
uniform float offsetUV = 0.0;                           \n\
void main(){                                            \n\
    vec2 targetUV = UV + vec2(0,offsetUV);              \n\
    vec4 texColor = texture2D(myTextureSampler,targetUV); \n\
    gl_FragColor = texColor*frag_color;         \n\
}                                                       \n\
";