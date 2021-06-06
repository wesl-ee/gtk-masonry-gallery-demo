#ifndef MASON_MASONLAYOUT_H
#define MASON_MASONLAYOUT_H

#include <filesystem>
#include <vector>
#include <glibmm/dispatcher.h>
#include <gtkmm/container.h>
#include <gtkmm/grid.h>
#include "MasonRow.h"
#include "ImageBrick.h"

typedef struct ImageData {
public:
	Glib::RefPtr<Gdk::Pixbuf> Image;
	bool Added;
} ImageData;

typedef struct LoadedImages {
public:
	std::vector<ImageData> Images;
	mutable std::mutex Lock;
} LoadedImages;

class MasonLayout : public Gtk::Grid {
public:
	MasonLayout();
	void Add(ImageData &data);
	void LoadDirectory(std::filesystem::path d);
	void Load(std::filesystem::path f);
	void RemoveAll();
private:
	void onImageLoaded();

	std::map<std::filesystem::path, bool> galleryFiles;
	std::vector<MasonRow> rows;
	MasonRow *nextRow;
	LoadedImages loaded;
	Glib::Dispatcher dispatcher;

	void newRow();
};

#endif
