#ifndef MASON_MASONROW_H
#define MASON_MASONROW_H

#include <cmath>
#include <iostream>
#include <gtkmm/grid.h>
#include "ImageBrick.h"

class MasonRow : public Gtk::Grid {
public:
	MasonRow();
	bool Append(ImageBrick *i);
	bool WouldOverflow(ImageBrick *i);
	void ClampHeight(unsigned h);
	void ExpandToFillWidth();
	void SetMaxWidth(unsigned w);
private:
	std::vector<ImageBrick*> content;
	unsigned currWidth;
	unsigned clampHeight;
	unsigned clampWidth;
};

#endif
