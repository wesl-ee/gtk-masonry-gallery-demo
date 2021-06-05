#ifndef MASON_IMAGEBRICK_H
#define MASON_IMAGEBRICK_H

#include <filesystem>
#include <gtkmm/image.h>
#include <gdkmm/pixbuf.h>

class ImageBrick {
public:
	ImageBrick();
	Gtk::Image *Widget();
	void FromFile(std::filesystem::path file);
	void ConstrainSize(uint32_t w, uint32_t h);
	void UnconstrainSize();
private:
	Glib::RefPtr<Gdk::Pixbuf> imageData;
	Gtk::Image widget;
	uint32_t width, height;
};

#endif
