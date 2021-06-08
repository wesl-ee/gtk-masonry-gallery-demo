#ifndef MASON_MASONLAYOUT_H
#define MASON_MASONLAYOUT_H

#include <filesystem>
#include <vector>
#include <thread>
#include <glibmm/dispatcher.h>
#include <gtkmm/container.h>
#include <gtkmm/grid.h>
#include "AtomicQ.h"
#include "MasonRow.h"
#include "ImageBrick.h"

class MasonLayout : public Gtk::Grid {
public:
	MasonLayout();
	void Add(ImageBrickData *data);
	void LoadDirectory(std::filesystem::path d);
	void LazyLoadDirectory(std::filesystem::path d);
	void Load(std::filesystem::path f);
	void RemoveAll();
	void ClampWidth(unsigned w);
	unsigned ClampWidth();
private:
	void onImagePendingDraw();
	void resizeRows();

	unsigned clampHeight, clampWidth, lastWidth, lastHeight;
	std::map<std::filesystem::path, bool> galleryFiles;
	std::vector<MasonRow> rows;
	std::vector<ImageBrick*> displayed;
	Glib::Dispatcher dispatcher;
	AtomicQ<std::size_t> updated;

	std::thread *loadThread;
	std::thread *resizeThread;

	void newRow();
};

#endif
