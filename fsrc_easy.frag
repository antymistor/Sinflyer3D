#version 330
//uniform sampler2D sTexture;
//in vec2 vTextureCood;
in vec4 vAmbient;
in vec4 vDiffuse;
in vec4 vSpecular;
in vec3 position_n;
in vec4 color_n;
out vec4 fragColor;

void main(void)
{
    vec4 finalColor;
   if(color_n.w!=0)
    {
         finalColor=color_n;
    }
   else
    {
         finalColor= vec4(position_n.x/20,position_n.y/20,position_n.z/20,0.4);
    }
    //vec4 finalColor = vec4(0.1,0.4,0.6,1);
    finalColor = finalColor * (vAmbient + vDiffuse + vSpecular);
    fragColor = finalColor;
    //gl_FragColor=fragColor;
}

