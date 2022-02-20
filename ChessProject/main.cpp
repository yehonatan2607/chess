#include <iostream>
#include "board.h"
#include "Pipe.h"
#include <thread>
#include <vector>

int main(void)
{
	Board* b;
	Pipe p;
	bool isConnect = p.connect();
	std::string ans = "";
	std::string move_choice = "";
	std::string code_str = "";
	std::string from_gui = "";
	std::vector<std::string> moves;
	std::ifstream ascii_file("ascii.txt");
	char to_gui[66];
	char code_cstr[2];
	int index = 0;
	while (std::getline(ascii_file, from_gui))
	{
		std::cout << from_gui << "\n";
	}
	std::cout << "\n\n";
	std::cout << "load previous game? (y/n) ";
	std::cin >> ans;
	if (ans == "y")
	{
		std::cout << "enter path: ";
		std::cin >> ans;
		b = new Board(ans);  // load mode
	}
	else
	{
		b = new Board();  // default mode 
	}
	ShellExecute(NULL, "open", "chessGraphics.exe", NULL, NULL, SW_SHOWDEFAULT);
	std::this_thread::sleep_for(std::chrono::microseconds{ 600000 });
	system("timeout /t 5");
	p.connect();
	code_str = "";
	code_str += b->GenerateString();
	code_str += b->get_current_turn() == Board::WhiteTurn ? '0' : '1';
	strcpy_s(to_gui, code_str.c_str());
	p.sendMessageToGraphics(to_gui);  // sending the board and the turn
	move_choice = p.getMessageFromGraphics();  // getting the move_choice
	std::cout << "move: " << move_choice << "\n";
	while (move_choice != "quit"/* && move_choice != "dont"*/)
	{
		//system("cls");
		std::cout << "previous move: " << move_choice << "\n";
		b->PrintBoard();
		strcpy_s(code_cstr, std::to_string(b->CheckMove(move_choice)).c_str());
		std::cout << "returning code: " << code_cstr << "\n";
		p.sendMessageToGraphics(code_cstr);  // sending the returning code
		move_choice = p.getMessageFromGraphics();  // getting the move_choice 
		std::cout << "move: " << move_choice << "\n";
		/*std::cout << "Enter your move: " << "\n";
		std::cin >> move_choice;*/
		/*if (move_choice != "dont")
		{
			std::cout << b.TranslateCode(b.CheckMove(move_choice)) << "\n";
		}*/
		moves.push_back(move_choice);
		//system("pause");
	}
	system("cls");
	std::cout << "your moves history: ";
	while (index < moves.size())
	{
		std::cout << moves[index] << " ";
		index++;
	}
	std::cout << "\n" << "save the game? (y/n)";
	std::cin >> ans;
	if (ans == "y")
	{
		b->Save();
		std::cout << "saved successfuly" << "\n";
	}
	//system("cls");
	system("pause");
	return 0;
}


// options for the board: a string array, a char** or just a string
// can also be a Piece* type array / vector

// order of move validity checks on Rooks:
//
// if one of the conditions isn't true, than
// the move is invalid

// 1. check which piece src is holding  
// 2. check if the dst is within limits of the board
// 3. check if src and dst have a character or a number in common
//    for example in case (src = a1) dst must include 'a' or '1'
// 4. check if another piece is holding the way
// (future:) 5. check if the move can cause a check 
// if passed all conditions, the move is valid

// lvl 3 for bishop movement will be to check if the
// differences are equal DST(ltr) - SRC(ltr) = DST(num) - SRC(num)

// GENERAL MOVEMENT CHECKS SEQUENCE*
// 1. src != dst
// 2. src and dst are within the board's limits
// 3. analize src and dst from given strings
// 4. call CheckValidity function of the src piece

// * create a move class with src and dst - each has a letter and a number

// TODO: change signture in evey piece (from the aravi)