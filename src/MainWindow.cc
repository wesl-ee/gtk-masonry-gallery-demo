#include "MainWindow.h"

MainWindow::MainWindow(std::filesystem::path d) {
	imageDirectory = d;

	set_title("Masonry Gallery");
	set_border_width(10);

	set_default_size(defaultHeight, defaultWidth);

	lastWidth = defaultWidth;
	lastHeight = defaultHeight;

	frame.set_label("Masonry Gallery");
	frame.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);

	add(frame);
	frame.add(scrollWindow);
	scrollWindow.add(masonLayout);

	show_all_children();

	masonThread = new std::thread([this, d] {
		this->masonLayout.LoadDirectory(d);
	});
}

MainWindow::~MainWindow() {
}

bool MainWindow::on_configure_changed(GdkEventConfigure *event) {
	lastWidth = event->width;
	lastHeight = event->height;

	return false;
}
