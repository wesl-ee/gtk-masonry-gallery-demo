#include "MasonLayout.h"

MasonLayout::MasonLayout() :
clampHeight{250},
clampWidth{500},
dispatcher(),
resizeThread{nullptr}
{
	set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
	set_row_spacing(0);
	set_column_spacing(0);

	dispatcher.connect(sigc::mem_fun(*this, &MasonLayout::onImagePendingDraw));

}

void MasonLayout::ClampWidth(unsigned w) {
	// TODO Resize rows
	clampWidth = w;
	// resizeRows();
}

void MasonLayout::onImagePendingDraw() {
	updated.Clear([&](std::size_t i) {
		rows.at(i).Draw();
	});
}

void MasonLayout::Add(ImageBrickData *data) {
	if (!rows.size()) {
		newRow();
	}

	if (!rows.back().Append(data)) {
		rows.back().ExpandToFillWidth();
		updated.Push(rows.size() - 1);

		newRow();
		rows.back().Append(data);
	} else {
		updated.Push(rows.size() - 1);
	}

	dispatcher.emit();
}

unsigned MasonLayout::ClampWidth() {
	return clampWidth;
}

void MasonLayout::resizeRows() {
/*	if (!resizeThread)
		resizeThread = new std::thread([this] {
	});*/
}

void MasonLayout::LazyLoadDirectory(std::filesystem::path d) {
	std::cout << d;
	/* loadThread = new std::thread([this, d] {
	}); */
}

void MasonLayout::LoadDirectory(std::filesystem::path d) {
	loadThread = new std::thread([this, d] {
		for (const auto &f : std::filesystem::directory_iterator(d)) {
			if (std::filesystem::is_directory(f))
				continue;
			this->Load(f);
		}
	});
}

void MasonLayout::Load(std::filesystem::path f) {
	if (galleryFiles[f])
		return; // File already added
	galleryFiles[f] = true;

	Glib::RefPtr<Gdk::Pixbuf> src;
	auto i = new ImageBrickData;

	try {
		i->FromFile(f);
	} catch (Gdk::PixbufError &e) {
		switch(e.code()) {
		case Gdk::PixbufError::CORRUPT_IMAGE:
		case Gdk::PixbufError::INSUFFICIENT_MEMORY:
		case Gdk::PixbufError::BAD_OPTION:
		case Gdk::PixbufError::UNKNOWN_TYPE:
		case Gdk::PixbufError::UNSUPPORTED_OPERATION:
		case Gdk::PixbufError::FAILED:
		case Gdk::PixbufError::INCOMPLETE_ANIMATION:
			return;
		}
	}

	Add(i);
	dispatcher.emit();
}

void MasonLayout::newRow() {
	rows.push_back(MasonRow{});
	add(rows.back());
	rows.back().SetMaxWidth(clampWidth);
}

void MasonLayout::RemoveAll() {
	galleryFiles.clear();
}
