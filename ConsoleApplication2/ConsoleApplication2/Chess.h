#pragma once
//#define DEBUG

// Лабораторная работа №2

enum FIGURECOLOR {
	white, black
};

enum FIGURETYPE {
	empty = 0, pawn, horse, bishop, king, rook, queen
};

struct figurePosition {
	char xPos;
	char yPos;
};

class TFigure {
protected:
	figurePosition position;
public:
	TFigure(FIGURECOLOR color, char letter, char number);
	void show();
	virtual void mapStep() {}
	virtual void Situation() {}
	virtual ~TFigure();
};

class TBoard {
private:
	static TBoard* instancePtr;
	figurePosition figuresMap[128];
	char mapPtr = 0;
	bool mapAct = true;
	TBoard() {}
public:
	FIGURETYPE chessboard[8][8] = {empty, empty, empty, empty, empty, empty, empty, empty,
									empty, empty, empty, empty, empty, empty, empty, empty, 
									empty, empty, empty, empty, empty, empty, empty, empty, 
									empty, empty, empty, empty, empty, empty, empty, empty, 
									empty, empty, empty, empty, empty, empty, empty, empty, 
									empty, empty, empty, empty, empty, empty, empty, empty, 
									empty, empty, empty, empty, empty, empty, empty, empty, 
									empty, empty, empty, empty, empty, empty, empty, empty};
	char bking = 0;
	char wking = 0;
	char bqueen = 0;
	char bbishop = 0;
	char bhorse = 0;
	char brook = 0;
	char bpawn = 0;
	TBoard(const TBoard& obj) = delete;
	static TBoard* getInstance();
	void show();
	bool add(int x, int y);
	bool checkCell(int x, int y);
	bool checkHit(int x, int y);
	void reloadMap();
	bool set(FIGURETYPE type, FIGURECOLOR color, char letter, char number);
};

class TKing : public TFigure {
public:
	TKing(FIGURECOLOR color, char letter, char number);
	void mapStep();
	void Situation();
	~TKing();
};

class TQueen : public TFigure {
public:
	TQueen(FIGURECOLOR color, char letter, char number);
	void mapStep();
	void Situation();
	~TQueen();
};

class TPawn : public TFigure {
public:
	TPawn(FIGURECOLOR color, char letter, char number);
	void mapStep();
	void Situation();
	~TPawn();
};

class THorse : public TFigure {
public:
	THorse(FIGURECOLOR color, char letter, char number);
	void mapStep();
	void Situation();
	~THorse();
};

class TBishop : public TFigure {
public:
	TBishop(FIGURECOLOR color, char letter, char number);
	void mapStep();
	void Situation();
	~TBishop();
};

class TRook : public TFigure {
public:
	TRook(FIGURECOLOR color, char letter, char number);
	void mapStep();
	void Situation();
	~TRook();
};