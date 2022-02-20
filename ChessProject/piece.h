#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include <array>
#include <Math.h>

class Piece
{
protected:
	char _tag;  // the Piece's identifier
public:
	const static short SrcNumber = 1;
	const static short SrcLetter = 0;
	const static short DstNumber = 3;
	const static short DstLetter = 2;
	const static char Empty = '#';
	Piece(const char tag);
	~Piece();
	char get_tag() const;
	virtual bool CheckPath(const std::array<std::array<Piece*, 8>, 8>& board, const std::string& move_choice) const = 0;
	virtual bool CheckValidity(const std::string& move_choice) const = 0;
};
