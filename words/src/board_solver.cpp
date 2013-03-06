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