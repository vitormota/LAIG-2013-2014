uniform float time;
//uniform sample2d hImage;

uniform sampler2D hImage;
uniform sampler2D tImage;

varying vec2 coords;
void main()
{
	gl_TexCoord[0] = gl_MultiTexCoord0;
	vec4 offset = vec4(0,0,0,0);
	coords = gl_TexCoord[0].st  + vec2(0,time/20) ;
	vec4 hcolor = texture2D(hImage, coords);
	
	
	offset.y = hcolor.r;
	gl_Position = gl_ModelViewProjectionMatrix*(gl_Vertex + offset);
	//gl_Position = gl_ModelView * gl_ProjectionMatrix * (gl_Vertex+offset);
}