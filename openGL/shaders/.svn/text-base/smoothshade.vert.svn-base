//in vec4 Position;
//in vec3 Normal;

//uniform mat4 Projection;
//uniform mat4 Modelview;
//uniform mat3 NormalMatrix;
//uniform vec3 DiffuseMaterial;

varying vec3 EyespaceNormal;

void main()
{
    EyespaceNormal = gl_NormalMatrix * gl_Normal;
    gl_Position     = ftransform();
}
