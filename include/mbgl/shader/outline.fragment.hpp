// NOTE: DO NOT CHANGE THIS FILE. IT IS AUTOMATICALLY GENERATED.

#ifndef MBGL_SHADER_OUTLINE_FRAGMENT
#define MBGL_SHADER_OUTLINE_FRAGMENT

#include <mbgl/platform/gl.hpp>

namespace mbgl {
namespace shaders {
namespace outline {

#ifdef GL_ES_VERSION_2_0
constexpr const char* fragment = R"MBGL_SHADER(precision highp float;
uniform vec4 u_color;

varying vec2 v_pos;

void main() {
    float dist = length(v_pos - gl_FragCoord.xy);
    float alpha = smoothstep(1.0, 0.0, dist);
    gl_FragColor = u_color * alpha;
}
)MBGL_SHADER";
#else
constexpr const char* fragment = R"MBGL_SHADER(#version 120
uniform vec4 u_color;

varying vec2 v_pos;

void main() {
    float dist = length(v_pos - gl_FragCoord.xy);
    float alpha = smoothstep(1.0, 0.0, dist);
    gl_FragColor = u_color * alpha;
}
)MBGL_SHADER";
#endif

} // namespace outline
} // namespace shaders
} // namespace mbgl

#endif
