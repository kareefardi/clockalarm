#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <time.h>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;
using namespace sf;


const int rows=12;
const int columns=12;
char grid[rows][columns],gridcopy[rows][columns];

bool isValid( char scene[][12], int i, int j, int move){
	int x=i,y=j;
	switch(move){
		case 1: x++; break;
		case 2: x--; break;
		case 3: y--; break;
		case 4: y++; break;
	}
	if(int(scene[i][j]-scene[x][y])==int('.')-int('#'))
		return false;
	return true;
}

bool checkM( char M[][columns], int i, int j, int t_i, int t_j);



int main(){
	enum direction{down,left,right,up};
	int posX=1,posY=down;
	float framecounter=0,framelimit=59,frameswitch=5;
	ifstream input;
	string s;
	int start_x,start_y,target_x,target_y;
	int NumEnemies; int t;
	int *B_x,*B_y;
	int *C_x,*C_y;
	int NumCoins;
	Clock clock1;
	int flagpressed=0;
	int x=0;
	int y=0;
	double p,k=p=0;
	int move_x,move_y=move_x=0;


	input.open("Text.txt");
	if(!input.fail()){
		input>>s; cout<<s<<endl;
		for (int i=0;i<rows;i++){
			for(int j=0;j<columns;j++){
				input>>grid[i][j];
				gridcopy[i][j]=grid[i][j];
			}
		}
		input>>s;
		input>>start_x>>start_y;cout<<start_x<<" "<<start_y<<endl;
		input>>s;
		input>>target_x>>target_y;cout<<target_x<<" "<<target_y<<endl;
		input>>s;
		input>>t;cout<<t<<endl;
		input>>s;
		input>>NumEnemies;cout<<NumEnemies<<endl;
		B_x=new int[NumEnemies];
		B_y=new int[NumEnemies];
		for(int i=0;i<NumEnemies;i++){
			input>>B_x[i]>>B_y[i];

			cout<<B_x[i]<<" "<<B_y[i]<<endl;
		}

		input>>s;
		input>>NumCoins;
		C_x=new int[NumCoins];
		C_y=new int[NumCoins];

		for(int i=0;i<NumCoins;i++){
			input>>C_x[i]>>C_y[i];
			input.close();
		}

		for (int i=0;i<rows;i++){
			for(int j=0;j<columns;j++)
				cout<<grid[i][j];
			cout<<endl;
		}
	}
	for (int i=0;i<rows;i++){
		for(int j=0;j<columns;j++){
			cout<<gridcopy[i][j];
		}
		cout<<endl;
	}

	if(checkM(gridcopy,1,1,target_x,target_y)){
		cout<<"YES"<<endl;
	}else{
		cout<<"NO"<<endl;
	}



	RenderWindow maze(VideoMode(800,800),"maze beta");
	Sprite wall[12][12],floor[12][12];
	Texture walltxture,floortxture;
	maze.setFramerateLimit(60);

	if(!walltxture.loadFromFile("wall.png")){
		cout<<"error cannot load background"<<endl;
	}
	if(!floortxture.loadFromFile("floor.png")){
		cout<<"error cannot load background"<<endl;
	}

	for (int i=0;i<rows;i++){
		for(int j=0;j<columns;j++){
			if(grid[i][j]=='#'){
				wall[i][j].setPosition(j*32,i*32); 
				
				wall[i][j].setTexture(walltxture);

			}if(grid[i][j]=='.'){

				floor[i][j].setPosition(j*32,i*32); 
				floor[i][j].setTexture(floortxture);
			}
		}
	}
	Sprite player;
	Texture ptxture;
	if(!ptxture.loadFromFile("player.png")){
		cout<<"error cannot load background"<<endl;
	}
	player.setTexture(ptxture);
	player.setPosition(32,32);

	while (maze.isOpen()){

		Event game;
		while(maze.pollEvent(game)&&flagpressed==0){
			switch (game.type){
			case Event::Closed:
				maze.close();
				break;
			case Event::KeyPressed:
				switch(game.key.code)
				{
					if(Keyboard::isKeyPressed){
				case Keyboard::Up:
					posY=up;
					x=0;
					k=-3.2;p=0;
					flagpressed=1;
					break;
				case Keyboard::Down:
					posY=down;
					k=3.2;p=0;x=0;
					flagpressed=1;
					break;
				case Keyboard::Left:
					posY=left;
					p=-3.2;k=0;x=0;
					flagpressed=1;
					break;
				case Keyboard::Right:
					posY=right;x=0;
					p=3.2;k=0;
					flagpressed=1;
					break;

					}
				}
			}
		}

		
		framecounter+=framelimit*clock1.restart().asSeconds();
		if(framecounter>=frameswitch && flagpressed==1&&y<10){
			framecounter=0;
			posX++;
			cout<<y<<endl;
			y=y%10+1;
			player.move(p,k);
			if(posX*32>=ptxture.getSize().x){
				posX=0;
			}
			}
			if(x==59){
				flagpressed=0;
				y=0;
		}

		for(int i=0;i<rows;i++){
			for(int j=0; j<columns; j++){
				maze.draw(floor[i][j]);
				maze.draw(wall[i][j]);	
			}
		}

		player.setTextureRect(IntRect(posX*32,posY*32,32,32));
		player.setScale(1,1);
		maze.draw(player);
		maze.display();
		maze.clear();
		x=x%60+1;
		

	}

	system("pause");	
}

bool checkM( char M[][columns], int i, int j, int t_i, int t_j){
	if(i<0||i>rows||j<0||j>columns){ 
		return false;
	}
	if(i==t_i&&j==t_j){
		return true;
	}
	if(M[i][j]=='#'){
		return false;
	}else{
		M[i][j] = '#'; 
		return (checkM(M, i+1,j,t_i,t_j) ||
			checkM(M, i,j-1,t_i,t_j) ||
			checkM(M, i-1,j,t_i,t_j) ||
			checkM(M, i,j+1,t_i,t_j));
	}

}	
