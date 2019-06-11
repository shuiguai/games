#include<iostream>
#include<stdio.h>
#include<time.h>
#include <stdlib.h>
#include<windows.h>
#include<conio.h>
using namespace std;
const int MaxMap = 21;
char map[MaxMap][MaxMap];
int snakeLength = 4;
char direction = 'd';
struct snake{
	int x;
	int y;
	struct snake *next;
}head,body1,body2,tail;

void printmap(){
	for (int i = 0; i < MaxMap; i++){
		for (int j = 0; j < MaxMap; j++){
			cout << map[i][j];
		}
		cout << endl;
	}
	return;
}
void food(){
	int x = 0, y = 0;
	srand(time(0));
	while (map[x][y]!=' '){
		x = rand() % (MaxMap - 1) + 1;
		y = rand() % (MaxMap - 1) + 1;
	}
	map[x][y] = 'f';
	return;
}
bool eat(int x,int y){
	if (map[x][y] == 'f'){
		food();
		return 1;
	}
	else{
		return 0;
	}
}
bool gameover(int x,int y){
	if (map[x][y] == 'W' || map[x][y] == 'B')
		return 1;
	else
		return 0;
}

bool move(){
	char letter = direction;
	struct snake *p = &tail;
	int nextX = 0, nextY = 0, tailX = p->x, tailY = p->y;
	if (_kbhit()){
		letter = _getch();
	

		if (letter == 'w' || letter == 's' || letter == 'a' || letter == 'd'){
			if (0 != (direction - letter)){
				if (!((letter == 'w' && direction == 's') ||
					(letter == 's' && direction == 'w') ||
					(letter == 'a' && direction == 'd') ||
					(letter == 'd' && direction == 'a')))
					direction = letter;
			}
		}
	}

	switch (direction){
	case 'w':
		nextX = -1;
		nextY = 0;
		break;
	case 's':
		nextX = 1;
		nextY = 0;
		break;
	case 'a':
		nextX = 0;
		nextY = -1;
		break;
	case 'd':
		nextX = 0;
		nextY = 1;
		break;
	default:
		break;
	}
	
	map[p->x][p->y] = ' ';
	while (p->next != NULL){
		
		p->x = p->next->x;
		p->y = p->next->y;
		map[p->x][p->y] = 'B';
		p = p->next;
	}
	
	map[head.x][head.y] = 'B';
	head.x += nextX;
	head.y += nextY;
	if (gameover(head.x, head.y)){
		return 1;
	}
	if (eat(head.x, head.y)){
		snake *newBody = new snake;
		newBody->x = tail.x; newBody->y = tail.y; newBody->next = tail.next;
		tail.x = tailX, tail.y = tailY;
		tail.next = newBody;
		map[tailX][tailY] = 'B';
		snakeLength++;
	}
	map[head.x][head.y] = 'H';

	return 0;
}

void initial(){
	for (int i = 0; i < MaxMap; i++){
		for (int j = 0; j < MaxMap; j++){
			 map[i][j]=' ';
		}
	}
	head = { 10, 10, NULL };
	body1 = { 10, 9, &head };
	body2 = { 10, 8, &body1 };
	tail = { 10, 7, &body2 };

	for (int i = 0; i < MaxMap; i++){
		map[0][i] = 'W';
		map[MaxMap - 1][i] = 'W';
	}
	for (int i = 1; i < MaxMap-1; i++){
		map[i][0] = 'W';
		map[i][MaxMap - 1] = 'W';
	}
	struct snake *p = &tail;
	while (p != NULL){
		map[p->x][p->y] = 'B';
		p = p->next;
	}
	map[head.x][head.y] = 'H';
	food();
	return;
}
int main(){
	initial();
	int i = 0;
	int starttime = time(0);
	while (1){
		
		cout << "score:"<<snakeLength-4<<"\n";
		cout << "time:" << time(0)-starttime << "s\n";
		printmap();
		
		if (move() == 1){
			printf("%s", "GAME OVER\n");
			snake *p = tail.next;
			while (snakeLength - 4 >0)
			{
				tail.next = p->next;
				delete p;
				p = tail.next;
				snakeLength--;
			}
			break;
		}
		else{
			Sleep(500-2*(snakeLength-4));
			system("cls");
			i++;
		}
	}
	return 0;
}