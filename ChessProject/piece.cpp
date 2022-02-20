#include "piece.h"



/*
A constructor method for the Piece class
Input: void
Output: the type to assign to the Piece
*/
Piece::Piece(const char tag)
{
	this->_tag = tag;
}

/*
A destructor method for the Piece class
Input: void
Output: void
*/
Piece::~Piece()
{
	
}

/*
Returns the Piece's type
Input: void
Output: void
*/
char Piece::get_tag() const
{
	return this->_tag;
}
