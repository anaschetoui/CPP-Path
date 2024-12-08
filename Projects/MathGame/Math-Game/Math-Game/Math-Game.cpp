#include <iostream>
#include <cstdlib>
using namespace std;
enum enQuestionsLevel {Easy=1,Med=2,Hard=3,Mix=4};
enum enQuestionsType { Add = 1 ,Sub= 2 ,Mul=3,Dev=4,MixOp=5 };

struct stQuizzResults
{
	short NumberOfQuestions = 0;
	string QuestionsLevel = "";
	string OpType = "";
	short NumberOfRightQuestions = 0;
	short NumberOfWrongQuestions = 0;
};

struct stQuizzLevel
{
	short Num1 = 0;
	short Num2 = 0;
	enQuestionsLevel Easy=enQuestionsLevel::Easy;
	enQuestionsLevel Meduim=enQuestionsLevel::Med;
	enQuestionsLevel Hard=enQuestionsLevel::Hard;
	enQuestionsLevel Mix=enQuestionsLevel::Mix;

};

short HowManyQuestions()
{
	short Number = 0;
	do
	{
		cout << "How many Questions do You Want To Answer: ";
		cin >> Number;
	} while (Number < 1 || Number>10);

	return Number;
}

enQuestionsLevel ReadQuestionsLevel()
{
	short enReadQuestionsLevel = 0;
	do
	{
		cout << "Enter Questions Level [1] Easy, [2] Medium, [3] Hard, [4] Mix : ";
		cin >> enReadQuestionsLevel;
	} while (enReadQuestionsLevel < 1 || enReadQuestionsLevel > 4);

	return enQuestionsLevel(enReadQuestionsLevel);
}

enQuestionsType ReadOpType()
{
	short OpType = 0;

	do
	{
		cout << "Enter Operation Type [1] Add, [2] Sub, [3]Mul, [4]Div, [5] Mix : ";
		cin >> OpType;
	} while (OpType < 1 || OpType > 5);

	return enQuestionsType(OpType);
}

string QuestionsLevel(enQuestionsLevel QuestionsLevel)
{
	string arr[4] = { "Easy","Medium"," Hard","Mix" };
	return arr[QuestionsLevel - 1];
}

string QuestionsType(enQuestionsType OpType)
{
	string arr[5] = { "Add","Sub","Mul","Div","Mix" };
	return arr[OpType - 1];
}

int RandomNum(int from, int to)
{
	return rand() % (to - from + 1) + from;
}


char OperationType(enQuestionsType OpType)
{
	switch (OpType)
	{
	case Add:
		return '+';
		break;
	case Sub:
		return '-';
		break;
	case Mul:
		return '*';
		break;
	case Dev:
		return '/';
		break;
	case MixOp:
		return OperationType(enQuestionsType(RandomNum(1, 4)));
		break;
	}
}

stQuizzLevel FillQuizLeveList(enQuestionsLevel Player ,stQuizzLevel &QuizzLevel)
{
	
	
	if (QuizzLevel.Easy== Player)
	{
		QuizzLevel.Num1 = RandomNum(1, 10);
		QuizzLevel.Num2 = RandomNum(1, 10);
	}
	else if (QuizzLevel.Meduim== Player)
	{
		QuizzLevel.Num1 = RandomNum(10, 50);
		QuizzLevel.Num2 = RandomNum(10, 50);
	}
	else if (QuizzLevel.Hard== Player)
	{
		QuizzLevel.Num1 = RandomNum(50, 100);
		QuizzLevel.Num2 = RandomNum(50, 100);
	}
	else
	{
		QuizzLevel.Num1 = RandomNum(1, 100);
		QuizzLevel.Num2 = RandomNum(1, 100);
	}

	return QuizzLevel;
}

stQuizzResults FillFinalResults(short NumberOfQuestions, short NumberOfRightAnswer, short NumberOfWrongAnswer, enQuestionsType OpType, enQuestionsLevel Level)
{
	stQuizzResults FinalResults;

	FinalResults.NumberOfQuestions = NumberOfQuestions;
	FinalResults.QuestionsLevel=QuestionsLevel(Level);
	FinalResults.OpType=QuestionsType(OpType);
	FinalResults.NumberOfRightQuestions = NumberOfRightAnswer;
	FinalResults.NumberOfWrongQuestions = NumberOfWrongAnswer;
	return FinalResults;
}

short ConverterOpType(short Num1,short Num2,enQuestionsType OpType)
{
	
	
	switch (OpType)
	{
	case enQuestionsType::Add:
		return Num1 + Num2;
		break;
	case enQuestionsType::Sub:
		return Num1 - Num2;
		break;
	case enQuestionsType::Mul:
		return Num1 * Num2;
		break;
	case enQuestionsType::Dev:
		return Num1 / Num2;
		break;
	case enQuestionsType::MixOp:
		return ConverterOpType(Num1, Num2, enQuestionsType(OperationType(OpType)));
		break;
	}
}

short PrintQuizzResults(short Num1, short Num2, enQuestionsType OpType)
{
	cout << Num1 << endl;
	cout << Num2 << "  " << OperationType(OpType)<<endl;
	cout << "________________\n";

	return ConverterOpType(Num1, Num2, OpType);
	

}

void PASSNOTPASS(stQuizzResults QuestionsResult)
{

	if (QuestionsResult.NumberOfRightQuestions > QuestionsResult.NumberOfWrongQuestions)
	{
		cout << "\n________________________________________\n";
		cout << "             YOU PASS :)                   \n";
		cout << "________________________________________\n";
		system("COLOR 2F");
	}

	else
	{
		cout << "\n________________________________________\n";
		cout << "             YOU FAIL :(                   \n";
		cout << "________________________________________\n";
		system("COLOR 4F");
	}
}

void PrintFinaQuizzResult(stQuizzResults QuizzResults)
{
	cout << "Number Of Questions      : " << QuizzResults.NumberOfQuestions << endl;
	cout << "Questions type           : " << QuizzResults.OpType << endl;
	cout << "Questions Level          : " << QuizzResults.QuestionsLevel << endl;
	cout << "Number Of Right Questions: " << QuizzResults.NumberOfRightQuestions << endl;
	cout << "Number Of Wrong Questions: " << QuizzResults.NumberOfWrongQuestions << endl;
	cout << "________________________________________\n";
}

void CheckIfAnswerRight(short UserAnswer, short Num1,short Num2,enQuestionsType OpType)
{
	short Result = ConverterOpType(Num1, Num2, OpType);
		if (UserAnswer == Result)
	{
		cout << "Right Answer :)\n\n";
		system("COLOR 2F");
	}

	else
	{
		cout << "Wrong Answer :(";
		system("COLOR 4F");
		cout << "\n\aThe right answer is: " << Result << endl;
	}
} 

stQuizzResults Quizz()
{
	short NumberOfQuestions = HowManyQuestions();
	short UserAnswer=0;
	short  NumberOfRightAnswer = 0, NumberOfWrongAnswer = 0;
	enQuestionsLevel enReadLevel = ReadQuestionsLevel();
	stQuizzLevel QuizzLevel;
	
	enQuestionsType enReadOpType = ReadOpType();


	for (int i = 1; i <= NumberOfQuestions; i++)
	{
		cout << endl;
		cout << "Question [" << i << "/" << NumberOfQuestions << "]\n";
		FillQuizLeveList(enReadLevel,QuizzLevel);
		
		short Num1 = QuizzLevel.Num1;
		short Num2 = QuizzLevel.Num2;

		short Result =PrintQuizzResults(Num1, Num2, enReadOpType);
		cin >> UserAnswer;
		CheckIfAnswerRight(UserAnswer, Num1, Num2, enReadOpType);

		if (UserAnswer == Result)
			NumberOfRightAnswer++;
		else if (UserAnswer != Result)
			NumberOfWrongAnswer++;
	}

	return FillFinalResults(NumberOfQuestions,NumberOfRightAnswer,NumberOfWrongAnswer, enReadOpType,enReadLevel);
}

void ScreenRest()
{
	system("COLOR 0F");
	system("CLS");
}

void PlayQuizz()
{
	char PlayAgain = 'y';

	do
	{
		ScreenRest();

		stQuizzResults QuizzResults = Quizz();
		PASSNOTPASS(QuizzResults);
		PrintFinaQuizzResult(QuizzResults);	

		cout << "Do you want play again: ";
		cin >> PlayAgain;

	} while (PlayAgain == 'y' || PlayAgain == 'Y');

}

int main()
{
	srand((unsigned)time(NULL));
	//PlayQuizz();
	char Plus = '+';
	short Num = 2;
	short Num2 = 4;
	short Result = Num << Plus << Num;
	cout << Result;
	return 0;
}
