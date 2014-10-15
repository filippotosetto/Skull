/**
* @author brunoimbrizi.com
*
* Based on
* http://www.john-chapman.net/content.php?id=3
* https://github.com/mrdoob/three.js/blob/master/src/renderers/shaders/ShaderChunk/lights_phong_fragment.glsl
*/

#version 120
#extension GL_EXT_gpu_shader4 : require

varying vec3 reflectVec;
varying vec3 eyeVec;

varying vec3 V;
varying vec3 E;
varying vec3 N;

void main() 
{
	V = vec3(gl_ModelViewMatrix * gl_Vertex);
	E = normalize(-V);
	N = normalize(gl_NormalMatrix * gl_Normal);
	
	reflectVec = reflect(V, N);
	eyeVec = -V;
	
	// gl_Position = ftransform(); 
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}