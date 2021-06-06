#ifndef MASON_MAINWINDOW_H
#define MASON_MAINWINDOW_H

#include <iostream>
#include <filesystem>
#include <cmath>
#include <thread>
#include <mutex>
#include <gtkmm/window.h>
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>
#include <gtkmm/scrolledwindow.h>
#include <glibmm/dispatcher.h>
#include "MasonLayout.h"

class MainWindow : public Gtk::Window {
public:
	MainWindow(std::filesystem::path d);
	~MainWindow();
private:
	uint32_t lastWidth, lastHeight;
	bool on_configure_changed(GdkEventConfigure *event);

	std::filesystem::path imageDirectory;
	MasonLayout masonLayout;
	Gtk::Frame frame;
	Gtk::Grid grid;
	Gtk::ScrolledWindow scrollWindow;

	std::thread *masonThread;

	const uint32_t defaultHeight = 500;
	const uint32_t defaultWidth = 500;
};

#endif
