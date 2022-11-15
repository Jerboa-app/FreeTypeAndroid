#ifndef TYPEUTILS_H
#define TYPEUTILS_H

#include <glUtils.h>
#include <Text/type.h>
#include <iostream>

void loadASCIIGlyphs(const FT_Face & face, GlyphMap & g){
  // have a look at this https://learnopengl.com/In-Practice/Text-Rendering
  // Some modifications have been made, e.g to render \n characters as line breaks

  for (unsigned char c = 0; c < 128; c++/*ayy lmao*/){
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)){
      continue;
    }
    GLuint tex;
    glGenTextures(1,&tex);
    glBindTexture(GL_TEXTURE_2D,tex);
    glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_R8,
      face->glyph->bitmap.width,
      face->glyph->bitmap.rows,
      0,
      GL_RED,
      GL_UNSIGNED_BYTE,
      face->glyph->bitmap.buffer
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    Glyph glyph(
      tex,
      glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
      glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
      face->glyph->advance.x
    );
    glError("Loading Glyph: "+std::to_string(c)+" :");
    g.insert(std::pair<char, Glyph>(c,glyph));
  }
}

// forces the number x to be rendered in exactly length characters as a string
std::string fixedLengthNumber(double x, unsigned length){
  std::string d = std::to_string(x);
  std::string dtrunc(length,' ');
  for (int c = 0; c < dtrunc.length(); c++){
    dtrunc[c] = d[c];
  }
  return dtrunc;
}

#endif
