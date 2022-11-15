#include <Text/type.h>
#include <Text/typeUtils.h>

Type::Type(std::string path, std::string font, uint8_t w, AAssetManager * assets){

  width = w;
  name = font;

  __android_log_print(ANDROID_LOG_INFO, "", "FINDING OTF");
  AAsset* fontFile = AAssetManager_open(assets, "fonts/OpenDyslexic-Regular.otf", AASSET_MODE_BUFFER);
  off_t fontDataSize = AAsset_getLength(fontFile);

  __android_log_print(ANDROID_LOG_INFO, "", "OTF LOADED");
  FT_Byte* fontData = new FT_Byte[fontDataSize];
  AAsset_read(fontFile, fontData, (size_t) fontDataSize);
  AAsset_close(fontFile);

  __android_log_print(ANDROID_LOG_INFO, "", "FREETYPE LOADING");
  //construct freetype objects
  FT_Library ftLib;
  if (FT_Init_FreeType(&ftLib)){
    std::cout << "Could not init FreeType\n";
  }
  __android_log_print(ANDROID_LOG_INFO, "", "LIB LOADED");
  FT_Face ftFace;
  if (FT_New_Memory_Face(ftLib, (const FT_Byte*)fontData, (FT_Long)fontDataSize, 0, &ftFace)){
    std::cout << "Could not load font: " + font + " at: " + path + "\n";
  }
  __android_log_print(ANDROID_LOG_INFO, "", "FACE LOADED");

  FT_Set_Pixel_Sizes(ftFace,0,width); //dynamic width for height 48

  glyphs.clear();

  glError("Type constructor: ");

  loadASCIIGlyphs(ftFace,glyphs);

  FT_Done_Face(ftFace);
  FT_Done_FreeType(ftLib);

}

Glyph & Type::operator[](char c){
  return glyphs[c];
}
