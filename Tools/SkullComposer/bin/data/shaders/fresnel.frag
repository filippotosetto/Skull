/**
* @author brunoimbrizi.com
*
* Based on
* https://github.com/mrdoob/three.js/blob/master/examples/js/shaders/FresnelShader.js
*/

#version 120

uniform samplerCube envMap;
varying vec3 vReflect;
varying vec3 vRefract[3];
varying float vReflectionFactor;


void main() {
	vec4 reflectedColor = textureCube( envMap, vec3( -vReflect.x, vReflect.y, -vReflect.z ) );
	vec4 refractedColor = vec4( 1.0 );

	refractedColor.r = textureCube( envMap, vec3( -vRefract[0].x, vRefract[0].y, -vRefract[0].z ) ).r;
	refractedColor.g = textureCube( envMap, vec3( -vRefract[1].x, vRefract[1].y, -vRefract[1].z ) ).g;
	refractedColor.b = textureCube( envMap, vec3( -vRefract[2].x, vRefract[2].y, -vRefract[2].z ) ).b;

	gl_FragColor = mix( refractedColor, reflectedColor, clamp( vReflectionFactor, 0.0, 1.0 ) );
}