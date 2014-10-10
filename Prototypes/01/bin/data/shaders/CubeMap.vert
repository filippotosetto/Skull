#version 120

varying vec3 normal;
varying vec3 eyeVec;
varying vec3 reflectVec; 

void main() 
{
	// vec4	texcoord0 = gl_ModelViewMatrix * gl_Vertex;
	//texcoord = texcoord0.xyz;
	// texcoord = normalize(gl_Vertex.xyz);

	// gl_Position    = ftransform();

	gl_TexCoord[0] = gl_MultiTexCoord0; 
	gl_Position = ftransform(); 
	normal = normalize(gl_NormalMatrix * gl_Normal); 
	eyeVec = vec3(gl_ModelViewMatrix * gl_Vertex); 
	reflectVec = reflect(eyeVec, normal);
}