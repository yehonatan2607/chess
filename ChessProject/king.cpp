#include "king.h"



King::King(const char tag) : Piece(tag)
{
    
}

King::~King()
{

}

bool King::CheckValidity(const std::string& move_choice) const 
{
    return (move_choice[0] == move_choice[2] + 1 || move_choice[0] == move_choice[2] - 1 || move_choice[0] == move_choice[2]) && (move_choice[1] == move_choice[3] + 1 || move_choice[1] == move_choice[3] - 1 || move_choice[1] == move_choice[3]) && !(move_choice[1] == move_choice[3] && move_choice[0] == move_choice[2]);
}

bool King::CheckPath(const std::array<std::array<Piece*, 8>, 8>& board, const std::string& move_choice) const 
{
    return true;
}

