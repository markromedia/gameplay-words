#ifdef WIN32

#include "../src/board_file_loader.hpp"

void BoardFileLoader::LoadPrecalculatedBoard( std::queue<PrecalculatedBoard*> *precalculated_boards )
{
	//load the precalculated boards
	FILE* f = gameplay::FileSystem::openFile("res/dict/precalculated_boards.txt", "r");

	//first, verify that the dice used to generate the boards are the same we're using now
	int d_id;
	std::string d_sides[6];
	for (unsigned int i = 0; i < DiceManager::dice.size(); i++) {
		fscanf(f, "%i%s%s%s%s%s%s", &d_id, &d_sides[0], &d_sides[1], &d_sides[2], &d_sides[3], &d_sides[4], &d_sides[5]);
		Dice* d = DiceManager::GetDieById(d_id);
		assert(d != NULL);
		for (unsigned int i = 0; i < d->sides.size(); i++) {
			std::string s = std::string(d_sides[i].c_str());
			assert (d->sides[i] == s);
		}
	}

	bool has_data = true;
	int word_count;
	std::vector<PrecalculatedBoard*> v;
	std::string s;

	while (!feof(f) && has_data) {
		int board_values[32];
		int idx = 0;

		has_data = fscanf(f, "%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%i%s", 
			&board_values[idx++], &board_values[idx++], &board_values[idx++], &board_values[idx++], &board_values[idx++], &board_values[idx++], &board_values[idx++], &board_values[idx++], 
			&board_values[idx++], &board_values[idx++], &board_values[idx++], &board_values[idx++], &board_values[idx++], &board_values[idx++], &board_values[idx++], &board_values[idx++], 
			&board_values[idx++], &board_values[idx++], &board_values[idx++], &board_values[idx++], &board_values[idx++], &board_values[idx++], &board_values[idx++], &board_values[idx++], 
			&board_values[idx++], &board_values[idx++], &board_values[idx++], &board_values[idx++], &board_values[idx++], &board_values[idx++], &board_values[idx++], &board_values[idx++], 
			&word_count, &s) != NULL; //read to see if there's anything in here

		if (has_data) {
			PrecalculatedBoard* p = new PrecalculatedBoard;
			p->word_count = word_count;

			//TODO values are backwards from some reason. need to fix
			int cnt = 31;
			for (int i = 0; i < 16; i++) {
				p->board[i][0] = board_values[cnt--];
				p->board[i][1] = board_values[cnt--];
			}
			v.push_back(p);
		} 
	}
	fclose(f);

	assert(v.size() > 1);

	//shuffle boards and add to the queue
	std::random_shuffle(v.begin(), v.end());
	for (unsigned int i = 0; i < v.size(); i++) {
		precalculated_boards->push(v[i]);
	}
}

#endif