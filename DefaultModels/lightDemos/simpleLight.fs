#version 430
in vec3 vPos;//world space
in vec3 vNormal;//world space
out vec4 outColor;

struct Light {
    vec4 position;
    vec4 color;
};

uniform LightUBlock {
    Light uLights[1];
};

uniform uint uLightCount;
uniform vec3 uWarmColor=vec3(0.3, 0.3, 0);
uniform vec4 uEyePosition;
uniform vec3 uFUnlit=vec3(0.0, 0.0, 0.0);

vec3 lit(vec3 l, vec3 n, vec3 v) {
    vec3 r_l = reflect(-l, n);
    float s = clamp(100.0 * dot(r_l, v) - 97.0, 0.0, 1.0);
    vec3 highlightColor = vec3(2, 2, 2);
    return mix(uWarmColor, highlightColor, s);
}

void main() {
    //vec3 color = (vPos + 1.0f) * 0.5f;
    //outColor = vec4(color, 1.0f);
    vec3 n = normalize(vNormal);
    vec3 v = normalize(uEyePosition.xyz - vPos);
    outColor = vec4(uFUnlit, 1.0);

    for (uint i = 0u; i < uLightCount; i++) {
        vec3 l = normalize(uLights[i].position.xyz - vPos);
        float NdL = clamp(dot(n, l), 0.0, 1.0);
        outColor.rgb += NdL * uLights[i].color.rgb * lit(l, n, v);
    }
}
