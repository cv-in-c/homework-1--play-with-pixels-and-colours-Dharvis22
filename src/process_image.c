#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
   int m=x+y*im.w+c*im.w*im.h;
    return im.data[m];
    
}

void set_pixel(image im, int x, int y, int c, float v)
{
     if(x<0||x>=im.w||y<0||y>=im.h||c<0||c>=im.c){
        return;
    }
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    memcpy(copy.data,im.data,im.w*im.h*im.c*sizeof(float));
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    for(int x=0;x<im.w;x++){
        for(int y=0;y<im.h;y++){
            float r=get_pixel(im,x,y,0);
            float g=get_pixel(im,x,y,1);
            float b=get_pixel(im,x,y,2);
            float gray_value=0.299*r +0.587*g +0.114*b;
            set_pixel(gray,x,y,0,gray_value);

        }
    }
    return gray;
}

void shift_image(image im, int c, float v)
{
   for(int x=0;x<im.w;x++){
        for(int y=0;y<im.h;y++){
            float n=get_pixel(im,x,y,c);
            set_pixel(im,x,y,c,n+v);
        }
    }
}

void clamp_image(image im)
{
    for(int c=0;c<im.c;c++){
    for(int x=0;x<im.w;x++){
        for(int y=0;y<im.h;y++){
            float k=get_pixel(im,x,y,c);
            if(k<0){
                set_pixel(im,x,y,c,0);
            }
            else if(k>1){
                set_pixel(im,x,y,c,1);
            }
        }

    }
   }
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    for(int x=0;x<im.w;x++){
        for(int y=0;y<im.h;y++){
            float r=get_pixel(im,x,y,0);
            float g=get_pixel(im,x,y,1);
            float b=get_pixel(im,x,y,2);
            float V=three_way_max(r,g,b);
            float m=three_way_min(r,g,b);
            float C=V-m;
            float H;
            if(C==0){
                H=0;
            }
            else if(V==r){
                H=(g-b)/C;
            }
            else if(V==g){
                H=((b-r)/C)+2;

            }
            else if(V==b){
                H=((r-g)/C)+4;
            }
            float h;
            if(H<0){
                h=H/6+1;
            }
            else{
                h=H/6;
            }
            float s;
            if(V==0){
                s=0;

            }
            else{
                s=C/V;
            }
            set_pixel(im,x,y,0,h);
            set_pixel(im,x,y,1,s);
            set_pixel(im,x,y,2,V);


        }
    }
}

void hsv_to_rgb(image im)
{
    for(int x=0;x<im.w;x++){
        for(int y=0;y<im.h;y++){
            float h=get_pixel(im,x,y,0);
            float s=get_pixel(im,x,y,1);
            float V=get_pixel(im,x,y,2);
            float c=s*V;

        }
    }
}
