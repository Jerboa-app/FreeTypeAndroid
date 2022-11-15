#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H

#include <Text/type.cpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TextRenderer {
public:

  TextRenderer(glm::mat4 p);
  ~TextRenderer(){
    glDeleteBuffers(1,&VBO);
    glDeleteVertexArrays(1,&VAO);
    glDeleteProgram(shader);
  }

  void renderText(
    Type type,
    std::string text,
    float x,
    float y,
    float scale,
    glm::vec3 colour);

private:
  GLuint shader;
  GLuint VAO;
  GLuint VBO;

  glm::mat4 projection;

 const char * defaultVertexShader = "#version 300 es\n"
    "precision lowp float;\n"
    "layout(location=0) in vec4 postex;\n"
    "out vec2 texCoords;\n"
    "uniform mat4 proj;\n"
    "void main(){\n"
    " gl_Position = proj*vec4(postex.xy,0.0,1.0);\n"
    " texCoords = postex.zw;\n"
    "}";

  const char * defaultFragmentShader = "#version 300 es\n"
    "precision lowp float;\n"
    "in vec2 texCoords; out vec4 colour;\n"
    "uniform sampler2D glyph;\n"
    "uniform vec3 textColour;\n"
    "void main(){\n"
    " vec4 glyphSample = vec4(1.0,1.0,1.0,texture(glyph,texCoords).r);\n"
    " colour = vec4(textColour,1.0)*glyphSample;\n"
    "}";
};

#endif
