// NOTE: DO NOT CHANGE THIS FILE. IT IS AUTOMATICALLY GENERATED.

#ifndef MBGL_SHADER_ICON_FRAGMENT
#define MBGL_SHADER_ICON_FRAGMENT

#include <mbgl/platform/gl.hpp>

namespace mbgl {
namespace shaders {
namespace icon {

#ifdef GL_ES_VERSION_2_0
constexpr const char* fragment = R"MBGL_SHADER(precision highp float;
uniform sampler2D u_texture;

varying vec2 v_tex;
varying float v_alpha;

void main() {
    gl_FragColor = texture2D(u_texture, v_tex) * v_alpha;
}
)MBGL_SHADER";
#else
constexpr const char* fragment = R"MBGL_SHADER(#version 120
uniform sampler2D u_texture;

varying vec2 v_tex;
varying float v_alpha;

void main() {
    gl_FragColor = texture2D(u_texture, v_tex) * v_alpha;
}
)MBGL_SHADER";
#endif

} // namespace icon
} // namespace shaders
} // namespace mbgl

#endif
