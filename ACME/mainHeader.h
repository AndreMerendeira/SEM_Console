//---------------------------------------------------------------------------------------
// mainHeader.h : Header with preprocessor instructions and function prototypes
//---------------------------------------------------------------------------------------
//
// Copyright(C) 2020 - Dr. Luis Aranda Barjola
// Universidad Nebrija - ARIES Research Center
//
// This program is free software : you can redistribute it and / or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.
//
//---------------------------------------------------------------------------------------
// INCLUDES
//---------------------------------------------------------------------------------------
#pragma once
#include <bitset>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

//---------------------------------------------------------------------------------------
// NAMESPACES
//---------------------------------------------------------------------------------------
using namespace std;

//---------------------------------------------------------------------------------------
// DEFINES
//---------------------------------------------------------------------------------------
#define BITS_IN_LINE 32				// Number of Bits in an EBD Line
#define WF_ULTRASCALE 123			// Words per Frame (UltraScale Family)
#define WF_7SERIES 101				// Words per Frame (7-Series Family)
#define WF_ULTRASCALE_P 93			// Words per Frame (UltraScale+ Family)
#define DUMMY_ULTRASCALE 141		// UltraScale EBD Header + Dummy Lines (8 + 123 + 10)
#define DUMMY_7SERIES 109			// 7-Series EBD Header + Dummy Lines (8 + 101)
#define DUMMY_ULTRASCALE_P 126		// UltraScale+ EBD Header + Dummy Lines (8 + 93 + 25)

#define KCU105_MIN_X 50				// KCU105 Minimum X Coordinate
#define KCU105_MAX_X 357			// KCU105 Maximum X Coordinate
#define KCU105_MIN_Y 0				// KCU105 Minimum Y Coordinate
#define KCU105_MAX_Y 309			// KCU105 Maximum Y Coordinate
#define KCU105_Y4 61				// KCU105 Maximum Row of Clock Region Y4
#define KCU105_Y3 123				// KCU105 Maximum Row of Clock Region Y3
#define KCU105_Y2 185				// KCU105 Maximum Row of Clock Region Y2
#define KCU105_Y1 247				// KCU105 Maximum Row of Clock Region Y1
#define KCU105_OFFSET_X 50			// KCU105 Tiles Starting Column
#define KCU105_FX 17				// KCU105 Frames per X Coordinate (Tile Column)
#define KCU105_FY 5236				// KCU105 Frames per Horizontal Clock Regions


#define ULTRA96_2_MIN_X 161				// Ultra96_2 Minimum X Coordinate
#define ULTRA96_2_MAX_X 301		// Ultra96_2 Maximum X Coordinate
#define ULTRA96_2_MIN_Y 1				// Ultra96_2 Minimum Y Coordinate
#define ULTRA96_2_MAX_Y 185			// Ultra96_2 Maximum Y Coordinate
#define ULTRA96_2_Y2 61				// Ultra96_2 Maximum Row of Clock Region Y2
#define ULTRA96_2_Y1 123				// Ultra96_2 Maximum Row of Clock Region Y1
#define ULTRA96_2_OFFSET_X 161			// Ultra96_2 Tiles Starting Column
#define ULTRA96_2_FX 24		     // Ultra96_2 Frames per X Coordinate (Tile Column)
#define ULTRA96_2_FY 3458				// Ultra96_2 Frames per Horizontal Clock Regions


#define PYNQ_MIN_X 10			// PYNQ Minimum X Coordinate
#define PYNQ_MAX_X 176			// PYNQ Maximum X Coordinate
#define PYNQ_MIN_Y 1				// PYNQ Minimum Y Coordinate
#define PYNQ_MAX_Y 155			// PYNQ Maximum Y Coordinate
#define PYNQ_Y2 51				// PYNQ Maximum Row of Clock Region Y2
#define PYNQ_Y1 103				// PYNQ Maximum Row of Clock Region Y1
#define PYNQ_OFFSET_X 10			// PYNQ Tiles Starting Column
#define PYNQ_FX 16				// PYNQ Frames per X Coordinate (Tile Column)
#define PYNQ_FY 2650				// PYNQ Frames per Horizontal Clock Regions


//---------------------------------------------------------------------------------------
// FUNCTION PROTOTYPES
//---------------------------------------------------------------------------------------
string bin2hex(bitset<BITS_IN_LINE> b, int w);
string dec2bin(unsigned long);
vector<int> ebdFrames(vector<int>, vector<int>&, int&);
string ebdName();
int ebdTranslate(string, vector<int>, vector<int>, vector<int>, int);
vector<int> welcome();
