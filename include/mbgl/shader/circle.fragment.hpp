// NOTE: DO NOT CHANGE THIS FILE. IT IS AUTOMATICALLY GENERATED.

#ifndef MBGL_SHADER_CIRCLE_FRAGMENT
#define MBGL_SHADER_CIRCLE_FRAGMENT

#include <mbgl/platform/gl.hpp>

namespace mbgl {
namespace shaders {
namespace circle {

#ifdef GL_ES_VERSION_2_0
constexpr const char* fragment = R"MBGL_SHADER(precision highp float;
uniform vec4 u_color;
uniform float u_blur;
uniform float u_size;

varying vec2 v_extrude;

void main() {
    float t = smoothstep(1.0 - u_blur, 1.0, length(v_extrude));
    gl_FragColor = u_color * (1.0 - t);
}
)MBGL_SHADER";
#else
constexpr const char* fragment = R"MBGL_SHADER(#version 120
uniform vec4 u_color;
uniform float u_blur;
uniform float u_size;

varying vec2 v_extrude;

void main() {
    float t = smoothstep(1.0 - u_blur, 1.0, length(v_extrude));
    gl_FragColor = u_color * (1.0 - t);
}
)MBGL_SHADER";
#endif

} // namespace circle
} // namespace shaders
} // namespace mbgl

#endif
