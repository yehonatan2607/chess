#pragma once
#include "piece.h"

class Knight : public Piece
{
public:
	Knight(const char tag);
	~Knight();
	bool CheckPath(const std::array<std::array<Piece*, 8>, 8>& board, const std::string& move_choice) const;
	bool CheckValidity(const std::string& move_choice) const;
};
