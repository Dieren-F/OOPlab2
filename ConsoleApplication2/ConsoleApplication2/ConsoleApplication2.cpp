#include <iostream>
#include <stdexcept>
#include "Chess.h"


int main()
{
	FILE* inputFile;
	fopen_s(&inputFile, "input.txt", "r");
	if (inputFile == NULL) {
		printf("Не удалось открыть файл input.txt\n");
		return 1;
	}

	char note[5];
	int i = 0;
	TFigure* figures[32];
	while (fgets(note, sizeof(note), inputFile) != NULL) {
		note[3] = '\0';
		try {
			switch (note[0]) {
			case 'e':
				figures[i] = new TPawn(black, note[1], note[2] - 48);
#ifdef DEBUG
				std::cout << "pawn" << std::endl;
#endif
				break;
			case 'R':
				figures[i] = new TRook(black, note[1], note[2] - 48);
#ifdef DEBUG
				std::cout << "rook" << std::endl;
#endif
				break;
			case 'N':
				figures[i] = new THorse(black, note[1], note[2] - 48);
#ifdef DEBUG
				std::cout << "knight" << std::endl;
#endif
				break;
			case 'B':
				figures[i] = new TBishop(black, note[1], note[2] - 48);
#ifdef DEBUG
				std::cout << "bishop" << std::endl;
#endif
				break;
			case 'Q':
				figures[i] = new TQueen(black, note[1], note[2] - 48);
#ifdef DEBUG
				std::cout << "queen" << std::endl;
#endif
				break;
			case 'K':
				figures[i] = new TKing(black, note[1], note[2] - 48);
#ifdef DEBUG
				std::cout << "king" << std::endl;
#endif
				break;
			default:
				std::cout << "Figure doesn't exist" << std::endl;
				i--;
			}
		}
		catch (const std::exception& e) {
			std::cout << "line " << note << " error: ";
			std::cout << e.what() << std::endl;
			i--;
		}
		i++;
	}

	fclose(inputFile);
	//setlocale(LC_ALL, "Russian");
	//std::cout.imbue(std::locale(""));
	//std::cout.sync_with_stdio(false);
	//TKing bKing(black, 'h', 5);
	//THorse bHorse1(black, 'c', 5);
	//TPawn bPawn1(black, 'c', 3);
	//TRook bRook1(black, 'h', 2);
	//TKing bKing2(black, 'a', 1);	// эта строчка работать не должна, потому что двух
	// одинаковых королей быть не может
	//THorse bHorse2(black, ’с’, 2);	// эта строчка работать не должна, потому что клетка
	// с2 уже занята
	//THorse bHorse3(black, ’z’, 20);	// эта строчка работать не должна из-за 
	// неправильных координат

	/*
	figures[0] = &bKing;
	figures[1] = &bHorse1;
	figures[2] = &bPawn1;
	figures[3] = &bRook1;
	*/

	for (int j = 0; j < i; j++) figures[j]->mapStep();

	std::cout << "e - pawn\nR - rook\nN - knight\nB - bishop\nQ - queen\nK - king" << std::endl;

	figures[0]->show();
	std::cout << "Enter the position of the white king (leter and a number): ";
	fgets(note, sizeof(note), stdin);
	note[2] = '\0';
	try {
		TKing wKing(white, note[0], note[1] - 48);
		wKing.show();
		wKing.Situation();
	}
	catch (const std::exception& e) {
		std::cout << "line " << note << " error: ";
		std::cout << e.what() << std::endl;
	}


	return 0;
}
