// NOTE: DO NOT CHANGE THIS FILE. IT IS AUTOMATICALLY GENERATED.

#ifndef MBGL_SHADER_RASTER_FRAGMENT
#define MBGL_SHADER_RASTER_FRAGMENT

#include <mbgl/platform/gl.hpp>

namespace mbgl {
namespace shaders {
namespace raster {

#ifdef GL_ES_VERSION_2_0
constexpr const char* fragment = R"MBGL_SHADER(precision highp float;
uniform sampler2D u_image;
uniform float u_opacity;

varying vec2 v_pos;

uniform float u_brightness_low;
uniform float u_brightness_high;

uniform float u_saturation_factor;
uniform float u_contrast_factor;
uniform vec3 u_spin_weights;

void main() {

    vec4 color = texture2D(u_image, v_pos) * u_opacity;
    vec3 rgb = color.rgb;

    // spin
    rgb = vec3(
        dot(rgb, u_spin_weights.xyz),
        dot(rgb, u_spin_weights.zxy),
        dot(rgb, u_spin_weights.yzx));

    // saturation
    float average = (color.r + color.g + color.b) / 3.0;
    rgb += (average - rgb) * u_saturation_factor;

    // contrast
    rgb = (rgb - 0.5) * u_contrast_factor + 0.5;

    // brightness
    vec3 u_high_vec = vec3(u_brightness_low, u_brightness_low, u_brightness_low);
    vec3 u_low_vec = vec3(u_brightness_high, u_brightness_high, u_brightness_high);

    gl_FragColor = vec4(mix(u_high_vec, u_low_vec, rgb), color.a);
}
)MBGL_SHADER";
#else
constexpr const char* fragment = R"MBGL_SHADER(#version 120
uniform sampler2D u_image;
uniform float u_opacity;

varying vec2 v_pos;

uniform float u_brightness_low;
uniform float u_brightness_high;

uniform float u_saturation_factor;
uniform float u_contrast_factor;
uniform vec3 u_spin_weights;

void main() {

    vec4 color = texture2D(u_image, v_pos) * u_opacity;
    vec3 rgb = color.rgb;

    // spin
    rgb = vec3(
        dot(rgb, u_spin_weights.xyz),
        dot(rgb, u_spin_weights.zxy),
        dot(rgb, u_spin_weights.yzx));

    // saturation
    float average = (color.r + color.g + color.b) / 3.0;
    rgb += (average - rgb) * u_saturation_factor;

    // contrast
    rgb = (rgb - 0.5) * u_contrast_factor + 0.5;

    // brightness
    vec3 u_high_vec = vec3(u_brightness_low, u_brightness_low, u_brightness_low);
    vec3 u_low_vec = vec3(u_brightness_high, u_brightness_high, u_brightness_high);

    gl_FragColor = vec4(mix(u_high_vec, u_low_vec, rgb), color.a);
}
)MBGL_SHADER";
#endif

} // namespace raster
} // namespace shaders
} // namespace mbgl

#endif
