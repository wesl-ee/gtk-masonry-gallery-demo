#include "ImageBrick.h"

ImageBrick::ImageBrick(ImageBrickData *d) :
data{d}
{
}

ImageBrick::~ImageBrick() {
}

unsigned ImageBrick::ConstrainWidth(unsigned w) {
	return data->ConstrainWidth(w);
}

unsigned ImageBrick::ScaledWidth(unsigned h) {
	return data->ScaledWidth(h);
}

unsigned ImageBrick::ScaledWidth() {
	return data->ScaledWidth();
}

void ImageBrick::Draw() {
	set(data->Rendered());
	show();
}

