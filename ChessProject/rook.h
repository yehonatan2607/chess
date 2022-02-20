#pragma once
#include <iostream>
#include "Piece.h"
#include <string.h>
#include <string>

class Rook : public Piece
{
public:
	Rook(const char tag);
	~Rook();
	bool CheckValidity(const std::string& move_choice) const;
	bool CheckPath(const std::array<std::array<Piece*, 8>, 8>& board, const std::string& move_choice) const;
};
