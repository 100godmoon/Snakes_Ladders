//Snake and Ladder Game 

#include <bits/stdc++.h>
#include <random>
using namespace std;

class Game{

//Attributes 
int size;
unordered_map<int,int> snakePosition;
unordered_map<int,int> ladderPosition;
vector<pair<string,int> > Player;
public :


//Board Size initialisation
Game(int size)
{
  this->size=size;
}

// Adding snakes to the game according to users input
bool insertSnakePosition(int head,int tail)
{
  //Handeled Edge cases
  if(head>=size || head<=0 || tail>=head || tail>=size || tail<=0)
  {
    cout<<"Enter a valid head and tail of snake"<<endl;
    return false;
  }
   snakePosition[head]=tail;
   return true;
}


//Adding Ladder to the game according to user input
bool insertLadderPosition(int tail,int head)
{
  //handling edge cases
  if(head<=tail || head<=0 || tail<=0)
  {
     cout<<"Enter a valid head and tail of ladder"<<endl;
    return false;
  }
  ladderPosition[tail]=head;
  return true;
}

//inserting player
void insertPlayers(string name)
{
   Player.push_back(make_pair(name,0));
}

//Rolling function
int rollDice() 
{
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(1, 6);
  return dis(gen);
 }

//Game simulation function
void startGame()
{

  int currentPlayerIndex=0;
  int NumberOfPlayers=Player.size();
  while(true)
  {
    
    int roll=rollDice();
    string currentPlayerName=Player[currentPlayerIndex].first;
    int currentPlayerPosition=Player[currentPlayerIndex].second;
    int positionOnBoard=roll + currentPlayerPosition;

    if((positionOnBoard)>size)
    {
      // if roll + currentplayerPosition > size of the board then player will stay at its current position 
      cout<<"Player makes No move: ROLL OUT OF BOUND "<<endl; 
    }else  if(positionOnBoard==size)
    {
      cout<<currentPlayerName<<" wins the game: "<<endl;
      break;
      
    }else if(snakePosition.find(positionOnBoard)!=snakePosition.end())
    {
       // if a player reaches to a cell having a snake head : Then he will go to the snake's tail 
        cout<<"You have got bitten by a Snake at position: "<<" "<< positionOnBoard<<endl;
        positionOnBoard=snakePosition[positionOnBoard];
 
    }else if(ladderPosition.find(positionOnBoard)!=ladderPosition.end())
    {
      // if the cell contains ladders tail , player will go to ladders head
      cout<<"You got Ladder at position: "<<" "<< positionOnBoard<<endl;
       positionOnBoard=ladderPosition[positionOnBoard];
    }
    
    if(positionOnBoard<=size)
    {
         Player[currentPlayerIndex].second=positionOnBoard;
        cout<<currentPlayerName<<" "<<"is at position: "<<positionOnBoard<<endl;
    }
    
    //we are continously switching between players so that every player get their chance
    currentPlayerIndex++;
   
    if(currentPlayerIndex>=NumberOfPlayers)
    {
      currentPlayerIndex=0;
    }
    
  }


}

};


int main()
{

  int sizeOfBoard;
  cout<<"Enter Size of Board: "<<endl;
  cin>>sizeOfBoard;


// BOARD INITIALISED 
  Game game(sizeOfBoard);

 
//ADDING PLAYERS TO THE GAME 

  cout<<"Enter Number of Players you want to play with: "<<endl;
  int totalPlayers;
  cin>>totalPlayers;


  int playerCount=1;
  while(playerCount<=totalPlayers)
  {
   cout<<"Enter player"<<" "<<playerCount<<endl;
   string name;
   cin>>name;
   game.insertPlayers(name);
   playerCount++;
  }


// ADDING LADDERS TO THE GAME

cout<<"Enter Number of ladders you want to put in the game: "<<endl;
int numberOfLadders;
cin>>numberOfLadders;

int ladderCount=1;

while(ladderCount<=numberOfLadders)
{
  cout<<"Enter start and end position of the ladder : ";
  int start,end;
  cin>>start>>end;
  
  // only increase count if start and end are valid
  if(game.insertLadderPosition(start,end))
  {
    ladderCount++;
  }

}


// ADDING SNAKES IN THE GAME

int snakeCount=1;

cout<<"Enter Number of Snakes you want to put int the game "<<endl;
int NumberOfSnakes;
cin>>NumberOfSnakes;

while(snakeCount<=NumberOfSnakes)
{
  cout<<"Enter head and tail of snake: "<<endl;
  int head,tail;
  cin>>head>>tail;

  if(game.insertSnakePosition(head,tail))snakeCount++;
}



cout<<"###################################################################################################"<<endl;
cout<<"Game Starts Now"<<endl;


game.startGame();





}
