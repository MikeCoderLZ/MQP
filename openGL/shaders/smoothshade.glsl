-- Varying

//uniform mat4 Projection;
//uniform mat4 Modelview;
//uniform mat3 NormalMatrix;
//uniform vec3 DiffuseMaterial;

-- Vertex
 
//in vec4 Position;
//in vec3 Normal;

varying vec3 EyespaceNormal;

void main()
{
    EyespaceNormal = gl_NormalMatrix * gl_Normal;
    gl_Position     = ftransform();
}

-- Fragment

//in vec3 EyespaceNormal;
//in vec3 Diffuse;
//out vec4 FragColor;

varying vec3 N, L, E, H;

//uniform vec3 LightPosition;
//uniform vec3 AmbientColor;
//uniform vec3 SpecularColor;
//uniform vec3 DiffuseColor;
//uniform float Shininess;

varying vec3 EyespaceNormal;
//varying vec3 Diffuse;

void main()
{
    vec3 LightPosition=(0.0, 0.0, 4.0);
    vec3 AmbientColor=(0.0, 0.5, 0.0);
    vec3 SpecularColor=(0.0, 0.0, 1.0);
    vec3 DiffuseColor=(0.2, 0.2, 0.2);
    float Shininess=50.0;

    vec3 N = normalize(EyespaceNormal);
    vec3 L = normalize(LightPosition);
    vec3 E = vec3(0, 0, 1);
    vec3 H = normalize(L + E);

    float df = max(0.0, dot(N, L));
    float sf = max(0.0, dot(N, H));
    sf = pow(sf, Shininess);

    vec3 color = AmbientColor + df * DiffuseColor + sf * SpecularColor;
    gl_FragColor = vec4(color, 1.0);
}