#include <iostream>
#include <cstdlib>
using namespace std;

enum enChoice {Stone=1,Paper=2,Scissor=3};

string Choice(enChoice choice)
{
	
	switch (choice)
	{
	case enChoice::Stone:
		return "Stone";
		break;
	case enChoice::Paper:
		return "Paper";
		break;
	case enChoice::Scissor:
		return "Scissor";
		break;

	default :
		return "Worng Choice Please try again.";
		break;
	}
}

int ReadRoundNumber()
{
	int RoundNum;
	do
	{
		cout << "enter how many rounds (choose 1-10): ";
		cin >> RoundNum;
	} while (RoundNum <= 0 || RoundNum>10);

	return RoundNum;
}

int RandomNumbers(int from, int to)
{
	return rand() % (to - from + 1) + from;
}

enChoice getComputerChoice()
{
	return enChoice(RandomNumbers(1, 3));
}

enChoice getPlayerChoice()
{
	int ReadPlayerChoice;
	do
	{
		cout << "Your Choice: [1]:Stone,  [2]:Paper,  [3]:Scissor:  ";
		cin >> ReadPlayerChoice;
	} while (ReadPlayerChoice <= 0 || ReadPlayerChoice > 3);

	return enChoice(ReadPlayerChoice);
}

string  DetermineWinner(enChoice PlayerChoice, enChoice ComputerChoice)
{
	if (PlayerChoice == ComputerChoice)
	{
		system("color 6F");
		return "[No Winner]";
	}
	else if (PlayerChoice == enChoice::Scissor && ComputerChoice == enChoice::Paper)
	{
		system("color 2F");
		return "[Player]";
	}
	else if (PlayerChoice == enChoice::Paper && ComputerChoice == enChoice::Stone)
	{
		system("color 2F");
		return "[Player]";
	}
	else if (PlayerChoice == enChoice::Stone && ComputerChoice == enChoice::Scissor)
	{
		system("color 2F");
		return "[Player]";
	}
	else
	{
		system("color 4F");
		system("echo \a");
		return "[Computer]";

	}

}
struct stTrackReuslut
{
	int GameRound;
	int PlayerWon;
	int ComputerWon;
	int Draw;
};


void  Game(stTrackReuslut &TrackResult)
{
	TrackResult.GameRound = ReadRoundNumber();
	enChoice PlayerChoice;
	string FinalWinner = "";
	int RoundCount = 1;
	while (RoundCount<= TrackResult.GameRound)
	{
		cout << "Round[" << RoundCount << "] begin: \n\n";
		PlayerChoice= getPlayerChoice();
		enChoice ComputerChoice = getComputerChoice();
		cout << "\n\n____________ Round[" << RoundCount << "] ____________ \n\n";
		cout << "Player Choice: " << Choice(PlayerChoice) << endl;
		cout << "Computer Choice: " << Choice(ComputerChoice) << endl;
		string FinalWinner = DetermineWinner(PlayerChoice, ComputerChoice);
		cout << "Round Winner: " << FinalWinner;
		if (FinalWinner == "[Player]")
		{
			TrackResult.PlayerWon++;
		}
		else if (FinalWinner == "[Computer]")
		{
			TrackResult.ComputerWon++;
		}
		else
		{
			TrackResult.Draw++;
		}
		cout << "\n\n____________________________________\n\n";
		RoundCount++;
		
	}
}

char getResults(stTrackReuslut &TrackResult)
{
	char YESNO;	

	cout << "\n\n\t\t__________________________________________________________________\n\n";
	cout << "\t\t\t\t\      +++ G a m e O v e r +++\t\t";
	cout << "\n\t\t__________________________________________________________________\n\n";
	cout << "\t\t__________________________ [Game Result]__________________________\n\n";
	cout << "\t\tGame Rounds        : " << TrackResult.GameRound << "\n";
	cout << "\t\tPlayer won times   : " << TrackResult.PlayerWon << "\n";
	cout << "\t\tComputer won times : " << TrackResult.ComputerWon << "\n";
	cout << "\t\tDraw times         : " << TrackResult.Draw << "\n";
	cout << "\t\tFinal Winner       : ";
	if (TrackResult.PlayerWon < TrackResult.ComputerWon)
	{
		cout << "Computer\n";
	}
	else if (TrackResult.PlayerWon > TrackResult.ComputerWon)
		cout << "Player\n";
	else
		cout << "No Winner\n";
	cout << "\t\t__________________________________________________________________\n\n";
	cout << " \t\tDo you want to play again (Y/N): ";
	cin >> YESNO;
	
	return YESNO;
}

void StartGame()
{
	char YESNO;
	do
	{
		stTrackReuslut TrackResult{ 0,0,0,0 };
		system("color 0F");
		system("CLS");
		Game(TrackResult);
		YESNO=getResults(TrackResult);
	} while (YESNO == 'y' || YESNO == 'Y');
}


int main()
{
	srand((unsigned)time(NULL));
	
	StartGame();

	return 0;
}