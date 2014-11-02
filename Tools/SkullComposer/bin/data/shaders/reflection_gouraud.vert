/**
* @author Bruno Imbrizi - brunoimbrizi.com
*
* Based on
* https://github.com/mrdoob/three.js/blob/master/src/renderers/shaders/ShaderChunk/lights_lambert_vertex.glsl
*/

#version 120

#define MAX_LIGHTS 3

uniform int combineLightsMode = 0;
uniform gl_MaterialParameters material;

varying vec3 vReflect;
varying vec4 vColor;

varying vec3 V;
varying vec3 E;
varying vec3 N;

struct LightingResults {
	vec4 diffuse;
	vec4 specular;
};


void point(in gl_LightSourceParameters light, inout LightingResults results) {
	// direction
	vec3 lightDirection = light.position.xyz - V;

	// distance
	float lightDistance = length(lightDirection);

	// attenuation
	float attenuation = 1.0 / (light.constantAttenuation + light.linearAttenuation * lightDistance + light.quadraticAttenuation * lightDistance * lightDistance);

	// angle of incidence (?)
	lightDirection = normalize(lightDirection);
	float dotProduct = max(0.0, dot(N, lightDirection));

	// diffuse
	results.diffuse += material.diffuse * light.diffuse * attenuation * dotProduct;

	// specular
	if (combineLightsMode == 0) {
		// john-chapman mode
		if (dotProduct > 0.0) {
			vec3 reflection = reflect(lightDirection, N);
			float specular = max(0.0, dot(reflection, normalize(V)));
			results.specular += material.specular * light.diffuse * pow(specular, material.shininess) * attenuation;
		}
	}
	else {
		// three.js mode
		vec3 halfVector = normalize(lightDirection + normalize(V));
		float dotNormalHalf = max( dot( N, halfVector ), 0.0 );
		float specularWeight = max( pow( dotNormalHalf, material.shininess ), 0.0 );
		float specularNormalization = ( material.shininess + 2.0 ) / 8.0;

		vec4 schlick = material.specular + vec4( 1.0 - material.specular ) * pow( max( 1.0 - dot( lightDirection, halfVector ), 0.0 ), 5.0 );
		results.specular += schlick * light.diffuse * specularWeight * attenuation * dotProduct * specularNormalization;
	}
}

void spot(in gl_LightSourceParameters light, inout LightingResults results) {
	// direction
	vec3 lightDirection = light.position.xyz - V;

	// distance
	float lightDistance = length(lightDirection);

	// angle of incidence (?)
	lightDirection = normalize(lightDirection);
	float dotSpot = dot(normalize(light.spotDirection), -lightDirection);

	// attenuation
	float attenuation = 1.0 / (light.constantAttenuation + light.linearAttenuation * lightDistance + light.quadraticAttenuation * lightDistance * lightDistance);

	// if not in cut off area (?)
	if (dotSpot > light.spotCosCutoff) {
		attenuation *= pow(dotSpot, light.spotExponent);

		// diffuse
		float dotProduct = max(0.0, dot(N, lightDirection));
		results.diffuse += material.diffuse * light.diffuse * attenuation * dotProduct;

		// specular
		if (combineLightsMode == 0) {
			// john-chapman mode
			if (dotProduct > 0.0) {
				vec3 reflection = reflect(lightDirection, N);
				float specular = max(0.0, dot(reflection, normalize(V)));
				results.specular += material.specular * light.diffuse * pow(specular, material.shininess) * attenuation;
			}
			// three.js mode
			else {
				vec3 halfVector = normalize(lightDirection + normalize(V));
				float dotNormalHalf = max( dot( N, halfVector ), 0.0 );
				float specularWeight = max( pow( dotNormalHalf, material.shininess ), 0.0 );
				float specularNormalization = ( material.shininess + 2.0 ) / 8.0;

				vec4 schlick = material.specular + vec4( 1.0 - material.specular ) * pow( max( 1.0 - dot( lightDirection, halfVector ), 0.0 ), 5.0 );
				results.specular += schlick * light.diffuse * specularWeight * attenuation * dotSpot * specularNormalization;
			}
		}
	}
}

void directional(in gl_LightSourceParameters light, inout LightingResults results) {
	// direction
	vec3 lightDirection = normalize(light.position.xyz);

	// angle of incidence (?)
	float dotProduct = max(0.0, dot(N, lightDirection));

	// diffuse
	results.diffuse += material.diffuse * light.diffuse * dotProduct;

	// specular
	if (dotProduct > 0.0) {
		vec3 reflection = reflect(lightDirection, N);
		float specular = max(0.0, dot(reflection, normalize(V)));
		results.specular += light.diffuse * pow(specular, material.shininess);
	}
}


void main() {
	V = vec3(gl_ModelViewMatrix * gl_Vertex);
	E = normalize(-V);
	N = normalize(gl_NormalMatrix * gl_Normal);
	
	vReflect = reflect(V, N);

	// lights
	// vec4 result = vec4(0.0);
	LightingResults results;
	results.diffuse = vec4(0.0);
	results.specular = vec4(0.0);

	for (int i = 0; i < MAX_LIGHTS; i ++) {
		if (gl_LightSource[i].position.w != 0.0) {
			if (gl_LightSource[i].spotExponent != 0.0) {
				spot(gl_LightSource[i], results);
			}
			else {
				point(gl_LightSource[i], results);
			}
		}
		else {
			directional(gl_LightSource[i], results);
		}
	}

	vColor = material.emission + results.diffuse + results.specular;
	
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}