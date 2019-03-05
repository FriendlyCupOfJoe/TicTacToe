class Ai
{
public:
	int x;
	int y;
	int score; //Move's score that will be determined with MinMax algorithm from AiBestMove.
	Ai() {};
	Ai(int score) { this->score = score; };
	~Ai() {};
	void AiMove(char[][3], bool); //Places the Ai symbol on the field depending on the best move from AiBestMove.
	Ai AiBestMove(char[][3], bool); //Gets the best possible move with MinMax algorithm.
};

