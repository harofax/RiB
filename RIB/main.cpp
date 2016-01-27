#include "main.hpp"

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

Engine engine(110, 80);

int main() {
	while (!TCODConsole::isWindowClosed()) {
		engine.update();
		engine.render();
		TCODConsole::flush();
	}
	return 0;
}