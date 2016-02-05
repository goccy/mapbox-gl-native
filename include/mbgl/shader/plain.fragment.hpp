// NOTE: DO NOT CHANGE THIS FILE. IT IS AUTOMATICALLY GENERATED.

#ifndef MBGL_SHADER_PLAIN_FRAGMENT
#define MBGL_SHADER_PLAIN_FRAGMENT

#include <mbgl/platform/gl.hpp>

namespace mbgl {
namespace shaders {
namespace plain {

#ifdef GL_ES_VERSION_2_0
constexpr const char* fragment = R"MBGL_SHADER(precision highp float;
uniform vec4 u_color;

void main() {
    gl_FragColor = u_color;
}
)MBGL_SHADER";
#else
constexpr const char* fragment = R"MBGL_SHADER(#version 120
uniform vec4 u_color;

void main() {
    gl_FragColor = u_color;
}
)MBGL_SHADER";
#endif

} // namespace plain
} // namespace shaders
} // namespace mbgl

#endif
