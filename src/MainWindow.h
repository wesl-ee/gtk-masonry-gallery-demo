#ifndef MASON_MAINWINDOW_H
#define MASON_MAINWINDOW_H

#include <filesystem>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include "ImageBrick.h"

class MainWindow : public Gtk::Window {
public:
	MainWindow();
	void Display(std::filesystem::path p);
private:
	const uint32_t defaultHeight = 500;
	const uint32_t defaultWidth = 500;

	ImageBrick image;
	std::filesystem::path singleImagePath;
};

#endif
