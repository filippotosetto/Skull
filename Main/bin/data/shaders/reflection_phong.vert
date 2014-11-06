/**
* @author Bruno Imbrizi - brunoimbrizi.com
*
* Based on
* http://www.john-chapman.net/content.php?id=3
* https://github.com/mrdoob/three.js/blob/master/src/renderers/shaders/ShaderChunk/lights_phong_fragment.glsl
*/

#version 120

varying vec3 vReflect;

varying vec3 V;
varying vec3 E;
varying vec3 N;

void main() 
{
	V = vec3(gl_ModelViewMatrix * gl_Vertex);
	E = normalize(-V);
	N = normalize(gl_NormalMatrix * gl_Normal);
	
	vReflect = reflect(V, N);
	
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}