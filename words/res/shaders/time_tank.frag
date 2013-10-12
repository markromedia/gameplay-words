#ifdef OPENGL_ES
precision highp float;
#endif

// Uniforms
uniform sampler2D u_diffuseTexture;     	// Diffuse texture
uniform sampler2D u_timerGradient;			// Timer gradient

#if defined(MODULATE_ALPHA)
uniform float u_modulateAlpha;              // Modulation alpha
#endif

// Varyings
varying vec2 v_texCoord0;                	// Texture coordinate(u, v)

uniform float u_alphaThreshold;


void main()
{
    // Sample the texture for the color
    gl_FragColor = texture2D(u_diffuseTexture, v_texCoord0);
    if (gl_FragColor.a == 0) {
        discard;
	}

	vec4 gradient_color = texture2D(u_timerGradient, v_texCoord0);
	if (gradient_color.r > u_alphaThreshold) {
		//gl_FragColor = vec4(0, 0, 0, 1);
		discard;
	}
	 
    // Global color modulation
    #if defined(MODULATE_ALPHA)
    gl_FragColor.a *= u_modulateAlpha;
    #endif
}
