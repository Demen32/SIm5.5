#version 330

in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 vWorldPos;
in vec3 vNormal;

uniform sampler2D texture0;
uniform vec4  colDiffuse;
uniform vec3  uLightPos;
uniform vec3  uViewPos;

uniform float uRangeScale;   //>1.0 = kürzere Reichweite, <1.0 = längere (Default 1.0)

out vec4 finalColor;

void main() {
    vec4 albedo = texture(texture0, fragTexCoord) * colDiffuse * fragColor;

    vec3 N = normalize(vNormal);
    vec3 L = normalize(uLightPos - vWorldPos);

    float ambient = 0.7;
    float diff    = max(dot(N, L), 0.0);

    // Distanz skalieren
    float d   = length(uLightPos - vWorldPos) * uRangeScale;
    float att = 1.0 / (1.0 + 0.09*d + 0.032*d*d);

    float lighting = ambient + diff * att;
    finalColor = vec4(albedo.rgb * lighting, albedo.a);
}


