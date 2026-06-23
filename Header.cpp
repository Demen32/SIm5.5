#include "Header.h"

int HEIGHT = 1500;
int WIDTH = 0;
int OFFSET = 0;
int FONTSIZE = 0;


void startRaylib()
{
	//Abfrage für Bildschirmgröße
	

	system("cls");
	cout << "\nAGV SIMULATOR \nTU BERLIN\n\nIndustrielle Informationstechnik - Einfuhrung in die Informationstechnik fur Ingenieur:innen\n";
	
	/*cout << "\nPlease enter window pixel height:\n";
	int h;*/
	/*while (true) {
		if (std::cin >> h && h > 0) {
			HEIGHT = h;
			break;
		}
		std::cout << "Ungueltig. Bitte eine ganze Zahl > 0 eingeben: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}*/

	InitWindow(WIDTH, HEIGHT, "AGV SIMULATOR");

	int m = GetCurrentMonitor();
	int monW = GetMonitorWidth(m);
	int monH = GetMonitorHeight(m);          

	
	HEIGHT = (int)std::lround(monH * 0.90);
	WIDTH = (int)std::lround(HEIGHT * 1.8);

	// Falls Breite zu groß
	int maxW = (int)std::lround(monW * 0.95);
	if (WIDTH > maxW) {
		WIDTH = maxW;
		HEIGHT = (int)std::lround(WIDTH / 1.6);
	}

	OFFSET = WIDTH / 20;
	FONTSIZE = (int)std::lround(OFFSET / 2.5);

	SetWindowSize(WIDTH, HEIGHT);            
	SetWindowPosition((monW - WIDTH) / 2, (monH - HEIGHT) / 2);
	
	 /* WIDTH = HEIGHT * 1.4;
	  OFFSET = WIDTH / 20;
	  FONTSIZE = OFFSET / 2.5;*/

	
}
