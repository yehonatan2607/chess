#pragma once
#include <iostream>

class ChessPlayer
{
public:
	ChessPlayer();
	~ChessPlayer();

private:
	std::string _name;
	std::string _player_tools;
};