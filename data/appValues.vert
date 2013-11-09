// Getting values from application

uniform float normScale;
varying vec4 coords;

void main() {

	// Displace a vertex in the direction of its normal, with a scale factor)
	gl_Position = gl_ModelViewProjectionMatrix * (gl_Vertex+vec4(gl_Normal*normScale*0.1,0.0));

	// set the RGB components of "gl_FrontColor" (built-in varying) to the XYZ components of the normal (and alpha=1)
	// these values will be received interpolated in the fragment shader as "gl_Color"
	gl_FrontColor = vec4(gl_Normal,1.0);
	
	// set the custom varying "coords" to the original vertex coordinates
	// these will be interpolated in the fragment shader
	coords=gl_Vertex;
}