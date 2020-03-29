#include <injector_engine.h>

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

// =======================================================================
//
//    NO SECURITY GUARANTEE -- DO NOT USE THIS ON UNTRUSTED FONT FILES
//
// This library does no range checking of the offsets found in the file,
// meaning an attacker can use it to read arbitrary memory.
//
// =======================================================================

namespace Injector
{
	Font::Font(const std::string& filePath, float pixelHeight)
	{
		auto data = ReadBytesFromFile(filePath);
		unsigned char bitmap[512 * 512];
		stbtt_bakedchar charData[96];
		stbtt_BakeFontBitmap(&data[0], 0, pixelHeight, bitmap, 512, 512, 32, 96, charData);
	}
	Font::~Font()
	{

	}
}
