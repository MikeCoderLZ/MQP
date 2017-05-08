-- Uniforms
uniform vec3 DiffuseColor;

-- Vertex



varying vec3 EyespaceNormal, eyePosition;
//varying vec3 N, L, E, H;

void main()
{
    
    eyePosition = gl_ModelViewMatrix * gl_Vertex;
    EyespaceNormal = normalize(gl_NormalMatrix * gl_Normal);
    gl_Position     = ftransform();
    //vec3 test = reflect(eyePosition, Norm);
}

-- Fragment

uniform vec3 DiffuseColor;

uniform vec3 worldLightPosition;

//varying vec3 N, L, E, H;

varying vec3 EyespaceNormal, eyePosition;

void main()
{

    //vec3 LightPosition= (10.0, 10.0, 3.0);
    
    vec3 AmbientColor=(0.0, 0.5, 0.0);
    vec3 SpecularColor=(0.0, 0.0, 1.0);
    float Shininess=80.0;

    vec3 N = normalize(EyespaceNormal);//normal
    vec3 L = normalize(worldLightPosition-eyePosition);//Eye-light position
    vec3 E = -normalize(eyePosition);//;vec3(0, 0, 1);
    vec3 H = normalize(L + E);

    float df = max(0.0, dot(N, L));
    float sf = max(0.0, dot(N, H));
    sf = pow(sf, Shininess);

    vec3 color = AmbientColor + df * DiffuseColor + sf * SpecularColor;
    gl_FragColor = vec4(color, 1.0);
}