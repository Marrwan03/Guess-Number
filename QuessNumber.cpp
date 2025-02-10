#include <iostream>
using namespace std;
void ControlGuess();
string Tabs(short NumberOfTabs)
{
    string t = "";
    for (int i = 1; i < NumberOfTabs; i++)
    {
        t = t + "\t";
        cout << t;
    }
    return t;
}
enum enGameLevel { Easy = 1, Med = 2, Hard = 3 };
struct stRound {
    short NumberOfRound = 0;
    enGameLevel GameLevel;
    short nRandom[10];
    short UserAswer = 0;
    bool Result;
};
struct stListResult {
    short NumberOfRightAnswer = 0;
    short NumberOfWrongAnswer = 0;
    bool Pass;
};
short RandomNumber(short From, short To)
{
    short Random = rand() % (To - From + 1) + From;
    return Random;
}
enGameLevel ReadGameLevel()
{
    short Choice;
    do
    {
        cout << "Enter Guess level [1] = Easy, [2] = Med, [3] = Hard ? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);
    return (enGameLevel)Choice;
}
string StringGameLevel(short Choice)
{
    string arrGameLevel[3] = { "Easy", "Mediem", "Hard" };
    return arrGameLevel[Choice - 1];
}
short HowManyRound()
{
    short Limit = 0;
    do
    {
        cout << "How Many round do you want to play ? [1 : 10] ? ";
        cin >> Limit;
    } while (Limit < 1 || Limit > 10);
    return Limit;
}
void WelcomeUser(enGameLevel Choice)
{

    switch (Choice)
    {
    case enGameLevel::Easy:
        cout << "\n\n\t\t\t\t[Note : Enter The number is between [1 - 10] ].\n\n";
        break;
    case enGameLevel::Med:
        cout << "\n\n\t\t\t\t[Note : Enter The number is between [10 - 30] ].\n\n";
        break;
    case enGameLevel::Hard:
        cout << "\n\n\t\t\t\t[Note : Enter The number is between [30 - 60] ].\n\n";
        break;
    }
}
void GetRandomNumberAndGLevel(stRound& Round, short NumberArr)
{

    switch (Round.GameLevel)
    {
    case enGameLevel::Easy:
        Round.nRandom[NumberArr] = RandomNumber(1, 10);
        break;
    case enGameLevel::Med:
        Round.nRandom[NumberArr] = RandomNumber(10, 30);
        break;
    case enGameLevel::Hard:
        Round.nRandom[NumberArr] = RandomNumber(30, 60);
        break;
    }
}
void FillRandomNumbers(stRound& Round)
{
    for (short i = 0; i < Round.NumberOfRound; i++)
    {
        GetRandomNumberAndGLevel(Round, i);
    }
}
void ColorScreen(bool Right)
{
    if (Right)
    {
        system("color 2F");
    }
    else
    {
        system("color 4F");
        cout << "\a";
    }
}
void PrintQuestion(stRound Round, short NumberArr)
{
    cout << "\n\n\tGuess [" << NumberArr + 1 << "/" << Round.NumberOfRound << "].\n";
    cout << "Please, Enter your guess Number ? ";
}
short AnswerUser()
{
    short Answer;
    cin >> Answer;
    return Answer;
}
short EnterLowerNumber(short ChanceOne)
{
    cout << "\n======================";
    cout << "\t\nYou have one chance\n";
    cout << "======================\n";
    cout << "Enter a number lower of this Number [" << ChanceOne << "] ? ";
    cin >> ChanceOne;
    return ChanceOne;
}
short EnterUpperNumber(short ChanceOne)
{
    cout << "\n======================";
    cout << "\t\nYou have one chance\n";
    cout << "======================\n";
    cout << "Enter a number Upper of this Number [" << ChanceOne << "] ? ";
    cin >> ChanceOne;
    return ChanceOne;
}
void GiveUserOneChance(stRound& Round, short NumberArr)
{
    if (Round.UserAswer > Round.nRandom[NumberArr])
    {
        Round.UserAswer = EnterLowerNumber(Round.UserAswer);

    }
    else if (Round.UserAswer < Round.nRandom[NumberArr])
    {
        Round.UserAswer = EnterUpperNumber(Round.UserAswer);

    }
}
bool chickUserAnswer(stRound Round, short NumberArr)
{
    if (Round.UserAswer == Round.nRandom[NumberArr])
    {
        return true;
    }
    return false;
}
short LimitAnswer(stRound Round)
{
    if (Round.GameLevel == enGameLevel::Easy)
    {
        while (Round.UserAswer < 0 || Round.UserAswer > 10)
        {
            cout << "\n[The entered number is outside the levelGame].\n";
            cout << "Please enter number between [1 - 10] ? ";
            cin >> Round.UserAswer;
        }
        return Round.UserAswer;
    }
    else if (Round.GameLevel == enGameLevel::Med)
    {
        while (Round.UserAswer < 10 || Round.UserAswer > 30)
        {
            cout << "\n[The entered number is outside the levelGame].\n";
            cout << "Please enter number between [10 - 30] ? ";
            cin >> Round.UserAswer;
        }
        return Round.UserAswer;
    }
    else
    {
        while (Round.UserAswer < 30 || Round.UserAswer > 60)
        {
            cout << "\n[The entered number is outside the levelGame].\n";
            cout << "Please enter number between [30 - 60] ? ";
            cin >> Round.UserAswer;
        }
        return Round.UserAswer;
    }

}
string IsPass(bool Pass)
{
    if (Pass)
    {
        return "Pass :-)";
    }
    else
    {
        return "Fail :-(";
    }
}
stListResult AskUserAndCorrectAnswer(stRound& Round)
{
    stListResult Result;
    for (short i = 0; i < Round.NumberOfRound; i++)
    {
        PrintQuestion(Round, i);
        Round.UserAswer = AnswerUser();
        Round.UserAswer = LimitAnswer(Round);
        GiveUserOneChance(Round, i);
        if (chickUserAnswer(Round, i))
        {
            cout << "\nRight Answer :-)\n";
            Round.Result = true;
            Result.NumberOfRightAnswer++;
        }
        else
        {
            cout << "\nWrong Answer :-(\n";
            cout << "The Right answer is : " << Round.nRandom[i];
            Round.Result = false;
            Result.NumberOfWrongAnswer++;
        }
        ColorScreen(Round.Result);
    }
    Result.Pass = (Result.NumberOfRightAnswer >= Result.NumberOfWrongAnswer);
    return Result;
}
void PrintFinalyResult(stListResult Result)
{
    cout << "\n\n\n\t\t\t======================================\n";
    cout << "\t\t\t\tPlayer is: " << IsPass(Result.Pass) << endl;
    ColorScreen(Result.Pass);
    cout << "\t\t\t======================================\n\n";
}
void ResetScreen()
{
    system("cls");
    system("color 0F");
}
void PrintFinalResult(stListResult Result, stRound Round)
{
    cout << "\n\t\t\t======================================\n";
    cout << "\t\t\tNumber Of Round is       : " << Round.NumberOfRound << endl;
    cout << "\t\t\tGuess Level is           : " << StringGameLevel(Round.GameLevel) << endl;
    cout << "\t\t\tNumber Of Right Answer is: " << Result.NumberOfRightAnswer << endl;
    cout << "\t\t\tNumber Of Wrong Answer is: " << Result.NumberOfWrongAnswer << endl;
    cout << "\t\t\t======================================\n";
}

void StartGame()
{
    stRound Round;
    stListResult Result;
    Round.NumberOfRound = HowManyRound();
    Round.GameLevel = ReadGameLevel();
    FillRandomNumbers(Round);
    WelcomeUser(Round.GameLevel);
    Result = AskUserAndCorrectAnswer(Round);
    PrintFinalyResult(Result);
    PrintFinalResult(Result, Round);
}
void PlayGuessNumber()
{
    char Again;
    do
    {
        ResetScreen();
        StartGame();
        cout << "\n\t\t\tDo you want play again? [Y | N] ? ";
        cin >> Again;
    } while (toupper(Again) == 'Y');
}



enum enPlayers { Marwan = 1, Khalid = 2, Tareq = 3, NoOne = 4 };
enum enWinner { wMarwan = 1, wKhalid = 2, wTareq = 3, wNoOne = 4 };
struct stRoundInfo {
    short NumberOfRound;
    short YourAnswer;
    short WrongAnswer = 0;
    enGameLevel GameLevel;
    bool Result;
};
struct stResult
{
    enWinner WinnerGame;
    string stringWinnerName;
};
struct stPersonsGuess {
    short randomNumber[10];
    short GuessMarwan[10];
    short CountRightAnswerMarwan = 0;
    short CountWrongAnswerMarwan = 0;
    short GuessKhalid[10];
    short CountRightAnswerKhalid = 0;
    short CountWrongAnswerKhalid = 0;
    short GuessTareq[10];
    short CountRightAnswerTareq = 0;
    short CountWrongAnswerTareq = 0;
};
string StringWinnerName(short Winner)
{
    string arrWinner[4] = { "Marwan", "Khalid", "Tareq", "NoOne" };
    return arrWinner[Winner - 1];
}
stPersonsGuess GetRandomNumberToPersons(stRoundInfo Round, stPersonsGuess PersonsGuess, short NumberArr)
{
    switch (Round.GameLevel)
    {
    case enGameLevel::Easy:
        PersonsGuess.randomNumber[NumberArr] = RandomNumber(1, 10);
        PersonsGuess.GuessMarwan[NumberArr] = RandomNumber(1, 10);
        PersonsGuess.GuessKhalid[NumberArr] = RandomNumber(1, 10);
        PersonsGuess.GuessTareq[NumberArr] = RandomNumber(1, 10);
        break;
    case enGameLevel::Med:
        PersonsGuess.randomNumber[NumberArr] = RandomNumber(10, 30);
        PersonsGuess.GuessMarwan[NumberArr] = RandomNumber(10, 30);
        PersonsGuess.GuessKhalid[NumberArr] = RandomNumber(10, 30);
        PersonsGuess.GuessTareq[NumberArr] = RandomNumber(10, 30);
        break;
    case enGameLevel::Hard:
        PersonsGuess.randomNumber[NumberArr] = RandomNumber(30, 60);
        PersonsGuess.GuessMarwan[NumberArr] = RandomNumber(30, 60);
        PersonsGuess.GuessKhalid[NumberArr] = RandomNumber(30, 60);
        PersonsGuess.GuessTareq[NumberArr] = RandomNumber(30, 60);
        break;
    }
    return PersonsGuess;
}
stPersonsGuess FillRandomNumberToPersons(stRoundInfo Round)
{
    stPersonsGuess PGuess;
    for (short i = 0; i < Round.NumberOfRound; i++)
    {
        PGuess = GetRandomNumberToPersons(Round, PGuess, i);
    }
    return PGuess;
}

enWinner HowWinTheGame(stPersonsGuess PersonsGuess)
{
    if (PersonsGuess.CountRightAnswerMarwan > PersonsGuess.CountRightAnswerKhalid)
    {
        if (PersonsGuess.CountRightAnswerMarwan > PersonsGuess.CountRightAnswerTareq)
        {
            return enWinner::wMarwan;
        }
        else
        {
            return enWinner::wTareq;
        }

    }
    else if (PersonsGuess.CountRightAnswerKhalid > PersonsGuess.CountRightAnswerTareq)
    {
        return enWinner::wKhalid;
    }
    else if (PersonsGuess.CountRightAnswerKhalid < PersonsGuess.CountRightAnswerTareq)
    {
        return enWinner::wTareq;
    }
    else {
        return enWinner::wNoOne;
    }
}
void FillCounterRightANdWrongAnswer(stRoundInfo Round, stPersonsGuess& PGuess, short NumberArr)
{
    if (PGuess.GuessKhalid[NumberArr] == PGuess.randomNumber[NumberArr])
    {
        PGuess.CountRightAnswerKhalid++;
    }
    else
    {
        PGuess.CountWrongAnswerKhalid++;
    }
    if (PGuess.GuessMarwan[NumberArr] == PGuess.randomNumber[NumberArr])
    {
        PGuess.CountRightAnswerMarwan++;
    }
    else
    {
        PGuess.CountWrongAnswerMarwan++;
    }
    if (PGuess.GuessTareq[NumberArr] == PGuess.randomNumber[NumberArr])
    {
        PGuess.CountRightAnswerTareq++;
    }
    else
    {
        PGuess.CountWrongAnswerTareq++;
    }
}
enPlayers FillQuestion(stRoundInfo& Round, stPersonsGuess PGuess, short NumberArr)
{
    cout << "\n\nGuess: (" << NumberArr + 1 << ") is: " << PGuess.randomNumber[NumberArr] << endl;
    cout << "\n[1]Marwan is: (" << PGuess.GuessMarwan[NumberArr] << "),  ";
    cout << "\t[2]Khalid is: (" << PGuess.GuessKhalid[NumberArr] << "),  ";
    cout << "\t[3]Tareq is: (" << PGuess.GuessTareq[NumberArr] << "),  ";
    cout << "\t[4]NoOne.\n";
    do
    {
        cout << "\n\tChoose The Right Guess Answer [1, 4]: ";
        cin >> Round.YourAnswer;
    } while (Round.YourAnswer < 1 || Round.YourAnswer  >4);
    return (enPlayers)Round.YourAnswer;
}
bool ChickYourChoice(stRoundInfo& Round, stPersonsGuess& PGuess, short NumberArr)
{
    switch (Round.YourAnswer)
    {
    case enPlayers::Khalid:
    {
        if (PGuess.GuessKhalid[NumberArr] == PGuess.randomNumber[NumberArr])
        {

            Round.Result = true;

            return true;
        }
        else
        {
            Round.Result = false;
            Round.WrongAnswer++;

            return false;
        }
    }
    case enPlayers::Marwan:
    {
        if (PGuess.GuessMarwan[NumberArr] == PGuess.randomNumber[NumberArr])
        {

            Round.Result = true;
            return true;
        }
        else
        {
            Round.Result = false;
            Round.WrongAnswer++;
            return false;
        }
    }
    case enPlayers::Tareq:
    {
        if (PGuess.GuessTareq[NumberArr] == PGuess.randomNumber[NumberArr])
        {

            Round.Result = true;
            return true;
        }
        else
        {
            Round.Result = false;
            Round.WrongAnswer++;
            return false;
        }
    }
    case enPlayers::NoOne:
    {
        if (PGuess.GuessKhalid[NumberArr] != PGuess.randomNumber[NumberArr] &&
            PGuess.GuessMarwan[NumberArr] != PGuess.randomNumber[NumberArr] &&
            PGuess.GuessTareq[NumberArr] != PGuess.randomNumber[NumberArr])
        {
            Round.Result = true;
            return true;
        }
        else
        {
            Round.Result = false;
            Round.WrongAnswer++;
            return false;
        }
    }
    }
}
void PrintRightAnswer(bool Result, stPersonsGuess PGuess, short NumberArr)
{

    if (!Result)
    {
        if (PGuess.GuessKhalid[NumberArr] == PGuess.randomNumber[NumberArr])
        {
            cout << "\nThe Right Answer is: Khalid.\n";
        }
        if (PGuess.GuessMarwan[NumberArr] == PGuess.randomNumber[NumberArr])
        {
            cout << "\nThe Right Answer is: Marwan.\n";
        }
        if (PGuess.GuessTareq[NumberArr] == PGuess.randomNumber[NumberArr])
        {
            cout << "\nThe Right Answer is: Tareq.\n";
        }
        if (PGuess.GuessKhalid[NumberArr] != PGuess.randomNumber[NumberArr] &&
            PGuess.GuessMarwan[NumberArr] != PGuess.randomNumber[NumberArr] &&
            PGuess.GuessTareq[NumberArr] != PGuess.randomNumber[NumberArr])
        {
            cout << "\nThe Right Answer is: NoOne.\n";
        }
    }
}

int YourBlock()
{
    ResetScreen();
    cout << "\n\n\n\n\n";
    cout << Tabs(3) << "I have disappointed you.\n\n\n";
    cout << Tabs(3) << "How can you call yourself a referee when you are a cheater ?\n \n";
    cout << Tabs(3) << "Go and find yourself another job other than refereeing.\n\n";
    cout << Tabs(3) << "I think plumbing is right for you.\n\n";
    cout << Tabs(3) << "Yes, I am harsh towards you because you deserve it.";
    cout << "\n\n\n\n";

    return 0;
}
void AskAndCoreectAnswer(stRoundInfo& Round, stPersonsGuess& PGuess)
{
    char Again;
    for (short i = 0; i < Round.NumberOfRound; i++)
    {
        FillQuestion(Round, PGuess, i);
        ChickYourChoice(Round, PGuess, i);
        ColorScreen(Round.Result);
        PrintRightAnswer(Round.Result, PGuess, i);
        FillCounterRightANdWrongAnswer(Round, PGuess, i);
        if (Round.WrongAnswer == 2)
        {
            YourBlock();
            cout << Tabs(3) << "Do you want play again? [Y | N]? ";
            cin >> Again;
            if (toupper(Again) == 'Y')
            {
                ControlGuess();
            }
            else
            {
                break;
            }
        }

    }

}
stResult FillResult(stRoundInfo Round, stPersonsGuess PGuess)
{
    stResult Result;
    Result.WinnerGame = HowWinTheGame(PGuess);
    Result.stringWinnerName = StringWinnerName(Result.WinnerGame);
    return Result;
}
void PrintResult(stRoundInfo Round, stPersonsGuess PGuess, stResult Result)
{
    Result = FillResult(Round, PGuess);
    cout << "\n\n\n";
    cout << Tabs(3) << "==============================================\n";
    cout << Tabs(3) << " Winner Game: " << Result.stringWinnerName << endl;
    cout << Tabs(3) << "==============================================\n\n\n";
    cout << Tabs(3) << "===================[Result]===================\n";

    cout << Tabs(3) << "Number Of Round    : " << Round.NumberOfRound << endl;

    cout << Tabs(3) << "Guess Level        : " << StringGameLevel(Round.GameLevel) << endl;
    cout << Tabs(3) << "Right Guess Khalid : " << PGuess.CountRightAnswerKhalid << endl;
    cout << Tabs(3) << "Wrong Guess Khalid : " << PGuess.CountWrongAnswerKhalid << endl;

    cout << Tabs(3) << "Right Guess Marwan : " << PGuess.CountRightAnswerMarwan << endl;
    cout << Tabs(3) << "Wrong Guess Marwan : " << PGuess.CountWrongAnswerMarwan << endl;

    cout << Tabs(3) << "Right Guess Tareq  : " << PGuess.CountRightAnswerTareq << endl;
    cout << Tabs(3) << "wrong Guess Tareq  : " << PGuess.CountWrongAnswerTareq << endl;

    cout << Tabs(3) << "==============================================\n";
}
void ControlGuess()
{
    ResetScreen();
    stRoundInfo Round;
    stPersonsGuess PGuess;
    Round.NumberOfRound = HowManyRound();
    Round.GameLevel = ReadGameLevel();
    PGuess = FillRandomNumberToPersons(Round);
    AskAndCoreectAnswer(Round, PGuess);
    stResult Result = FillResult(Round, PGuess);
    PrintResult(Round, PGuess, Result);
}
void PlayControlGuess()
{
    char Again;
    do
    {
        ResetScreen();
        ControlGuess();
        cout << "\n\t\t\tDo you want play again? [Y | N]? ";
        cin >> Again;
    } while (toupper(Again) == 'Y');
}
void PrintTheIntroduction()
{

    system("color 0F");
    cout << endl;
    cout << Tabs(3) << "You are now in control of the game\n\n";
    cout << Tabs(2) << "The game involves guessing numbers\n\n";
    cout << Tabs(2) << "And you, the referee, calculate the number of rhubarb and the level of guessing\n\n";
    cout << Tabs(2) << "And choose the correct option\n\n";
    cout << Tabs(2) << "If you answer incorrectly more than twice, you will be expelled from the game.\n\n\n\n";
    cout << Tabs(3) << "[Start Game]\n";
    cout << Tabs(3) << "Enter anykey for play.";
    system("pause>0");
}

int main()
{
    PrintTheIntroduction();
    PlayControlGuess();

    return 0;

}