#include "main.h"

int main(int argc, char **argv) {
	int argc1;
	std::filesystem::path image;

	if (argc > 1) {
		image = argv[1];
		if (!std::filesystem::exists(image)) {
			std::cerr << "File does not exist!" << std::endl;
			return 1;
		}
	} else {
		std::cerr << "Must provide a file path!" << std::endl;
		return 1;
	}

	argc1 = 1;
	auto app = Gtk::Application::create(argc1, argv, "org.gtk-mason-gallery-demo");

	MainWindow main;
	main.Display(image);
	return app->run(main);
}
