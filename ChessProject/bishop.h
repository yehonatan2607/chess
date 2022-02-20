#pragma once
#include "piece.h"

class Bishop : public Piece
{
public:
	Bishop(const char tag);
	~Bishop();
	bool CheckValidity(const std::string& move_choice) const;										// to check if the move is valid
	bool CheckPath(const std::array<std::array<Piece*, 8>, 8>& board, const std::string& move_choice) const;//to check if there is no interrupt in the way
};
