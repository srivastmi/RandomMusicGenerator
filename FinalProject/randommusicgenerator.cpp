#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <iomanip>
#include <fstream>

using namespace std;

// struct for Instrument information
struct InstrumentLevels {
	int level;
	int startNum;
	int endNum;
};

// function prototypes
void intro(); // print starting info
bool generateMore(fstream& PracticeMusic); // check if user wants to generate more music
void outro(); // prints ending info
string nameSong(); // input for the name user wants for piece
int validDifficulty(); // difficulty input and verification
int validLength(); // length input and verification
string validInstrument(); // convert function for Instrument enum
void generateMusic(fstream&, string, int, int); // function to generate music
void generateMusicAltoSax(fstream&, string, int, int, string); // function to generate music for Alto Saxophones
void generateMusicTrumpet(fstream&, string, int, int, string); // function to generate music for Trumpets
void generateMusicFlute(fstream&, string, int, int, string); // function to generate music for Flutes
void generateMusicTuba(fstream&, string, int, int, string); // function to generate music for Tubas

// global variables
int length = 0; // variable for length choice
string instrumentName; // variable for instrument choice
int difficulty = 0; // variable for difficulty choice
string nameofPiece; // variable for name of piece
bool moreMusic = true; // bool to trigger the generation of music

// global arrays
const int INSTRUMENTSIZE = 3;
InstrumentLevels altoSax[INSTRUMENTSIZE] = {
		{1, 9, 21},
		{2, 6, 25},
		{3, 0, 31}
};
InstrumentLevels trumpet[INSTRUMENTSIZE] = {
		{1, 13, 25},
		{2, 8, 25},
		{3, 0, 30}
};
InstrumentLevels flute[INSTRUMENTSIZE] = {
		{1, 9, 20},
		{2, 6, 25},
		{3, 0, 31}
};
InstrumentLevels tuba[INSTRUMENTSIZE] = {
		{1, 2, 13},
		{2, 2, 19},
		{3, 0, 24}
};
// array of instrument notes
// the notes alto saxophones can play
string altoSaxophoneNotes[] = {
		"A#", "Bn", "Cn",
		"C#","Dn", "D#",
		"En", "Fn", "F#",
		"Gn", "G#", "An",
		"A#", "Bn", "B#",
		"C#","Dn", "D#",
		"En", "E#", "F#",
		"Gn", "G#", "An",
		"A#", "Bn", "B#",
		"C#", "Dn", "D#",
		"En", "E#"
};
// the notes trumpets can play
string trumpetNotes[] = {
		"F#", "Gn", "G#",
		"An", "A#", "Bn",
		"Cn", "C#", "Dn",
		"D#", "En", "Fn",
		"F#", "Gn", "G#",
		"An", "A#", "Bn",
		"Cn", "C#", "Dn",
		"D#", "En", "Fn",
		"F#", "Gn", "G#",
		"An", "A#", "Bn",
		"Cn"
};
// the notes flutes can play
string fluteNotes[] = {
		"Cn", "C#", "Dn",
		"D#", "En", "Fn",
		"F#", "Gn", "G#",
		"An", "A#", "Bn",
		"Cn", "C#", "D#",
		"En", "Fn", "F#",
		"Gn", "G#", "An",
		"A#", "Bn", "Cn",
		"C#", "Dn", "D#",
		"En", "Fn", "F#",
		"Gn", "G#", "An",
		"A#", "Bn", "Cn"
};
// the notes tubas can play
string tubaNotes[] = {
		"A#", "Bn", "Cn",
		"C#", "Dn", "D#",
		"En", "Fn", "F#",
		"Gn", "G#", "An",
		"A#", "Bn", "Cn",
		"C#", "Dn", "D#",
		"En", "Fn", "F#",
		"Gn", "G#", "An",
		"A#"
};
// array of instruments
string Instruments[4] = {
    "Alto Saxophone",
    "Trumpet",
    "Flute",
	"Tuba"
};
// main function
int main()
{
	// seeding randomness
	srand(time(0));
	// variables
	fstream PracticeMusic; // creating file to put music in
    // calling intro function
    intro();
    // open file
	PracticeMusic.open("PracticeMusic.txt", ios::out);
	// while loop to repeat music making process as many times as user wants
	while(moreMusic == true)
	{
    // calling valid instrument function
    instrumentName = validInstrument();
    // calling valid difficulty function
    difficulty = validDifficulty();
    // calling valid length function
    length = validLength();
    // calling name of the piece function
    nameofPiece = nameSong();
    // calling generate function
    generateMusic(PracticeMusic, instrumentName, difficulty, length);
    // calling continue function
    moreMusic = generateMore(PracticeMusic);
	}
    // close file
    PracticeMusic.close();
    //call outro function
    outro();
    // terminating main function
    return 0;
}
// user difficulty input validity function as well as converting to an int to return
int validDifficulty()
{
	char difficulty[50];
    int difficultyConverted = 0;
    // do-while loop to print information
    do {
    cout << "Our difficulty levels include Beginner, Intermediate, and Advanced. \n";
    cout << "Enter the difficulty you would like: ";
    cin.get(difficulty, 50);
    cin.ignore();
    // for loop to convert input to all lowercase
    for(int i = 0; i < 50; i++)
    {
        difficulty[i] = tolower(difficulty[i]);
    }
    // if/else/else if statements to check if user input is one of our options
    if (strncmp(difficulty, "beginner", 50) == 0)
    {
    	difficultyConverted = 1;
    }
    else if (strncmp(difficulty, "intermediate", 50) == 0)
    {
    	difficultyConverted = 2;
    }
    else if (strncmp(difficulty, "advanced", 50) == 0)
    {
    	difficultyConverted = 3;
    }
    else
    {
    	cout << "You entered an invalid option. ";
    	cout << "Take a look at our difficulty levels again. \n";
    }
    } while (difficultyConverted == 0);
    return difficultyConverted;
}
// function that tests validity of users length input
int validLength()
{
	int length;
	// do-while loop that continues while the length outside the range of 1-96
	do {
		cout << "Our program can produce music that has anywhere from 1 to 96 notes. \n";
		cout << "Enter the number of notes you would like: ";
		cin >> length;
		cin.clear();
		cin.ignore(4096, '\n');
		if (length > 96 || length <= 0)
		{
	    	cout << "You entered an invalid option. ";
	    	cout << "Take a look at our options again. \n";
		}
	} while (length > 96 || length <= 0);
	return length;
}
// function to test if user instrument is supported/valid
string validInstrument()
{
	int verify = 0;
	int instrumentNum;
	int i = 1;
	cout << "As of now we have support for the following instruments: \n";
	// simple range-based for loop to print out instrument options
	for (string x : Instruments)
	{
		cout << i << ". " << x << endl;
		i += 1;
	}
	//do-while loop that will only except the number instrument options we offer
	do {
	cout << "Enter the instrument number you would like: ";
	cin >> instrumentNum;
	cin.clear();
	cin.ignore(4096, '\n');
	if (instrumentNum > 4 || instrumentNum <= 0)
	{
		cout << "Invalid option. Try again. \n";
	}
	else
	{
		// verify == 1 if instrument num is valid
		verify = 1;
	}
	}while(verify == 0);
	return(Instruments[instrumentNum - 1]);
}
// function to call all the different generate music functions
void generateMusic(fstream& PracticeMusic, string instName, int diff, int len)
{
	// static variable remembers which piece # is being generated
	static int counter = 1;
	PracticeMusic << "Piece #" << counter << "\n \n";
	counter++;
	if (instName == "Alto Saxophone")
	{
		generateMusicAltoSax(PracticeMusic, nameofPiece, diff, len, instName);
	}
	else if (instName == "Trumpet")
	{
		generateMusicTrumpet(PracticeMusic, nameofPiece, diff, len, instName);
	}
	else if (instName == "Flute")
	{
		generateMusicFlute(PracticeMusic, nameofPiece, diff, len, instName);
	}
	else if (instName == "Tuba")
	{
		generateMusicTuba(PracticeMusic, nameofPiece, diff, len, instName);
	}
}
// function to generate music for Alto Saxophones
void generateMusicAltoSax(fstream& PracticeMusic, string name, int diff, int len, string instName)
{
	string emptySpace = "   ";
	int lineLen = 0;
	const int SIZE = 50;
	// printing key for user to file
	PracticeMusic << "Key: \n";
	PracticeMusic << "'-' = Continuation of the note \n";
	PracticeMusic << "' ' = Rest notes \n";
	PracticeMusic << "'n' Natural Note \n";
	PracticeMusic << "'#' Sharp Note \n \n";
	// printing user chosen name and instrument name
	PracticeMusic << setw(SIZE) << setfill('*') << "\n";
	PracticeMusic << name;
	PracticeMusic << setw(SIZE) << setfill(' ') << right << instName << endl;
	PracticeMusic << setw(SIZE) << setfill('*') << "\n" << "|";
	// for loop to determine random note and note length
	for (int i=0; i<len; i++){
		int note = altoSax[diff-1].startNum + rand() % (altoSax[diff-1].endNum - altoSax[diff-1].startNum +1);
		int noteLen = rand() % (4);
		if (noteLen == 1)
		{
			emptySpace = "-  ";
		}
		else if (noteLen == 2)
		{
			emptySpace = "-- ";
		}
		else if (noteLen == 3)
		{
			emptySpace = "---";
		}
		//writing the notes into a file and setting empty space back to original value
		PracticeMusic << altoSaxophoneNotes[note] + emptySpace + "|";
		emptySpace = "   ";
		//calculate total length of music
		lineLen += 5;
		// ending line in appropriate spot
		if (lineLen >= 40)
		{
			PracticeMusic << endl << "|";

			lineLen = 0;
		}
	}
}
// function to generate music for trumpets
void generateMusicTrumpet(fstream& PracticeMusic, string name, int diff, int len, string instName)
{
	string emptySpace = "   ";
	int lineLen = 0;
	const int SIZE = 50;
	// printing key for user to file
	PracticeMusic << "Key: \n";
	PracticeMusic << "'-' = Continuation of the note \n";
	PracticeMusic << "' ' = Rest notes \n";
	PracticeMusic << "'n' Natural Note \n";
	PracticeMusic << "'#' Sharp Note \n \n";
	// printing user chosen name and instrument name
	PracticeMusic << setw(SIZE) << setfill('*') << "\n";
	PracticeMusic << name;
	PracticeMusic << setw(SIZE) << setfill(' ') << right << instName << endl;
	PracticeMusic << setw(SIZE) << setfill('*') << "\n" << "|";
	// for loop to determine random note and note length
	for (int i=0; i<len; i++){
		int note = trumpet[diff-1].startNum + rand() % (trumpet[diff-1].endNum - trumpet[diff-1].startNum +1);
		int noteLen = rand() % (4);
		if (noteLen == 1)
		{
			emptySpace = "-  ";
		}
		else if (noteLen == 2)
		{
			emptySpace = "-- ";
		}
		else if (noteLen == 3)
		{
			emptySpace = "---";
		}
		//writing the notes into a file and setting empty space back to original value
		PracticeMusic << altoSaxophoneNotes[note] + emptySpace + "|";
		emptySpace = "   ";
		//calculate total length of music
		lineLen += 5;
		// ending line in appropriate spot
		if (lineLen >= 40)
		{
			PracticeMusic << endl << "|";

			lineLen = 0;
		}
	}
}
// function to generate music for flutes
void generateMusicFlute(fstream& PracticeMusic, string name, int diff, int len, string instName)
{
	string emptySpace = "   ";
	int lineLen = 0;
	const int SIZE = 50;
	// printing key for user to file
	PracticeMusic << "Key: \n";
	PracticeMusic << "'-' = Continuation of the note \n";
	PracticeMusic << "' ' = Rest notes \n";
	PracticeMusic << "'n' Natural Note \n";
	PracticeMusic << "'#' Sharp Note \n \n";
	// printing user chosen name and instrument name
	PracticeMusic << setw(SIZE) << setfill('*') << "\n";
	PracticeMusic << name;
	PracticeMusic << setw(SIZE) << setfill(' ') << right << instName << endl;
	PracticeMusic << setw(SIZE) << setfill('*') << "\n" << "|";
	// for loop to determine random note and note length
	for (int i=0; i<len; i++){
		int note = flute[diff-1].startNum + rand() % (flute[diff-1].endNum - flute[diff-1].startNum +1);
		int noteLen = rand() % (4);
		if (noteLen == 1)
		{
			emptySpace = "-  ";
		}
		else if (noteLen == 2)
		{
			emptySpace = "-- ";
		}
		else if (noteLen == 3)
		{
			emptySpace = "---";
		}
		//writing the notes into a file and setting empty space back to original value
		PracticeMusic << altoSaxophoneNotes[note] + emptySpace + "|";
		emptySpace = "   ";
		//calculate total length of music
		lineLen += 5;
		// ending line in appropriate spot
		if (lineLen >= 40)
		{
			PracticeMusic << endl << "|";

			lineLen = 0;
		}
	}
}
// function to generate music for Tubas
void generateMusicTuba(fstream& PracticeMusic, string name, int diff, int len, string instName)
{
	string emptySpace = "   ";
	int lineLen = 0;
	const int SIZE = 50;
	// printing key for user to file
	PracticeMusic << "Key: \n";
	PracticeMusic << "'-' = Continuation of the note \n";
	PracticeMusic << "' ' = Rest notes \n";
	PracticeMusic << "'n' Natural Note \n";
	PracticeMusic << "'#' Sharp Note \n \n";
	// printing user chosen name and instrument name
	PracticeMusic << setw(SIZE) << setfill('*') << "\n";
	PracticeMusic << name;
	PracticeMusic << setw(SIZE) << setfill(' ') << right << instName << endl;
	PracticeMusic << setw(SIZE) << setfill('*') << "\n" << "|";
	// for loop to determine random note and note length
	for (int i=0; i<len; i++){
		int note = tuba[diff-1].startNum + rand() % (tuba[diff-1].endNum - tuba[diff-1].startNum +1);
		int noteLen = rand() % (4);
		if (noteLen == 1)
		{
			emptySpace = "-  ";
		}
		else if (noteLen == 2)
		{
			emptySpace = "-- ";
		}
		else if (noteLen == 3)
		{
			emptySpace = "---";
		}
		//writing the notes into a file and setting empty space back to original value
		PracticeMusic << altoSaxophoneNotes[note] + emptySpace + "|";
		emptySpace = "   ";
		//calculate total length of music
		lineLen += 5;
		// ending line in appropriate spot
		if (lineLen >= 40)
		{
			PracticeMusic << endl << "|";

			lineLen = 0;
		}
	}
}
//function to prompt and store the name user wishes for the song
string nameSong()
{
	string namePiece;
	cout << "What would you like the title of your piece to be? ";
	getline(cin, namePiece);
	return namePiece;
}
// intro function to print general information about the program
void intro()
{
	const int SIZE = 65;
	cout << setw(SIZE) << setfill('~') << "\n";
    cout << "Hello! Welcome to My Random Practice Music Generator. \n";
    cout << "You may choose a difficulty level, instrument, and length and \n";
    cout << "we will generate practice music for you. \n";
	cout << setw(SIZE) << setfill('~') << "\n" << "\n";
}
// function asking the user whether they would like to have the program repeat and generate more music
bool generateMore(fstream& PracticeMusic)
{
	string another;
	// variable namesAreHard determines whether to repeat or not
	// variable loop determines if user input was within the accepted answers
	bool namesAreHard = false;
	bool loop = false;
	cout << "Your music has been generated! \n";
	cout << "It is ready for you in the file PracticeMusic. \n";
	do {
	cout << "Would you like to generate another piece? (Yes or No): ";
	getline(cin, another);
	if (another == "Yes" || another == "yes" || another == "y" || another == "Y")
	{
		namesAreHard = true;
		loop = true;
		PracticeMusic << "\n \n \n";
		return namesAreHard;
	}
	else if (another == "No" || another == "no" || another == "n" || another == "N")
	{
		namesAreHard = false;
		loop = true;
		return namesAreHard;
	}
	else
	{
		cout << "Sorry, that was an invalid answer. Try Again. \n";
	}

	}while (loop == false);
	return namesAreHard;
}
void outro()
{
	cout << "Hope you enjoy! Happy Practicing :) \n";
	cout << "See you soon! \n";
}
