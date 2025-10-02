#pragma once
#include "Announcement.h"
#include "DiceCup.h"

class MeiernDiceCup : public DiceCup {
public:
    MeiernDiceCup();
    Announcement getDiceValue() const;
    Announcement shake() { DiceCup::shake(); return getDiceValue(); }
};
