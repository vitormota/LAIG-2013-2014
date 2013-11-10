//uniform sampler2d tImage;

uniform sampler2D hImage;
uniform sampler2D tImage;

varying vec2 coords;
void main()
{
	gl_FragColor = texture2D(tImage, coords);
	//gl_FragColor = gl_Color;
}