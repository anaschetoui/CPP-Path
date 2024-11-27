#include <iostream>
#include <cstdlib>
using namespace std;

enum enChoice {Stone=1,Paper=2,Scissor=3};
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

short ReadNumberOfRounds()
{
	short NumberOfRounds = 0;
	do
	{
		cout << "How many Rounds do you want to play(1-10): ";
		cin >> NumberOfRounds;
	} while (NumberOfRounds <= 0 || NumberOfRounds >= 11);

	return NumberOfRounds;
}

int RandomNumbers(short from, short to)
{
	return rand() % (to - from + 1) + from;
}

string Choice(enChoice Choice)
{
	string arr[3] = { "Stone","Paper","Scissor" };
	return arr[Choice - 1];
}
struct stRoundInfo
{
	short RoundGame = 0;
	enChoice PlayerChoice = enChoice::Stone;
	enChoice ComputerChoice = enChoice::Stone;
	string WinnerOfTheGame;
	enWinner GameWinner = enWinner::Draw;
	string WinnerName;
};

struct stResultsInfo
{
	short RoundGame=0 ;
	short PlayerWonTimes = 0;
	short ComputerWonTimes = 0;
	short DrawTimes = 0;
	enWinner FinalWinner= enWinner::Draw;
	string WinnerName = "";
};

enWinner WinnerOfTheGame(short PlayerChoice, short ComputerChoice)
{
	if (PlayerChoice == ComputerChoice)
	{
		return enWinner::Draw;
	}
	switch (PlayerChoice)
	{
	case enChoice::Paper:
		if (ComputerChoice == enChoice::Scissor)
		{
			return enWinner::Computer;
		}
		break;
	case enChoice::Scissor:
		if (ComputerChoice == enChoice::Stone)
		{
			return enWinner::Computer;
		}
		break;
	case enChoice::Stone:
		if(ComputerChoice==Paper)
		{
			return enWinner::Computer;
		}
		break;
	}

	return enWinner::Player;
	
}

void WinnerColorInScreen(enWinner Winner)
{
    if (Winner == enWinner::Computer) {
        system("COLOR 4F");
    } else if (Winner == enWinner::Player) {
        system("COLOR 2F");
    }
	else {
		system("color 6F");
	}
}

enChoice getComputerChoice()
{
	return enChoice(RandomNumbers(1, 3));
}

enChoice ReadPlayerChoice()
{
	short PlayerChoice=0;
	do
	{
		cout << "Your Choice: [1]:Stone,  [2]:Paper,  [3]:Scissor: ";
		cin >> PlayerChoice;
	} while (PlayerChoice <= 0 || PlayerChoice > 3);

	return enChoice(PlayerChoice);
}
string WinnerName(enWinner Winner)
{
	string arr[3] = { "[Player]","[Computer]","[No Winner]" };
	return arr[Winner - 1];
}

string Tabs(short NumberOfTabs)
{
	string Tabs = "";
	for (int i = 1; i < NumberOfTabs;i++)
	{
		Tabs += '\t';
		cout << Tabs;
	}
	return Tabs;
}

void  RestScreen()
{
	system("COLOR 0F");
	system("CLS");	
}

void GameOverScreen()
{
	cout << Tabs(2) << "_______________________________________\n";
	cout << Tabs(2) << "         +++G a m e O v e r+++         \n";
	cout << Tabs(2) << "_______________________________________\n";
}

stResultsInfo FillGameResults(short Rounds,short PlayerWonTimes,short ComputerWonTimes,short DrawTimes)
{
	stResultsInfo GameResults;

	GameResults.RoundGame = Rounds;
	GameResults.ComputerWonTimes = ComputerWonTimes;
	GameResults.PlayerWonTimes = PlayerWonTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.FinalWinner = WinnerOfTheGame(PlayerWonTimes, ComputerWonTimes);
	GameResults.WinnerName = WinnerName(GameResults.FinalWinner);

	return GameResults;
	
}


void PrintRoundResult(stRoundInfo RoundInfo)
{
	cout << "_______________________________________\n";
	cout << "Player Choice: " << Choice(RoundInfo.PlayerChoice);
	cout << "\nComputer Choice: " << Choice(RoundInfo.ComputerChoice);
	cout << "\nRound Winner: " << WinnerName(RoundInfo.GameWinner) << endl;
	cout << "_______________________________________\n";
	WinnerColorInScreen(RoundInfo.GameWinner);
}

stResultsInfo PlayGame(short ReadNumberOfRounds)
{
	stRoundInfo RoundInfo;
	short PlayerWonTimes = 0;
	short ComputerWonTimes = 0;
	short DrawTimes = 0;

	for (int GameRound = 1; GameRound <= ReadNumberOfRounds; GameRound++)
	{
		cout << "Round[" << GameRound << "] " << "begin: \n";
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = getComputerChoice();
		RoundInfo.RoundGame = GameRound;
		RoundInfo.GameWinner = WinnerOfTheGame(RoundInfo.PlayerChoice, RoundInfo.ComputerChoice);
		RoundInfo.WinnerName = WinnerName(RoundInfo.GameWinner);
		PrintRoundResult(RoundInfo);

		if (RoundInfo.GameWinner == enWinner::Player)
		{
			PlayerWonTimes++;
		}
		else if (RoundInfo.GameWinner == enWinner::Computer)
		{
			ComputerWonTimes++;
		}
		else
		{
			DrawTimes++;
		}
	}
	

	return FillGameResults(ReadNumberOfRounds, PlayerWonTimes, ComputerWonTimes, DrawTimes);
	
}

void FinalResult(stResultsInfo GameResults)
{
	cout << Tabs(2) << "_____________[Game Results]_____________\n\n";
	cout << Tabs(2) << "GameRounds        : " << GameResults.RoundGame<<endl;
	cout << Tabs(2) << "Player won times  : " << GameResults.PlayerWonTimes<<endl;
	cout << Tabs(2) << "Computer won times: " << GameResults.ComputerWonTimes<<endl;
	cout << Tabs(2) << "Draw times        : " << GameResults.DrawTimes<<endl;
	cout << Tabs(2) << "Final Winner      : " << WinnerName(GameResults.FinalWinner) << endl;
	cout << Tabs(2) << "____________________________________________\n";

	WinnerColorInScreen(GameResults.FinalWinner);
}

void StatGame()
{
	char YESNO = 'y';
	
	do
	{
		RestScreen();
		short NumberOfRounds = ReadNumberOfRounds();
		stResultsInfo GameResults=PlayGame(NumberOfRounds);
		GameOverScreen();
		FinalResult(GameResults);
		cout << endl << Tabs(3) << "Do you want to play again (Y/N): ";
		cin >> YESNO;
	} while (YESNO == 'y' || YESNO == 'Y');

}


int main()
{
	srand((unsigned)time(NULL));
	
	StatGame();

	return 0;
}