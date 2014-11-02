/**
* @author Bruno Imbrizi - brunoimbrizi.com
*/

#version 120

#define MAX_LIGHTS 3

uniform samplerCube envMap;
uniform int combineLightsMode = 0;
uniform int combineEnvironmentMode = 1;
uniform bool reflectionGrayscale;
uniform float reflectivity;

varying vec3 vReflect;
varying vec4 vColor;

varying vec3 V;
varying vec3 E;
varying vec3 N;


void main() {
	// normal map
	// gl_FragColor = vec4((N + vec3(1.0, 1.0, 1.0)) / 2.0, 1.0);

	// lights
	gl_FragColor = vColor;

	// environment reflection
	vec4 cubeColor = textureCube(envMap, vec3(-vReflect.x, -vReflect.y, vReflect.z));
	
	if (reflectionGrayscale) {
		float gray = dot(cubeColor.rgb, vec3(0.299, 0.587, 0.114));
		cubeColor = vec4(gray, gray, gray, 1.0);
	}

	if (combineEnvironmentMode == 1) {
		gl_FragColor.xyz = mix( gl_FragColor.xyz, cubeColor.xyz, reflectivity);
	}
	else if (combineEnvironmentMode == 2) {
		gl_FragColor.xyz += cubeColor.xyz * reflectivity;
	}
	else {
		gl_FragColor.xyz = mix( gl_FragColor.xyz, gl_FragColor.xyz * cubeColor.xyz, reflectivity);
	}

}