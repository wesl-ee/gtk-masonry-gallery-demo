#include "MainWindow.h"

MainWindow::MainWindow() {
	set_title("Mason Gallery");
	set_border_width(10);

	set_default_size(defaultHeight, defaultWidth);
	image.ConstrainSize(defaultHeight, defaultWidth);

	add(*image.Widget());
	show_all_children();
}

void MainWindow::Display(std::filesystem::path p) {
	image.FromFile(p);
}
