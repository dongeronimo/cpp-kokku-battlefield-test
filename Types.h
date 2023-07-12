#pragma once
class Types
{
public:

    struct GridBox
    {
        int xIndex;
        int yIndex;
        bool ocupied;
        int Index;
        GridBox() {
            xIndex = 0;
            yIndex = 0;
            ocupied = false;
            Index = 0;
        }
        GridBox(int x, int y, bool isOcupied, int index)
        {
            xIndex = x;
            yIndex = y;
            ocupied = isOcupied;
            Index = index;
        }
    };

    enum CharacterClass
    {
        Paladin = 1,
        Warrior = 2,
        Cleric = 3,
        Archer = 4
    };

};

