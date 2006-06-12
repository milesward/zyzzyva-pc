//---------------------------------------------------------------------------
// CrosswordGameBoard.cpp
//
// A class to represent a crossword game board.
//
// Copyright 2006 Michael W Thelen <mthelen@gmail.com>.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//---------------------------------------------------------------------------

#include "CrosswordGameBoard.h"
#include "Defs.h"

using namespace Defs;

const int NUM_ROWS = 15;
const int NUM_COLUMNS = 15;

//---------------------------------------------------------------------------
//  CrosswordGameBoard
//
//! Constructor.
//---------------------------------------------------------------------------
CrosswordGameBoard::CrosswordGameBoard()
{
    initSquareTypes();
}

//---------------------------------------------------------------------------
//  getSquareType
//
//! Get the square type for a row and column.
//
//! @param row the row number
//! @param col the column number
//! @return the square type
//---------------------------------------------------------------------------
CrosswordGameBoard::SquareType
CrosswordGameBoard::getSquareType (int row, int col) const
{
    if ((row < 0) || (row > NUM_ROWS) || (col < 0) || (col > NUM_COLUMNS))
        return Invalid;

    return squareTypes[row][col];
}

//---------------------------------------------------------------------------
//  getNumRows
//
//! Get the number of rows.
//
//! @return the number of rows
//---------------------------------------------------------------------------
int
CrosswordGameBoard::getNumRows() const
{
    return NUM_ROWS;
}

//---------------------------------------------------------------------------
//  getNumColumns
//
//! Get the number of columns.
//
//! @return the number of columns
//---------------------------------------------------------------------------
int
CrosswordGameBoard::getNumColumns() const
{
    return NUM_COLUMNS;
}

//---------------------------------------------------------------------------
//  initSquareTypes
//
//! Initialize the collection of square types on the board.
//---------------------------------------------------------------------------
void
CrosswordGameBoard::initSquareTypes()
{
    QList<SquareType> col1;
    col1 << TripleWord << NoBonus << NoBonus << DoubleLetter << NoBonus <<
        NoBonus << NoBonus << TripleWord << NoBonus << NoBonus <<
        NoBonus << DoubleLetter << NoBonus << NoBonus << TripleWord;

    QList<SquareType> col2;
    col2 << NoBonus << DoubleWord << NoBonus << NoBonus << NoBonus <<
        TripleLetter << NoBonus << NoBonus << NoBonus << TripleLetter <<
        NoBonus << NoBonus << NoBonus << DoubleWord << NoBonus;

    QList<SquareType> col3;
    col3 << NoBonus << NoBonus << DoubleWord << NoBonus << NoBonus <<
        NoBonus << DoubleLetter << NoBonus << DoubleLetter << NoBonus <<
        NoBonus << NoBonus << DoubleWord << NoBonus << NoBonus;

    QList<SquareType> col4;
    col4 << DoubleLetter << NoBonus << NoBonus << DoubleWord << NoBonus <<
        NoBonus << NoBonus << DoubleLetter << NoBonus << NoBonus <<
        NoBonus << DoubleWord << NoBonus << NoBonus << DoubleLetter;

    QList<SquareType> col5;
    col5 << NoBonus << NoBonus << NoBonus << NoBonus << DoubleWord <<
        NoBonus << NoBonus << NoBonus << NoBonus << NoBonus <<
        DoubleWord << NoBonus << NoBonus << NoBonus << NoBonus;

    QList<SquareType> col6;
    col6 << NoBonus << TripleLetter << NoBonus << NoBonus << NoBonus <<
        TripleLetter << NoBonus << NoBonus << NoBonus << TripleLetter <<
        NoBonus << NoBonus << NoBonus << TripleLetter << NoBonus;

    QList<SquareType> col7;
    col7 << NoBonus << NoBonus << DoubleLetter << NoBonus << NoBonus <<
        NoBonus << DoubleLetter << NoBonus << DoubleLetter << NoBonus <<
        NoBonus << NoBonus << DoubleLetter << NoBonus << NoBonus;

    QList<SquareType> col8;
    col8 << TripleWord << NoBonus << NoBonus << DoubleLetter << NoBonus <<
        NoBonus << NoBonus << DoubleWord << NoBonus << NoBonus <<
        NoBonus << DoubleLetter << NoBonus << NoBonus << TripleWord;

    squareTypes << col1 << col2 << col3 << col4 << col5 << col6 << col7 <<
        col8 << col7 << col6 << col5 << col4 << col3 << col2 << col1;
}