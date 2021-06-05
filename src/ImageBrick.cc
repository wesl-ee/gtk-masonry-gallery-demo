#include "ImageBrick.h"

ImageBrick::ImageBrick() {
	width = 0;
	height = 0;
}

Gtk::Image *ImageBrick::Widget() {
	return &widget;
}

void ImageBrick::FromFile(std::filesystem::path file) {
	if (width or height)
		imageData = Gdk::Pixbuf::create_from_file(file, width, height);
	else
		imageData = Gdk::Pixbuf::create_from_file(file);
	widget.set(imageData);
}

void ImageBrick::ConstrainSize(uint32_t w, uint32_t h) {
	width = w;
	height = h;
}

void ImageBrick::UnconstrainSize() {
	width = 0;
	height = 0;
}
