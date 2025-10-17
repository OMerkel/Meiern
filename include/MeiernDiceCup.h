/**
 * @file MeiernDiceCup.h
 * @brief Declaration of the MeiernDiceCup class.
 *
 * This class represents a specialized dice cup used in the Meiern game,
 * inheriting from the base DiceCup class and providing additional
 * functionality specific to the game.
 *
 * @author Oliver Merkel
 * @date 2025-10-14
 */
#pragma once
#include "Announcement.h"
#include "DiceCup.h"

class MeiernDiceCup : public DiceCup {
public:
    MeiernDiceCup();
    Announcement getDiceValue() const;
    Announcement shake() { DiceCup::shake(); return getDiceValue(); }
};
