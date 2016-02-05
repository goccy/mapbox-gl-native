// NOTE: DO NOT CHANGE THIS FILE. IT IS AUTOMATICALLY GENERATED.

#ifndef MBGL_SHADER_CIRCLE_VERTEX
#define MBGL_SHADER_CIRCLE_VERTEX

#include <mbgl/platform/gl.hpp>

namespace mbgl {
namespace shaders {
namespace circle {

#ifdef GL_ES_VERSION_2_0
constexpr const char* vertex = R"MBGL_SHADER(precision highp float;
// set by gl_util
uniform float u_size;

attribute vec2 a_pos;

uniform mat4 u_matrix;
uniform mat4 u_exmatrix;

varying vec2 v_extrude;

void main(void) {
    // unencode the extrusion vector that we snuck into the a_pos vector
    v_extrude = vec2(mod(a_pos, 2.0) * 2.0 - 1.0);

    vec4 extrude = u_exmatrix * vec4(v_extrude * u_size, 0, 0);
    // multiply a_pos by 0.5, since we had it * 2 in order to sneak
    // in extrusion data
    gl_Position = u_matrix * vec4(floor(a_pos * 0.5), 0, 1);

    // gl_Position is divided by gl_Position.w after this shader runs.
    // Multiply the extrude by it so that it isn't affected by it.
    gl_Position += extrude * gl_Position.w;
}
)MBGL_SHADER";
#else
constexpr const char* vertex = R"MBGL_SHADER(#version 120
// set by gl_util
uniform float u_size;

attribute vec2 a_pos;

uniform mat4 u_matrix;
uniform mat4 u_exmatrix;

varying vec2 v_extrude;

void main(void) {
    // unencode the extrusion vector that we snuck into the a_pos vector
    v_extrude = vec2(mod(a_pos, 2.0) * 2.0 - 1.0);

    vec4 extrude = u_exmatrix * vec4(v_extrude * u_size, 0, 0);
    // multiply a_pos by 0.5, since we had it * 2 in order to sneak
    // in extrusion data
    gl_Position = u_matrix * vec4(floor(a_pos * 0.5), 0, 1);

    // gl_Position is divided by gl_Position.w after this shader runs.
    // Multiply the extrude by it so that it isn't affected by it.
    gl_Position += extrude * gl_Position.w;
}
)MBGL_SHADER";
#endif

} // namespace circle
} // namespace shaders
} // namespace mbgl

#endif
