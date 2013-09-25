// Attributes
attribute vec4 a_position;    								// Vertex Position							(x, y, z, w)
attribute vec2 a_texCoord0;									// Vertex Texture Coordinate				(u, v)
#if defined(TEXCOORD1)
attribute vec2 a_texCoord1;                                 // Second tex coord for multi-texturing
#endif
#if defined(SKINNING)
attribute vec4 a_blendWeights;								// Vertex blend weight, up to 4				(0, 1, 2, 3) 
attribute vec4 a_blendIndices;								// Vertex blend index int u_matrixPalette	(0, 1, 2, 3)
#endif
#if defined(VERTEX_COLOR)
attribute vec3 a_color;										// Output Vertex Color
varying vec3 v_color;										// Output Vertex Color
#endif

// Uniforms
uniform mat4 u_worldViewProjectionMatrix;					// Matrix to transform a position to clip space
#if defined(TEXTURE_REPEAT)
uniform vec2 u_textureRepeat;								// Texture repeat for tiling
#endif
#if defined(TEXTURE_OFFSET)
uniform vec2 u_textureOffset;								// Texture offset
#endif

// Varyings
varying vec2 v_texCoord0;									// Texture Coordinate

#include "skinning-none.vert" 


void main()
{
    // Get the vertex position
    vec4 position = getPosition();

    // Transform position to clip space.
    gl_Position = u_worldViewProjectionMatrix * position;

    // Texture transformation.
    v_texCoord0 = a_texCoord0;
    #if defined(TEXTURE_REPEAT)
    v_texCoord0 *= u_textureRepeat;
    #endif
    #if defined(TEXTURE_OFFSET)
    v_texCoord0 += u_textureOffset;
    #endif
    // Pass on vertex color to fragment shader
    #if defined(VERTEX_COLOR)
	v_color = a_color;
    #endif
}
