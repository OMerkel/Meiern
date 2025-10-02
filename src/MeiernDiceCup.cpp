#include "MeiernDiceCup.h"

MeiernDiceCup::MeiernDiceCup() : DiceCup(0) {
	addDie(6);
	addDie(6);
}

Announcement MeiernDiceCup::getDiceValue() const {
    if (getDiceCount() != 2) return Announcement( 0, 0); // Error case
    int die1 = getDie(0)->getValue();
    int die2 = getDie(1)->getValue();
    return Announcement(die1, die2);
}
