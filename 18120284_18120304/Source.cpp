#include "Header.h"

int width = 55;
int height = 35;
const float maxSpeed = 1.8f;
const int delay = 170; 

void set(Ball& ball, Pad& p1, Pad& p2, int& p1score, int& p2score, bool start)
{
	//cài đặt quả bóng ở chính giữa bàn chơi game
	ball.x = float(width / 2 - 1);
	ball.y = float(height / 2); 
	//cài đặt thanh đỡ ở chính giữa vị trí qua lại
	p1.x = p2.x = float(width / 2);
	//cài đặt vận tốc của quả bóng
	ball.vx = float(rand() % 3) - 1;
	ball.vy = 1;
	start = false;
	COORD c;
	c.X = 0;
	c.Y = height;
	//in ra bảng điểm của 2 người chơi
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	cout << endl << "Player 1 score: " << p1score << "\t\tPlayer 2 score: " << p2score << endl;

}

void setconsole()
{
	srand(unsigned int(time(NULL)));
	SMALL_RECT DisplayArea = { 0, 0, width, height + 3 };
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &DisplayArea);
}

void hidemousecursor()
{
	CONSOLE_CURSOR_INFO ConCurInf;
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConCurInf);
}

void setframework()
{
	//in ra khung bàn chơi
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	for (int i = 0; i < width - 1; ++i)
		cout << '-';
	for (int i = 0; i < height - 1; ++i) {
		cout << endl << '|';
		for (int i = 0; i < width - 3; ++i)
			cout << ' ';
		cout << '|';
	}
	cout << '\n';
	for (int i = 0; i < width - 1; ++i)
		cout << '-';
	cout << "\n    Player 1 score: 0\t\tPlayer 2 score: 0\n";
	for (int i = 0; i < width - 1; ++i)
		cout << '=';
}

void start()
{
	//tạo các giá trị ban đầu cho đối tượng
	Pad p1(width / 2, height - 2, 4);
	Pad p2(width / 2, 2, 4);
	Ball b(width / 2 - 1, height / 2);
	//đặt điểm của người chơi ban đầu bằng 0
	int p1score = 0, p2score = 0;
	//cài vận tốc ban đầu cho bóng
	b.vx = float(rand() % 3) - 1.5f;
	b.vy = 1;
}

void rungame()
{
	//in ra các kí tự ' ' để ẩn dòng chữ thông báo người chơi thắng nếu chọn chơi lại
	COORD p;
	p.X = int(width / 2 - 24);
	p.Y = int(height / 1.5f);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
	cout << "                                             ";

	//tạo các giá trị ban đầu trước khi vào chơi cho các đối tượng
	Pad p1(width / 2, height - 2, 4);
	Pad p2(width / 2, 2, 4);
	Ball b(width / 2 - 1, height / 2);
	int p1score = 0, p2score = 0;
	b.vx = float(rand() % 3) - 1.5f;
	b.vy = 1;

	bool start = false;
	while (true)
	{
		if (start)
		{
			//điều khiển thanh đỡ
			if (GetAsyncKeyState(VK_LEFT)) { p1.x -= 3; }
			else if (GetAsyncKeyState(VK_RIGHT)) { p1.x += 3; }

			if (GetAsyncKeyState(65)) { p2.x -= 3; }
			else if (GetAsyncKeyState(68)) { p2.x += 3; }

			if (p1.x < p1.size + 1) { p1.x = float(p1.size + 1); }
			else if (p1.x > width - p1.size - 2) { p1.x = float(width - p1.size - 2); }

			if (p2.x < p2.size + 1) {	p2.x = float(p2.size + 1);	}
			else if (p2.x > width - p2.size - 2) { p2.x = float(width - p2.size - 2); }

			//tối đa vận tốc của quá bóng nếu vận tốc quá mức cho phép
			if (b.vx < -maxSpeed) { b.vy = -maxSpeed; }
			else if (b.vx > maxSpeed) { b.x = maxSpeed; }

			b.x += b.vx;
			b.y += b.vy;

			//kiểm tra nếu bóng chạm thanh đỡ của người chơi 1
			if (b.y >= p1.y - 1 && b.y <= p1.y + 1) {
				if (b.x > p1.x - p1.size && b.x < p1.x + p1.size) {
					b.vy *= (-1.1);				//tăng tốc độ lên 10% như yêu cầu và đổi hướng ngược lại
					b.vx += float(b.x - p1.x) / 3;
					b.y = p1.y - 1;
				}
			}

			//kiểm tra nếu bóng chạm thanh đỡ của người chơi 2
			if (b.y <= p2.y + 1 && b.y >= p2.y - 1) {
				if (b.x > p2.x - p2.size && b.x < p2.x + p2.size) {
					b.vy *= (-1.1);				//tăng tốc độ lên 10% như yêu cầu và đổi hướng ngược lại
					b.vx += float(b.x - p2.x) / 3;
					b.y = p2.y + 1;
				}
			}

			//kiểm tra nếu bóng ra khỏi bàn chơi
			if (b.y >= height) {
				++p2score;						//cộng điểm cho người chơi 2
				set(b, p1, p2, p1score, p2score, start);
			}
			else if (b.y <= 1) {
				++p1score;						//cộng điểm cho người chơi 1
				set(b, p1, p2, p1score, p2score, start);
			}
			if (b.x <= 2) {
				b.vx *= -1;
				b.vx = 1.0f;
				b.x = 2;
			}
			else if (b.x >= width - 3) {
				b.vx *= -1;
				b.x = float(width - 3);
			}
		}
		else
		{
			//bắt đầu game và đợi người chơi nhấn phím space
			COORD p;
			p.X = int(width / 2 - 10);
			p.Y = int(height / 1.5f);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
			cout << "Press Space to start";
			if (GetAsyncKeyState(VK_SPACE)) {
				COORD p;
				p.X = int(width / 2 - 16);
				p.Y = int(height / 1.5f);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
				cout << "                                ";
				start = true;
			}
		}
		
		p1.drawpad();
		p2.drawpad();
		b.drawball();
		Sleep(delay);

		//nếu 1 trong 2 người chơi đạt 3 điểm thì sẽ thông báo thắng
		if (p1score == 3 || p2score == 3)
		{
			if (p1score == 3)
			{
				COORD p;
				p.X = int(width / 2 - 22);
				p.Y = int(height / 1.5f);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
				cout << "Player1 wins";
				system("pause");
				rungame();
			}
			else
			{
				COORD p;
				p.X = int(width / 2 - 22);
				p.Y = int(height / 1.5f);
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
				cout << "Player2 wins";
				system("pause");
				rungame();
			}
		}
	}
}