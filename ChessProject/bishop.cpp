#include "bishop.h"



Bishop::Bishop(const char tag) : Piece(tag)
{

}

Bishop::~Bishop()
{

}

bool Bishop::CheckValidity(const std::string& move_choice) const
{
	int deltaX = abs((move_choice[2]  - 'a') - (move_choice[0]  - 'a'));

	int deltaY = abs((move_choice[3] - '1') - (move_choice[1] - '1'));

	if (deltaX == deltaY)
	{
		return true;
	}
	return false;
}

bool Bishop::CheckPath(const std::array<std::array<Piece*, 8>, 8>& board, const std::string& move_choice) const 
{
	//we have 4 different cases, if the bishop is in the middle on a 9x9 board, we need to check the most accurate corner

	// each corner can be one of the diagonal sequence, we have to check that
	//		 a b c
	//	  1 |X| |X|
	//    2 | |B| |
	//	  3 |X| |X|
	int src_letter = 0;//a-97
	int dst_letter = 0;
	int src_number = 0;
	int dst_number = 0;
	int i = 0;

	src_letter = (int)move_choice[0] - 'a';  // turning the letters into indexes on board
	dst_letter = (int)move_choice[2] - 'a';
	src_number = (int)move_choice[1] - '1';
	dst_number = (int)move_choice[3] - '1';
	//src_number = 7 - src_number;
	/*src_letter = 7 - src_letter;*/
	//dst_number = 7 - dst_number;
	/*dst_letter = 7 - dst_letter;*/

	if(dst_letter > src_letter)// bottom and top right corners (in general moving right)
	{
		if (dst_number > src_number)  // bottom right corner
		{
			for(i = 1; i < dst_number - src_number; i++)
			{
				if(board.at(i + src_number).at(i + src_letter)!=nullptr)  // moving in a diaognal direction to the bottom right corner
				{
					return false;
				}
			}
		}
		else  // top right corner
		{
			for (i = 1; i < dst_number - src_number; i++)
			{
				if (board.at(src_number - i).at(src_letter + i) != nullptr)  // moving in a diaognal direction to the top right corner
				{
					return false;
				}
			}
		}
	}
	else  // bottom and top left corners
	{
		if(move_choice[3] > move_choice[1])//bottom left corner
		{
			for(i = 1; i < dst_number - src_number; i++)
			{
				if(board.at(src_number + i).at(src_letter - i)!=nullptr)//moving in a diaognal direction to the bottom left corner
				{
					return false;
				}
			}
		}
		else //top left corner
		{
			for (i = 1; i < dst_number - src_number; i++)
			{
				if(board.at(src_number - i).at(src_letter - i) != nullptr)//moving in a diaognal direction to the top left corner
				{
					return false;
				}
			}
		}
	}
	return true;
}
