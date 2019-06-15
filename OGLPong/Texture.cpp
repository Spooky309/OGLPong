#include "Texture.h"
#include "IO.h"
#include <assert.h>
#include <iostream>
Texture::Texture(const std::string& name) {
	std::string fullPath = SEIO::GetContentPath(name);
	std::string ext = fullPath.substr(fullPath.find_last_of('.'));
	if (ext == ".png") {
		LoadFromPNG(fullPath);
	}
	else if (ext == ".pcx") {
		LoadFromPCX(fullPath);
	}
	else if (ext == ".tga") {
		LoadFromTGA(fullPath);
	}
	else {
		std::cout << "Unsupported TEXTURE Type: ." << ext << "\n";
		return;
	}
	// send the texture to GL and set name
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	
	this->name = name;
	free(data); // don't have to keep this around
}

void Texture::LoadFromPNG(const std::string& fullp) {
	// LibPNG is hard enough on its own
	png_byte header[8];
	std::FILE* fp;
	fopen_s(&fp, fullp.c_str(), "rb");
	if (fp == nullptr)
	{
		std::cout << "Requested PNG file either does not exist or is not accessible.\n";
		std::cout << fullp << "\n";
		return;
	}
	fread(header, 1, 8, fp); // let's read in the header
	// check the header for validity
	if (png_sig_cmp(header, 0, 8))
	{
		std::cout << "Requested texture at " + fullp + " is not a valid PNG file.\n";
	}
	png_struct* png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	if (png_ptr == nullptr)
	{
		std::cout << "weird error: png_create_read_struct returned null\n";
	}
	png_info* info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == nullptr) {
		std::cout << "weird error: png_create_info_struct returned null\n";
	}
	if (setjmp(png_jmpbuf(png_ptr))) {
		std::cout << "weird error of some kind in LibPNG.\n";
	}
	png_init_io(png_ptr, fp);
	png_set_sig_bytes(png_ptr, 8);
	png_read_info(png_ptr, info_ptr);
	width = png_get_image_width(png_ptr, info_ptr);
	height = png_get_image_height(png_ptr, info_ptr);
	int colour_type = png_get_color_type(png_ptr, info_ptr);
	int bit_depth = png_get_bit_depth(png_ptr, info_ptr);
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth,
		&colour_type, nullptr, nullptr, nullptr);
	if (bit_depth == 16) {
#if PNG_LIBPNG_VER >= 10504
		png_set_scale_16(png_ptr);
#else
		png_set_strip_16(png_ptr);
#endif
	}
	if (colour_type == PNG_COLOR_TYPE_PALETTE) {
		png_set_palette_to_rgb(png_ptr);
	}
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
		png_set_tRNS_to_alpha(png_ptr);
	}
	if (colour_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) {
		png_set_expand_gray_1_2_4_to_8(png_ptr);
	}
	if (colour_type == PNG_COLOR_TYPE_RGB) {
		png_set_filler(png_ptr, 0xFF, PNG_FILLER_AFTER);
	}
	png_read_update_info(png_ptr, info_ptr);
	switch (colour_type) {
	case PNG_COLOR_TYPE_RGB:
		format = GL_RGB;
		break;
	case PNG_COLOR_TYPE_RGB_ALPHA: // It should always be this, but check anyway.
		format = GL_RGBA;
		break;
	default:
		std::cout << "png image was an unknown format\n";
		break;
	}
	std::size_t rowbytes = png_get_rowbytes(png_ptr, info_ptr);
	data = (unsigned char*)malloc(height * rowbytes);
	for (std::size_t y = height; y > 0; y--) {
		png_read_row(png_ptr, &data[(y - 1) * rowbytes], nullptr);
	}
	png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
}

void Texture::LoadFromPCX(const std::string & fullp) {
	// i have a headache...
	struct PCXHeader {
		unsigned char Manufacturer;
		unsigned char Version;
		unsigned char Encoding;
		unsigned char BitsPerPixel;
		unsigned short XMin;
		unsigned short YMin;
		unsigned short XMax;
		unsigned short YMax;
		unsigned short HDPI;
		unsigned short VDPI;
		unsigned char ColourMap[48];
		unsigned char Reserved;
		unsigned char NumBitPlanes;
		unsigned short BytesPerLine;
		unsigned short PaletteInfo;
		unsigned short HScreenSize;
		unsigned short VScreenSize;
		unsigned char Reserved2[54];
	};
	PCXHeader headerData;
	format = GL_RGB; // format is always RGB here
	FILE* PCXFile;
	fopen_s(&PCXFile, fullp.c_str(), "rb");
	assert(PCXFile); // crash if file isn't opened? probably not a good idea.
	fread(&headerData, sizeof(PCXHeader), 1, PCXFile); // read in header
	// calculate dimensions
	width = headerData.XMax - headerData.XMin + 1;
	height = headerData.YMax - headerData.YMin + 1;
	// get num compnents (should always be 3 for q2 texts)
	int components = (headerData.BitsPerPixel == 8 && headerData.NumBitPlanes == 4) ? 4 : 3;
	int dataSize = width * height * components;
	// allocate the data array to store the finished image
	data = (unsigned char*)malloc(dataSize);
	unsigned char count = 0;
	unsigned char value;
	int stride = width * components;
	// read in the indices for each component
	for (int y = 0; y < height; y++) {
		unsigned char* row = data + (stride * y);
		for (int x = 0; x < headerData.BytesPerLine; x++) {
			if (count == 0) {
				count = PCXGetRLECount(PCXFile, &value);
			}
			count--;
			if (x < width) {
				row[0] = value;
				row[1] = value;
				row[2] = value;
				row += 3;
			}
		}
	}
	unsigned char palette = PCXReadByte(PCXFile);
	// unpack the indices into their palette equivilants, to build the RGB image
	// for openGL
	if (palette == 0x0C) {
		unsigned char pal[768];
		fread(pal, sizeof(pal), 1, PCXFile);
		for (int y = 0; y < height; y++) {
			unsigned char* row = data + (stride * y);
			for (int x = 0; x < width; x++) {
				unsigned char index = row[0];
				row[0] = pal[index * 3];
				row[1] = pal[index * 3 + 1];
				row[2] = pal[index * 3 + 2];
				row += 3;
			}
		}
	}
}

unsigned char Texture::PCXReadByte(FILE * file)
{
	unsigned char byte;
	fread(&byte, 1, 1, file);
	return byte;
}

unsigned char Texture::PCXGetRLECount(FILE * file, unsigned char* outValue)
{
	unsigned char Count;
	unsigned char Value;
	Value = PCXReadByte(file);
	// 0b11000000 means the low 6 bits determine repeatedness
	if ((Value & 0xC0) == 0xC0)
	{
		// read in the count to repeat, and the byte that needs to be repeated
		Count = Value & 0x3F;
		Value = PCXReadByte(file);
	}
	else
	{
		// we only need to read in once using the current byte if it's not Cx
		Count = 1;
	}

	*outValue = Value;
	return Count;
}

void Texture::LoadFromTGA(const std::string & fullp) {
	// TODO
}

int Texture::GetWidth() const {
	return (int)width;
}

int Texture::GetHeight() const {
	return (int)height;
}

GLint Texture::GetFormat() const {
	return format;
}

GLuint Texture::GetTextureID() const {
	return texID;
}