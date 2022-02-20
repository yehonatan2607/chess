#include "knight.h"

Knight::Knight(const char tag) : Piece(tag)
{

}


Knight::~Knight()
{

}

bool Knight::CheckPath(const std::array<std::array<Piece*, 8>, 8>& board, const std::string& move_choice) const
{
	return true;  // knight can jump above other ally \ enemy pieces
}

bool Knight::CheckValidity(const std::string& move_choice) const
{
	const short StepTwice = 2;
	const short StepOnce = 1;
	int src_letter = (int)move_choice[0] - 'a';  // turning the letters into indexes on board
	int dst_letter = (int)move_choice[2] - 'a';
	int src_number = (int)move_choice[1] - '1';
	int dst_number = (int)move_choice[3] - '1';

	// vertically case
	if (dst_number + StepTwice == src_number || dst_number - StepTwice == src_number)  // in case we want to move firstly twice forwards \ twice backwards
	{
		if (dst_letter + StepOnce == src_letter || dst_letter - StepOnce == src_letter)  // then once forwards and once backwards horizontally
		{
			return true; 
		}
		else
		{
			return false;
		}
		
	}
	else if (dst_letter + StepTwice == src_letter || dst_letter - StepTwice == src_letter) //in case we want to move firstly twice to the right / twice to the left
	{
		if(dst_number + StepOnce == src_number || dst_number - StepOnce == src_number)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;  // didn't pass no check
	}
}

//    a   b   c   d   e
// 1 |   | X  <->  X |   |
// 2 | X |   | I |   | X |
// 3 | | - - | K | - - | |
// 4 | X |   | I |   | X |
// 5 |   | X  <->  X |   |