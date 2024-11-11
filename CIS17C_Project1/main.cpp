/**************************************************************
 *
 *                      UNSCRAMBLE GAME
 * ____________________________________________________________
 * This program is a word unscrambling game where
 *
 * players are presented with scrambled words and
 *
 * must guess the correct word. The game includes
 *
 * various difficulty levels, achievements,
 *
 * hints, scoring with combo points, and a shop
 *
 * for additional words.
 * ____________________________________________________________
 * INPUT
 *
 * wordCount       : Total number of words loaded from a dictionary file
 *
 * difficulty      : Selected difficulty level (Easy, Medium, or Hard)
 *
 * attemptsLeft    : Number of attempts allowed to guess each word
 *
 * hintsUsed       : Number of hints used for each word
 *
 * guess           : Player's input guess for the unscrambled word
 *
 * OUTPUT
 *
 * score           : Player's current score based on correct guesses
 *
 * highestScore    : Player's highest score achieved
 *
 * streak          : Current streak of consecutive correct guesses
 *
 * maxStreak       : Maximum streak achieved during the game
 *
 * achievements    : List of achievements unlocked by the player
 *
 * scrambledWord   : Display of scrambled version of the word to guess
 *
 **************************************************************/

// Include standard libraries
#include <iostream>  // Input-output operations
#include <iomanip>   // Output formatting
#include <fstream>   // File handling
#include <cstdlib>   // General-purpose functions
#include <ctime>     // Time-based functions
#include <array>     // Fixed-size array container
#include <string>    // String handling
#include <cstring>   // C-style string functions
#include <algorithm> // Algorithms
#include <limits>    // Numeric limits
#include <chrono>    // For high-precision time handling
#include <thread>    // For sleep functionality

// Use standard namespace
// This will save lots of typing times
using namespace std;

// Constants for game settings
const size_t maxWords = 200;   // Max words storage
const int easyMinLength = 3;   // Min length for easy
const int easyMaxLength = 5;   // Max length for easy
const int mediumMinLength = 6; // Min length for medium
const int mediumMaxLength = 8; // Max length for medium
const int hardMinLength = 9;   // Min length for hard
const int hintCost = 1;        // Points per hint
const int maxHintsPerWord = 2; // Max hints per word

// Function Prototypes
void displayIntro();                                                                                                                                                 // Show game intro
void displayRules();                                                                                                                                                 // Show game rules
void displayMenu(int score, int highestScore);                                                                                                                       // Show main menu
void displayDifficultyMenu();                                                                                                                                        // Show difficulty menu
int getDifficultyChoice();                                                                                                                                           // Get difficulty choice
bool isEasyWord(const string &word);                                                                                                                                 // Check if word is easy
bool isMediumWord(const string &word);                                                                                                                               // Check if word is medium
bool isHardWord(const string &word);                                                                                                                                 // Check if word is hard
void filterWordsByDifficulty(array<string, maxWords> &filteredWords, const array<string, maxWords> &words, size_t wordCount, int difficulty, size_t &filteredCount); // Filter words
void playGame(int &score, int &highestScore, int &streak, int &maxStreak, array<string, maxWords> &words, size_t wordCount, int difficulty);                         // Play game
void displayShop(array<string, maxWords> &words, size_t &wordCount);                                                                                                 // Show shop
size_t loadWords(const string &filename, array<string, maxWords> &words, size_t startIndex = 0);                                                                     // Load words
string scrambleWord(const string &word);                                                                                                                             // Scramble word
void handleGameOver(int &score, const string &correctWord);                                                                                                          // Handle game over
void updateScore(bool isCorrect, int &score, int &highestScore, int points);                                                                                         // Update scores
void displayHintMenu();                                                                                                                                              // Show hint menu
void useHint(const string &word, int &hintsUsed, int &score);                                                                                                        // Use hint
void displayAchievements();                                                                                                                                          // Show achievements
void updateAchievements(bool wonGame, int score, int hintsUsed, int timeTaken);                                                                                      // Update achievements
void playGame();                                                                                                                                                     // Game round placeholder

// Define the number of achievements
const int numAchievements = 4;

// Define Achievement struct
struct Achievement
{
    // Achievement name
    string name;

    // Achievement description
    string description;

    // Achievement status
    bool achieved;

    // Default constructor
    Achievement() : name(""), description(""), achieved(false) {}

    // Constructor with parameters
    Achievement(string n, string d) : name(n), description(d), achieved(false) {}
};

// Array of achievements with a fixed size
array<Achievement, numAchievements> achievements = {
    // First Achievement
    Achievement("First Win", "Win your first game"),
    // Second Achievement
    Achievement("Hint Master", "Win without using a hint"),
    // Third Achievement
    Achievement("High Scorer", "Reach a score of 50 or more"),
    // Fourth Achievement
    Achievement("Quick Thinker", "Win within 30 seconds")};

// Main function where the program starts execution
int main()
{
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Initialize player's score
    int score = 0;

    // Initialize highest score variable
    int highestScore = 0;

    // Current streak of consecutive correct guesses
    int streak = 0;

    // Highest streak reached
    int maxStreak = 0;

    // Display game intro
    displayIntro();

    // Display game rules
    displayRules();

    // Wait for the user to press enter
    cin.get();

    // Array to store words from the file
    array<string, maxWords> words;

    // Load initial words
    size_t wordCount = loadWords("dictionary.txt", words);

    // Variable to track if the game should exit
    bool exitGame = false;

    // Main game loop
    while (!exitGame)
    {
        // Display Achievements
        playGame();

        // Display game menu with score
        displayMenu(score, highestScore);

        // Variable to store the menu option selected
        int option;

        // Prompt on what user should input
        cout << "Enter your selection: ";

        // Validate input
        while (!(cin >> option))
        {
            // Clear the error flag on cin
            cin.clear();

            // Ignore the rest of the line
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Prompt user to enter a number
            cout << "Invalid selection. Please enter a number: ";
        }

        // Process menu option
        switch (option)
        {
        // Start a new game
        case 1:
        {
            // Get difficulty choice from the player
            int difficulty = getDifficultyChoice();

            // Start the game with chosen difficulty
            playGame(score, highestScore, streak, maxStreak, words, wordCount, difficulty);

            // Break out of switch case
            break;
        }

        // Display the shop
        case 2:
            // displayShop Function will run
            displayShop(words, wordCount);

            // Break out of switch case
            break;

        // Exit the game
        case 3:
            // exitGame will be true
            exitGame = true;

            // Prompt user that game is exiting
            cout << "Exiting the game.\n";

            // Break out of switch case
            break;

        // Handle invalid selection
        default:

            // Prompt user to enter a number 1-3
            cout << "Invalid selection. Please enter a number between 1 and 3.\n";

            // Break out of switch case
            break;
        }
    }

    // End program
    return 0;
}

// Function to display introductory text for the game
void displayIntro()
{
    cout << "\n\n";
    cout << "****************************************\n";
    cout << "*              UNSCRAMBLE              *\n";
    cout << "****************************************\n";
    cout << "* Hello Welcome to my Unscramble game! *\n";
    cout << "* This program is a word unscrambling  *\n";
    cout << "* game where players are presented with*\n";
    cout << "* scrambled words and must guess the   *\n";
    cout << "* correct word. The game includes      *\n";
    cout << "* various difficulty levels, achieveme *\n";
    cout << "* nts, hints, scoring with combo points*\n";
    cout << "* and a shop for additional words.     *\n";
    cout << "* Created by \"Vannara Thong\"         *\n";
    cout << "****************************************\n";
}

// Function to display the rules of the game
// This provides players with instructions on how to play and what to expect
void displayRules()
{
    cout << "****************************************\n";
    cout << "*                 RULES                *\n";
    cout << "****************************************\n";
    cout << "* You'll be given a word to unscramble *\n";
    cout << "* and must solve it within 3 tries.    *\n";
    cout << "* Points are awarded based on word     *\n";
    cout << "* length and difficulty level chosen.  *\n";
    cout << "* If the word is guessed incorrectly a *\n";
    cout << "* point will be taken from your score. *\n";
    cout << "****************************************\n";
    cout << "Press \"Enter\" to continue.\n";
}

// Function to display the main menu with the current score and highest score
// Shows the player their progress and offers options to play, shop, or exit
void displayMenu(int score, int highestScore)
{
    cout << "\n****************************************\n";
    cout << "* Current Score: " << score << setw(23) << "*\n";
    cout << "* Highest Score: " << highestScore << setw(23) << "*\n";
    cout << "****************************************\n";
    cout << "Choose an option from the menu\n";
    cout << "1. Play the game\n";
    cout << "2. Shop\n";
    cout << "3. Exit the game\n";
    // cout << "Enter your selection: ";
}

// Function to display the difficulty menu for the player
// Provides the player with difficulty level options before starting a game
void displayDifficultyMenu()
{
    cout << "\nSelect Difficulty Level:\n";
    cout << "1. Easy (3-5 letters)\n";
    cout << "2. Medium (6-8 letters)\n";
    cout << "3. Hard (9+ letters)\n";
    cout << "Enter your choice: ";
}

// Function to retrieve the difficulty choice from the player
// Prompts the player to select a difficulty level and returns their choice
int getDifficultyChoice()
{
    // Display the difficulty menu
    displayDifficultyMenu();

    // Variable to store difficulty choice
    int difficulty;

    // Get difficulty choice from user
    // This can be easy, medium, and hard
    cin >> difficulty;

    // Return chosen difficulty
    return difficulty;
}

// Helper function to check if a word is an "Easy" word
bool isEasyWord(const string &word)
{
    // Check if word length falls within easy range
    return word.length() >= easyMinLength && word.length() <= easyMaxLength;
}

// Helper function to check if a word is a "Medium" word
bool isMediumWord(const string &word)
{
    // Check if word length falls within medium range
    return word.length() >= mediumMinLength && word.length() <= mediumMaxLength;
}

// Helper function to check if a word is a "Hard" word
bool isHardWord(const string &word)
{
    // Check if word length is within hard range
    return word.length() >= hardMinLength;
}

// Function to filter words by selected difficulty level
void filterWordsByDifficulty(array<string, maxWords> &filteredWords, const array<string, maxWords> &words, size_t wordCount, int difficulty, size_t &filteredCount)
{
    // Initialize filtered word count
    filteredCount = 0;

    // Loop through each word in the word list
    for (size_t i = 0; i < wordCount; ++i)
    {
        // Check if word matches the selected difficulty level
        if ((difficulty == 1 && isEasyWord(words[i])) ||
            (difficulty == 2 && isMediumWord(words[i])) ||
            (difficulty == 3 && isHardWord(words[i])))
        {
            // Add matching word to filtered list
            filteredWords[filteredCount++] = words[i];
        }
    }
}

// Function to display hint menu
void displayHintMenu()
{
    cout << "\nAvailable Hints:\n";
    cout << "1. Reveal the first letter\n";
    cout << "2. Show word length\n";
    cout << "3. Reveal a random letter\n";
    cout << "Enter your choice: ";
}

// Function to provide a hint to the player and update score
void useHint(const string &word, int &hintsUsed, int &score)
{
    // Check if maximum hints have been used
    if (hintsUsed >= maxHintsPerWord)
    {
        cout << "You have used all available hints for this word.\n";
        return;
    }

    // Display the hint menu
    displayHintMenu();
    int hintChoice;
    cin >> hintChoice;

    // Process the player's hint choice
    if (hintChoice == 1) // Reveal the first letter
    {
        cout << "First letter: " << word[0] << endl;
    }
    else if (hintChoice == 2) // Show the word length
    {
        cout << "Word length: " << word.length() << " letters.\n";
    }
    else if (hintChoice == 3) // Reveal a random letter
    {
        size_t randIndex = static_cast<size_t>(rand() % static_cast<int>(word.length()));
        cout << "Revealed letter at position " << randIndex + 1 << ": " << word[randIndex] << endl;
    }
    else
    {
        cout << "Invalid hint choice.\n";
        return;
    }

    // Increment hint usage
    hintsUsed++;

    // Deduct points
    score -= hintCost;

    // Display the current score
    cout << "Hint cost deducted. Current score: " << score << endl;
}

// Function to play the game with streak and combo points
void playGame(int &score, int &highestScore, int &streak, int &maxStreak, array<string, maxWords> &words, size_t wordCount, int difficulty)
{
    // Check if there are any loaded words to play with
    if (wordCount == 0)
    {
        // Display error and exit function if no words are available
        cout << "Error: No words loaded from the dictionary files.\n";

        // Breaks out of this if statement
        return;
    }

    // Declare an array to store words filtered by difficulty
    array<string, maxWords> filteredWords;

    // Track the number of filtered words
    size_t filteredCount = 0;

    // Filter the loaded words by selected difficulty level
    filterWordsByDifficulty(filteredWords, words, wordCount, difficulty, filteredCount);

    // Check if there are words available for the chosen difficulty
    if (filteredCount == 0)
    {
        // Display message if no matching words are found
        cout << "No words available for the selected difficulty level.\n";

        // Breaks out of this if statement
        return;
    }

    // Select a random word from the filtered list
    string word = filteredWords[static_cast<size_t>(rand()) % filteredCount];

    // Scramble the selected word to create an anagram
    string scrambledWord = scrambleWord(word);

    // Display the unscramble word
    cout << "Anagram of the word is: " << scrambledWord << endl;

    // Initialize the number of attempts and hints
    // Total attempts allowed per word
    int attemptsLeft = 3;

    // Number of hints available per word
    // Track the number of hints used
    int hintsUsed = 0;

    // Variable to store player's guess
    string guess;

    // Track if the word was guessed correctly
    bool wordGuessed = false;

    // Main loop for guessing attempts
    while (attemptsLeft > 0 && !wordGuessed)
    {
        // Prompt the player for a guess
        cout << "Guess the word (or type 'hint' for a hint): ";
        cin >> guess;

        // Check if the player requested a hint
        if (guess == "hint")
        {
            // Provide a hint and continue the loop without using an attempt
            useHint(word, hintsUsed, score);

            // Continues the flow of code
            continue;
        }

        // Check if the player's guess is correct
        if (guess == word)
        {
            // Calculate points based on word length and combo streak
            int points = static_cast<int>(word.length());

            // Example: 2 extra points per streak level
            int comboBonus = streak * 2;

            // Bonus increases points
            points += comboBonus;

            // Increment the streak and update max streak if new streak is higher
            streak++;

            // Increase max streak value
            if (streak > maxStreak)
            {
                // Maxstreak takes value of streak
                maxStreak = streak;
            }

            // Display points earned, including combo points
            cout << "Correct! You earned " << points << " points (including " << comboBonus << " combo points)!\n";
            cout << "Current streak: " << streak << " | Max streak: " << maxStreak << endl;

            // Update the score with points and end the round
            updateScore(true, score, highestScore, points);
            wordGuessed = true;
        }
        else
        {
            // Deduct an attempt if the guess was incorrect
            attemptsLeft--;
            cout << "Incorrect guess. Attempts left: " << attemptsLeft << endl;

            // Reset the streak since the guess was incorrect
            streak = 0;
        }
    }

    // If the player didn't guess the word correctly, handle game over
    if (!wordGuessed)
    {
        handleGameOver(score, word);
    }

    // Prompt the user to press Enter to continue
    cout << "Press \"Enter\" to continue.\n";
    cin.ignore();
    cin.get();
}

// Function to display shop and offer more words
void displayShop(array<string, maxWords> &words, size_t &wordCount)
{
    // Display shop menu options
    cout << "Welcome to the shop.\n";
    cout << "1. Load more difficult words\n";
    cout << "2. Exit shop\n";
    cout << "Enter your choice: ";

    // Get user's choice
    int shopOption;

    // User input an option
    cin >> shopOption;

    // Check if user chose to load more words
    if (shopOption == 1)
    {
        // Load words from an additional file
        size_t newWords = loadWords("dictionary2.txt", words, wordCount);

        // Update word count with new words added
        wordCount += newWords;

        // Display number of new words added
        cout << newWords << " new words added!\n";
    }
    else
    {
        // Exit the shop if the user chose to
        cout << "Exiting the shop.\n";
    }

    // Prompt user to press Enter to continue
    cout << "Press \"Enter\" to continue.\n";
    cin.ignore();
    cin.get();
}

// Function to load words from a file into a fixed-size array
size_t loadWords(const string &filename, array<string, maxWords> &words, size_t startIndex)
{
    // Open the file
    ifstream file(filename);

    // Start counting from the given index
    size_t count = startIndex;

    // Read words from the file until reaching maxWords
    while (file >> words[count] && count < maxWords)
    {
        // Count is incremented by 1
        count++;
    }

    // Return the number of words loaded
    return count - startIndex;
}

// Function to scramble a word to create an anagram
string scrambleWord(const string &word)
{
    // Copy the original word to scramble
    string anagram = word;

    // Loop through each character in the word
    for (size_t j = 0; j < word.length(); j++)
    {
        // Generate a random index
        size_t k = static_cast<size_t>(rand()) % word.length();

        // Swap characters to scramble
        swap(anagram[j], anagram[k]);
    }

    // Return the scrambled word
    return anagram;
}

// Function to handle game over scenario
void handleGameOver(int &score, const string &correctWord)
{
    // Display the correct answer
    cout << "Game Over! The correct answer was \"" << correctWord << "\"\n";

    // Reset the score to zero
    score = 0;
}

// Function to update score and track highest score
void updateScore(bool isCorrect, int &score, int &highestScore, int points)
{
    // If the answer is correct
    if (isCorrect)
    {
        // Add points based on word length
        score += points;

        // Update highest score if needed
        if (score > highestScore)
        {
            // Highest Score will equal the current score
            highestScore = score;
        }
    }
    else
    {
        // Deduct one point for incorrect answer
        score--;
    }
}

// Function to display all achievements and their status
void displayAchievements()
{
    // Print achievement header
    cout << "\nAchievements:\n";

    // Loop through each achievement
    for (const auto &achievement : achievements)
    {
        // Display achievement name
        cout << "- " << achievement.name << ": ";

        // Display status if achieved
        if (achievement.achieved)
        {
            cout << "Achieved! ";
        }

        // Display achievement description
        cout << "(" << achievement.description << ")\n";
    }

    // Add extra line for spacing
    cout << endl;
}

// Function to check and update achievements based on game progress
// Function do not award player
void updateAchievements(bool wonGame, int score, int hintsUsed, int timeTaken)
{
    // Check if "First Win" achievement is earned
    if (wonGame && !achievements[0].achieved)
    {
        // Achievement 1
        achievements[0].achieved = true;

        // Prompt User that achievement is earned
        cout << "Congratulations! You earned the achievement: " << achievements[0].name << "!\n";
    }

    // Check if "Hint Master" achievement is earned
    if (wonGame && hintsUsed == 0 && !achievements[1].achieved)
    {
        // Achievement 2
        achievements[1].achieved = true;

        // Prompt User that achievement is earned
        cout << "Amazing! You earned the achievement: " << achievements[1].name << "!\n";
    }

    // Check if "High Scorer" achievement is earned
    if (score >= 50 && !achievements[2].achieved)
    {
        // Achievement 3
        achievements[2].achieved = true;

        // Prompt User that achievement is earned
        cout << "Impressive! You earned the achievement: " << achievements[2].name << "!\n";
    }

    // Check if "Quick Thinker" achievement is earned
    if (wonGame && timeTaken <= 30 && !achievements[3].achieved)
    {
        // Achievement 4
        achievements[3].achieved = true;

        // Prompt User that achievement is earned
        cout << "Fast thinking! You earned the achievement: " << achievements[3].name << "!\n";
    }
}

// Function to simulate a game round and check achievements
// This function will run after each played game
void playGame()
{
    // Track the player's score
    int score = 0;

    // Track number of hints used
    int hintsUsed = 0;

    // Time taken to win the game in seconds
    int timeTaken = 25;

    // Did the player win the game?
    bool wonGame = true;

    // Example score increment after winning a game
    score += 10;

    // Assume no hints were used this round
    hintsUsed = 0;

    // Check for new achievements
    updateAchievements(wonGame, score, hintsUsed, timeTaken);

    // Display all achievements
    displayAchievements();
}