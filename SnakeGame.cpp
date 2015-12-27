#include<iostream>
#include<cmath>
#include<windows.h>
#include<conio.h>
#define W 23		//Height
#define H 23		//Width
//integer equivalents of  directions
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
//Ascii values...
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
//Snake Length. It must be less than your Width - 2 as there are walls on the side.
#define LENGTH 5

using namespace std;

int ctr=LENGTH;
bool ateFood=false;

//To print the field
void printField(char [W][H]);
//Gets length of snake - 1 as it doesnt include head.
int length(char [W][H]);
//What to do when you die.
void dead(char [W][H]);
//Changes direction according to key press.
int changeDirection(char,int);
//Scans next body part.
void scanNext(int [W][H],int &, int &);
//Moves head.
void moveHead(char [W][H],int [W][H],int,int);
//Moves body to follow head. 
void moveBody(char [W][H],int[W][H],int);
//Makes food appear at random places.
void foodAppear(char [W][H]);
//Clears screen in an un-laggy way.
void clearScreen()
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}
int main()
{
	int choice = 0 ;
	cout<<" 1.EASY\n 2.MEDIUM\n 3.HARD\n";
	cout<<"What difficulty level do you choose"<<endl;
	while(choice<1 || choice>3)
	{
		cin>>choice;
		if(choice>3 || choice<1)
		cout<<"That is not an option\n";
	}
	clearScreen();
	int ch,path[W][H]={0},i,j,headDir=RIGHT;
	char field[W][H];
	for(i=0;i<W;i++)
	{
		for(j=0;j<H;j++)
		field[i][j]=' ';
	}
	for(i=0;i<W;i++)
	{
		field[i][0]='x';
		field[i][H-1]='x';
	}
	for(j=0;j<H;j++)
	{
		field[0][j]='x';
		field[W-1][j]='x';
	}
	for(j=1;j<=LENGTH;j++)
	{
		if(j==LENGTH)
		field[1][j]='#';
		else
		field[1][j]='*';
		path[1][j]=j;
	}
	foodAppear(field);
	printField(field);
	while(true)
	{
		if (kbhit()) 
		{
            // Change to direction determined by key pressed
            headDir=changeDirection(getch(),headDir);
        }
        clearScreen();
        if (kbhit()) 
		{
            // Change to direction determined by key pressed
            headDir=changeDirection(getch(),headDir);
        }
		
		moveHead(field,path,headDir,ctr);
		moveBody(field,path,ctr);
		if (kbhit()) 
		{
            // Change to direction determined by key pressed
            headDir=changeDirection(getch(),headDir);
        }
		printField(field);
		if (kbhit()) 
		{
            // Change to direction determined by key pressed
            headDir=changeDirection(getch(),headDir);
        }
        switch(choice)
        {
			case 1:Sleep(1000);
				break;
			case 2:Sleep(50);
				break;
			case 3:
				break;
		}
		ctr++;
	}
}
int changeDirection(char ch,int headDir)
{
	switch (int(ch)) 
	{
   		case KEY_UP:
			if (headDir != DOWN) 
			headDir = UP;
			break;
		case KEY_LEFT:
   	    	if (headDir != RIGHT) 
			headDir = LEFT;
	   	    break;
   		case KEY_RIGHT:
   	    	if (headDir != LEFT) 
			headDir = RIGHT;
			break;
    	case KEY_DOWN:
			if (headDir != UP)
			headDir = DOWN;
   	    	break;
   	}
    return headDir;
}
void foodAppear(char field[W][H])
{
	int i,j;
	i = rand() % (W-1) + 1;
	j = rand() % (H-1) + 1;
	if(field[i][j]!=' ')
		foodAppear(field);
	else
		field[i][j]='O';
}
void printField(char field[W][H])
{
	cout<<"SCORE: "<<(length(field)+1-LENGTH) * 50 + ctr<<" points.\n";
	int i,j;
	field[0][0]='x';
	for(i=0;i<W;i++)
	{
		for(j=0;j<H;j++)
		cout<<field[i][j]<<" ";
		cout<<endl;
	}
}
void dead(char field[W][H])
{
	system("cls");
	cout<<endl<<endl;
	cout<<"\t\t YOU ARE DEAD!!!!\n\n";
	cout<<"\t\t You scored "<<(length(field)+1-LENGTH) * 50 + ctr<<" points.\n";
	getch();
	exit(0);
}
void moveHead(char field[W][H],int path[W][H],int headDir,int ctr)
{
	int i,j;
	//Storing position of head in i and j
	for(i=0;i<W;i++)
	{
		for(j=0;j<H;j++)
		{
			if(field[i][j]=='#')
			break;
		}
		if(field[i][j]=='#')
		break;
	}
	if(headDir==UP)
	{
		if(field[i-1][j]=='*' || field[i-1][j]=='x')
		dead(field);
		else if(field[i-1][j]=='O') 
		{
			ateFood=true;
			foodAppear(field);
		}
		
		field[i-1][j]=field[i][j];
		path[i-1][j]=ctr+1;
	}
	else if(headDir==DOWN)
	{
		if(field[i+1][j]=='*' || field[i+1][j]=='x')
		dead(field);
		else if(field[i+1][j]=='O') 
		{
			ateFood=true;
			foodAppear(field);
		}
		
		field[i+1][j]=field[i][j];
		path[i+1][j]=ctr+1;
	}	
	else if(headDir==LEFT)
	{
		if(field[i][j-1]=='*' || field[i][j-1]=='x')
		dead(field);
		else if(field[i][j-1]=='O') 
		{
			ateFood=true;
			foodAppear(field);
		}
		
		
		field[i][j-1]=field[i][j];
		path[i][j-1]=ctr+1;	
	}
	else if(headDir==RIGHT)
	{
		if(field[i][j+1]=='*' || field[i][j+1]=='x')
		dead(field);
		else if(field[i][j+1]=='O') 
		{
			ateFood=true;
			foodAppear(field);
		}
		
		field[i][j+1]=field[i][j];
		path[i][j+1]=ctr+1;
	}
}
void scanNext(int path[W][H],int ctr,int &posi,int &posj)
{
	int i,j;
	for(i=0;i<W;i++)
	{
		for(j=0;j<H;j++)
		{
			if(path[i][j]==ctr)
			{
				posi=i;
				posj=j;
				return;
			}
		}
	}
}
int length(char field[W][H])
{
	int i,j,length = 0;
	for(i=0;i<W;i++)
	{
		for(j=0;j<H;j++)
		{
			if(field[i][j]=='*')
			length++;
		}
	}
	return length;
}
void moveBody(char field[W][H],int path[W][H],int ctr)
{
	int i,j,bodyLength;
	bodyLength=length(field);
	do
	{
		ctr--;
		scanNext(path,ctr,i,j);
		//Returns the co-ordinates of next segment.
		//This segment will now move to the position with counter 1 more than that of it's current position.
		if(path[i-1][j]==ctr+1)
		{
			field[i-1][j]=field[i][j];
		}
		else if(path[i+1][j]==ctr+1)
		{
			field[i+1][j]=field[i][j];
		}
		else if(path[i][j-1]==ctr+1)
		{
			field[i][j-1]=field[i][j];
		}
		else if(path[i][j+1]==ctr+1)
		{
			field[i][j+1]=field[i][j];
		}
		field[i][j]=' ';
	}while(bodyLength--);
	if(ateFood==true)
	{
		scanNext(path,ctr+1,i,j);
		field[i][j]='*';
		ateFood=false;
	}
}
