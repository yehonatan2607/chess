#include "queen.h"

Queen::Queen(const char tag) : Piece(tag)
{
	this->_bishop_mover = new Bishop(tag);
	this->_rook_mover = new Rook(tag);
}

Queen::~Queen()
{
	delete this->_bishop_mover;
	delete this->_rook_mover;
}

bool Queen::CheckPath(const std::array<std::array<Piece*, 8>, 8>& board, const std::string& move_choice) const
{
	if (this->_rook_mover->CheckValidity(move_choice)== false)
	{
		return this->_bishop_mover->CheckPath(board, move_choice);
	}
	else
	{
		return this->_rook_mover->CheckPath(board, move_choice);
	}
}

bool Queen::CheckValidity(const std::string& move_choice) const
{
	return (this->_rook_mover->CheckValidity(move_choice) || this->_bishop_mover->CheckValidity(move_choice));
}
