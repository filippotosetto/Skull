#version 120

#define MAX_POINT_LIGHTS 3
#define MAX_SPOT_LIGHTS 3

uniform samplerCube envMap;
uniform int combineLightsMode = 1;
uniform int combineEnvironmentMode = 1;
uniform float reflectivity;

uniform gl_MaterialParameters material;

varying vec3 N;
varying vec3 V;
varying vec3 reflectVec;

void main()
{
	vec4 cubeColor = textureCube(envMap, vec3(reflectVec.x, -reflectVec.y, reflectVec.z));

	vec3 L = normalize(gl_LightSource[0].position.xyz - V);   
	vec3 E = normalize(-V); // we are in Eye Coordinates, so EyePos is (0,0,0)  
	vec3 R = normalize(-reflect(L,N));

	vec3 vViewPosition = -V;
	vec3 viewPosition = normalize(vViewPosition);


#if MAX_POINT_LIGHTS > 0
	vec3 pointDiffuse = vec3( 0.0 );
	vec3 pointSpecular = vec3( 0.0 );

	for ( int i = 0; i < MAX_POINT_LIGHTS; i ++ ) {

		vec4 lPosition = gl_LightSource[ i ].position;
		// vec4 lPosition = gl_ModelViewProjectionMatrix * gl_LightSource[ i ].position;
		vec3 lVector = lPosition.xyz + vViewPosition.xyz;

		float lDistance = 1.0;

		lVector = normalize( lVector );

				// diffuse

		float dotProduct = dot( N, lVector );

		float pointDiffuseWeight = max( dotProduct, 0.0 );

		pointDiffuse += material.diffuse.xyz * gl_LightSource[ i ].diffuse.xyz * pointDiffuseWeight * lDistance;

				// specular

		vec3 pointHalfVector = normalize( lVector + viewPosition );
		float pointDotNormalHalf = max( dot( N, pointHalfVector ), 0.0 );
		float pointSpecularWeight = max( pow( pointDotNormalHalf, material.shininess ), 0.0 );

		float specularNormalization = ( material.shininess + 2.0 ) / 8.0;

		vec3 schlick = material.specular.xyz + vec3( 1.0 - material.specular.xyz ) * pow( max( 1.0 - dot( lVector, pointHalfVector ), 0.0 ), 5.0 );
		pointSpecular += schlick * gl_LightSource[ i ].diffuse.xyz * pointSpecularWeight * pointDiffuseWeight * lDistance * specularNormalization;

	}
#endif



#if MAX_SPOT_LIGHTS > 0

	vec3 spotDiffuse = vec3( 0.0 );
	vec3 spotSpecular = vec3( 0.0 );

	for ( int i = 0; i < MAX_SPOT_LIGHTS; i ++ ) {

		vec4 lPosition = gl_LightSource[ i ].position;
		vec3 lVector = lPosition.xyz + vViewPosition.xyz;

		float lDistance = 1.0;

		lVector = normalize( lVector );

		float spotEffect = dot( gl_LightSource[ i ].spotDirection, normalize( gl_LightSource[ i ].position.xyz ) );

		if ( spotEffect > gl_LightSource[ i ].spotCosCutoff ) {

			spotEffect = max( pow( max( spotEffect, 0.0 ), gl_LightSource[ i ].spotExponent ), 0.0 );

					// diffuse

			float dotProduct = dot( N, lVector );

			float spotDiffuseWeight = max( dotProduct, 0.0 );

			spotDiffuse += material.diffuse.xyz * gl_LightSource[ i ].diffuse.xyz * spotDiffuseWeight * lDistance * spotEffect;

					// specular

			vec3 spotHalfVector = normalize( lVector + viewPosition );
			float spotDotNormalHalf = max( dot( N, spotHalfVector ), 0.0 );
			float spotSpecularWeight = max( pow( spotDotNormalHalf, material.shininess ), 0.0 );

			float specularNormalization = ( material.shininess + 2.0 ) / 8.0;

			vec3 schlick = material.specular.xyz + vec3( 1.0 - material.specular.xyz ) * pow( max( 1.0 - dot( lVector, spotHalfVector ), 0.0 ), 5.0 );
			spotSpecular += schlick * gl_LightSource[ i ].diffuse.xyz * spotSpecularWeight * spotDiffuseWeight * lDistance * specularNormalization * spotEffect;

		}

	}

#endif

	vec4 totalDiffuse = vec4( 0.0, 0.0, 0.0, 1.0 );
	vec4 totalSpecular = vec4( 0.0, 0.0, 0.0, 1.0 );

	totalDiffuse.xyz += pointDiffuse;
	totalSpecular.xyz += pointSpecular;

	// totalDiffuse.xyz += spotDiffuse;
	// totalSpecular.xyz += spotSpecular;

	vec4 diffuse = totalDiffuse * max(dot(N,L),0.0) * material.diffuse;
	vec4 specular = totalSpecular * pow(max(dot(R, E), 0.0), 0.3 * material.shininess) * material.specular;

	
	// combine lights
	if ( combineLightsMode == 1 ) {
		gl_FragColor = material.emission + material.ambient + diffuse + specular;
	}
	else if ( combineLightsMode == 2 ) {
		gl_FragColor = material.emission + totalDiffuse + material.ambient + totalSpecular;
	}
	else {
		gl_FragColor = material.emission + diffuse + material.ambient + totalSpecular;
	}

	// gl_FragColor.a = 0.5;

	
	// combine environment
	if ( combineEnvironmentMode == 1 ) {
		gl_FragColor.xyz = mix( gl_FragColor.xyz, cubeColor.xyz, reflectivity );
	}
	else if ( combineEnvironmentMode == 2 ) {
		gl_FragColor.xyz += cubeColor.xyz * reflectivity;
	}
	else {
		gl_FragColor.xyz = mix( gl_FragColor.xyz, gl_FragColor.xyz * cubeColor.xyz, reflectivity );
	}
	
	
}