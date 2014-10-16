/**
* @author brunoimbrizi.com
*
* Based on
* http://www.john-chapman.net/content.php?id=3
* https://github.com/mrdoob/three.js/blob/master/src/renderers/shaders/ShaderChunk/lights_phong_fragment.glsl
*/

#version 120

#define MAX_LIGHTS 3

uniform samplerCube envMap;
uniform int combineLightsMode = 0;
uniform int combineEnvironmentMode = 1;
uniform float reflectivity;

uniform gl_MaterialParameters material;

varying vec3 vReflect;

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
			else {
				// three.js mode
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
	results.diffuse += light.diffuse * dotProduct;

	// specular
	if (dotProduct > 0.0) {
		vec3 reflection = reflect(lightDirection, N);
		float specular = max(0.0, dot(reflection, normalize(V)));
		results.specular += light.specular * pow(specular, material.shininess);
	}
}


void main() {
	// normal map
	// gl_FragColor = vec4((N + vec3(1.0, 1.0, 1.0)) / 2.0, 1.0);


	// lights
	LightingResults results;
	results.diffuse = vec4(0.0);
	results.specular = vec4(0.0);

	for (int i = 0; i < MAX_LIGHTS; i ++) {
		if (gl_LightSource[i].position.w != 0.0) { 			// with openFrameworks this is always true because ofLight.position is ofVec3f
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

	gl_FragColor = material.emission + results.diffuse + results.specular;


	// environment reflection
	vec4 cubeColor = textureCube(envMap, vec3(-vReflect.x, -vReflect.y, vReflect.z));

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