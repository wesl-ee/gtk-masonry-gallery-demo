#include "MasonRow.h"

MasonRow::MasonRow() {
	clampWidth = 1500;
	clampHeight = 250;
	currWidth = 0;
}

void MasonRow::SetMaxWidth(unsigned w) {
	unsigned oldW = clampWidth;
	clampWidth = w;
	if (oldW != w) {
		// TODO Resize
	}
}

void MasonRow::ExpandToFillWidth() {
	double ratio = clampWidth / (double)currWidth;
	for (auto &i : content) {
		i->ConstrainWidth(round(i->Width() * ratio));
		i->Draw();
	}
}

bool MasonRow::Append(ImageBrick *i) {
	auto w = i->ConstrainHeight(clampHeight);
	if (currWidth + w > clampWidth)
		return false;
	content.push_back(i);
	currWidth += w;
	add(*i);
	i->Draw();
	show();
	return true;
}

void MasonRow::ClampHeight(unsigned h) {
	clampHeight = h;
}

bool MasonRow::WouldOverflow(ImageBrick *i) {
	return currWidth + i->get_width() > clampWidth;
}
