#include "board_solver.hpp"

//init static vars
BoardSolver* BoardSolver::instance = NULL;
ValueProvider* BoardSolver::value_provider = NULL;

ValueProvider::ValueProvider()
{


	//init unique sided dice
	for (int i = 0; i < 16; i++) {
		unique_sided_dice[i] = new UniqueSidedDie;
		unique_sided_dice[i]->Reset();
	}
}

void ValueProvider::Init( BoardValue** values, int num_values )
{
	this->num_values = num_values;
	for (int i = 0; i < num_values; i++) {
		this->values[i] = values[i];
		//allocate dice
		this->dice[i] = DiceManager::GetRandomDie();
	}

	//we only care about the ref, so immediately return dice
	for (int i = 0; i < num_values; i++) 
		DiceManager::ReturnDie(this->dice[i]);

	//reset unique dice
	for (int i = 0; i < 16; i++)
		this->unique_sided_dice[i]->Reset();

	//figure out the unique sides to each dice
	for (int i = 0; i < num_values; i++) {
		UniqueSidedDie* unique_sided_die = unique_sided_dice[i];
		Dice* c_die = this->dice[i];
		
		unique_sided_die->Reset();
		unique_sided_die->die = c_die;
		for (int i = 0; i < 6; i++) {
			unique_sided_die->add(c_die->sides[i].c_str()[0]);
		}
	}
}

bool ValueProvider::AssignNextValues()
{
	for (int i = 0; i < num_values; i++) {
		this->values[i]->die_id = unique_sided_dice[i]->die->id;
		this->values[i]->value = unique_sided_dice[i]->unique_values[std::rand() % unique_sided_dice[i]->unique_count];
	}
	return true;
}

void BoardSolver::Init()
{
	//init instance and its associated members
	instance = new BoardSolver();
	instance->board_to_score = new char[16];
	for (int i = 0; i < 16; i++) {
		instance->board[i] = new BoardValue;
		instance->board[i]->Reset();

		instance->high_board[i] = new BoardValue;
		instance->high_board[i]->Reset();
	}

	//create the solver
	instance->solver = BoggleSolver::Create(44, "res/dict/dictionary.txt");

	BoardSolver::value_provider = new ValueProvider;
}


void BoardSolver::PrepareToSolveCurrentBoard()
{
	//reset some counts
	instance->current_max_words = 0;
	instance->num_variable_values = 0;
	instance->number_of_boards_solved = 0;


	//reset our boards
	for (int i = 0; i < 16; i++) {
		instance->board[i]->Reset();
		instance->high_board[i]->Reset();
	}

	//build our "board"
	int idx = 0;
	for (int row = 3; row >= 0; row--) {
		for (int col = 0; col < 4; col++) {
			BoardColumn* column = Board::Columns()[col];
			BoardCell* cell = column->cells[row];
			BoardValue* board_value = instance->board[idx];
			BoardValue* high_board_value = instance->high_board[idx];
			idx++;

			//keep track of the cell
			board_value->cell = cell;

			if (cell->die != NULL) {
				//copy fixed values into board and highboard (they never change, so this fine)
				board_value->die_id = cell->die->id;									
				board_value->die_side_index = cell->die->side_index;					
				board_value->is_fixed = true;											
				board_value->value = cell->die->getAssignedLetter().c_str()[0];
				
				high_board_value->die_side_index = board_value->die_side_index;
				high_board_value->is_fixed = board_value->is_fixed;
				high_board_value->die_id = board_value->die_id;
				high_board_value->value = board_value->value;
				high_board_value->cell = board_value->cell;
			} else {
				instance->variable_values[instance->num_variable_values++] = board_value;
			}
		}
	}

	//init the value provider
	value_provider->Init(instance->variable_values, instance->num_variable_values);
}

void BoardSolver::SolveBoard()
{
	//assign the next set of values (if we can, otherwise we're out of values and just return)
	if (!instance->value_provider->AssignNextValues()) {
		return;
	}

	//copy the current board into an array
	char current_board[17];
	for (int i = 0; i < 16; i++) 
		current_board[i] = instance->board[i]->value;
	current_board[16] = '\0'; //c string fun

	//solve the board here
	instance->solver->Score(current_board);
	int word_count = instance->solver->WordCount;

	//track if its the high count
	if (word_count > instance->current_max_words) {
		//assign it as our high board
		for (int i = 0; i < 16; i++) {
			if (!instance->board[i]->is_fixed) {
				BoardValue* board_value = instance->board[i];
				BoardValue* high_board_value = instance->high_board[i];
				high_board_value->die_id = board_value->die_id;
				high_board_value->value = board_value->value;
			}
		}
		instance->current_max_words = word_count;
	}

	instance->number_of_boards_solved++;
}

void BoardSolver::AssignHighBoardToMainBoard()
{
	char current_board[17];
	for (int i = 0; i < 16; i++) 
		current_board[i] = instance->high_board[i]->value;
	current_board[16] = '\0'; //c string fun

	std::stringstream ss;
	ss << "\nProcessed " << instance->number_of_boards_solved << " boards\n";
	ss << "The best preforming board was [" << current_board << "]\n";
	ss << "It has " << instance->current_max_words << " words\n\n";
	gameplay::Logger::log(gameplay::Logger::LEVEL_INFO, ss.str().c_str());

	for (int i = 0; i < instance->num_variable_values; i++) {
		BoardValue* board_value = instance->variable_values[i];
		if (!board_value->is_fixed) {
			//find a side
			Dice* die = DiceManager::GetDieById(board_value->die_id);
			for (unsigned int i = 0; i < die->sides.size(); i++) {
				if (board_value->value == (die->sides[i]).c_str()[0]) {
					die->side_index = i;
				}
			}
			board_value->cell->die = die;
		}
	}
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
		instance->solver->WordCount;
	}

	string_stream << word_count << " " << board;
	return string_stream.str();
}