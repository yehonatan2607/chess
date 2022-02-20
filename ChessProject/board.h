#pragma once
#include <iostream>
#include <array>
#include <cctype>
#include <fstream>

#include "piece.h"
#include "rook.h"
#include "bishop.h"
#include "king.h"
#include "pawn.h"
#include "queen.h"
#include "knight.h"

const static short SideLength = 8;

class Board
{
public:  // public constants
	const static short PawnRow = 1;
	// indexes:
	const static short SrcNumber = 1;
	const static short SrcLetter = 0;
	const static short DstNumber = 3;
	const static short DstLetter = 2;
	const static char WhiteTurn = 'b';
	const static char BlackTurn = 'W';
private:
	// result codes enum:
	enum { ValidMove, CausedEnemyCheck, SrcHasEmptyOrEnemy, DstHasAlly, CanCauseSelfCheck, OutOfBonds, InvalidPieceMove, DstEqualsSrc };
	// private fields:
	std::array<std::array<Piece*, SideLength>, SideLength> _pieces;
	char _current_turn;
	static Piece* GetObjectByType(const char type);
	void Move(const std::string& move_choice);
	void Eat(const std::string& move_choice, Piece*& save);
protected:
	void PassTurn();
	void Reset();
	bool IsAllyPiece(const Piece* target) const;
	bool FoundCheck(bool self_mode, Piece* eaten_piece);
	std::string FindLocation(const char search_tag) const;
public:
	Board();
	Board(const std::string& path);
	~Board();
	void PrintBoard() const;
	char get_current_turn() const;
	int CheckMove(const std::string& move_choice);
	std::string GenerateString() const;
	static std::string GetLocationChoice();
	static std::string TranslateCode(int code);
	void Load(const std::string& move_choice);
	void Save() const;
};

// working with a char 2D array is much better - WAY easier to implement, cheaper on memory
// Board is the object who manages most things in the code
// also - beside the code tidines there is no real reason to use a Piece 2D array
