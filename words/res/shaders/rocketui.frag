#ifdef OPENGL_ES
precision highp float;
#endif

// Uniforms
uniform sampler2D u_diffuseTexture;         // Diffuse texture
#if defined(MODULATE_COLOR)
uniform vec4 u_modulateColor;               // Modulation color
#endif
#if defined(MODULATE_ALPHA)
uniform float u_modulateAlpha;              // Modulation alpha
#endif

// Varyings
varying vec2 v_texCoord0;                	// Texture coordinate(u, v)
#if defined(VERTEX_COLOR)
varying vec3 v_color;						// Input Vertex color ( r g b )
#endif

void main()
{
    // Sample the texture for the color
    gl_FragColor = texture2D(u_diffuseTexture, v_texCoord0);
    #if defined(VERTEX_COLOR)
//    gl_FragColor = gl_FragColor * vec4(v_color, 1.0);
    #endif
    // Global color modulation
    #if defined(MODULATE_COLOR)
    gl_FragColor *= u_modulateColor;
    #endif
    #if defined(MODULATE_ALPHA)
    gl_FragColor.a *= u_modulateAlpha;
    #endif
    gl_FragColor.a = texture2D(u_diffuseTexture, v_texCoord0).a;
//    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
