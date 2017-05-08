--Vertex

attribute vec3 position;
attribute vec3 vertColor;

uniform mat4 perspective;

varying vec3 color;

void main()
{



    /**vec4 semiProjection = mat4( 0.10, 0.0, 0.0, 0.0,
                                0.0, 0.10, 0.0, 0.0,
                                0.0, 0.0, -1.22, -0.22,
                                0.0, 0.0, -1.0, 0.0) * vec4(position, 1.0);*/

    vec4 semiProjection = perspective * vec4(position, 1.0);

    gl_Position = semiProjection;

    //gl_Position = vec4(position, 1.0);

    color = vertColor;

}

--Fragment

varying vec3 color;

void main(){

    gl_FragColor = vec4(color,1.0);

}