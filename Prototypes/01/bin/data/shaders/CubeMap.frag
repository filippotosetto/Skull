#version 120

uniform samplerCube EnvMap;

// varying vec3 normal;
// varying vec3 eyeVec;
varying vec3 reflectVec;

void main()
{
	// vec3 envColor = vec3 (textureCube(EnvMap, texcoord));
	//vec3 envColor = vec3 (textureCube(EnvMap, gl_TexCoord[0]));
	vec4 cubeColor = textureCube(EnvMap, vec3(reflectVec.x, -reflectVec.y, reflectVec.z));
	float reflectivity = 0.5;

	// gl_FragColor = vec4 (envColor, 1.0);
	gl_FragColor = cubeColor * reflectivity;
	gl_FragColor.a = 1.0;
}