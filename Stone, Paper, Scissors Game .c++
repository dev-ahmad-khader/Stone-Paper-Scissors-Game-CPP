#include <iostream>
#include <cmath>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

enum enChoice
{
  Stone = 1,
  Paper,
  Scissors
};
enum enResult
{
  Win = 1,
  Draw,
  Lose
};
enum enFinalWinner
{
  User = 1,
  Computer,
  Nobody
};

struct stRound
{
  enChoice PlayerChoiceInRound;
  enChoice ComputerChoiceInRound;
  enResult RoundResult;
  enFinalWinner RoundWinner;
};
struct stGame
{
  int TotalRounds = 0;
  int WinsCounter = 0;
  int LosesCounter = 0;
  int DrawsCounter = 0;
  enFinalWinner FinalWinner;
};

int RandomNumber(int From, int To)
{
  return rand() % (To - From + 1) + From;
}

int ReadRounds()
{
  int num;
  cout << "\nHow many rounds do you want to play? ";
  cin >> num;
  while (num < 1 || num > 10)
  {
    cout << "How many rounds do you want to play (1 to 10) ? ";
    cin >> num;
  }
  return num;
}

int ReadChoiceNumber()
{
  int num;
  do
  {
    cout << "Your choice: [1] Stone , [2] Paper , [3] Scissors ? ";
    cin >> num;
  } while (num < 1 || num > 3);
  return num;
}

enChoice ReadGameChoice(int ChoiceNumber)
{
  return enChoice(ChoiceNumber);
}

string GetChoiceString(enChoice Choice)
{
  string stringChoices[] = {"Stone", "Paper", "Scissors"};
  return stringChoices[Choice - 1];
}

enResult GetRoundResult(stRound RoundInfo)
{
  if (RoundInfo.PlayerChoiceInRound == RoundInfo.ComputerChoiceInRound)
  {
    return Draw;
  }
  if ((RoundInfo.PlayerChoiceInRound == Stone && RoundInfo.ComputerChoiceInRound == Scissors) || (RoundInfo.PlayerChoiceInRound == Paper && RoundInfo.ComputerChoiceInRound == Stone) || (RoundInfo.PlayerChoiceInRound == Scissors && RoundInfo.ComputerChoiceInRound == Paper))
  {
    return Win;
  }
  return Lose;
}

string GetResultString(enResult Result)
{
  string stringResults[] = {"Win", "Draw", "Lose"};
  return stringResults[Result - 1];
}

enFinalWinner GetRoundWinner(enResult RoundResult)
{
  if (RoundResult == Win)
    return User;
  else if (RoundResult == Lose)
    return Computer;
  else
    return Nobody;
}

enFinalWinner GetGameWinner(int WinsCounter, int LosesCounter, int DrawsCounter)
{
  if (WinsCounter > LosesCounter)
    return User;
  else if (WinsCounter < LosesCounter)
    return Computer;
  else
    return Nobody;
}

string GetRoundWinnerString(enFinalWinner RoundWinner)
{
  string stringWinner[] = {"Player", "Computer", "No Winner"};
  return stringWinner[RoundWinner - 1];
}

void SetWinnerScreenColor(enFinalWinner winner)
{
  switch (winner)
  {
  case User:
    system("color 2F");
    break;
  case Computer:
    system("color 4F");
    cout << "\a";
    break;
  case Nobody:
    system("color E0");
    break;
  }
}

void PrintRoundResult(stRound &RoundInfo, int RoundNumber)
{
  SetWinnerScreenColor(RoundInfo.RoundWinner);

  cout << "\n------------------------------------------------\n\n";
  cout << "------------------- Round [" << RoundNumber << "]-------------------" << endl;
  cout << "player choice : " << GetChoiceString(RoundInfo.PlayerChoiceInRound) << endl;
  cout << "computer choice : " << GetChoiceString(RoundInfo.ComputerChoiceInRound) << endl;
  cout << "PlayRound winner : " << GetRoundWinnerString(RoundInfo.RoundWinner) << endl;
  cout << "------------------------------------------------" << endl;
}

void PrintGameResult(stGame GameInfo)
{
  SetWinnerScreenColor(GameInfo.FinalWinner);

  cout << "\n         ----------------------------------------------------------\n";
  cout << "         ----------------------[ GAME OVER! ]----------------------\n";
  cout << "         ----------------------------------------------------------\n\n";
  cout << "         _____________________[ Game results ]______________________\n";
  cout << "         Game rounds         : " << GameInfo.TotalRounds << endl;
  cout << "         Player won times    : " << GameInfo.WinsCounter << endl;
  cout << "         computer won times  : " << GameInfo.LosesCounter << endl;
  cout << "         Draw times          : " << GameInfo.DrawsCounter << endl;
  cout << "         Final winner        : " << GetRoundWinnerString(GameInfo.FinalWinner) << endl;
  cout << "         _____________________________________________________________" << endl;
}

void PlayRound(stRound &RoundInfo, stGame &GameInfo, int RoundNumber)
{
  cout << "Round [" << RoundNumber << "] begins : " << endl;
  RoundInfo.PlayerChoiceInRound = ReadGameChoice(ReadChoiceNumber());
  RoundInfo.ComputerChoiceInRound = ReadGameChoice(RandomNumber(1, 3));
  RoundInfo.RoundResult = GetRoundResult(RoundInfo);
  RoundInfo.RoundWinner = GetRoundWinner(RoundInfo.RoundResult);

  if (RoundInfo.RoundResult == Win)
  {
    GameInfo.WinsCounter++;
  }
  else if (RoundInfo.RoundResult == Lose)
  {
    GameInfo.LosesCounter++;
  }
  else
  {
    GameInfo.DrawsCounter++;
  }

  PrintRoundResult(RoundInfo, RoundNumber);
}

void ResetScreen()
{
  system("color 0F");
  system("cls");
}

stGame PlayGame()
{
  stGame GameInfo;
  stRound RoundInfo;
  GameInfo.TotalRounds = ReadRounds();

  for (int RoundNumber = 1; RoundNumber <= GameInfo.TotalRounds; RoundNumber++)
  {
    PlayRound(RoundInfo, GameInfo, RoundNumber);
  }
  GameInfo.FinalWinner = GetGameWinner(GameInfo.WinsCounter, GameInfo.LosesCounter, GameInfo.DrawsCounter);
  return GameInfo;
}

bool WannaPlayAgain()
{
  string answer = "n";
  do
  {
    cout << "\nDo you want to play again? (Y/N): ";
    cin >> answer;
  } while (answer != "y" && answer != "Y" && answer != "n" && answer != "N");
  if (answer == "y" || answer == "Y")
    return true;
  else
    return false;
}

void StartGame()
{
  stGame GameInfo;
  do
  {
    ResetScreen();
    cout << "==============================================\n";
    cout << "     Welcome to Stone - Paper - Scissors!     \n";
    cout << "==============================================\n\n";
    GameInfo = PlayGame();
    PrintGameResult(GameInfo);
  } while (WannaPlayAgain());
}

int main()
{
  srand((unsigned)time(0));
  StartGame();
  return 0;
}
