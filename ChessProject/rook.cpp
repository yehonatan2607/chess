#include "rook.h"





Rook::Rook(const char tag) : Piece(tag)
{
	//nothing
}

Rook::~Rook()
{

}

/*
This function checks if the given position is eligble to move to by the object's moving rules
Input: the location to move to
Output: 
*/
bool Rook::CheckValidity(const std::string& move_choice) const // a1b3  =  a1 -> b3
{
	return (move_choice[0] == move_choice[2] || move_choice[1] == move_choice[3]);  // valid move
}

bool Rook::CheckPath(const std::array<std::array<Piece*, 8>, 8>& board, const std::string& move_choice) const
{
	int src_letter = 0;//a-97
	int dst_letter = 0;
	int src_number = 0;
	int dst_number = 0;
	int temp = 0;

	src_letter = (int)move_choice[0] - 'a';  // turning the letters into indexes on board
	dst_letter = (int)move_choice[2] - 'a';
	src_number = (int)move_choice[1] - '1';
	dst_number = (int)move_choice[3] - '1';
	//src_number = 7 - src_number;
	//src_letter = 7 - src_letter;
	//dst_number = 7 - dst_number;
	//dst_letter = 7 - dst_letter;

	if(move_choice[0] == move_choice[2])// we want to move vertically (this direction | ) (SRCletter = DSTletter/)
	{
		if (/*src_letter > dst_letter*/ src_number > dst_number)  // in case the rook goes backwards, the check is made backwards
		{
			// in case we want to move from a5 to a1, then this if statement will make src a1 and dst a5
			temp = src_number;  // switching the indexes to check from dst to src
			src_number = dst_number; 
			dst_number = temp;
		}
		//			
		for(int i = src_number + 1; i <= dst_number - 1; i++)
		{
			//std::cout << board.at(i).at(src_letter) << " ";
			if(board.at(i).at(src_letter) != nullptr) //&& board.at(i).at(src_letter) != 'r' && board.at(i).at(src_letter) != 'R')  // row (left) - number, col (right) - letter
			{
				return false;
			}
		}
		
	}
	else if(move_choice[1]==move_choice[3])  // we want to move horizontally (^  (SRCnumber = DSTnumber) 
	{
		if (src_letter > dst_letter /*src_number > dst_number*/)  // in case the rook goes backwards, the check is made backwards
		{
			// in case we want to move from a5 to a1, then this if statement will make src a1 and dst a5
			temp = src_letter;  // switching the indexes to check from dst to src
			src_letter = dst_letter; 
			dst_letter = temp;
		}

		for(int i = src_letter + 1; i <= dst_letter - 1; i++)
		{
			//std::cout << board.at(i).at(src_letter) << " ";
			if(board.at(src_number).at(i) != nullptr) //&& board.at(i).at(src_letter) != 'r' && board.at(i).at(src_letter) != 'R')  // row (left) - number, col (right) - letter
			{
				return false;
			}
		}
	}
	return true;
}



/*
{
	std::string pos = this->_position;
	//char** bor = get_board();

	//if((move_choice[2]>H || move_choice[2]< A) || (move_choice[3]>8 || move_choice[3]<1))
	//{
	//	throw "out of the board";
	//	return 5;
	//}
	//else
	//{

	//}

	if (((int)(move_choice[2]) >= 1 && (int)(move_choice[2]) <= 8)  &&  ((int)(move_choice[3]) >= 1 && (int)(move_choice[3]) <= 8))// out of bonds
	{
		if (move_choice[0] == move_choice[2] || move_choice[1] == move_choice[3]) //valid move?
		{
			if (move_choice[0] != move_choice[2] && move_choice[1] != move_choice[3]) // dst and src are the same?
			{
				if (move_choice[0] == pos[0] && move_choice[1] == pos[1])
				{
					if (false)//bor[(int)(move_choice[2])][(int)(move_choice[3])] == '#')
					{

					}
					else
					{
						return 3;// dst isn't empty
					}
				}
				else
				{
					return 2; // src is empty
				}
			}
			else
			{
				//throw "dst and src are the same";
				return 7; // dst and src the same
			}
		}
		else
		{
			//throw "not a valid move";
			return 6; //not a valid move
		}
	}
	else
	{
		//throw "out of the board";
		return 5;
	}

}
*/

// TODO: (Ori & Neria) fix and finish Rook's CheckPath function
// TODO: (Ori) implement Board with a Piece pointer like planed (functions and all)
// TODO: (Neria) debug Bishop::CheckPath function
