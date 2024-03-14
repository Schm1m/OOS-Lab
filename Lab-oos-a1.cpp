
#include <string>
#include <ctime>
#include <iostream>

using namespace std;

// Aufzählungstyp für wählbare Objekte
// STEIN - 0, SCHERE - 1, PAPIER - 2
enum class Object
{
    ROCK,
    SCISSORS,
    PAPER
};

// Aufzählungstyp für mögliche Spielausgänge
enum class Result
{
    PLAYER_ONE_WINS,
    PLAYER_TWO_WINS,
    DRAW
};

// Struktur für einen Spieler bestehend aus Name und Wahl des Spielers
struct Player
{
    string name;
    Object choice;
};

// Name des Spielers eingeben
string insert_name()
{

    // HIER programmieren:
    // Den Namen des Spielers von der Konsole einlesen und zurückgeben
    // Tip: für das Einlesen eines Strings gibt es eine bestimmte Funktion, siehe auch Vorlesung Folie "Eine Zeile als String einlesen"
    cout << "Name des Spielers: ";
    string name;
    cin.clear();
    getline(cin, name);
    return name;

}

Object determine_choice(string choice)
{
    if (choice.compare("CoderunnerTestValueROCK") == 0)
    {
        return Object::ROCK;
    }
    else if (choice.compare("CoderunnerTestValueSCISSORS") == 0)
    {
        return Object::SCISSORS;
    }
    else if (choice.compare("CoderunnerTestValuePAPER") == 0)
    {
        return Object::PAPER;
    }
    else
    {
        // Den Computer zufällig waehlen lassen.

        // HIER beantworten Sie folgende Fragen:
        // Was bewirkt die funktion srand?
            // srand() setzt den Seed für die rand() funktion,
            // sozusagen eine art Anfangswert aus welchem dann alle
            // pseudo-zufälligen zahlen berechnet werden
        // Warum wird hier die Zeit (time) als Eingabe für die Funktion srand verwendet?
            // damit sich der seed für die rand() funktion bei jedem programmstart
            // verändert und nicht so leicht berechnet werden kann
            // ( wenn man den seed kennt, kann man alle Zufallszahlen vorraussagen )
        // Wie funktioniert die funktion rand?
            // rand() gibt basieren auf den in srand() gegebenen seed
            // ( oder 0 wenn keiner gegeben ) eine ganze Zahl zwischen
            // 0 und RAND_MAX ( in cstdlib definiert, minimum 32767, je nach libary unterschiedlich ) zurück
        // Warum wird hier modulo 3 verwendet?
            // für das Spiel brauchen wir eine zufällige antwort des computers
            // zwischen 0-2 ( die Enums der antworten ), damit die random generierte Zahl
            // innerhalb diese Bereiches liegt nehmen wir den modulo 3 um
            // von der random generierten Zahl so oft 3 abzuziehen bis eine Zahl < 3 vorhanden ist.

        srand(static_cast<int>(time(nullptr)));
        int choice = rand() % 3;
        return static_cast<Object>(choice);
    }
}

// Die Wahl von Stein etc. als String zurückgeben lassen
string get_name(Object object)
{

    // HIER programmieren:
    // Abhängig vom vorliegenden Object einen entsprechenden String zurückgeben.
    // z.B: Wenn Object dem Wert Object::ROCK entspricht, dann String "Stein" zurückgeben

    switch (object)
    {
    case Object::ROCK:
        return "Stein";
    case Object::PAPER:
        return "Papier";
    case Object::SCISSORS:
        return "Schere";
    default:
        return "undefined"; // workaround 2 for error described in function "determine_result()"
    }

}

// Einen Text mit dem Namen des Spielers und seiner Wahl ausgeben
void print_choice(Player player)
{

    // HIER programmieren:
    // Auf der Konsole ausgeben, für welches Object sich der Spieler entschieden hat.
    // z.B.: "Computer hat das Object Schere gewählt"
    // TIP: Nutzen sie hierzu die Funktion get_name

    cout << player.name << " hat das Objekt " << get_name(player.choice) << " gewählt" << endl;
    
}

// Die Wahl des Spielers abfragen
Object choose()
{

    // HIER programmieren:
    // Die Wahl des Spielers von der Konsole einlesen und zurückgeben
    // Stellen sie sicher, dass es sich um eine gültige Wahl handelt!
    // TIP: Nutzen Sie dazu eine geeignete Schleife. Siehe auch Vorlesung Folie "Annehmende Schleifenanweisungen – Do"
    cout << "Bitte Objektwahl eingeben (1 = Stein, 2 = Schere, 3 = Papier): ";
    int input;
    do
    {
        cin >> input;
    } while (input < 1 || input > 3); // ask for an valid input as long as the input is invalid
    return static_cast<Object>(input - 1);
}

Result determine_result(Player player_1, Player player_2)
{

    // HIER programmieren:
    // Vergleichen Sie die gewählten Objekte, ermitteln sie das Spielergebnis und geben sie es zurück.
    // TIP: Wenn Sie für den Vergleich mit ganzene Zahlen _rechnen_ wollen, dann nutzen sie den static_cast, siehe auch Vorlesung Folie "Casts in C++: Static_cast"
    int compChoice = static_cast<int>(player_1.choice);
    int playerChoice = static_cast<int>(player_2.choice);
    int relation = compChoice - playerChoice;
    switch (relation)
    {
    case 0: // if both players pick the same option, their difference is 0 -> p1 - p2 is also 0
        return static_cast<Result>(2); // return "DRAW"
    case -1: // if the player picks an object one enum furter than the computer
    case 2: // or 2 ahead, the computer will win
        return static_cast<Result>(0); // return "PLAYER_1_WINS"
    case 1: // if the player picks an object one enum ahead than the computer
    case -2: // or 2 further, the player will win
        return static_cast<Result>(1); // return "PLAYER_2_WINS"
    }
    return Result::DRAW; // workaround for error "control reaches end of non-void function", as the compiler thinks the function has no return value

    /*
    looking at this error, it seems as whenever a switch-case has no default case. the compiler thinks there could be a case without a return value
    so it throws an error for the case of a non-void function returning nothing
    */
}

void print_result(Player player_1, Player player_2)
{

    // HIER programmieren:
    // Ermitteln Sie zunächst das Spielergebnis. Nutzen sie dazu die Funktion determine_result.
    // Geben Sie anschließend auf der Konsole aus, wer gewonnen hat.
    // z.B: "Spieler Computer hat gewonnen" oder "Unentschieden"
    Result result = determine_result(player_1, player_2);
    switch (result)
    {
    case Result::PLAYER_ONE_WINS:
        cout << "Spieler " << player_1.name << " hat gewonnen." << endl;
        break;
    case Result::PLAYER_TWO_WINS:
        cout << "Spieler " << player_2.name << " hat gewonnen." << endl;
        break;
    case Result::DRAW:
        cout << "Unentschieden" << endl;
        break;
    }

}

int main(int argc, char *argv[])
{
    Player player_1, player_2;
    player_1.name = "Computer";
    player_2.name = insert_name();
    player_1.choice = determine_choice(player_2.name);
    cout << "Der Computer hat seine Wahl getroffen." << endl;
    player_2.choice = choose();
    print_choice(player_1);
    print_choice(player_2);
    print_result(player_1, player_2);

    return 0;
}