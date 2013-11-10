uniform sampler2DRect tex0; //  background
    uniform sampler2DRect tex1; //  displacement
    
    void main(){
        vec2 st = gl_TexCoord[0].st;
        
        float offsetX = texture2DRect(tex1, st + vec2(-1.0, 0.0)).r - texture2DRect(tex1, st + vec2(1.0, 0.0)).r;
        float offsetY = texture2DRect(tex1, st + vec2(0.0,- 1.0)).r - texture2DRect(tex1, st + vec2(0.0, 1.0)).r;
        
        float shading = offsetX;
        
        vec3 pixel = texture2DRect(tex0, st + vec2(offsetX, offsetY)).rgb;
        
        pixel.r += shading;
        pixel.g += shading;
        pixel.b += shading;
        
        gl_FragColor.rgb =  pixel;
        gl_FragColor.a = 1.0;
    }