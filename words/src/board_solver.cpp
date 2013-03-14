#include "board_solver.hpp"

//init static vars
BoardSolver* BoardSolver::instance = NULL;

void BoardSolver::Init()
{
	instance = new BoardSolver();

	//create the solver
	instance->solver = BoggleSolver::Create(44, "res/dict/dictionary.txt");
}

bool BoardSolver::IsWord(const char* str )
{
	return instance->solver->prefix_tree->IsWord(str);
}

void BoardSolver::CreatePrecalculatedBoards()
{
	FILE* f = gameplay::FileSystem::openFile("res/dict/precalculated_boards.txt", "w");

	//write the dice in as the first 16 lines
	for (unsigned int i = 0; i < DiceManager::dice.size(); i++) {
		Dice* dice = DiceManager::dice[i];
		std::stringstream ss; 
		ss << dice->id << " ";
		fprintf(f, ss.str().c_str());
		
		for (unsigned int j = 0; j < dice->sides.size(); j++) {
			fprintf(f, dice->sides[j].c_str());
			fprintf(f, " ");
		}
		fprintf(f, "\n");
	}
	
	for (unsigned int i = 0; i < 100; i++) {
		std::string board = GenerateRandomHiBoard();
		fprintf(f, board.c_str());
		fprintf(f, "\n");
	}
	fclose(f);
}

std::string BoardSolver::GenerateRandomHiBoard() 
{
	int word_count = 0;
	std::string board;
	std::stringstream string_stream;

	while (word_count < 300) {
		Board::CreateRandomBoard();
		board = "";
		string_stream.str("");
		
		//copy the board into a string
		for (int i = 3; i >= 0; i--) {
			BoardColumn* col = Board::Columns()[i];
			for (int j = 0; j < 4; j++) {
				string_stream << col->cells[j]->die->id  << " " 
					          << col->cells[j]->die->side_index << " ";
				board.append(col->cells[j]->die->getAssignedLetter());
			}
		}
		
		instance->solver->Score(board.c_str());
		word_count = 300;//instance->solver->WordCount;
	}

	string_stream << word_count << " " << board;
	return string_stream.str();
}