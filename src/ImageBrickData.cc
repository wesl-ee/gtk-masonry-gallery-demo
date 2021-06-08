#include "ImageBrickData.h"

ImageBrickData::ImageBrickData() :
renderW{0},
renderH{0}
{
}

void ImageBrickData::RenderSrc() {
	rendered = src->scale_simple(renderW, renderH, Gdk::InterpType::INTERP_BILINEAR);
}

void ImageBrickData::FromFile(std::filesystem::path p) {
	src = Gdk::Pixbuf::create_from_file(p);
	aspectRatio = src->get_width() / (double)src->get_height();
}

unsigned ImageBrickData::ScaledWidth(unsigned h) {
	return std::round(src->get_width() * (h / (double)src->get_height()));
}

unsigned ImageBrickData::ScaledHeight(unsigned w) {
	return std::round(src->get_height() * (w / (double)src->get_width()));
}

unsigned ImageBrickData::ScaledHeight() {
	return renderH;
}

unsigned ImageBrickData::ScaledWidth() {
	return renderW;
}

unsigned ImageBrickData::ConstrainWidth(unsigned w) {
	renderW = w;
	renderH = ScaledHeight(renderW);

	RenderSrc();
	return renderH;
}

Glib::RefPtr<Gdk::Pixbuf> ImageBrickData::Rendered() {
	return rendered;
}

unsigned ImageBrickData::ConstrainHeight(unsigned h) {
	renderH = h;
	renderW = ScaledWidth(renderH);

	RenderSrc();
	return renderW;
}

