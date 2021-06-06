#include "MasonLayout.h"

MasonLayout::MasonLayout() :
dispatcher()
{
	set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
	set_row_spacing(0);
	set_column_spacing(0);

	dispatcher.connect(sigc::mem_fun(*this, &MasonLayout::onImageLoaded));
}

void MasonLayout::onImageLoaded() {
	std::vector<ImageData> toAdd;
	{
		std::lock_guard<std::mutex> lock(loaded.Lock);
		for (auto &i : loaded.Images) {
			if (i.Added)
				continue;
			toAdd.push_back(i);
			i.Added = true;
		}
	}

	for (auto &i : toAdd) {
		Add(i);
	}
}

void MasonLayout::Add(ImageData &data) {
	auto i = Gtk::manage(new ImageBrick);

	i->FromPixbuf(data.Image);

	if (!rows.size())
		newRow();

	rows.back().SetMaxWidth(get_width() - 2);

	if (!rows.back().Append(i)) {
		nextRow->ExpandToFillWidth();

		newRow();
		nextRow->Append(i);
	}
}

void MasonLayout::LoadDirectory(std::filesystem::path d) {
	for (const auto &f : std::filesystem::directory_iterator(d)) {
		if (std::filesystem::is_directory(f))
			continue;
		Load(f);
	}
}

void MasonLayout::Load(std::filesystem::path f) {
	if (galleryFiles[f])
		return; // File already added
	galleryFiles[f] = true;

	ImageData i;

	try {
		i.Image = Gdk::Pixbuf::create_from_file(f);
		i.Added = false;
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

	{
		std::lock_guard<std::mutex> lock(loaded.Lock);
		loaded.Images.push_back(i);
	}
	dispatcher.emit();
}

void MasonLayout::newRow() {
	rows.push_back(MasonRow{});
	add(rows.back());
	nextRow = &rows.back();
}

void MasonLayout::RemoveAll() {
	galleryFiles.clear();
}
