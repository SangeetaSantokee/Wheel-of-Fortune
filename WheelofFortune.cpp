#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <string>
#include <ctime>
#include <windows.h>
#include <unistd.h>

using namespace std;

struct Puzzle {
    string category;
    char puzzle[80];
};

int readCategories(string categories[], int numCategories) {
	
    ifstream in("Categories.txt");
    if (!in.is_open()) {
        cout << "Cannot open Categories.txt. Aborting..." << endl;
        exit(1);
    }

    string category;
    while (numCategories < 50 && getline(in, category)) {
        categories[numCategories++] = category;
    }

    in.close();

    return numCategories;
    
}

void decryptPuzzle(string encrypted, char decrypted[]) {
	
    int len = encrypted.length();
    int i = 0;
    for (i = 0; i < len; i++) {
        if (isalpha(encrypted[i])) {
            decrypted[i] = (((encrypted[i] - 'A' - 5) % 26) + 26) % 26 + 'A';
        } else {
            decrypted[i] = encrypted[i];
        }
    }
    decrypted[len] = '\0'; // End the decrypted puzzle
    
}

int readPuzzles(Puzzle puzzles[]) {
	
    ifstream in;
    in.open("WOF-Puzzles.txt");
    if (!in.is_open()) {
        cout << "Cannot open WOF-Puzzles.txt. Aborting..." << endl;
        exit(1);
    }

    int numPuzzles = 0;
    string category, encryptedPuzzle;
    while (numPuzzles < 2000 && getline(in, category) && getline(in, encryptedPuzzle)) {
        Puzzle newPuzzle;
        newPuzzle.category = category;
        decryptPuzzle(encryptedPuzzle, newPuzzle.puzzle);
        puzzles[numPuzzles++] = newPuzzle;
    }

    in.close();
    return numPuzzles;
    
}

string chooseCategory(string categories[], int numCategories) {
	
    srand(time(NULL));
    string selectedCategories[3];

    for (int i = 0; i < 3; i++) {
        int randNum = rand() % numCategories;
        selectedCategories[i] = categories[randNum];
    }

    cout << "Please choose from one of the following categories:" << endl;
    for (int i = 0; i < 3; ++i) {
        cout << i + 1 << ". " << selectedCategories[i] << endl;
    }

    int choice;
    cout << endl;
    cout << "Your choice? ";
    cin >> choice;
    cout << endl << endl;

    if (choice < 1 || choice > 3) {
        cout << "Invalid choice. Please choose a number between 1 and 3." << endl;
        exit(1);
    }

    return selectedCategories[choice - 1]; // Return the chosen category
    
}

void choosePuzzle(Puzzle puzzles[], int numPuzzles, string category, Puzzle& selectedPuzzle) {

    Puzzle categoryPuzzles[2000];
    int categoryPuzzleCount = 0;
	int i =0;

    for (i = 0; i < numPuzzles; i++) {
        if (puzzles[i].category == category) {
            categoryPuzzles[categoryPuzzleCount++] = puzzles[i];
        }
    }

    if (categoryPuzzleCount > 0) {
        srand(time(NULL));
        selectedPuzzle = categoryPuzzles[rand() % categoryPuzzleCount];

        char decryptedPuzzle[80];
        decryptPuzzle(selectedPuzzle.puzzle, decryptedPuzzle);

        for (i = 0; decryptedPuzzle[i] != '\0'; i++) {
            char c = decryptedPuzzle[i];
            if (c == ' ' || c == '-') {
                cout << c; // Spaces and dashes are revealed
            } else {
                cout << '#'; // Other letters are blanked off
            }
        }
//        cout << endl;
//        cout << selectedPuzzle.puzzle << endl;
        cout << endl;
    } else {
        cout << "No puzzles found in the category." << endl;
        exit(1);
    }
    
}

void rstlne(char puzzle[]) {
	
    cout << "Revealing R, S, T, L, N, E ..." << endl << endl;
    cout << "The puzzle is now: ";

    int i = 0;
    char c;

    while (puzzle[i] != '\0') {
        c = puzzle[i];
        if (c == 'R' || c == 'S' || c == 'T' || c == 'L' || c == 'N' || c == 'E') {
            cout << c; // Reveal specific letters
        } else if (c == ' ' || c == '-') {
            cout << c; // Reveal spaces and dashes
        } else {
            cout << '#'; // Blank off other letters
        }

        i++;
    }

    cout << endl;
    
}

void chooseLetters(char letters[]) {
	
    cout << "Please choose 3 consonants and 1 vowel: ";
    for (int i = 0; i < 4; i++) {
        cin >> letters[i];
    }
}

char toUpper(char letter) {
    if (islower(letter)) {
        return toupper(letter);
    } else {
        return letter;
    }
}

void revealLetters(string puzzle, char chosenLetters[]) {
    cout << "The new puzzle is: ";

    for (int i = 0; i < puzzle.length(); i++) {
        char c = puzzle[i];
        bool revealed = false;

        c = toUpper(c);

        for (int j = 0; j <= 4; j++) {
            if (c == toUpper(chosenLetters[j])) {
                cout << c;
                revealed = true;
                break;
            }
        }

        if (!revealed && (c == 'R' || c == 'S' || c == 'T' || c == 'L' || c == 'N' || c == 'E' || c == ' ' || c == '-')) {
            cout << c;
        } else if (!revealed) {
            cout << '#';
        }
    }

    cout << endl << endl;
    
}

string selectPrize() {
	
	srand(time(NULL));
	string prize;
	
    int randNum = rand() % 25;
    if (randNum < 3) {
        prize = "Car";
    } else if (randNum < 22) {
        prize =  "$40,000.00";
    } else if (randNum < 24) {
        prize =  "$45,000.00";
    } else {
        prize =  "Jackpot ($100,000.00)";
    }
    
    return prize;
}

int main() {

    Puzzle puzzles[2000];
    string categories[50];
    Puzzle selectedPuzzle;

    int numCategories = 0;
    int numPuzzles = 0;
    string selectedCategory;
    int wildCard = 0;
    bool hasWildcard = false;

    numCategories = readCategories(categories, numCategories);
    numPuzzles = readPuzzles(puzzles);

    cout << "# of categories read from the file: " << numCategories << endl;
    cout << "# of puzzles read from the file: " << numPuzzles << endl << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\tWelcome to ";
	sleep(1); 
	cout << "WHEEL ";
	Beep(800, 700);
	sleep(1); 
	cout << "OF " ;
	Beep(200, 700);
	sleep(1); 
	cout << "FORTUNE!" << endl;
    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    Beep(300, 900);
    Beep(400, 900);
    Beep(500, 900);
    cout << endl;

    selectedCategory = chooseCategory(categories, numCategories);
    cout << "Category chosen for this round is: " << selectedCategory << endl << endl;
    cout << "The puzzle to start with is: ";
    choosePuzzle(puzzles, numPuzzles, selectedCategory, selectedPuzzle);
    cout << endl;
    rstlne(selectedPuzzle.puzzle);

    char chosenLetters[5]; // Changed size to 5 to accommodate the wildcard option
    chooseLetters(chosenLetters);
    cout << endl << endl;

    //-------------------WILD CARD-----------------------
    cout << "Do you have the wildcard? (0-No, 1-Yes)" << endl;
    cin >> wildCard;
    cout << endl;

    if (wildCard == 0) {
        hasWildcard = false;
        cout << "You do not have a wild card... Sorry..." << endl << endl;
    } else if (wildCard == 1) {
        hasWildcard = true;
        cout << "You have a wildcard! Please choose a fourth consonant: ";
        cin >> chosenLetters[4]; // Store the fourth consonant in the array
    } else {
        hasWildcard = false;
        cout << "Invalid input. Please enter either 0 or 1." << endl;
        cin >> wildCard;
    }

    revealLetters(selectedPuzzle.puzzle, chosenLetters);
    bool guessed = false;

    for (int attempt = 1; attempt <= 3; attempt++) {
	    char guess[80];
	    cout << "Attempt " << attempt << ": Enter your guess: ";
	    cin.ignore();
	    cin.getline(guess, 80); 
	
	    int i = 0;
	    while (guess[i] != '\0') {
	        guess[i] = toupper(guess[i]);
	        i++;
	    }
	
	    if (strcmp(guess, selectedPuzzle.puzzle) == 0) {
	        cout << "Congratulations! You guessed the puzzle correctly!" << endl << endl;
	        Beep(300, 600);
    		Beep(400, 700);
    		Beep(500, 900);
	
	        string prize = selectPrize();
	        cout << "You win: " << prize << endl;
			guessed = true;
	        return 0;
	    } else if (attempt < 3){
	        cout << "Incorrect guess. Try again!" << endl << endl;
	    }
	}
	
	if (!guessed) {
        cout << "You have 0 tries left." << endl;
        cout << "I am sorry. You will not get a prize." << endl << endl;
        Beep(400, 600);
    	Beep(300, 700);
    	Beep(200, 800);
        cout << "The Solution is: " << selectedPuzzle.puzzle << endl;
    }
	
    return 0;
}
