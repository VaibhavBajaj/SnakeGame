//This is my Snake Game.

#include<iostream>
#include<cmath>			//for random function
#include<windows.h>		//for my clearScreen function and for Sleep function
#include<conio.h>		//for the function which checks key press. (kbhit())
#define W 30		//Width
#define H 20		//Height
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

//This variables function becomes apparent later on.
int ctr=LENGTH;
//This stores whether the snake has eaten food or not.
bool ateFood=false;

//To print the field
void printField(char [H][W]);
//Gets length of snake - 1 as it doesnt include head.
int length(char [H][W]);
//What to do when you die.
void dead(char [H][W]);
//Changes direction according to key press.
int changeDirection(char,int);
//Scans next body part.
void scanNext(int [H][W],int &, int &);
//Moves head.
void moveHead(char [H][W],int [H][W],int,int);
//Moves body to follow head. 
void moveBody(char [H][W],int [H][W],int);
//Makes food appear at random places.
void foodAppear(char [H][W]);
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
	//This has been taken as a character to prevent
	//user from entering alphabets or special charachters 
	char choice;
	cout<<" 1.EASY\n 2.MEDIUM\n 3.HARD\n";
	cout<<"What difficulty level do you choose"<<endl;
	do
	{
		cin>>choice;
		if(choice>3 || choice<1)
		cout<<"That is not an option\n";
	}while(int(choice)<49 || int(choice)>51);
	//ASCII VALUES: 1 - 49, 2 - 50, 3 - 51 
	clearScreen();
	int ch,i,j;
	int path[H][W]={0};		//This stores the numbers indicating the places the head snake has been to.
						//The rest of the segments then follow the path of the head snake. 
	int headDir=RIGHT;	//Default direction of snake.
	char field[H][W];	//This stores the field as it looks.
	
	for(i=0;i<H;i++)
	{
		for(j=0;j<W;j++)
		field[i][j]=' ';	//Initializing field to spaces.
	}
	
	//Placing borders.
	for(i=0;i<H;i++)
	{
		field[i][0]='x';
		field[i][W-1]='x';	
	}
	for(j=0;j<W;j++)
	{
		field[0][j]='x';
		field[H-1][j]='x';
	}
	
	//Placing snake. The snake's head is a # sign
	for(j=1;j<=LENGTH;j++)
	{
		if(j==LENGTH)
		field[1][j]='#';
		else
		field[1][j]='*';
		path[1][j]=j;		//This initializes the first few values going into path.
	}
	/*
	CONCEPT:
	The (*) parts of the snake must follow each other. So, I have given them each a value that is one greater than the previous.
	Now, to follow the next one, the star will search in all four directions (up,down,right,left) for a path array cell with
	value one more than that of its own current position's path array cell value. Thus, the head will move according to the 
	whims of the user while the others will follow in a chain like manner.
	*/
	foodAppear(field);	//Initializing the position of the first food piece.
	printField(field);	//Printing field for the first time.
	while(true)
	{
		//The below given if statement checks whether a key is pressed.
		//Full form is something like key button hit... A wild guess by me.
		if (kbhit()) 
		{
            // Change to direction determined by key pressed
            headDir=changeDirection(getch(),headDir);
        }
        //Refreshing screen
        clearScreen();
        //You may notice I have used this if statement at least four times after each sub-step.
        //This has been done so that it checks for key press after each step. If there had been only one,
        //the game would lag quite a lot in terms of detection of key press.
        if (kbhit()) 
		{
            // Change to direction determined by key pressed
            headDir=changeDirection(getch(),headDir);
        }
		//Purpose of functions stated above.
		moveHead(field,path,headDir,ctr);
		moveBody(field,path,ctr);
		if (kbhit()) 
		{
            // Change to direction determined by key pressed
            headDir=changeDirection(getch(),headDir);
        }
        //Printing field.
		printField(field);
		if (kbhit()) 
		{
            // Change to direction determined by key pressed
            headDir=changeDirection(getch(),headDir);
        }
        //The toughness level
        switch(choice)
        {
        	//If easy, computer sleeps for 0.1 seconds.
        	//If medium, 0.05 seconds.
        	//If hard, it doesn't sleep
			case '1':Sleep(100);
				break;
			case '2':Sleep(50);
				break;
			case '3':
				break;
		}
		ctr++;
		//You may have noticed the ctr variable being passed into both moveHead and moveBody functions.
		//This sets the value of the path array cell where the head moves in moveHead.
		//In moveBody, it acts as an identification of the cell to be moved next.
	}
}
int changeDirection(char ch,int headDir)
{
	//ch contains the value of the key pressed
	switch (int(ch)) 
	{
   		case KEY_UP:
   			//If user is moving down, we must ignore the move up instruction.
   			//Same stands for the other cases.
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
   	//headDir holds the direction of movements of the head.
    return headDir;
}
void foodAppear(char field[H][W])
{
	int i,j;
	//rand() function returns a random value.
	//To return a random value in a specific range, we get the remainder after dividing with the max valu of that range.
	//I have used W-1 as I don't want it to generate a random value which lies in the border. 
	// I have added 1 to ignore the left border and the top border.
	i = rand() % (W-1) + 1;
	j = rand() % (H-1) + 1;
	//If this place is where the snake is already present, make it appear somewhere else...
	if(field[i][j]!=' ')
		foodAppear(field);
	else
		field[i][j]='O';
}
void printField(char field[H][W])
{
	//This displays the score.
	cout<<"SCORE: "<<(length(field)+1-LENGTH) * 50 + ctr<<" points.\n";
	int i,j;
	//For some reason field[0][0] appears as blank so I have added this statement.
	field[0][0]='x';
	//Printing field.
	for(i=0;i<H;i++)
	{
		for(j=0;j<W;j++)
		cout<<field[i][j]<<" ";
		cout<<endl;
	}
}
void dead(char field[H][W])
{
	//If user dies, what to do?
	system("cls");
	cout<<endl<<endl;
	cout<<"\t\t YOU ARE DEAD!!!!\n\n";
	cout<<"\t\t You scored "<<(length(field)+1-LENGTH) * 50 + ctr<<" points.\n";
	getch();
	exit(0);
}
void moveHead(char field[H][W],int path[H][W],int headDir,int ctr)
{
	int i,j;
	//Storing position of head in i and j
	for(i=0;i<H;i++)
	{
		for(j=0;j<W;j++)
		{
			if(field[i][j]=='#')
			break;
		}
		if(field[i][j]=='#')
		break;
	}
	//Storing complete.
	
	//If snakehead is going up we move it up by 1 cell and so on for other directions
	/* 
	For clarity, you may see this 3x3 matrix containing i,j respectively:
	0,0	   0,1    0,2
	1,0	   1,1    1,2
	2,0    2,1    2,2
	*/
	if(headDir==UP)
	{
		if(field[i-1][j]=='*' || field[i-1][j]=='x')
		dead(field);
		else if(field[i-1][j]=='O') 
		{
			//If the head moves onto a food piece, we make another food piece appear.
			//The size of snake is incremented while moving the body.
			ateFood=true;		//Mind you, this is a global variable.
			foodAppear(field);
		}
		
		field[i-1][j]=field[i][j];	//Moving head...
		path[i-1][j]=ctr+1;			//The new value of where the head just moved is 1 + initial value.
									//This value may now be followed by the other cells.
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
	field[i][j]=' ';	//This is an unnecessary statement unless length of snake is 1.
						//It simply refreshes the value of field array cell.
}
void scanNext(int path[H][W],int ctr,int &posi,int &posj)
{
	//Here we are scanning for the cell with path array cell value ctr.
	//Told ya it was a very important variable.
	int i,j;
	for(i=0;i<H;i++)
	{
		for(j=0;j<W;j++)
		{
			if(path[i][j]==ctr)
			{
				posi=i;
				posj=j;
				return;	//This function returns control to the calling function.
						//It is used to break out of control of void functions.
			}
		}
	}
}
int length(char field[H][W])
{
	int i,j,length = 0;
	//Here we measure the length of the snake - 1 (the head) as we need to move only the body in the moveBody() function
	for(i=0;i<H;i++)
	{
		for(j=0;j<W;j++)
		{
			if(field[i][j]=='*')
			length++;
		}
	}
	return length;
}
void moveBody(char field[H][W],int path[H][W],int ctr)
{
	int i,j,bodyLength;
	bodyLength=length(field);	//This stores the number of times we will run the loop.
	do
	{
		//The ctr passed  into the function was the path array value of the head.
		//We continue decrementing this value to get the path array values of the cells following.
		ctr--;
		scanNext(path,ctr,i,j);
		//Returns the co-ordinates of next cell. This cell will now move to the position with counter 1 
		//more than that of it's current position. We  search all four directions for where the preceding 
		//cell resided initially i.e where the path array cell value is ctr+1
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
		
		//Here this statement gains value as, if not put, the length of the snake would keep increasing by one.
		//It would then look like the hash sign was leaving behind '*'s as droppings.
		field[i][j]=' ';
		
	}while(bodyLength--);
	if(ateFood==true)
	{	
		//If the snake ate food, we will search for cell with value ctr + 1 and give it value '*'
		scanNext(path,ctr+1,i,j);
		//It is ctr+1 and not ctr because the '*' cell being added has moved t althugh we don't notice it from our perspective. 
		field[i][j]='*';
		//If ateFood wasn't initialized, well, read line (379-380). You know the story
		ateFood=false;
	}
}
//PROGRAM FINISH!!
