#ifndef MASON_MASONROW_H
#define MASON_MASONROW_H

#include <cmath>
#include <iostream>
#include <gtkmm/grid.h>
#include "AtomicQ.h"
#include "ImageBrick.h"

class MasonRow : public Gtk::Grid {
public:
	MasonRow();
	void Draw();
	bool Append(ImageBrickData *i);
	void ClampHeight(unsigned h);
	void ExpandToFillWidth();
	void SetMaxWidth(unsigned w);
	bool Has(ImageBrick*);
private:
	bool dirty;
	std::vector<ImageBrick*> content;
	unsigned currWidth, clampHeight, clampWidth;
	AtomicQ<ImageBrickData*> toAdd;
};

#endif
