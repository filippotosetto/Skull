#version 120

#define MAX_DIR_LIGHTS 3
#define MAX_POINT_LIGHTS 3
#define MAX_SPOT_LIGHTS 3


uniform samplerCube envMap;
uniform int combine = 1;
uniform float reflectivity;

uniform gl_MaterialParameters material;

varying vec3 N;
varying vec3 v;
varying vec3 reflectVec;

void main()
{
	vec4 cubeColor = textureCube(envMap, vec3(reflectVec.x, -reflectVec.y, reflectVec.z));

	vec3 L = normalize(gl_LightSource[0].position.xyz - v);   
	vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0)  
	vec3 R = normalize(-reflect(L,N));

	vec4 mvPosition = vec4(v, 1.0);
	vec3 vViewPosition = -mvPosition.xyz;
	vec3 viewPosition = normalize(vViewPosition);


#if MAX_POINT_LIGHTS > 0
	vec3 pointDiffuse = vec3( 0.0 );
	vec3 pointSpecular = vec3( 0.0 );

	for ( int i = 0; i < MAX_POINT_LIGHTS; i ++ ) {

		vec4 lPosition = gl_ProjectionMatrixInverse * gl_LightSource[ i ].position;
		// vec4 lPosition = gl_ProjectionMatrixInverse * vec4(800.0, 0.0, 0.0, 0.0);
		vec3 lVector = lPosition.xyz + vViewPosition.xyz;

		float lDistance = 1.0;
		// if ( pointLightDistance[ i ] > 0.0 )
			// lDistance = 1.0 - min( ( length( lVector ) / pointLightDistance[ i ] ), 1.0 );
		lDistance = 1.0 - min( ( length( lVector ) / 10000.0 ), 1.0 );

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


/*
#if MAX_SPOT_LIGHTS > 0

	vec3 spotDiffuse = vec3( 0.0 );
	vec3 spotSpecular = vec3( 0.0 );

	for ( int i = 0; i < MAX_SPOT_LIGHTS; i ++ ) {

		vec4 lPosition = gl_ProjectionMatrixInverse * gl_LightSource[ i ].position;
		// vec4 lPosition = gl_ModelViewMatrixInverse * vec4(-1500.0, 0.0, 1500.0, 0.0);
		vec3 lVector = lPosition.xyz + vViewPosition.xyz;

		float lDistance = 1.0;
		// if ( spotLightDistance[ i ] > 0.0 )
			// lDistance = 1.0 - min( ( length( lVector ) / spotLightDistance[ i ] ), 1.0 );

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
			// vec3 spotHalfVector = gl_LightSource[i].halfVector.xyz;
			float spotDotNormalHalf = max( dot( N, spotHalfVector ), 0.0 );
			float spotSpecularWeight = max( pow( spotDotNormalHalf, material.shininess ), 0.0 );

			float specularNormalization = ( material.shininess + 2.0 ) / 8.0;

			vec3 schlick = material.specular.xyz + vec3( 1.0 - material.specular.xyz ) * pow( max( 1.0 - dot( lVector, spotHalfVector ), 0.0 ), 5.0 );
			spotSpecular += schlick * gl_LightSource[ i ].diffuse.xyz * spotSpecularWeight * spotDiffuseWeight * lDistance * specularNormalization * spotEffect;

		}

	}

#endif
*/


	vec4 totalDiffuse = vec4( 0.0, 0.0, 0.0, 1.0 );
	vec4 totalSpecular = vec4( 0.0, 0.0, 0.0, 1.0 );

	totalDiffuse.xyz += pointDiffuse;
	totalSpecular.xyz += pointSpecular;

	// totalDiffuse.xyz += spotDiffuse;
	// totalSpecular.xyz += spotSpecular;

	// ambient
	// vec4 Iamb = gl_FrontLightProduct[0].ambient;
	vec4 ambient = material.ambient;

	// diffuse
	// vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(N,L), 0.0);
	// vec4 diffuse = gl_LightSource[0].diffuse * max(dot(N,L),0.0) * material.diffuse;
	vec4 diffuse = totalDiffuse * max(dot(N,L),0.0) * material.diffuse;

	// specular
	// vec4 Ispec = gl_FrontLightProduct[0].specular * pow(max(dot(R,E),0.0),0.3 * material.shininess);
	// vec4 specular = gl_LightSource[0].specular * pow(max(dot(R, E), 0.0), 0.3 * material.shininess) * material.specular;
	vec4 specular = totalSpecular * pow(max(dot(R, E), 0.0), 0.3 * material.shininess) * material.specular;

	// final color
	gl_FragColor = material.emission + ambient + diffuse + specular;
	// gl_FragColor = material.emission + totalDiffuse + material.ambient + totalSpecular;
	// gl_FragColor = material.emission;

	/*
	// combine with environment map
	if ( combine == 1 )
	{
		gl_FragColor.xyz = mix( gl_FragColor.xyz, cubeColor.xyz, reflectivity );
	}
	else if ( combine == 2 )
	{
		gl_FragColor.xyz += cubeColor.xyz * reflectivity;
	}
	else
	{
		gl_FragColor.xyz = mix( gl_FragColor.xyz, gl_FragColor.xyz * cubeColor.xyz, reflectivity );
	}
	*/
	
}