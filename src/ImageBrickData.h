#ifndef MASON_IMAGEBRICKDATA_H
#define MASON_IMAGEBRICKDATA_H

#include <cmath>
#include <filesystem>
#include <gdkmm/pixbuf.h>

class ImageBrickData {
public:
	ImageBrickData();
	void FromFile(std::filesystem::path p);
	void RenderSrc();
	unsigned ScaledWidth(unsigned h);
	unsigned ScaledHeight(unsigned w);
	unsigned ScaledWidth();
	unsigned ScaledHeight();
	Glib::RefPtr<Gdk::Pixbuf> Rendered();
	unsigned ConstrainHeight(unsigned h);
	unsigned ConstrainWidth(unsigned w);
private:
	Glib::RefPtr<Gdk::Pixbuf> src;
	Glib::RefPtr<Gdk::Pixbuf> rendered;
	unsigned renderW, renderH;
	double aspectRatio;
};

#endif
