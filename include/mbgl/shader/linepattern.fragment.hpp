// NOTE: DO NOT CHANGE THIS FILE. IT IS AUTOMATICALLY GENERATED.

#ifndef MBGL_SHADER_LINEPATTERN_FRAGMENT
#define MBGL_SHADER_LINEPATTERN_FRAGMENT

#include <mbgl/platform/gl.hpp>

namespace mbgl {
namespace shaders {
namespace linepattern {

#ifdef GL_ES_VERSION_2_0
constexpr const char* fragment = R"MBGL_SHADER(precision highp float;
uniform vec2 u_linewidth;
uniform float u_blur;

uniform vec2 u_pattern_size_a;
uniform vec2 u_pattern_tl_a;
uniform vec2 u_pattern_br_a;
uniform vec2 u_pattern_size_b;
uniform vec2 u_pattern_tl_b;
uniform vec2 u_pattern_br_b;
uniform float u_fade;
uniform float u_opacity;

uniform sampler2D u_image;

varying vec2 v_normal;
varying float v_linesofar;
varying float v_gamma_scale;

void main() {
    // Calculate the distance of the pixel from the line in pixels.
    float dist = length(v_normal) * u_linewidth.s;

    // Calculate the antialiasing fade factor. This is either when fading in
    // the line in case of an offset line (v_linewidth.t) or when fading out
    // (v_linewidth.s)
    float blur = u_blur * v_gamma_scale;
    float alpha = clamp(min(dist - (u_linewidth.t - blur), u_linewidth.s - dist) / blur, 0.0, 1.0);

    float x_a = mod(v_linesofar / u_pattern_size_a.x, 1.0);
    float y_a = 0.5 + (v_normal.y * u_linewidth.s / u_pattern_size_a.y);
    vec2 pos_a = mix(u_pattern_tl_a, u_pattern_br_a, vec2(x_a, y_a));
    float x_b = mod(v_linesofar / u_pattern_size_b.x, 1.0);
    float y_b = 0.5 + (v_normal.y * u_linewidth.s / u_pattern_size_b.y);
    vec2 pos_b = mix(u_pattern_tl_b, u_pattern_br_b, vec2(x_b, y_b));

    vec4 color = mix(texture2D(u_image, pos_a), texture2D(u_image, pos_b), u_fade);

    alpha *= u_opacity;

    gl_FragColor = color * alpha;
}
)MBGL_SHADER";
#else
constexpr const char* fragment = R"MBGL_SHADER(#version 120
uniform vec2 u_linewidth;
uniform float u_blur;

uniform vec2 u_pattern_size_a;
uniform vec2 u_pattern_tl_a;
uniform vec2 u_pattern_br_a;
uniform vec2 u_pattern_size_b;
uniform vec2 u_pattern_tl_b;
uniform vec2 u_pattern_br_b;
uniform float u_fade;
uniform float u_opacity;

uniform sampler2D u_image;

varying vec2 v_normal;
varying float v_linesofar;
varying float v_gamma_scale;

void main() {
    // Calculate the distance of the pixel from the line in pixels.
    float dist = length(v_normal) * u_linewidth.s;

    // Calculate the antialiasing fade factor. This is either when fading in
    // the line in case of an offset line (v_linewidth.t) or when fading out
    // (v_linewidth.s)
    float blur = u_blur * v_gamma_scale;
    float alpha = clamp(min(dist - (u_linewidth.t - blur), u_linewidth.s - dist) / blur, 0.0, 1.0);

    float x_a = mod(v_linesofar / u_pattern_size_a.x, 1.0);
    float y_a = 0.5 + (v_normal.y * u_linewidth.s / u_pattern_size_a.y);
    vec2 pos_a = mix(u_pattern_tl_a, u_pattern_br_a, vec2(x_a, y_a));
    float x_b = mod(v_linesofar / u_pattern_size_b.x, 1.0);
    float y_b = 0.5 + (v_normal.y * u_linewidth.s / u_pattern_size_b.y);
    vec2 pos_b = mix(u_pattern_tl_b, u_pattern_br_b, vec2(x_b, y_b));

    vec4 color = mix(texture2D(u_image, pos_a), texture2D(u_image, pos_b), u_fade);

    alpha *= u_opacity;

    gl_FragColor = color * alpha;
}
)MBGL_SHADER";
#endif

} // namespace linepattern
} // namespace shaders
} // namespace mbgl

#endif
