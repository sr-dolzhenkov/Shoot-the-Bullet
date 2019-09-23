class Row {
public:
	Row(int _y);
	~Row();
	void CreateBlock(int _x);
	bool CheckWin();
	void CreateRow();
	void Clean();//???
	bool CheckLose();//???
	void NewGame();//???

private:
	int x;
	int y;
};