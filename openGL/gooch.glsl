-- Uniforms
uniform vec3 DiffuseColor;

-- Vertex

uniform vec3 DiffuseColor;

void main()
{
	
    vec3 ambient, diffuse, specular;
    vec3 eyePosition = gl_ModelViewMatrix * gl_Vertex;
    vec3 eyeLightPos = (0.0,4.0,0.0);
    vec3 N = normalize(gl_NormalMatrix * gl_Normal);
    vec3 L = normalize(eyeLightPos - eyePosition);
    vec3 E = -normalize(eyePosition);
    vec3 H = normalize(L + E);

	/* compute diffuse, ambient, and specular contributions */
    float Kd = max(dot(L, N), 0.0);
    float Ks = pow(max(dot(N, H), 0.0), 10);
    float Ka = 0.1;
    ambient = Ka*(0.1,0.1,0.1);
    diffuse = Kd*DiffuseColor;
    specular = Ks*(.2,.4,.7);
    
    gl_Position = ftransform()
    gl_FrontColor = ambient+diffuse+specular;

} 

-- Fragment

void main()
{
	gl_FragColor =  gl_Color;
}