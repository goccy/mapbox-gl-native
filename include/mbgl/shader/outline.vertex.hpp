// NOTE: DO NOT CHANGE THIS FILE. IT IS AUTOMATICALLY GENERATED.

#ifndef MBGL_SHADER_OUTLINE_VERTEX
#define MBGL_SHADER_OUTLINE_VERTEX

#include <mbgl/platform/gl.hpp>

namespace mbgl {
namespace shaders {
namespace outline {

#ifdef GL_ES_VERSION_2_0
constexpr const char* vertex = R"MBGL_SHADER(precision highp float;
attribute vec2 a_pos;
uniform mat4 u_matrix;
uniform vec2 u_world;

varying vec2 v_pos;

void main() {
    gl_Position = u_matrix * vec4(a_pos, 0, 1);
    v_pos = (gl_Position.xy / gl_Position.w + 1.0) / 2.0 * u_world;
}
)MBGL_SHADER";
#else
constexpr const char* vertex = R"MBGL_SHADER(#version 120
attribute vec2 a_pos;
uniform mat4 u_matrix;
uniform vec2 u_world;

varying vec2 v_pos;

void main() {
    gl_Position = u_matrix * vec4(a_pos, 0, 1);
    v_pos = (gl_Position.xy / gl_Position.w + 1.0) / 2.0 * u_world;
}
)MBGL_SHADER";
#endif

} // namespace outline
} // namespace shaders
} // namespace mbgl

#endif
