#include <Text/textRenderer.h>
#include <glUtils.h>

TextRenderer::TextRenderer(glm::mat4 p){
  projection = p;
  // text buffers
  glGenVertexArrays(1,&VAO);
  glGenBuffers(1,&VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER,sizeof(float)*6*4,NULL,GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,4*sizeof(float),0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  shader = glCreateProgram();
  compileShader(shader,defaultVertexShader,defaultFragmentShader);
  glUseProgram(shader);

  glUniformMatrix4fv(
    glGetUniformLocation(shader,"proj"),
    1,
    GL_FALSE,
    &projection[0][0]
  );

  glError("TextRenderer constructor: ");
}

void TextRenderer::renderText(
  Type type,
  std::string text,
  float x,
  float y,
  float scale,
  glm::vec3 colour){
    // have a look at this https://learnopengl.com/In-Practice/Text-Rendering
    // Some modifications have been made, e.g to render \n characters as line breaks

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(shader);
    glUniform3f(glGetUniformLocation(shader, "textColour"), colour.x, colour.y, colour.z);
    glError("Setting textColour uniform for type: ");
    glUniform1i(glGetUniformLocation(shader, "glyph"), 0);
    glError("Setting texture id uniform for type: ");
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    float initalX = x;

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++){
        Glyph ch = type[*c];

        // quick and dirty line break
        if (*c == '\n'){
          y -= 32.0f;
          x = initalX;
          continue;
        }

        float xpos = x + ch.bearing.x * scale;
        float ypos = y - (ch.size.y - ch.bearing.y) * scale;

        float w = ch.size.x * scale;
        float h = ch.size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glError("Setting data for Glyph texture " + std::to_string(*c) + " :");
        glBufferStatus("Setting data for Glyph texture "+ std::to_string(*c) + " :");
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.offset >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
