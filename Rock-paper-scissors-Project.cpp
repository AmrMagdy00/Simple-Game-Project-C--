#include <iostream>
#include <cstdlib>
using namespace std;
int RandomNumber(int From, int To) {
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}

enum enGameChoise {
	Stone = 1,
	Paper = 2,
	Scissors = 3,

};
enum enWinner {
	PlayerWin = 1,
	ComputerWin = 2,
	Draw = 3,
};
enGameChoise ReadPlayerChoise() {
	short PlayerChoise;
	do {
		std::cout << "Your Choise : [1]:Stone, [2]:Paper, [3]:Scissors ? ";
		std::cin >> PlayerChoise;
	} while (PlayerChoise > 3 || PlayerChoise < 1);
	return (enGameChoise)PlayerChoise;

}
enGameChoise GetComputerChoise() {
	return (enGameChoise)RandomNumber(1, 3);
};
struct stRoundInfo {
	short Rounds;
	enGameChoise PlayerChoise;
	enGameChoise ComputerChoise;
	enWinner GamesResult;
	string PlayerName;
};
enWinner HowWonTheRound(stRoundInfo RoundInfo) {
	if (RoundInfo.PlayerChoise == RoundInfo.ComputerChoise) {
		return enWinner::Draw;
	}

	switch (RoundInfo.ComputerChoise) {
	case enGameChoise::Paper:
		if (RoundInfo.PlayerChoise == enGameChoise::Stone) {
			return enWinner::ComputerWin;
			break;
		}
	case enGameChoise::Scissors:
		if (RoundInfo.PlayerChoise == enGameChoise::Paper) {
			return enWinner::ComputerWin;
			break;
		}

	case enGameChoise::Stone:
		if (RoundInfo.PlayerChoise == enGameChoise::Scissors) {
			return enWinner::ComputerWin;
			break;
		}
	}
	return enWinner::PlayerWin;
}

struct stResultTimes {
	short PlayerWinTimes = 0;
	short	ComputerWinTimes = 0;
	short	DrawTimes = 0;
	short HowManyRounds = 0;
};

void SystemReset() {
	system("color 0");
	system("cls");
}
short ReadHowManyRounds() {
	SystemReset();
	short HowManyRounds;
	do {
		std::cout << "How Many rounds You Want To Play [From 1 To 10]" << endl;
		std::cin >> HowManyRounds;
	} while (HowManyRounds > 10 || HowManyRounds < 0);
	return HowManyRounds;
};
string WinnerNamer(enWinner Winner) {
	string arrWinnerName[3]{ "Player","Computer","No Winner" };
	return arrWinnerName[Winner - 1];
}
string choiseName(enGameChoise Choise) {
	string ChoiseName[3]{ "Stone" ,"Paper" ,"Scissors" };
	return ChoiseName[Choise - 1];
}

void SystemColor(stRoundInfo RoundInfo) {
	if (RoundInfo.GamesResult == enWinner::ComputerWin) {
		system("color 4f");
	}
	else 	if (RoundInfo.GamesResult == enWinner::PlayerWin) {
		system("color 2f");
	}
	else {
		system("color 6e");
	}
}
void PrintRoundDetails(stRoundInfo RoundInfo) {
	SystemColor(RoundInfo);
	std::cout << "\n------------- [Round " << RoundInfo.Rounds << "] -------------\n" << endl;
	std::cout << "Player Choice : " << choiseName(RoundInfo.PlayerChoise) << endl;
	std::cout << "Computer Choice : " << choiseName(RoundInfo.ComputerChoise) << endl;
	std::cout << "Round Winner : " << RoundInfo.PlayerName << endl;
	std::cout << "\n--------------------------------------" << endl;
}
string FinalWinner(short NoOneWinCount, short ComputerWinCount, short UserWinCount) {
	if (UserWinCount > ComputerWinCount) {
		return "User";
	}
	else if (ComputerWinCount > UserWinCount) {
		return "Computer";
	}
	else { return "No Winner"; }
};
void GameOver() {
	cout << "\n\n" << endl;
	cout << "\t\t-------------------------------------------------------------\n" << endl;
	cout << "\t\t\t\t +++ G A M E   O V E R +++\n" << endl;
	cout << "\t\t-------------------------------------------------------------\n" << endl;
}
void PrintFinalResult(short Rounds, short PlayerWinTimes, short ComputerWinTimes, short DrawTimes) {
	stResultTimes ResultTimes;
	system("color 5C");
	GameOver();
	cout << "\t\t-----------------------[Game Results]------------------------\n" << endl;
	cout << "\t\tGames Rounds        : " << Rounds << endl;
	cout << "\t\tPlayer Won Times    : " << PlayerWinTimes << endl;
	cout << "\t\tComputer Won Times  : " << ComputerWinTimes << endl;
	cout << "\t\tDraw Times          : " << DrawTimes << endl;
	cout << "\t\tFinal Winner        : " << FinalWinner(ResultTimes.DrawTimes, ResultTimes.ComputerWinTimes, ResultTimes.PlayerWinTimes) << endl;
	cout << "\t\t-------------------------------------------------------------\n" << endl;
}



void PlayGame() {
	short PlayerWinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
	stRoundInfo RoundInfo;
	stResultTimes ResultTimes;
	char PlayAgain = 'y';
	do {
		SystemReset();
		short Rounds = ReadHowManyRounds();
		for (short Round = 1; Round <= Rounds; Round++) {
			std::cout << "\nRound [" << Round << "] Begins : \n" << endl;
			RoundInfo.Rounds = Round;
			RoundInfo.PlayerChoise = ReadPlayerChoise();
			RoundInfo.ComputerChoise = GetComputerChoise();
			RoundInfo.GamesResult = HowWonTheRound(RoundInfo);
			RoundInfo.PlayerName = WinnerNamer(RoundInfo.GamesResult);
			PrintRoundDetails(RoundInfo);

			if (RoundInfo.GamesResult == enWinner::PlayerWin) {
				PlayerWinTimes++;
			}
			else if (RoundInfo.GamesResult == enWinner::ComputerWin) {
				ComputerWinTimes++;
			}
			else {
				DrawTimes++;
			}


		}
		PrintFinalResult(Rounds, PlayerWinTimes, ComputerWinTimes, DrawTimes);



		std::cout << "Do You Want To Play Again ? " << endl;
		std::cin >> PlayAgain;

	} while (PlayAgain == 'y' || PlayAgain == 'Y');

}

int main()
{
	srand((unsigned)time(NULL));

	PlayGame();
}

