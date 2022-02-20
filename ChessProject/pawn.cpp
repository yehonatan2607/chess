#include "pawn.h"

Pawn::Pawn(const char tag) : Piece(tag)
{

}

Pawn::~Pawn()
{

}

bool Pawn::CheckValidity(const std::string& move_choice) const
{
	return true;
}

bool Pawn::CheckPath(const std::array<std::array<Piece*, 8>, 8>& board, const std::string& move_choice) const
{
	int src_letter = (int)move_choice[0] - 'a';  // turning the letters into indexes on board
	int dst_letter = (int)move_choice[2] - 'a';
	int src_number = (int)move_choice[1] - '1';
	int dst_number = (int)move_choice[3] - '1';
	bool is_on_pawn_line = false;
	//a1a3 a1->a3
	int adder = 1;//in case its black turn, we need to add location in a positive way
	int adder2 = 1;
	if (islower(this->_tag))  // = white turn
	{
		adder = -1;  // we need to add location in a negative way (if the piece moves against the positive direction)
		adder2 = -1;
	}
	if (isupper(this->_tag) && move_choice[1] < move_choice[3] || islower(this->_tag) && move_choice[3] < move_choice[1])  // checking if the piece needs to walk up or down the board to be considered as valid
	{
		adder *= 2;
		if(move_choice[0] == move_choice[2] && move_choice[1] + adder == move_choice[3])// if the col is the same, and we want to step twice(from row 1 to row 3 for example)
		{
			if (islower(this->_tag) && src_number == 6)
			{
				is_on_pawn_line = true;
			}
			else if (isupper(this->_tag) && src_number == 1)//
			{
				is_on_pawn_line = true;
			}
			if (is_on_pawn_line && board[dst_number][src_letter] == nullptr)  // if the pawn is on its first turn and the path isn't blocked 
			{
				return true;
			}
			return false;
		}
		else if ((move_choice[2] + adder2 == move_choice[0] || move_choice[2] - adder2 == move_choice[0]) && move_choice[1] + adder2 == move_choice[3] && board[dst_number][dst_letter] != nullptr)  // moving diagonaly
		{
			return true;
		}
		else if (move_choice[1] + adder2 == move_choice[3] && move_choice[0] == move_choice[2] && board[dst_number][dst_letter] == nullptr)  // step once
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
		return false;
	}
	//return true;
}