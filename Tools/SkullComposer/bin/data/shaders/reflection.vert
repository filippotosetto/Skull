#version 120

varying vec3 reflectVec;
varying vec3 N;
varying vec3 V;

void main() 
{
	V = vec3(gl_ModelViewMatrix * gl_Vertex);
	N = normalize(gl_NormalMatrix * gl_Normal);
	
	reflectVec = reflect(V, N);
	
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	// gl_Position = ftransform(); 
}