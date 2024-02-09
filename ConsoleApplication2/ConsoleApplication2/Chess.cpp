#include <iostream>
#include "Chess.h"

TBoard* TBoard::instancePtr = nullptr;
TBoard* TBoard::getInstance() {
		if (instancePtr == nullptr)
		{
			instancePtr = new TBoard();
			return instancePtr;
		}
		else
		{
			return instancePtr;
		}
	}

bool TBoard::set(FIGURETYPE type, FIGURECOLOR color, char letter, char number) {
	int xpos = letter - 97;
	int ypos = number - 1;
	if (xpos > 7 || xpos < 0) return false;
	if (ypos > 7 || ypos < 0) return false;
	if (chessboard[ypos][xpos] != empty) return false;
	if (type == king) {
		if (color == white) {
			if (wking > 0) return false;
			else wking++;
		}
		if (color == black) {
			if (bking > 0) return false;
			else bking++;
		}
	}
	if (type == queen) {
		if (color == black && bqueen > 0) return false;
		else bqueen++;
	}
	if (type == bishop) {
		if (color == black && bbishop > 1) return false;
		else bbishop++;
	}
	if (type == horse) {
		if (color == black && bhorse > 1) return false;
		else bhorse++;
	}
	if (type == rook) {
		if (color == black && brook > 1) return false;
		else brook++;
	}
	if (type == pawn) {
		if (color == black && bpawn > 7) return false;
		else bpawn++;
	}
	chessboard[ypos][xpos] = type;
	return true;
};

void TBoard::show() {
	char names[8] = { ".eNBKRQ" };
	std::cout << "abcdefgh" << std::endl;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			std::cout << names[chessboard[i][j]];
		}
		std::cout << i+1;
		std::cout << std::endl;
	}
}

bool TBoard::add(int x, int y) {
	figurePosition pos = { x, y };
	if (mapAct) {
		for (int i = 0; i < 128; i++) {
			figuresMap[i].xPos = 0;
			figuresMap[i].yPos = 0;
		}
		mapPtr = 0;
		mapAct = false;
	}
	if (pos.xPos < 0 || pos.xPos > 7) return false;
	if (pos.yPos < 0 || pos.yPos > 7) return false;
	figuresMap[mapPtr] = pos;
	mapPtr++;
	if (mapPtr > 127) mapAct = true;
	return true;
}

bool TBoard::checkCell(int x, int y) {
	if (x < 0 || x > 7) return false;
	if (y < 0 || y > 7) return false;
	if (chessboard[y][x] == empty) return true;
	return false;
}

bool TBoard::checkHit(int x, int y) {
	if (x < 0 || x > 7) return true;
	if (y < 0 || y > 7) return true;
	for (int i = 0; i < mapPtr; i++) {
		if (figuresMap[i].xPos == x && figuresMap[i].yPos == y) return true;
	}
	return false;
}

void TBoard::reloadMap() {
	mapAct = true;
}

TFigure::TFigure(FIGURECOLOR color, char letter, char number) {
#ifdef DEBUG
	std::cout << "constructorTFigure" << std::endl;
#endif
}

TFigure::~TFigure() {
#ifdef DEBUG
	std::cout << "destructorTFigure" << std::endl;
#endif
}

TKing::TKing(FIGURECOLOR color, char letter, char number):TFigure(color, letter, number) {
#ifdef DEBUG
	std::cout << "constructorTKing" << std::endl;
#endif
	TBoard* p = TBoard::getInstance();
	if (!p->set(king, color, letter, number)) throw std::logic_error("incorrect placement");
	position.xPos = letter - 97;
	position.yPos = number - 1;
}

void TKing::mapStep() {
	TBoard* p = TBoard::getInstance();
	p->add(position.xPos + 1, position.yPos);
	p->add(position.xPos + 1, position.yPos + 1);
	p->add(position.xPos, position.yPos + 1);
	p->add(position.xPos - 1, position.yPos + 1);
	p->add(position.xPos - 1, position.yPos);
	p->add(position.xPos - 1, position.yPos - 1);
	p->add(position.xPos, position.yPos - 1);
	p->add(position.xPos + 1, position.yPos - 1);
}

void TKing::Situation() {
	TBoard* p = TBoard::getInstance();
	p->reloadMap();
	bool isMove = !p->checkHit(position.xPos + 1, position.yPos) ||
			!p->checkHit(position.xPos + 1, position.yPos + 1) ||
			!p->checkHit(position.xPos, position.yPos + 1) ||
 			!p->checkHit(position.xPos - 1, position.yPos + 1) ||
			!p->checkHit(position.xPos - 1, position.yPos) ||
			!p->checkHit(position.xPos - 1, position.yPos - 1) ||
			!p->checkHit(position.xPos, position.yPos - 1)||
			!p->checkHit(position.xPos + 1, position.yPos - 1);
	bool isHit = p->checkHit(position.xPos, position.yPos);
	if (!isMove && isHit) { std::cout << "Checkmate!" << std::endl; return; }
	if (isMove && isHit) { std::cout << "Check!" << std::endl; return; }
	if (!isMove && !isHit) { std::cout << "Stalemate!" << std::endl; return; }
	std::cout << "The king is fine!" << std::endl;
}

void TFigure::show() {
	TBoard* p = TBoard::getInstance();
	p->show();
}

TKing::~TKing() {
#ifdef DEBUG
	std::cout << "destructorTKing" << std::endl;
#endif
}

TPawn::TPawn(FIGURECOLOR color, char letter, char number) :TFigure(color, letter, number) {
#ifdef DEBUG
	std::cout << "constructorTPawn" << std::endl;
#endif
	TBoard* p = TBoard::getInstance();
	if (!p->set(pawn, color, letter, number)) throw std::logic_error("incorrect placement");
	position.xPos = letter - 97;
	position.yPos = number - 1;
}

void TPawn::mapStep() {
	TBoard* p = TBoard::getInstance();
	p->add(position.xPos + 1, position.yPos - 1);
	p->add(position.xPos - 1, position.yPos - 1);
}

void TPawn::Situation() {}

TQueen::TQueen(FIGURECOLOR color, char letter, char number) :TFigure(color, letter, number) {
#ifdef DEBUG
	std::cout << "constructorTQueen" << std::endl;
#endif
	TBoard* p = TBoard::getInstance();
	if (!p->set(queen, color, letter, number)) throw std::logic_error("incorrect placement");
	position.xPos = letter - 97;
	position.yPos = number - 1;
}

void TQueen::mapStep() {
	TBoard* p = TBoard::getInstance();
	int i = 0;
	do {
		i++;
		if (position.xPos + i > 7) break;
		if (position.yPos + i > 7) break;
		p->add(position.xPos + i, position.yPos + i);
	} while (p->checkCell(position.xPos + i, position.yPos + i));
	i = 0;
	do {
		i++;
		if (position.xPos - i < 0) break;
		if (position.yPos - i < 0) break;
		p->add(position.xPos - i, position.yPos - i);
	} while (p->checkCell(position.xPos - i, position.yPos - i));
	i = 0;
	do {
		i++;
		if (position.xPos - i < 0) break;
		if (position.yPos + i > 7) break;
		p->add(position.xPos - i, position.yPos + i);
	} while (p->checkCell(position.xPos - i, position.yPos + i));
	i = 0;
	do {
		i++;
		if (position.xPos + i > 7) break;
		if (position.yPos - i < 0) break;
		p->add(position.xPos + i, position.yPos - i);
	} while (p->checkCell(position.xPos + i, position.yPos - i));
	i = 0;
	do {
		i++;
		if (position.xPos + i > 7) break;
		p->add(position.xPos + i, position.yPos);
	} while (p->checkCell(position.xPos + i, position.yPos));
	i = 0;
	do {
		i++;
		if (position.xPos - i < 0) break;
		p->add(position.xPos - i, position.yPos);
	} while (p->checkCell(position.xPos - i, position.yPos));
	i = 0;
	do {
		i++;
		if (position.yPos + i > 7) break;
		p->add(position.xPos, position.yPos + i);
	} while (p->checkCell(position.xPos, position.yPos + i));
	i = 0;
	do {
		i++;
		if (position.yPos - i < 0) break;
		p->add(position.xPos, position.yPos - i);
	} while (p->checkCell(position.xPos, position.yPos - i));
}

void TQueen::Situation() {}

TQueen::~TQueen() {
#ifdef DEBUG
	std::cout << "destructorTQueen" << std::endl;
#endif
}

TPawn::~TPawn() {
#ifdef DEBUG
	std::cout << "destructorTPawn" << std::endl;
#endif
}

THorse::THorse(FIGURECOLOR color, char letter, char number) :TFigure(color, letter, number) {
#ifdef DEBUG
	std::cout << "constructorTHorse" << std::endl;
#endif
	TBoard* p = TBoard::getInstance();
	if (!p->set(horse, color, letter, number)) throw std::logic_error("incorrect placement");
	position.xPos = letter - 97;
	position.yPos = number - 1;
}

void THorse::mapStep() {
	TBoard* p = TBoard::getInstance();
	p->add(position.xPos + 1, position.yPos + 2);
	p->add(position.xPos - 1, position.yPos + 2);
	p->add(position.xPos + 2, position.yPos + 1);
	p->add(position.xPos - 2, position.yPos + 1);
	p->add(position.xPos + 1, position.yPos - 2);
	p->add(position.xPos - 1, position.yPos - 2);
	p->add(position.xPos + 2, position.yPos - 1);
	p->add(position.xPos - 2, position.yPos - 1);
}

void THorse::Situation() {}

THorse::~THorse() {
#ifdef DEBUG
	std::cout << "destructorTHorse" << std::endl;
#endif
}

TBishop::TBishop(FIGURECOLOR color, char letter, char number) :TFigure(color, letter, number) {
#ifdef DEBUG
	std::cout << "constructorTBishop" << std::endl;
#endif
	TBoard* p = TBoard::getInstance();
	if (!p->set(bishop, color, letter, number)) throw std::logic_error("incorrect placement");
	position.xPos = letter - 97;
	position.yPos = number - 1;
}

void TBishop::mapStep() {
	TBoard* p = TBoard::getInstance();
	int i = 0;
	do {
		i++;
		if (position.xPos + i > 7) break;
		if (position.yPos + i > 7) break;
		p->add(position.xPos + i, position.yPos + i);
	} while (p->checkCell(position.xPos + i, position.yPos + i));
	i = 0;
	do {
		i++;
		if (position.xPos - i < 0) break;
		if (position.yPos - i < 0) break;
		p->add(position.xPos - i, position.yPos - i);
	} while (p->checkCell(position.xPos - i, position.yPos - i));
	i = 0;
	do {
		i++;
		if (position.xPos - i < 0) break;
		if (position.yPos + i > 7) break;
		p->add(position.xPos - i, position.yPos + i);
	} while (p->checkCell(position.xPos - i, position.yPos + i));
	i = 0;
	do {
		i++;
		if (position.xPos + i > 7) break;
		if (position.yPos - i < 0) break;
		p->add(position.xPos + i, position.yPos - i);
	} while (p->checkCell(position.xPos + i, position.yPos - i));
}

void TBishop::Situation() {}

TBishop::~TBishop() {
#ifdef DEBUG
	std::cout << "destructorTBishop" << std::endl;
#endif
}

TRook::TRook(FIGURECOLOR color, char letter, char number) :TFigure(color, letter, number) {
#ifdef DEBUG
	std::cout << "constructorTRook" << std::endl;
#endif
	TBoard* p = TBoard::getInstance();
	if (!p->set(rook, color, letter, number)) throw std::logic_error("incorrect placement");
	position.xPos = letter - 97;
	position.yPos = number - 1;
}

void TRook::mapStep() {
	TBoard* p = TBoard::getInstance();
	int i = 0;
	do {
		i++;
		if (position.xPos + i > 7) break;
		p->add(position.xPos + i, position.yPos);
	} while (p->checkCell(position.xPos + i, position.yPos));
	i = 0;
	do {
		i++;
		if (position.xPos - i < 0) break;
		p->add(position.xPos - i, position.yPos);
	} while (p->checkCell(position.xPos - i, position.yPos));
	i = 0;
	do {
		i++;
		if (position.yPos + i > 7) break;
		p->add(position.xPos, position.yPos + i);
	} while (p->checkCell(position.xPos, position.yPos + i));
	i = 0;
	do {
		i++;
		if (position.yPos - i < 0) break;
		p->add(position.xPos, position.yPos - i);
	} while (p->checkCell(position.xPos, position.yPos - i));
}

void TRook::Situation() {}

TRook::~TRook() {
#ifdef DEBUG
	std::cout << "destructorTRook" << std::endl;
#endif
}