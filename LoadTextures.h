
vector<GLuint> texture;  
vector<string> image;

void imageFiles(){
image.push_back("images/Link.png");
image.push_back("images/brick.png");
image.push_back("images/bg2.png");
image.push_back("images/open_vert.png");
image.push_back("images/open_hor.png");
image.push_back("images/enemies.png");//5
image.push_back("images/triforce.png");
image.push_back("images/win.png");
image.push_back("images/heart1.png");
image.push_back("images/heart2.png");
image.push_back("images/game-over.png");

}

int LoadGLTextures()     
{

for(int i=0;i<image.size();i++){
    texture.push_back( SOIL_load_OGL_texture(image[i].c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y));
   if(texture[i] == 0) return false;
    glBindTexture(GL_TEXTURE_2D, texture[i]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);}
    return true;                                       
}
