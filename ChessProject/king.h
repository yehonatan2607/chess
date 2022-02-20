#pragma once
#include "piece.h"

class King : public Piece
{
public:
    King(const char tag);
    ~King();
	
	bool CheckValidity(const std::string& move_choice) const;
	bool CheckPath(const std::array<std::array<Piece*, 8>, 8>& board, const std::string& move_choice) const;
};