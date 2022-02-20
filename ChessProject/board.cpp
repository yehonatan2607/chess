#include "board.h"

/*
Board's default constructor - creates a blank board with default pieces
Input: void
Output: the new Board object
*/
Board::Board()
{
    this->_current_turn = WhiteTurn;
    this->Reset();
}

/*
Board's custom constructor - creates a board with custom pieces from a file
Input: the path of the file to load the board from
Output: the new Board object
*/
Board::Board(const std::string& path)
{
    this->_current_turn = WhiteTurn;
    this->Load(path);
}

/*
A deconstructor method for the Board class
deletes all Piece Pointers from the _pieces array
Input: void
Output: void
*/
Board::~Board()
{
    int i = 0;
    int j = 0;
    for (i = 0; i < 8; i++)  // running on the array
    {
        for (j = 0; j < 8; j++)
        {
            if (this->_pieces[i][j] != nullptr)  // can't delete an empty Piece*
            {
                delete (this->_pieces[i][j]);
            }
        }
    }
}

/*
Returns the current turn 
Input: void
Output: the _current_turn field
*/
char Board::get_current_turn() const
{
    return this->_current_turn;
}

/*
Sets the pieces on the board to be on their default starting state
Input: void
Output: void (edits the _state field)
*/
void Board::Reset()  // # = nullptr
{
    std::string king_location = "";
    const std::string first_row = "RNBQKBNR";
    const std::string second_row = "PPPPPPPP";  // white pawns
    const std::string eighth_row = "rnbqkbnr";
    const std::string seventh_row = "pppppppp";  // black pawns
    int row = 0, col = 0;

    for (row = 0; row < SideLength; row++)
    {
        switch (row)
        {
        case 0:
            for (col = 0; col < SideLength; col++)  // running on the first row (row=0)
            {
                switch (first_row[col])
                {
                case 'R':
                    this->_pieces[row][col] = new Rook(first_row[col]);
                    break;
                case 'N':
                    this->_pieces[row][col] = new Knight(first_row[col]);
                    break;
                case 'B':
                    this->_pieces[row][col] = new Bishop(first_row[col]);
                    break;
                case 'Q':
                    this->_pieces[row][col] = new Queen(first_row[col]);
                    break;
                case 'K':
                    this->_pieces[row][col] = new King(first_row[col]);
                    break;
                
                
                default:
                    this->_pieces[row][col] = nullptr;
                    break;
                }
            }
            break;
        case 1:
            for (col = 0; col < SideLength; col++)  // second row is made of white pawns
            {
                this->_pieces[row][col] = new Pawn(second_row[col]);
            }
            break;
        case 6:
            for (col = 0; col < SideLength; col++)
            {
                this->_pieces[row][col] = new Pawn(seventh_row[col]);  // seventh row is made of black pawns
            }
            break;
        case 7:
            for (col = 0; col < SideLength; col++)
            {
                switch (eighth_row[col])
                {
                case 'r':
                    this->_pieces[row][col] = new Rook(eighth_row[col]);
                    break;
                case 'n':
                    this->_pieces[row][col] = new Knight(eighth_row[col]);
                    break;
                case 'b':
                    this->_pieces[row][col] = new Bishop(eighth_row[col]);
                    break;
                    case 'q':
                        this->_pieces[row][col] = new Queen(eighth_row[col]);
                        break;
                case 'k':
                    this->_pieces[row][col] = new King(eighth_row[col]);
                    break;
                default:
                    this->_pieces[row][col] = nullptr;
                    break;
                }
            }
            break;
        default:  // rows third (2) to sixth (5) (including both)
            for (col = 0; col < SideLength; col++)
            {
                this->_pieces[row][col] = nullptr;  // empty ('#') = nullptr (null Piece pointer)
            }
            break;
        }
    }
}

/*
Deeply analizes the given move_choice and runs a series of checks as described below:
 1. src != dst (if src == dst return error code 7)
 2. analize src and dst from given strings
 3. call CheckValidity and CheckPath functions of the src Piece pointer
 4. analize dst:
 5. ...if dst is an ally, return error code 3
 6. ...if dst is an enemy, call Eat function
 7. ...if dst is empty, call Move function
 Input: the move to analize (for example, a1a7 or d3h4)
 Output: the result - which is the error \ completion code
*/
int Board::CheckMove(const std::string& move_choice)
{
    Piece* save = nullptr;
    std::string temp_move = "";
    int src_board_ltr_index = (int)move_choice[SrcLetter] - 'a';
    int src_board_num_index = (int)move_choice[SrcNumber] - '1';
    int dst_board_ltr_index = (int)move_choice[DstLetter] - 'a';
    int dst_board_num_index = (int)move_choice[DstNumber] - '1';

    if (!(move_choice[SrcLetter] == move_choice[DstLetter] && move_choice[SrcNumber] == move_choice[DstNumber]))
    {
        //std::cout << this->_pieces[src_board_num_index][src_board_ltr_index]->get_tag() << "\n";
        if (this->_pieces[src_board_num_index][src_board_ltr_index] == nullptr)  // if src is empty
        {
            return SrcHasEmptyOrEnemy;  // error code 2
        }
        else if (!IsAllyPiece(this->_pieces[src_board_num_index][src_board_ltr_index]))  // if src doesnt have an ally piece
        {
            return SrcHasEmptyOrEnemy;  // error code 2
        }
        else if (IsAllyPiece(this->_pieces[dst_board_num_index][dst_board_ltr_index]))  // if dst has an ally piece
        {
            return DstHasAlly;  // error code 3
        }
        else if (this->_pieces[src_board_num_index][src_board_ltr_index]->CheckValidity(move_choice) && this->_pieces[src_board_num_index][src_board_ltr_index]->CheckPath(this->_pieces, move_choice))
        {
            if (this->_pieces[dst_board_num_index][dst_board_ltr_index] != nullptr && !IsAllyPiece(this->_pieces[dst_board_num_index][dst_board_ltr_index]))  // in case dst has an enemy
            {
                Eat(move_choice, save);
                if (FoundCheck(true, save))  // if a check can be caused on own king
                {
                    temp_move = "";
                    temp_move += move_choice[DstLetter];
                    temp_move += move_choice[DstNumber];
                    temp_move += move_choice[SrcLetter];
                    temp_move += move_choice[SrcNumber];
                    Move(temp_move);  // restoring the move
                    this->_pieces[dst_board_num_index][dst_board_ltr_index] = GetObjectByType(save->get_tag());
                    return CanCauseSelfCheck;
                }
                else
                {
                    this->_pieces[src_board_num_index][src_board_ltr_index] = nullptr;
                    PassTurn();
                    if (FoundCheck(false, nullptr))  // in case an enemy check was caused
                    {
                        return CausedEnemyCheck;
                    }
                    else
                    {
                        return ValidMove;
                    }
                }
            }
            else  // in case dst is empty
            {
                Move(move_choice);  // call replacement move
                if (FoundCheck(true, nullptr))  // if a check can be caused on own king
                {
                    temp_move += move_choice[DstLetter];
                    temp_move += move_choice[DstNumber];
                    temp_move += move_choice[SrcLetter];
                    temp_move += move_choice[SrcNumber];
                    Move(temp_move);  // restoring the move
                    return CanCauseSelfCheck;
                }
                else
                {
                    if (FoundCheck(false, nullptr))  // if a check can be caused on enemy's king
                    {
                        PassTurn();  // note: the turn can only be passed after the FoundCheck function is called
                        return CausedEnemyCheck;
                    }
                    else  // in case of a valid, regular move
                    {
                        PassTurn();
                        return ValidMove;
                    }
                }
            }
        }
        return InvalidPieceMove;
    }
    else
    {
        return DstEqualsSrc;  // error code 7
    }
}

/*
Replaces src with dst (first part of move_choice with other part of move_choice)
Called especialy when moving a piece to an empty location
Input: the move to make
Output: void
*/
void Board::Move(const std::string& move_choice)
{
    int src_board_ltr_index = (int)move_choice[SrcLetter] - 'a';
    int src_board_num_index = (int)move_choice[SrcNumber] - '1';
    int dst_board_ltr_index = (int)move_choice[DstLetter] - 'a';
    int dst_board_num_index = (int)move_choice[DstNumber] - '1';
    Piece* temp = this->_pieces[dst_board_num_index][dst_board_ltr_index];

    this->_pieces[dst_board_num_index][dst_board_ltr_index] = this->_pieces[src_board_num_index][src_board_ltr_index];
    this->_pieces[src_board_num_index][src_board_ltr_index] = temp;
    
}

void Board::Eat(const std::string& move_choice, Piece*& save)
{
    int src_board_ltr_index = (int)move_choice[SrcLetter] - 'a';
    int src_board_num_index = (int)move_choice[SrcNumber] - '1';
    int dst_board_ltr_index = (int)move_choice[DstLetter] - 'a';
    int dst_board_num_index = (int)move_choice[DstNumber] - '1';

    save = GetObjectByType(this->_pieces[dst_board_num_index][dst_board_ltr_index]->get_tag());  // saving the eaten piece
    this->_pieces[dst_board_num_index][dst_board_ltr_index] = this->_pieces[src_board_num_index][src_board_ltr_index];
    this->_pieces[src_board_num_index][src_board_ltr_index] = nullptr;  // eating 
}

/*
Returns true if the given Piece pointer is an ally piece, overwise returns false
Input: a pointer to the Piece to check
Output: true if the given Piece pointer is an ally piece
*/
bool Board::IsAllyPiece(const Piece* target) const
{
    if (target != nullptr)
    {
        return (isupper(this->_current_turn) && isupper(target->get_tag()) ||
            islower(this->_current_turn) && islower(target->get_tag()));
        // the condition above checks if the piece belongs to the player using the piece's tag and turn tag case similarity
    }
    else
    {
        return false;  // an empty Piece is not an ally
    }
}

/*
Gets an input from the pattern letter-number-letter-number (a1c5 or b3e1, for example)
Input: void
Output: the corrected-user-entered location
*/
std::string Board::GetLocationChoice()
{
    std::string location = "";
    do
    {
        std::cin >> location;  // reading the location and checking it
    } while (location.length() != 4 || !islower(location[0]) ||
        !islower(location[2]) || !isdigit(location[1]) || !isdigit(location[3]));
    return location;
}

/*
Scans the board to find if a certain game-piece can cause a check on one of the kings.
If it operates in self mode, it searches for a check on the players own king, 
overwises it searches for a check on the enemy king. the save parameter is 
used to exclude from the check a game piece which is about to be eaten (or was eaten)
Input: the board to check on, the self (true) or enemy (false) mode, and the recently eaten piece
Output: true if a check can be cause on the selcted king, overwise false
*/
bool Board::FoundCheck(bool self_mode, Piece* eaten_piece = nullptr)
{
    std::string king_dst = "";
    std::string current_src = "";
    char search_tag = ' ';
    int src_letter = 0;
    int src_number = 0;

    if (self_mode && isupper(this->_current_turn) || islower(this->_current_turn) && !self_mode)  // white turn and check self or black turn and check enemy
    {
        search_tag = 'K';  // searching on white king
    }
    else if (islower(this->_current_turn) && self_mode || isupper(this->_current_turn) && !self_mode)  // black turn and check self or white turn and check enemy
    {
        search_tag = 'k';  // searching  black king
    }
    if (!self_mode)
    {
        PassTurn();  // passing the turn to check from the enemy's point of view (friendlys are now enemys)
    }
    king_dst = FindLocation(search_tag);  // getting the king's board location
    for (src_number = 0; src_number < SideLength; src_number++)
    {
        for (src_letter = 0; src_letter < SideLength; src_letter++)  // running on each row cell by cell
        {
            current_src = "";
            current_src += (char)(src_letter + 'a');
            current_src += (char)(src_number + '1');
            // the condition bellow runs a series of checks. Hard to read, but has an efficient complexity
            // checks order: if src is not empty and src is not the searched king and src is not the eaten piece
            // and src is an enemy and src is valid and has a clear path to eat the king - than a check can be occured.
            if (this->_pieces[src_number][src_letter] != nullptr && current_src != king_dst && this->_pieces[src_number][src_letter] != eaten_piece
                && !IsAllyPiece(this->_pieces[src_number][src_letter]) && this->_pieces[src_number][src_letter]->CheckValidity(current_src + king_dst)
                && this->_pieces[src_number][src_letter]->CheckPath(this->_pieces, current_src + king_dst))  // if the piece can get to the king
            {
                if (!self_mode)
                {
                    PassTurn();  // passing back the turn
                }
                return true;  // a check can be caused on the searched king
            }
        }
    }
    if (!self_mode)
    {
        PassTurn();  // passing back the turn
    }
    return false;  // if the loop checked the whole board and didn't find a single validity, no piece can get to the searched king
}

/*
Turns the board into a single string. Can be used to load \ save games on txt files
Input: void
Output: a string with all of the board pieces (for example RNBQKBNR#####...)
*/
std::string Board::GenerateString() const
{
    std::string board_str = "";
    int row = 0, col = 0;

    for (row = 0; row < SideLength; row++)
    {
        for (col = 0; col < SideLength; col++)  // running on the whole board
        {
            if (this->_pieces[row][col] != nullptr)
            {
                board_str += this->_pieces[row][col]->get_tag();  // copying the piece's char to the string
            }
            else
            {
                board_str += '#';  // '#' represents an empty piece
            }
        }
    }
    return board_str;
}

// GENERAL MOVEMENT CHECKS SEQUENCE*
// 1. src != dst (if src == dst return error code 7)
// 2. src and dst are within the board's limits
// 3. analize src and dst from given strings
// 4. call CheckValidity and CheckPath functions of the src piece*
// ADDITION: 
// 5. analize dst 
// 6. if dst is an ally, return error code 3
// 6. if dst is an enemy, call Eat function*
// 7. if dst is empty, call Move function

// Notes:
// 1. CheckPath needs to check the path to dst, not including dst itself (because dst can be filled with a piece)
// 2. Eat will do the same thing as Move, but will not replace dst with src (and maybe will raise the player's score?)

/*
Get's a search tag and returns the location of the first found appearence. Mainly used to obtain the king's location
Input: the boad to search on and the tag to search
Output: the location of the tab (for example "a1" or "h7")
*/
std::string Board::FindLocation(/*const std::array<std::array<Piece*, 8>, 8>& board, */const char search_tag) const
{
    std::string found_location = "";
    for (int i = 0; i < SideLength; i++)
    {
        for (int j = 0; j < SideLength; j++)
        {
            if (this->_pieces.at(i).at(j) != nullptr && this->_pieces.at(i).at(j)->get_tag() == search_tag)  // if the current tag equals the tag to search
            {
                found_location += (int)j + 'a';
                found_location += (int)i + '1';
                return found_location;  // returning the location
            }
        }
    }
    return "";  // didn't find the piece
}

/*
Switches the current_turn's tag from black to white or from white to black
Input: void
Output: void
*/
void Board::PassTurn()
{
    if (this->_current_turn == WhiteTurn)  // if turn was white
    {
        this->_current_turn = BlackTurn;
    }
    else  // if turn was black
    {
        this->_current_turn = WhiteTurn;
    }
}

/*
Prints the board on the console screen. Used for mainly for debug, or for players who prefer the console appearence 
Input: void
Output: void
*/
void Board::PrintBoard() const
{
    int row = 0;
    int col = 0;
    std::cout << "  a b c d e f g h\n";
    for (row = 0; row < SideLength; row++)
    {
        std::cout << (row + 1) << " ";
        for (col = 0; col < SideLength; col++)
        {
            if (this->_pieces[row][col] != nullptr)
            {
                std::cout << this->_pieces[row][col]->get_tag() << " ";  // printing the Piece's tag
            }
            else
            {
                std::cout << "# ";
            }
        }
        std::cout << "\n";
    }
}

/*
Translates the error code number and returns the descryption string.
Input: the code to translate
Output: the descriptive string which tells the player about his move (for example, "caused a chess on enemy")
Note: code can be either an error code or a vlidity code
*/
std::string Board::TranslateCode(int code)
{
    switch (code)
    {
    case ValidMove:
        return "Valid Move";
    case CausedEnemyCheck:
        return "Caused Enemy Check";
    case SrcHasEmptyOrEnemy:
        return "Error: source tile is empty or contains an enemy game piece";
    case DstHasAlly:
        return "Error: destination tile contains an ally game piece";
    case CanCauseSelfCheck:
        return "Error: entered move can cause a check on your king";
    case InvalidPieceMove:
        return "Error: the piece in the source tile cannot move to the destination tile";
    case DstEqualsSrc:
        return "Error: the source and the destination are the same tile";
    default:
        return " ";
    }
}

/*
Creates and returns the object equivalent for the given tag
Input: the tag to create an object with
Output: the newly created object
*/
Piece* Board::GetObjectByType(const char type)
{
    switch(type)
    {
    case 'r':
    case 'R':
        return new Rook(type);
    case 'k':
    case 'K':
        return new King(type);
    case 'b':
    case 'B':
        return new Bishop(type);
    case 'q':
    case 'Q':
        return new Queen(type);
    case 'n':
    case 'N':
        return new Knight(type);
    case 'p':
    case 'P':
        return new Pawn(type);
    default:
        return nullptr;
    }
}

/*
Loads a board from a file which contains a board string
Input: the file path
Outupt: void
*/
void Board::Load(const std::string& path)
{
    std::ifstream file_obj(path);
    if (!file_obj.is_open())
    {
        std::cout << "cannot open file. starting a new game... " << "\n";
    }
    else
    {
        std::string result = "";
        int row = 0, col = 0;

        file_obj >> result;  // should only be one line long
        if (result.length() < SideLength * SideLength)
        {
            std::cout << "invalid file format. starting a new game... " << "\n";
        }
        else
        {
            for (row = 0; row < SideLength; row++)
            {
                for (col = 0; col < SideLength; col++)
                {
                    if (result[SideLength * row + col] != '#' && this->_pieces[row][col] != nullptr)
                    {
                        this->_pieces[row][col] = GetObjectByType(result[SideLength * row + col]);  // building the board from the string in the file
                    }
                    else
                    {
                        this->_pieces[row][col] = nullptr;
                    }
                }
            }
            file_obj >> result;
            this->_current_turn = (char)result[0];
        }

    }
}

/*
Saves the game on it's current state on a .txt file
Input: void
Output: void 
*/
void Board::Save() const
{
    std::string path = "";
    std::cout << "note: do not use paths who contain hebrew letters" << "\n";
    std::cout << "enter path to save the game into: ";
    std::cin >> path;
    std::ofstream file_obj(path);
    file_obj << this->GenerateString() << "\n";
    file_obj << this->_current_turn;
    file_obj.close();
}

//  1 2 3 4 5 6
//  1 2 3 4 5 6
//  1 2 3 4 5 6

// 1 2 3 4 5 6 7 8 9 10 11 12