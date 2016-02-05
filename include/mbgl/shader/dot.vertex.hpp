// NOTE: DO NOT CHANGE THIS FILE. IT IS AUTOMATICALLY GENERATED.

#ifndef MBGL_SHADER_DOT_VERTEX
#define MBGL_SHADER_DOT_VERTEX

#include <mbgl/platform/gl.hpp>

namespace mbgl {
namespace shaders {
namespace dot {

#ifdef GL_ES_VERSION_2_0
constexpr const char* vertex = R"MBGL_SHADER(precision highp float;
uniform mat4 u_matrix;
uniform float u_size;

attribute vec2 a_pos;

void main(void) {
    gl_Position = u_matrix * vec4(a_pos, 0, 1);
    gl_PointSize = u_size;
}
)MBGL_SHADER";
#else
constexpr const char* vertex = R"MBGL_SHADER(#version 120
uniform mat4 u_matrix;
uniform float u_size;

attribute vec2 a_pos;

void main(void) {
    gl_Position = u_matrix * vec4(a_pos, 0, 1);
    gl_PointSize = u_size;
}
)MBGL_SHADER";
#endif

} // namespace dot
} // namespace shaders
} // namespace mbgl

#endif
