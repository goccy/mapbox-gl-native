// NOTE: DO NOT CHANGE THIS FILE. IT IS AUTOMATICALLY GENERATED.

#ifndef MBGL_SHADER_RASTER_VERTEX
#define MBGL_SHADER_RASTER_VERTEX

#include <mbgl/platform/gl.hpp>

namespace mbgl {
namespace shaders {
namespace raster {

#ifdef GL_ES_VERSION_2_0
constexpr const char* vertex = R"MBGL_SHADER(precision highp float;
uniform mat4 u_matrix;
uniform float u_buffer;

attribute vec2 a_pos;

varying vec2 v_pos;


void main() {
    gl_Position = u_matrix * vec4(a_pos, 0, 1);
    float dimension = (8192.0 + 2.0 * u_buffer);
    v_pos = (a_pos / dimension) + (u_buffer / dimension);
}
)MBGL_SHADER";
#else
constexpr const char* vertex = R"MBGL_SHADER(#version 120
uniform mat4 u_matrix;
uniform float u_buffer;

attribute vec2 a_pos;

varying vec2 v_pos;


void main() {
    gl_Position = u_matrix * vec4(a_pos, 0, 1);
    float dimension = (8192.0 + 2.0 * u_buffer);
    v_pos = (a_pos / dimension) + (u_buffer / dimension);
}
)MBGL_SHADER";
#endif

} // namespace raster
} // namespace shaders
} // namespace mbgl

#endif
