#ifndef MASON_IMAGEBRICK_H
#define MASON_IMAGEBRICK_H

#include <iostream>
#include <filesystem>
#include <gtkmm/image.h>
#include <gdkmm/pixbuf.h>

class ImageBrick : public Gtk::Image {
public:
	ImageBrick();
	~ImageBrick();
	void FromFile(std::filesystem::path file);
	void FromPixbuf(Glib::RefPtr<Gdk::Pixbuf>);
	unsigned ConstrainHeight(unsigned h);
	unsigned ConstrainWidth(unsigned w);
	void UnconstrainSize();
	unsigned Width();
	unsigned Height();
	void Draw();
private:
	bool isVertical();
	bool isHorizontal();
	bool isSquare();
	void calculateDimsFromConstraints();
	std::filesystem::path srcFile;
	Glib::RefPtr<Gdk::Pixbuf> srcImageData;
	Glib::RefPtr<Gdk::Pixbuf> renderImageData;
	uint32_t maxWidth, maxHeight, srcWidth, srcHeight, width, height;
	double aspectRatio;
	static const uint32_t defaultWidth = 300;
	static const uint32_t defaultHeight = 300;
};

#endif
