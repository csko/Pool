#include <stdio.h>
#include "../include/texturefunctions.h"
#include <iostream>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/gl.h>			// Header File For The OpenGL32 Library
#include <GL/glext.h>

using std::cout;

// quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane only.  
// See http://www.dcs.ed.ac.uk/~mxr/gfx/2d/BMP.txt for more info.
Image ImageLoad(char *filename) {
    FILE *file;
    unsigned long size;                 // size of the image in bytes.
    unsigned long i;                    // standard counter.
    unsigned short int planes;          // number of planes in image (must be 1) 
    unsigned short int bpp;             // number of bits per pixel (must be 24)
    char temp;                          // temporary color storage for bgr-rgb conversion.
    Image image;
    
    // allocate space for texture
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL)
    {
	printf("File Not Found : %s\n",filename);
    }
    
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);

    // read the width
    if ((i = fread(&image.sizeX, 4, 1, file)) != 1) {
	printf("Error reading width from %s.\n", filename);
    }
    printf("Width of %s: %lu\n", filename, image.sizeX);
    
    // read the height 
    if ((i = fread(&image.sizeY, 4, 1, file)) != 1) {
	printf("Error reading height from %s.\n", filename);
    }
    printf("Height of %s: %lu\n", filename, image.sizeY);
    
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = image.sizeX * image.sizeY * 3;

    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
	printf("Error reading planes from %s.\n", filename);
    }
    if (planes != 1) {
	printf("Planes from %s is not 1: %u\n", filename, planes);
    }

    // read the bpp
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
	printf("Error reading bpp from %s.\n", filename);
    }
    if (bpp != 24) {
	printf("Bpp from %s is not 24: %u\n", filename, bpp);
    }
	
    // seek past the rest of the bitmap header.
    fseek(file, 24, SEEK_CUR);

    // read the data. 
    image.data = (char *) malloc(size);
    if (image.data == NULL) {
	printf("Error allocating memory for color-corrected image data");
    }

    if ((i = fread(image.data, size, 1, file)) != 1) {
	printf("Error reading image data from %s.\n", filename);
    }

    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
	temp = image.data[i];
	image.data[i] = image.data[i+2];
	image.data[i+2] = temp;
    }
    
    // we're done.
    return image;
}
    

void OGL_Set_Current_Texture_Map(Image image1, float u_scale, float v_scale, float u_offset, float v_offset)
{
glTexImage2D(GL_TEXTURE_2D, 0, 3, image1.sizeX, image1.sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1.data);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  // glShadeModel(GL_FLAT);
}

/*GLuint loadMipmappedTexture(RGBImage *img) {
    GLuint textureId;
    glGenTextures(1, &textureId);
    cout << "Texture-id ist : " << textureId << "\n";
    glBindTexture(GL_TEXTURE_2D, textureId);
    cout << "Textur gebunden.\n";
    cout << "Fehler beim generieren von Mipmaps: " << gluBuild2DMipmaps(GL_TEXTURE_2D,
                      GL_RGB,
                      img->width, img->height,
                      GL_RGB,
                      GL_UNSIGNED_BYTE,
                      img->imgData) << "\n";
    return textureId;
}

void setMipmappedTexture(GLuint texname)
{
  glBindTexture(GL_TEXTURE_2D, texname);


  }*/
