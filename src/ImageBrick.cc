#include "ImageBrick.h"

ImageBrick::ImageBrick() {
	maxWidth = 0;
	maxHeight = 0;
}

ImageBrick::~ImageBrick() {
}

void ImageBrick::calculateDimsFromConstraints() {
	width = height = 0;

	if (maxHeight and maxWidth) {
		// TODO
	} else if (maxHeight) {
		height = maxHeight;
		width = srcWidth * ((double)height / (double)srcHeight);
	} else if (maxWidth) {
		width = maxWidth;
		height = srcHeight * ((double)width / (double)srcWidth);
	} else {
		height = srcHeight;
		width = srcWidth;
	}
}

bool ImageBrick::isVertical() {
	return aspectRatio < 1;
}

bool ImageBrick::isHorizontal() {
	return aspectRatio > 1;
}

bool ImageBrick::isSquare() {
	return aspectRatio == 1;
}

unsigned ImageBrick::Height() {
	return height;
}

unsigned ImageBrick::Width() {
	return width;
}

void ImageBrick::FromPixbuf(Glib::RefPtr<Gdk::Pixbuf> data) {
	srcImageData = data;

	srcWidth = srcImageData->get_width();
	srcHeight = srcImageData->get_height();
	aspectRatio = (double)srcWidth / (double)srcHeight;

	calculateDimsFromConstraints();
	renderImage();
}

void ImageBrick::FromFile(std::filesystem::path file) {
	srcFile = file;
	std::cout << file << std::endl;
	srcImageData = Gdk::Pixbuf::create_from_file(file);

	srcWidth = srcImageData->get_width();
	srcHeight = srcImageData->get_height();
	aspectRatio = (double)srcWidth / (double)srcHeight;

	calculateDimsFromConstraints();
	renderImage();
}

void ImageBrick::renderImage() {
	renderImageData = srcImageData->scale_simple(width, height,
		Gdk::InterpType::INTERP_BILINEAR);
	set(renderImageData);
	show();
}

unsigned ImageBrick::ConstrainHeight(unsigned h) {
	maxHeight = h;
	maxWidth = 0;

	calculateDimsFromConstraints();

	if (srcImageData) {
		renderImage();
	}

	return width;
}

unsigned ImageBrick::ConstrainWidth(unsigned w) {
	maxWidth = w;
	maxHeight = 0;

	calculateDimsFromConstraints();

	if (srcImageData) {
		renderImage();
	}

	return height;
}

void ImageBrick::UnconstrainSize() {
	maxWidth = 0;
	maxHeight = 0;
}
