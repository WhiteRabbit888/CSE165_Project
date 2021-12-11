#include <SOIL2.h>
#include "stb_image.h"
#include "Texture.h"
#include <iostream>
#include <string>

Texture2D::Texture2D()
    : Width(0), Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR)
{
}

unsigned int Texture2D::Generate(int width, int height, unsigned char* data)
{
    stbi_set_flip_vertically_on_load(true);

    //unsigned char* data = SOIL_load_image(file, &width, &height, &nrChannels, SOIL_LOAD_RGB);
    //this->ID = SOIL_load_OGL_texture(file, 3, 0, SOIL_FLAG_TEXTURE_REPEATS);
    //glGenTextures(1, &ID);

    // create Texture
    //glBindTexture(GL_TEXTURE_2D_ARRAY, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);
    // unbind texture
    //glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

    //SOIL_free_image_data(data);

    return ID;
}

void Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}

void Texture2D::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}