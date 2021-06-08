#include "MasonRow.h"

MasonRow::MasonRow() :
dirty{false},
currWidth{0},
clampHeight{250},
clampWidth{1500}
{
}

void MasonRow::SetMaxWidth(unsigned w) {
	clampWidth = w;
}

void MasonRow::ExpandToFillWidth() {
	dirty = true;
	double ratio = clampWidth / (double)currWidth;
	for (auto &i : content)
		i->ConstrainWidth(std::floor(i->ScaledWidth() * ratio));
}

void MasonRow::Draw() {
	if (dirty)
		for (auto &i : content)
			i->Draw();
	toAdd.Clear([&](ImageBrickData *i) {
		auto brick = Gtk::manage(new ImageBrick(i));
		content.push_back(brick);
		brick->Draw();
		add(*brick);
		show();
	});
}

bool MasonRow::Append(ImageBrickData *i) {
	auto w = i->ScaledWidth(clampHeight);
	if (currWidth + w > clampWidth)
		return false;

	i->ConstrainWidth(w);
	toAdd.Push(i);
	currWidth += w;

	return true;
}

void MasonRow::ClampHeight(unsigned h) {
	clampHeight = h;
}
