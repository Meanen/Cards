#include <iostream>
#include "Cards.h"


using namespace std;

int main (){

	Deck deck;

	deck.deckGen ();
	deck.shuffle ();

	deck.printDeck ();
	cout << deck.getNoCards () << endl;
	system ( "pause" );

}