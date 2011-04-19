#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl.h>
#include <GL/glu.h>

struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};
typedef struct Image Image;

Image ImageLoad(char *filename);
void OGL_Set_Current_Texture_Map(Image image1, float u_scale, float v_scale, float u_offset, float v_offset);

void OGL_Set_Current_Material_Parameters(float shininess, float r_diffuseColor, float g_diffuseColor, float b_diffuseColor, float r_specularColor, float g_specularColor, float b_specularColor);

//GLuint loadMipmappedTexture(RGBImage*);
//void   setMipmappedTexture(GLuint);

#endif

