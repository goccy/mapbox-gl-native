// NOTE: DO NOT CHANGE THIS FILE. IT IS AUTOMATICALLY GENERATED.

#ifndef MBGL_SHADER_PLAIN_VERTEX
#define MBGL_SHADER_PLAIN_VERTEX

#include <mbgl/platform/gl.hpp>

namespace mbgl {
namespace shaders {
namespace plain {

#ifdef GL_ES_VERSION_2_0
constexpr const char* vertex = R"MBGL_SHADER(precision highp float;
attribute vec2 a_pos;

uniform mat4 u_matrix;

void main() {
    gl_Position = u_matrix * vec4(a_pos, 0, 1);
}
)MBGL_SHADER";
#else
constexpr const char* vertex = R"MBGL_SHADER(#version 120
attribute vec2 a_pos;

uniform mat4 u_matrix;

void main() {
    gl_Position = u_matrix * vec4(a_pos, 0, 1);
}
)MBGL_SHADER";
#endif

} // namespace plain
} // namespace shaders
} // namespace mbgl

#endif
