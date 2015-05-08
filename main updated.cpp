#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <time.h>
#include <string>
#include <fstream>

using namespace std;
using namespace sf;


const int rows=12;
	const int columns=12;
	char grid[rows][columns],gridcopy[rows][columns];

bool checkM( char M[][columns], int i, int j, int t_i, int t_j);



int main(){
	ifstream input;
	string s;
	int start_x,start_y,target_x,target_y;
	int NumEnemies; int t;
	int *B_x,*B_y;
	int *C_x,*C_y;
	int NumCoins;

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
	
	if(!walltxture.loadFromFile("wall.png")){
	cout<<"error cannot load background"<<endl;
	}
	if(!floortxture.loadFromFile("floor.png")){
	cout<<"error cannot load background"<<endl;
	}
	
	  	for (int i=0;i<rows;i++){
			for(int j=0;j<columns;j++){
				if(grid[i][j]=='#'){
					wall[i][j].setPosition(i*50,j*50); 
					wall[i][j].setScale(sf::Vector2f(1,1));
					wall[i][j].setTexture(walltxture);
						cout<<i<<j<<endl;
				}if(grid[i][j]=='.'){
					
					floor[i][j].setPosition(i*50,j*50); 
					floor[i][j].setScale(sf::Vector2f(1,1));
					floor[i][j].setTexture(floortxture);
					cout<<i<<j<<endl;
						}
					}
				}


		while (maze.isOpen()){
	
	Event game;
	while(maze.pollEvent(game)){
		switch (game.type){
	case Event::Closed:
	maze.close();
	break;
		}
	}
	
	for(int i=0;i<rows;i++){
		for(int j=0; j<columns; j++){
				maze.draw(floor[i][j]);
				maze.draw(wall[i][j]);	
				
						}
		
					}
	maze.display();

	
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