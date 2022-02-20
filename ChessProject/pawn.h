#pragma once
#include <iostream>
#include <cctype>
#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(const char tag);
	~Pawn();
	bool CheckValidity(const std::string& move_choice) const;
	bool CheckPath(const std::array<std::array<Piece*, 8>, 8>& board, const std::string& move_choice) const;


	bool _first_turn;
};

//
//    O
//   o.o
//    P
//
// if (_first_turn == true): | if (<WANTS TO GO ONE OR TWO STEPS FORWARD>): return true
//                           \-> if (<WANTS TO GO DIAGONAL AND DIAGS NOT EMPTY>): return true