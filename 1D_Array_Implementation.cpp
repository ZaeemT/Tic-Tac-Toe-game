/*	
		Muhammad Zaeem Tauqir
			2020376
		CS103L final project
		
		1D-Array Implementation
*/
#include<iostream>
#include<cstdlib>
#include<time.h>
#include<windows.h>
#include <iomanip>
using namespace std;

void display_array( char * array, int nbox){
	int i = 0;
	while(i <= nbox){
		cout << setw(60) << "     |     |     " << endl;
		cout << setw(45) << "  " << *(array+i) << "  |  " << *(array+i+1)  << "  |  " << *(array+i+2) << endl;
		i += 3;
		if( i == nbox)
			break;
		else
			cout << setw(60) << "-----+-----+-----" << endl;
	}
	cout << endl;
	return;
}

char user_symbol(){
	char mark;
	cout << "   Choose your mark 'O' or 'X'? ";
	cin >> mark;		// Asking user to choose a symbol.
	cout << endl;
		
	while(true){
		if( mark != 'X' && mark != 'O' ){		// Check.
			cout << "   Invalid character. Please choose from 'X' or 'O' : ";
			cin >> mark;
			cout << endl;
		}
		else
			break;
	}
	return mark;
}

bool turn(){
	int rnum = 0;
	
	srand(time(NULL));
	rnum = rand() % 10;  	// Randomly chooses if its user's turn or computer's turn 
	if ( rnum % 2 == 0)
		return true;
	// Else 
	return false;
}

int get_user_input( char * array, char symbol, int size ){
	int input;
	cout << "   Make your move by entering the number of box. " << endl;
	cout << "\n   Player [" << symbol << "] make your move : ";
	cin >> input;
	input--;
	while(true){
		if( *( array + input ) == 'X' || *( array + input ) == 'O' ){
			// This condition checks if the entered slot is marked or not.
			cout << "\n   Invalid move. Please re-enter the number of box : ";
			cin >> input;
			input--;
		}
		else if ( input < 0 || input > 9 ){
			// This condition checks if the entered number is valid or not.	
			cout << "\n   Invalid move. Please re-enter the number of box : ";
			cin >> input;
			input--;
		}
		else
			break;
	} 
	return input;
}

int get_comp_input( char * array ){
	int choice;
	
	srand(time(NULL));		// Assigning a random seed every time.
	choice = rand() % 9;		// Generating a random number as a choice.
	
	while(true){
		if( *( array + choice ) == 'X' || *( array + choice ) == 'O' ){
			// This condition checks if the entered slot is marked or not.
			choice = rand() % 9;
		}
		else
			break;
	} 
	return choice ;
}


void update_array( int location, char symbol, char * array ){	
	*( array + location ) = symbol;		// Same as assigning the symbol to moves[location].
	return;
}

void display_countdown( char symbol ){
	int time = 5;
	cout << "   Waiting for Computer [" << symbol << "] to make a move." << endl;
	while( time != 0 ){
		Sleep(1000);  // Will create a delay of a second. 
		cout << "  " << time << "...";
		time--;  	// Countdown.
	}
	cout << endl;
	return;
}

bool is_there_a_winner( char * array, int size){
	// This loop checks the rows for the streak.
	for( int i = 0; i < size; i++){
		if( *(array+i) == *(array +i+1) && *(array +i+1) == *(array +i+2) )
			return true;
		i += 2;
	}
	// This loop checks the coloumn for the streak.
	for( int i = 0; i < size; i++){
		if( *(array+i) ==  *(array +i+3) && *(array +i+3) ==  *(array +i+6))
			return true;	
	}
	
	if( *(array+0) ==  *(array+4) &&  *(array+4) ==  *(array+8) )	// Checks diagnols from top left to bottom right.
		return true;
	if( *(array+2) ==  *(array+4) &&  *(array+4) ==  *(array+6) )	// Checks diagnols from top right to bottom left.
		return true;
		
	return false; 	
}

bool is_it_a_draw( char * array, int size){
	int count = 0;
	for( int i=0; i < size; i++){
		if( *( array + i ) == 'X' || *( array + i ) == 'O')
			count++; 
	}
	if ( count == 9)
		return true;
	// Else it will,	
	return false;		 	
}

int main(){
	
	char playermark, compmark, playAgain = 'y';		 
	bool user_turn, game_finished = false;
	int playermove, compmove;
		
	while( playAgain == 'y'){
		char moves[9] = {'1','2','3','4','5','6','7','8','9'};
		
		system("cls");
		
		playermark = user_symbol();
		
		if( playermark == 'O')
			compmark = 'X';
		else					// Computer is assigned an opposite symbol.
			compmark = 'O';
			
		user_turn = turn();
		
		cout << endl;

		display_array( moves, 9);
		
		cout << "   _______________________________________________ \n" << endl;

		do{
			
			if( user_turn == true){
				playermove = get_user_input( moves, playermark, 9);
				update_array( playermove, playermark, moves );
				user_turn = false;		// After player move it is toggled to false so in next loop
			}							// its computer's turn. 
			else{
				display_countdown(compmark);
				compmove = get_comp_input( moves );
				update_array( compmove, compmark, moves );
				user_turn = true;		// After player move it is toggled to true so in next loop
			}							// its the player's turn.
			
			system("cls");
			cout << "\n \n " << endl;
			
			display_array( moves, 9);		// Displays the updated grid.
			
			cout << "   _______________________________________________ \n" << endl;
			
			if( is_there_a_winner( moves, 9) == true)
 				break;
					
			game_finished = is_it_a_draw( moves, 9);
			
		} while( game_finished == false );
		
		if( game_finished == true )
			cout << "\t It is a DRAW!" << endl;
		else{
			if( user_turn == true )
				cout << "\tThe Computer [" << compmark << "] is the WINNER!!" << endl;
			if( user_turn == false )
				cout << "\t( player [" << playermark << "] ) You are the WINNER!! ;) " << endl;
		}
		cout << endl;	
			
		cout << "   Do you want to play again (y/n) ? ";
		cin >> playAgain;
		cout << endl;	
	}
	
	system("pause");
	
	return 0;
}
