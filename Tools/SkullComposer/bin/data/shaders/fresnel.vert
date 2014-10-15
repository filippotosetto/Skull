/**
* @author brunoimbrizi.com
*
* Based on
* https://github.com/mrdoob/three.js/blob/master/examples/js/shaders/FresnelShader.js
*/

#version 120

varying vec3 vReflect;
varying vec3 vRefract[3];
varying float vReflectionFactor;

uniform float mRefractionRatio = 1.02;
uniform float mFresnelBias = 0.1;
uniform float mFresnelPower = 2.0;
uniform float mFresnelScale = 1.0;

void main() 
{
	mat4 modelMatrix = gl_ModelViewProjectionMatrix;

	vec3 worldPosition = vec3(modelMatrix * gl_Vertex);

	vec3 worldNormal = normalize( mat3( modelMatrix[0].xyz, modelMatrix[1].xyz, modelMatrix[2].xyz ) * gl_Normal );

	vec3 I = worldPosition.xyz; // - cameraPosition; // no need

	vReflect = reflect( I, worldNormal );
	vRefract[0] = refract( normalize( I ), worldNormal, mRefractionRatio );
	vRefract[1] = refract( normalize( I ), worldNormal, mRefractionRatio * 0.99 );
	vRefract[2] = refract( normalize( I ), worldNormal, mRefractionRatio * 0.98 );
	vReflectionFactor = mFresnelBias + mFresnelScale * pow( 1.0 + dot( normalize( I ), worldNormal ), mFresnelPower );

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}