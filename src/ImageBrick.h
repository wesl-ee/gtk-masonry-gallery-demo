#ifndef MASON_IMAGEBRICK_H
#define MASON_IMAGEBRICK_H

#include <iostream>
#include <filesystem>
#include <gtkmm/image.h>
#include <gdkmm/pixbuf.h>
#include "ImageBrickData.h"

class ImageBrick : public Gtk::Image {
public:
	ImageBrick(ImageBrickData *d);
	~ImageBrick();
	unsigned ConstrainWidth(unsigned w);
	unsigned ScaledWidth(unsigned h);
	unsigned ScaledWidth();
	void Draw();

private:
	std::filesystem::path srcFile;
	ImageBrickData *data;
	double aspectRatio;
	static const uint32_t defaultWidth = 300;
	static const uint32_t defaultHeight = 300;
};

#endif
