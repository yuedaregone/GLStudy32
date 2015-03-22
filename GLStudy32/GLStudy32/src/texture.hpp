#ifndef TEXTURE_HPP
#define TEXTURE_HPP

// Load a .BMP file using our custom loader
GLuint loadBMP_custom(const char * imagepath, unsigned int &width, unsigned int &height);

//// Since GLFW 3, glfwLoadTexture2D() has been removed. You have to use another texture loading library, 
//// or do it yourself (just like loadBMP_custom and loadDDS)
//// Load a .TGA file using GLFW's own loader
//GLuint loadTGA_glfw(const char * imagepath);

// Load a .DDS file using GLFW's own loader
GLuint loadDDS(const char * imagepath, unsigned int& _w, unsigned int& _h);

// Load Data
GLuint loadData(void* _data, size_t _size, size_t _width, size_t _height);

//set testure 
void setTextureParameteri();
#endif