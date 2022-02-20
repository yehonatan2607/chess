#pragma once
#include "piece.h"
#include "rook.h"
#include "bishop.h"

class Queen : public Piece
{
private:
	Bishop* _bishop_mover;
	Rook* _rook_mover;
public:
	Queen(const char tag);
	~Queen();
	bool CheckValidity(const std::string& move_choice) const;
	bool CheckPath(const std::array<std::array<Piece*, 8>, 8>& board, const std::string& move_choice) const;
};

// Queen's CheckValidity(move_choice):
// return _bishop_mover.CheckValidity(move_choice) || _rook_mover.CheckValidity(move_choice)

// Queen's CheckPath:
// if (_rook_mover.ChekValidity(move_choice) == false) - > return _bishop_mover.CheckPath(board, move_choice)
// else - > return _rook_mover.CheckPath(board, move_choice)
//
//	 ^  ^  ^
//	  \ | /
// <--- Q --->
//    / | \    
//   v  v  v
