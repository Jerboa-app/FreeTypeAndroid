#ifndef TYPE_H
#define TYPE_H

#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>
#include <string>
#include <Text/glyph.h>

typedef std::map<char,Glyph> GlyphMap;

class Type {
public:
  Type(
    std::string path,
    std::string font,
    uint8_t w,
    AAssetManager * assets
  );

  Glyph & operator[](char c);
private:
  GlyphMap glyphs;
  uint8_t width;
  std::string name;
};

#endif
