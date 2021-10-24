#include<bits/stdc++.h>
#include<cstdlib>
#include<stdlib.h>
#define MAXSIDES 30
#define MAXMINES 190
using namespace std;
int sides;
int mines;
bool isValidBlock(int row,int col)
{
	if(((row>=0)&&(row<sides))&&((col>=0)&&(col<sides)))
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool isMine(int row,int col,char board[][MAXSIDES])
{
	if(board[row][col]=='X')
		return true;
	else
		return false;
}
void chooseMode(int mode)
{
	cout<<"\nEnter the difficulty mode you want:"<<endl;
	cout<<"1.Easy Mode"<<endl;
	cout<<"2.Medium Mode"<<endl;
	cout<<"3.Hard Mode"<<endl;
	cout<<"4.Exit"<<endl;
	cout<<"Enter you choice(1-4):";
	cin>>mode;
	switch(mode)
	{
		case 1:	sides=10,mines=10;
				break;
		case 2:	sides=20,mines=82;
				break;
		case 3: sides=30,mines=190;
				break;
		case 4:	exit(0);
				break;
		default:cout<<"\nWrong choice please choose appropriate option!!!!";
				chooseMode(mode);
				break;
	}
}
void move(int *row,int *col)
{
	cout<<"\nEnter the move:"<<endl;
	cout<<"Enter row and column:";
	cin>>*row>>*col;
	return;
}
int adjMines(int row,int col,int minesArr[][2],char playBoard[][MAXSIDES])
{
	int cnt=0;
	//for upper left block
	if(isValidBlock(row-1,col-1)==true)
		if(isMine(row-1,col-1,playBoard)==true)
			cnt++;
	
	//for upper block
	if(isValidBlock(row-1,col)==true)
		if(isMine(row-1,col,playBoard)==true)
			cnt++;
	
	//for upper right block
	if(isValidBlock(row-1,col+1)==true)
		if(isMine(row-1,col+1,playBoard)==true)
			cnt++;

	//for left block
	if(isValidBlock(row,col-1)==true)
		if(isMine(row,col-1,playBoard)==true)
			cnt++;

	//for right block
	if(isValidBlock(row,col+1)==true)
		if(isMine(row,col+1,playBoard)==true)
			cnt++;

	//for lower left block
	if(isValidBlock(row+1,col-1)==true)
		if(isMine(row+1,col-1,playBoard)==true)
			cnt++;

	//for lower block
	if(isValidBlock(row+1,col)==true)
		if(isMine(row+1,col,playBoard)==true)
			cnt++;

	//for lower right block
	if(isValidBlock(row+1,col+1)==true)
		if(isMine(row+1,col+1,playBoard)==true)
			cnt++;
			
	return cnt;
}
void printBoard(char currboard[][MAXSIDES])
{
	cout<<"\t";
	for(int i=0;i<sides;i++)
	{
		cout<<i<<"  ";
	}
	cout<<endl;
	cout<<"\t";
	for(int i=0;i<sides;i++)
	{
		cout<<"_"<<"  ";
	}
	cout<<endl;
	for(int i=0;i<sides;i++)
	{
		cout<<i<<"|\t";
		for(int j=0;j<sides;j++)
		{
			cout<<currboard[i][j]<<"  ";
		}
		cout<<endl;
	}
	return;
}
void replaceMineloc(int row,int col,char board[][MAXSIDES])
{
	for(int i=0;i<sides;i++)
	{
		for(int j=0;j<sides;j++)
		{
			if(board[i][j]!='X')
			{
				board[i][j]='X';
				board[row][col]='#';
				return;
			}
		}
	}
	return;
}
void arrangeMines(int minesArr[][2],char playBoard[][MAXSIDES])
{
	bool mark[MAXSIDES*MAXSIDES];
	memset(mark,false,sizeof(mark));	//marking all positions in array mark as false
	//loop for all the mines are created and placed
	for(int i=0;i<mines;)
	{
		int randMines=rand()%(sides*sides);
		int row=randMines/sides;
		int col=randMines%sides;

		//condition for finding if there is no mine then 
		//it will place mine and increment i
		if(mark[randMines]==false)
		{
			//taking row of the mine
			minesArr[i][0]=row;
			//taking column index of the mine
			minesArr[i][1]=col;
			playBoard[minesArr[i][0]][minesArr[i][1]]='X';	//placing the mine
			mark[randMines]=true;	//marking the place mine as true
			i++;
		}
	}
	return;
}
void initializingBoard(char playBoard[][MAXSIDES],char currboard[][MAXSIDES])
{
	//Initialize the random number and  
	srand(time(NULL));
	//Hidding all the mines and safe places
	for(int i=0;i<sides;i++)
	{
		for(int j=0;j<sides;j++)
		{
			currboard[i][j]=playBoard[i][j]='#';
		}
	}
	return;
}
bool recMineSweeper(int row,int col,int *movesLeft,int minesArr[][2],char currboard[][MAXSIDES],char playBoard[][MAXSIDES])
{
	//Base condition
	if(currboard[row][col]!='#')
		return false;

	//if the choosen block contains mine
	if(playBoard[row][col]=='X')
	{
		currboard[row][col]='X';
		for(int i=0;i<mines;i++)
		{
			currboard[minesArr[i][0]][minesArr[i][1]]='X';
		}
		printBoard(currboard);
		cout<<"\nGAME OVER"<<endl;
		return true;
	}
	else
	{
		//count is the variable which counts the adjacent mines
		int count;
		count=adjMines(row,col,minesArr,playBoard);
		(*movesLeft)--;
		currboard[row][col]=count+'0';
		if(!count)
		{
			//for upper left block
			if(isValidBlock(row-1,col-1)==true)
				if(isMine(row-1,col-1,playBoard)==false)
					recMineSweeper(row-1,col-1,movesLeft,minesArr,currboard,playBoard);

			//for upper block
			if(isValidBlock(row-1,col)==true)
				if(isMine(row-1,col,playBoard)==false)
					recMineSweeper(row-1,col,movesLeft,minesArr,currboard,playBoard);

			//for upper right block
			if(isValidBlock(row-1,col+1)==true)
				if(isMine(row-1,col+1,playBoard)==false)
					recMineSweeper(row-1,col+1,movesLeft,minesArr,currboard,playBoard);

			//for left block
			if(isValidBlock(row,col-1)==true)
				if(isMine(row,col-1,playBoard)==false)
					recMineSweeper(row,col-1,movesLeft,minesArr,currboard,playBoard);
			
			//for right block
			if(isValidBlock(row,col+1)==true)
				if(isMine(row,col+1,playBoard)==false)
					recMineSweeper(row,col+1,movesLeft,minesArr,currboard,playBoard);
			
			//for lower left block
			if(isValidBlock(row+1,col-1)==true)
				if(isMine(row+1,col-1,playBoard)==false)
					recMineSweeper(row+1,col-1,movesLeft,minesArr,currboard,playBoard);

			//for lower block
			if(isValidBlock(row+1,col)==true)
				if(isMine(row+1,col,playBoard)==false)
					recMineSweeper(row+1,col,movesLeft,minesArr,currboard,playBoard);
			
			//for lower right block
			if(isValidBlock(row+1,col+1)==true)
				if(isMine(row+1,col+1,playBoard)==false)
					recMineSweeper(row+1,col+1,movesLeft,minesArr,currboard,playBoard);
			
		}
		return false;
	}
}
void mineSweeperMain()
{
	//gameStatus false means the game hasn't over
	bool gameStatus=false;
	int row,col;
	char playBoard[MAXSIDES][MAXSIDES],currboard[MAXSIDES][MAXSIDES];
	int movesLeft=sides*sides-mines;
	int noOfMoves=0;
	int minesArr[MAXMINES][2];
	//initialises the boards and hides all mines and numbers
	initializingBoard(playBoard,currboard);
	//this function arrages the mines
	arrangeMines(minesArr,playBoard);
	while(gameStatus==false)
	{
		cout<<"\nCurrent board:"<<endl;
		//prints the current status of the board
		printBoard(currboard);
		//takes the row and column from user
		move(&row,&col);
		//condition for the first move
		if(noOfMoves==0)
			if(isMine(row,col,playBoard)==true)
				replaceMineloc(row,col,playBoard);
		noOfMoves++;
		gameStatus=recMineSweeper(row,col,&movesLeft,minesArr,currboard,playBoard);
		if((gameStatus==false)&&(movesLeft==0))
		{
			cout<<"\nCongratulations you won the game!!!!!!!!"<<endl;
			gameStatus=true;
		}
	}
	return;
}
int main()
{
    int mode;
	chooseMode(mode);
	mineSweeperMain();
	return 0;
}
