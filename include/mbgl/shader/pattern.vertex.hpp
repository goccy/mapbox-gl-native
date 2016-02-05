// NOTE: DO NOT CHANGE THIS FILE. IT IS AUTOMATICALLY GENERATED.

#ifndef MBGL_SHADER_PATTERN_VERTEX
#define MBGL_SHADER_PATTERN_VERTEX

#include <mbgl/platform/gl.hpp>

namespace mbgl {
namespace shaders {
namespace pattern {

#ifdef GL_ES_VERSION_2_0
constexpr const char* vertex = R"MBGL_SHADER(precision highp float;
uniform mat4 u_matrix;
uniform mat3 u_patternmatrix_a;
uniform mat3 u_patternmatrix_b;

uniform vec2 u_offset_a;
uniform vec2 u_offset_b;

attribute vec2 a_pos;

varying vec2 v_pos_a;
varying vec2 v_pos_b;

void main() {
    gl_Position = u_matrix * vec4(a_pos, 0, 1);
    v_pos_a = (u_patternmatrix_a * vec3(a_pos, 1)).xy + u_offset_a;
    v_pos_b = (u_patternmatrix_b * vec3(a_pos, 1)).xy + u_offset_b;
}
)MBGL_SHADER";
#else
constexpr const char* vertex = R"MBGL_SHADER(#version 120
uniform mat4 u_matrix;
uniform mat3 u_patternmatrix_a;
uniform mat3 u_patternmatrix_b;

uniform vec2 u_offset_a;
uniform vec2 u_offset_b;

attribute vec2 a_pos;

varying vec2 v_pos_a;
varying vec2 v_pos_b;

void main() {
    gl_Position = u_matrix * vec4(a_pos, 0, 1);
    v_pos_a = (u_patternmatrix_a * vec3(a_pos, 1)).xy + u_offset_a;
    v_pos_b = (u_patternmatrix_b * vec3(a_pos, 1)).xy + u_offset_b;
}
)MBGL_SHADER";
#endif

} // namespace pattern
} // namespace shaders
} // namespace mbgl

#endif
