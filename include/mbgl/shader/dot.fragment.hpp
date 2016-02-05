// NOTE: DO NOT CHANGE THIS FILE. IT IS AUTOMATICALLY GENERATED.

#ifndef MBGL_SHADER_DOT_FRAGMENT
#define MBGL_SHADER_DOT_FRAGMENT

#include <mbgl/platform/gl.hpp>

namespace mbgl {
namespace shaders {
namespace dot {

#ifdef GL_ES_VERSION_2_0
constexpr const char* fragment = R"MBGL_SHADER(precision highp float;
uniform vec4 u_color;
uniform float u_blur;

void main() {
    float dist = length(gl_PointCoord - 0.5);
    float t = smoothstep(0.5, 0.5 - u_blur, dist);

    gl_FragColor = u_color * t;
}
)MBGL_SHADER";
#else
constexpr const char* fragment = R"MBGL_SHADER(#version 120
uniform vec4 u_color;
uniform float u_blur;

void main() {
    float dist = length(gl_PointCoord - 0.5);
    float t = smoothstep(0.5, 0.5 - u_blur, dist);

    gl_FragColor = u_color * t;
}
)MBGL_SHADER";
#endif

} // namespace dot
} // namespace shaders
} // namespace mbgl

#endif
