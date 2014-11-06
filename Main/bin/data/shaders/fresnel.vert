/**
* @author brunoimbrizi.com
*
* Based on
* https://github.com/mrdoob/three.js/blob/master/examples/js/shaders/FresnelShader.js
*/

#version 120

varying vec3 vReflect;
varying vec3 vRefract[3];
varying float fresnelReflection;

uniform float refractionRatio = 1.02;
uniform float fresnelBias = 0.1;
uniform float fresnelPower = 2.0;
uniform float fresnelScale = 1.0;

void main() 
{
	vec3 worldNormal = normalize( mat3(gl_ModelViewProjectionMatrix) * gl_Normal );

	vec3 worldPosition = vec3(gl_ModelViewProjectionMatrix * gl_Vertex);

	vReflect = reflect( worldPosition, worldNormal );
	vRefract[0] = refract( normalize( worldPosition ), worldNormal, refractionRatio );
	vRefract[1] = refract( normalize( worldPosition ), worldNormal, refractionRatio * 0.99 );
	vRefract[2] = refract( normalize( worldPosition ), worldNormal, refractionRatio * 0.98 );
	fresnelReflection = fresnelBias + fresnelScale * pow( 1.0 + dot( normalize( worldPosition ), worldNormal ), fresnelPower );

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}