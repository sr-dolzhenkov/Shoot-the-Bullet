class Plane {
public:
	Plane();
	~Plane();
	static void MoveLeft();
	static void MoveRight();

private:
	int x;
	int y;
};