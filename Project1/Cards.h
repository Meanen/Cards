
#include <time.h>
#include <stdlib.h>

#define HEARTS		0
#define DIAMONDS	1
#define CLUBS		2
#define SPADES		3

#define JACK		11
#define QUEEN		12
#define KING		13
#define ACE			14

#define HEADER		0


struct card{
	int suite;
	int color;
	int val;
	int visible;
	card* next;
};


class Deck{

private:

	card *header;
	int nrCards;

	//set 'nrCards to how many cards currently in the deck
	void countCards (){

		int counter = 0;
		card *ptr = header;

		while ( ptr->next ){
			counter++;
			ptr = ptr->next;
		}
		nrCards = counter;
	}

public:

	//Constructor, creates the header
	Deck (){
		header = new card{ 0,0,0,0 };
	}

	//Generates 52 cards on the header on an empty deck
	void deckGen (){

		if ( header->next )			//can't generate cards if not empty
			return;

		card *curr = header;


		for ( int i = 0; i < 52; i++ ){
			card *next = new card{ ( i / 13 ), ( i / 26 ), ( 2 + ( i % 13 ) ), 0, 0 };

			curr->next = next;
			curr = next;
		}
		countCards ();
	}

	//Prints a deck on terminal
	void printDeck (){
		card *curr = header->next;

		while ( curr ){
			printf ( "%c, %d \n" , curr->suite + 3 , curr->val );
			curr = curr->next;
		}
	}

	//Retrives the Nth card. Send 'HEADER' to recieve all the cards without removing any
	card *getCard ( int N ){
		card *curr = header;
		card *prev = curr;					//used to reassign the pointer when card is taken

		switch ( N ){
			case ( HEADER ) :
				return header;
				break;

			case ( 1 ) :					//First card is a special case
				curr = header->next;
				header->next = curr->next;
				curr->next = 0;
				nrCards--;
				return curr;
		}

		for ( int i = 0; i < N; i++ ){		//jump to the Nth card
			prev = curr;
			curr = curr->next;

			if ( !curr ){					//deck was smaller than N
				return 0;
			}
		}

		prev->next = curr->next;
		curr->next = 0;
		nrCards--;


		return curr;
	}

	//Retrives the Nth card and all cards under it. Send 'HEADER' or 0 to recieve all the cards without removing any
	card *getCards ( int N ){
		card *curr = header;
		card *prev = curr;					//used to reassign the pointer when card is taken


		switch ( N ){
			case ( HEADER ) :
				return header;
				break;

			case ( 1 ) :						//First card is a special case
				curr = header->next;
				header->next = 0;
				countCards ();
				return curr;
		}

		for ( int i = 0; i < N; i++ ){		//jump to the Nth card
			prev = curr;
			curr = curr->next;

			if ( !curr ){			//deck was smaller than N
				return 0;
			}
		}

		prev->next = 0;
		countCards ();

		return curr;
	}

	//Retrives the first card and reveals it
	card *popCard (){
		if ( header->next ){
			card *out = header->next;
			header->next = out->next;

			out->visible = 1;
			out->next = 0;
			return out;
		}
		return 0;

	}

	//Shuffle a deck
	void shuffle (){
		int cardsLeft = nrCards - 1;					// 51 because the first card needs to declared outside the loop

		srand ( time ( 0 ) );

		int rng = 1 + rand () % cardsLeft;
		card* shufld = getCard ( rng );
		card *ptr = shufld;

		while ( cardsLeft ){
			rng = 1 + rand () % cardsLeft;
			ptr->next = getCard ( rng );
			ptr = ptr->next;
			cardsLeft--;
		}
		header->next = shufld;
		countCards ();
	}

	//Adds two decks together, adds 'in' on the bottom of 'deck'
	void addCardsBot ( card* in ){
		card *curr = header;
		while ( curr->next ){
			curr = curr->next;
		}
		curr->next = in;
		countCards ();
	}

	//Adds two decks together, adds 'in' on the top of 'deck'
	void addCardsTop ( card* in ){
		card *curr = in;

		while ( curr->next ){
			curr = curr->next;
		}
		curr->next = header->next;
		header->next = in->next;
		countCards ();
	}

	//Sets visibility of all cards in a deck to visible
	void setVisible (){
		card *curr = header;
		while ( curr ){
			curr->visible = 1;
			curr = curr->next;
		}
	}

	//Sets visibility of the Nth card in a deck to visible
	void setVisible ( int N ){
		card *curr = header;
		while ( N ){
			N--;
			curr->visible = 1;
			curr = curr->next;
		}
	}

	//Sets visibility of all cards in a deck to invisible
	void setInvisible (){
		card *curr = header;
		while ( curr ){
			curr->visible = 0;
			curr = curr->next;
		}
	}

	//Sets visibility of the Nth card in a deck to invisible
	void setInvisible ( int N ){
		card *curr = header;
		while ( N ){
			N--;
			curr->visible = 0;
			curr = curr->next;
		}
	}

	//Reverses order on a deck
	void reverseCards (){
		card *temp;
		card rev = { 0,0,0,0 };

		while ( header->next ){
			temp = getCard ( 0 );
			temp->next = rev.next;
			rev.next = temp;
		}

		header->next = rev.next;
	}

	//Deletes all the cards in the deck
	void clean (){
		card *tmp = header->next;
		card *next = tmp->next;

		while ( tmp->next ){
			delete tmp;
			tmp = next;
			next = next->next;
		}

		header->next = 0;
	}

	//Gives you the ammount of cards in the deck
	int getNoCards (){
		return nrCards;
	}
};

