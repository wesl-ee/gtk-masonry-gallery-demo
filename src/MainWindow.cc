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

	signal_realize().connect([&, d] {
		masonLayout.ClampWidth(get_width() - 20);
		masonLayout.LoadDirectory(d);
	});

	signal_configure_event().connect([&, d](GdkEventConfigure *event) {
		if ((unsigned)event->width == lastWidth &&
		(unsigned)event->height == lastHeight)
			return false;

		masonLayout.ClampWidth(event->width - 20);
		this->lastWidth = event->width;
		this->lastHeight = event->width;
		return false;
	}, false);
}

MainWindow::~MainWindow() {
}

bool MainWindow::on_configure_changed(GdkEventConfigure *event) {
	lastWidth = event->width;
	lastHeight = event->height;

	return false;
}
