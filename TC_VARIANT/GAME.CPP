/*
Copyright (c) 2014 Jai Luthra <me@jailuthra.in>, Shardul Aggarwal

This file is licensed under MIT/X License.
See COPYING.txt file in the project root for details.
*/

#include <iostream.h>
#include <stdlib.h>
#include <conio.h>

void play();
char toss();
int first_innings (char batsman);
void end_innings (char &batsman);
int second_innings (char batsman, int target);
void display_winner (char current_batsman, int runs_scored, int runs_chased);
void display_help();
void display_credits();

int main() {
    // Main Menu
    int option = 0;
    while (option != 4) {
	clrscr();
	cout << "\n\n======HAND CRICKET (aka Odd-Even)======\n\n";
	cout << "1. New Game" << endl;
	cout << "2. How to play?" << endl;
	cout << "3. Credits" << endl;
	cout << "4. Quit Game" << endl << endl;
	cout << "Please enter your option: ";
	cin >> option;
	switch (option) {
	    case 1:
		play();
	    break;
	    case 2:
		display_help();
	    break;
	    case 3:
		display_credits();
	    break;
	    case 4:
		// It will exit the loop
	    break;
	    default:
		cout << endl << "Please enter a valid option!\n";
	}
    }
    return 0;
}

void play() {
    char batsman = toss();
    if (batsman == 'a') {    // a for AI, p for Player
	cout << "AI wins the toss and thus will bat first" << endl;
    } else {
	cout << "Player wins the toss and thus will bat first" << endl;

    }
    getch();
    int runs_scored = first_innings(batsman);
    end_innings(batsman);
    int runs_chased = second_innings(batsman, runs_scored+1);
    display_winner(batsman, runs_scored, runs_chased);
}

char toss() {
    clrscr();
    cout << "\n\n*=*=TOSS*=*=\n\n";
    char option[4];
    cout << endl << "Please select your option for the toss (o)dd/(e)ven: ";
    cin >> option;
    unsigned int p_gesture, a_gesture, sum;
    cout << endl << "Enter your throw/gesture (from 1-6): ";
    cin >> p_gesture;
    a_gesture = (rand() % 6) + 1;
    cout << endl << "AI plays: " << a_gesture;
    getch();
    sum = a_gesture + p_gesture;
    cout << "\n\nThe sum is " << sum << endl;
    char batsman;
    // Decide winner of the Toss
    switch (option[0]) {
	case 'o':
	    // Player chose odd
	    if (sum % 2 != 0)
		batsman = 'p';
	    else
		batsman = 'a';
	break;
	case 'e':
	    // Player chose even
	    if (sum % 2 == 0)
		batsman = 'p';
	    else
		batsman = 'a';
	break;
	default:
	    cout << endl <<  "ERROR: Unrecognized option. Please enter from o/e.";
	    toss();
    }
    return batsman;
}

int first_innings (char batsman) {
    clrscr();
    cout << "\n\n*=*=FIRST INNINGS*=*=\n\n";
    int score = 0, a_throw, p_throw;
    if (batsman == 'a') {
	cout << endl << "CURRENT BATSMAN: AI\n";
    } else {
	cout << endl << "CURRENT BATSMAN: Player\n";
    }
    do {
	cout << endl << "Please enter your throw for this turn (1-6): ";
	cin >> p_throw;
	// Error testing
	if (p_throw < 1 || p_throw > 6) {
	    cout << p_throw << " is not a recognized throw.";
	    continue;
	}
	a_throw = (rand() % 6) + 1;
	cout << "AI chose to throw " << a_throw;
	getch();
	if (p_throw != a_throw) {
	    if (batsman == 'p') {
		score += p_throw;
		cout << endl << "Player gets " << p_throw << " runs";
	    } else {
		score += a_throw;
		cout << "\n\nAI gets " << a_throw << " runs";
	    }
	    cout << endl << "SCORE: " << score << endl;
	}
	else {
	    cout << endl << "******  That's OUT!!  ******";
	}
    } while (p_throw != a_throw);
    cout << endl << "The batsman scored " << score << " runs";
    getch();
    return score;
}

void end_innings (char &batsman) {
   if (batsman == 'p') {
       cout << "\n\nThis ends the first innings. AI is the new batsman";
       batsman = 'a';
   } else {
       cout << "\n\nThis ends the first innings. Player is the new batsman";
       batsman = 'p';
   }
   getch();
}

int second_innings (char batsman, int target) {
    clrscr();
    cout << "\n\n*=*=SECOND INNINGS*=*=\n\n";
    int score = 0, a_throw, p_throw;
    if (batsman == 'a') {
	cout << endl << "CURRENT BATSMAN: AI\n";
    } else {
	cout << endl << "CURRENT BATSMAN: Player\n";
    }
    cout << "\nTARGET: " << target << endl;
    do {
	cout << endl << "Please enter your throw for this turn (1-6): ";
	cin >> p_throw;
	// Error testing
	if (p_throw < 1 || p_throw > 6) {
	    cout << p_throw << " is not a recognized throw.";
	    continue;
	}
	a_throw = (rand() % 6) + 1;
	cout << "AI chose to throw " << a_throw;
	getch();
	if (p_throw != a_throw) {
	    if (batsman == 'p') {
		score += p_throw;
		cout << endl << "Player gets " << p_throw << " runs";
	    } else {
		score += a_throw;
		cout << "\n\nAI gets " << a_throw << " runs";
	    }
	    cout << endl << "SCORE: " << score << endl;
	    if (score<target)
		cout << (target - score) << " runs far from victory\n";
	}
	else {
	    cout << endl << "******  That's OUT!!  ******";
	}
    } while ( (p_throw != a_throw) && (score < target) );
    cout << endl << "The batsman scored " << score << " runs";
    getch();
    return score;
}

void display_winner (char current_batsman, int runs_scored, int runs_chased) {
    if (current_batsman == 'p') {
	if (runs_chased > runs_scored)
	    cout << "\n\n****** Congrats Player! You won the match! ******";
	else
	    cout << "\n\n****** Bah! Player, you lost the match! ******";
    } else {
	if (runs_chased > runs_scored)
	    cout << "\n\n****** Bah! Player, you lost the match! ******";
	else
	    cout << "\n\n****** Congrats Player! You won the match by " << runs_scored - runs_chased << " runs! ******";
    }
    getch();
}

void display_help() {
    clrscr();
    cout << "\n\n*=*=HOW TO PLAY*=*=\n\n(assuming user knows how to play normal cricket)\n\n\n\n";
    cout <<"* The \"Player\" refers to the human player, and \"AI\" refers to the BOT/CPU that throws numbers randomly.\n\n";
    cout << "* For the toss, both the players select from 'odd' and 'even' and make throws; "
	 << "if the sum of these (i.e. their nos.) is odd/even, then the side having chosen that will bat first.\n\n";
    cout << "* For the play, The batsman and the bowler make throws at every ball; if the throws are the same, "
	 << "the batsman is out, else the throw gets added to the batsman's runs.";
    getch();
}

void display_credits() {
    clrscr();
    cout << "\n\n*=*=CREDITS*=*=\n\n";
    cout << "Copyright (c) 2014 Jai Luthra, Shardul Aggarwal\n\n";
    cout << "This game is licensed under MIT/X License.\nSee COPYING.txt file in the project root for details.";
    cout << "\n\nJai Luthra\t\tShardul Aggarwal" << endl << "11-C\t\t\t11-C" << endl << "me@jailuthra.in";
    getch();
}