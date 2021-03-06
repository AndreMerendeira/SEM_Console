//---------------------------------------------------------------------------------------
// ebdFrames.cpp : Calculate first and last frames and words to read from the EBD file
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
#include "stdafx.h"
#include "mainHeader.h"

//---------------------------------------------------------------------------------------
// FUNCTION
//---------------------------------------------------------------------------------------
vector<int> ebdFrames(vector<int> coordinates, vector<int>& words, int &clk_regions)
{
	// Variables Definition
	vector<int> frameRanges;					// Vector with EBD File Ranges

	// Obtain Device Type
	if (coordinates.at(0) == 1) {
		//----------
		// KCU105
		//----------
		// Y Lo and Y Hi belong to CLOCK REGION Y4
		if ((coordinates.at(2) >= 0) && (coordinates.at(4) <= KCU105_Y4)) {
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 4) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 4) * WF_ULTRASCALE);		// Last Frame
			words.push_back((KCU105_Y4 - coordinates.at(4)) * 2);																				// First Word
			if (coordinates.at(2) == 0) { words.push_back(WF_ULTRASCALE - 1); }
			else { words.push_back((KCU105_Y4 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 1;
		}
		// Y Lo and Y Hi belong to CLOCK REGION Y3
		else if ((coordinates.at(2) > KCU105_Y4) && (coordinates.at(4) <= KCU105_Y3)) {
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 3) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 3) * WF_ULTRASCALE);		// Last Frame
			words.push_back((KCU105_Y3 - coordinates.at(4)) * 2);																				// First Word
			if (coordinates.at(2) == (KCU105_Y4 + 1)) { words.push_back(WF_ULTRASCALE - 1); }
			else { words.push_back((KCU105_Y3 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 1;
		}
		// Y Lo and Y Hi belong to CLOCK REGION Y2
		else if ((coordinates.at(2) > KCU105_Y3) && (coordinates.at(4) <= KCU105_Y2)) {
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 2) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 2) * WF_ULTRASCALE);		// Last Frame
			words.push_back((KCU105_Y2 - coordinates.at(4)) * 2);																				// First Word
			if (coordinates.at(2) == (KCU105_Y3 + 1)) { words.push_back(WF_ULTRASCALE - 1); }
			else { words.push_back((KCU105_Y2 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 1;
		}
		// Y Lo and Y Hi belong to CLOCK REGION Y1
		else if ((coordinates.at(2) > KCU105_Y2) && (coordinates.at(4) <= KCU105_Y1)) {
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 1) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 1) * WF_ULTRASCALE);		// Last Frame
			words.push_back((KCU105_Y1 - coordinates.at(4)) * 2);																				// First Word
			if (coordinates.at(2) == (KCU105_Y2 + 1)) { words.push_back(WF_ULTRASCALE - 1); }
			else { words.push_back((KCU105_Y1 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 1;
		}
		// Y Lo and Y Hi belong to CLOCK REGION Y0
		else if ((coordinates.at(2) > KCU105_Y1) && (coordinates.at(4) <= KCU105_MAX_Y)) {
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 0) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 0) * WF_ULTRASCALE);		// Last Frame
			words.push_back((KCU105_MAX_Y - coordinates.at(4)) * 2);																			// First Word
			if (coordinates.at(2) == (KCU105_Y1 + 1)) { words.push_back(WF_ULTRASCALE - 1); }
			else { words.push_back((KCU105_MAX_Y - coordinates.at(2)) * 2 + 1); }																// Last Word
			clk_regions = 1;
		}
		// Y Lo belongs to CLOCK REGION Y4 and Y Hi belongs to CLOCK REGION Y3
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= KCU105_Y4)) && ((coordinates.at(4) > KCU105_Y4) && (coordinates.at(4) <= KCU105_Y3))) {
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 3) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 3) * WF_ULTRASCALE);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 4) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 4) * WF_ULTRASCALE);		// Last Frame
			if (coordinates.at(4) == (KCU105_Y4 + 1)) { words.push_back(WF_ULTRASCALE - 1); }
			else { words.push_back((KCU105_Y3 - coordinates.at(4)) * 2); }																		// First Word
			words.push_back(WF_ULTRASCALE - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == 0) { words.push_back(WF_ULTRASCALE - 1); }
			else { words.push_back((KCU105_Y4 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 2;
		}
		// Y Lo belongs to CLOCK REGION Y3 and Y Hi belongs to CLOCK REGION Y2
		else if (((coordinates.at(2) > KCU105_Y4) && (coordinates.at(2) <= KCU105_Y3)) && ((coordinates.at(4) > KCU105_Y3) && (coordinates.at(4) <= KCU105_Y2))) {
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 2) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 2) * WF_ULTRASCALE);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 3) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 3) * WF_ULTRASCALE);		// Last Frame
			if (coordinates.at(4) == (KCU105_Y3 + 1)) { words.push_back(WF_ULTRASCALE - 1); }
			else { words.push_back((KCU105_Y2 - coordinates.at(4)) * 2); }																		// First Word
			words.push_back(WF_ULTRASCALE - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == (KCU105_Y4 + 1)) { words.push_back(WF_ULTRASCALE - 1); }
			else { words.push_back((KCU105_Y3 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 2;
		}
		// Y Lo belongs to CLOCK REGION Y2 and Y Hi belongs to CLOCK REGION Y1
		else if (((coordinates.at(2) > KCU105_Y3) && (coordinates.at(2) <= KCU105_Y2)) && ((coordinates.at(4) > KCU105_Y2) && (coordinates.at(4) <= KCU105_Y1))) {
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 1) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 1) * WF_ULTRASCALE);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 2) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 2) * WF_ULTRASCALE);		// Last Frame
			if (coordinates.at(4) == (KCU105_Y2 + 1)) { words.push_back(WF_ULTRASCALE - 1); }
			else { words.push_back((KCU105_Y1 - coordinates.at(4)) * 2); }																		// First Word
			words.push_back(WF_ULTRASCALE - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == (KCU105_Y3 + 1)) { words.push_back(WF_ULTRASCALE - 1); }
			else { words.push_back((KCU105_Y2 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 2;
		}
		// Y Lo belongs to CLOCK REGION Y1 and Y Hi belongs to CLOCK REGION Y0
		else if (((coordinates.at(2) > KCU105_Y2) && (coordinates.at(2) <= KCU105_Y1)) && ((coordinates.at(4) > KCU105_Y1) && (coordinates.at(4) <= KCU105_MAX_Y))) {
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 0) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 0) * WF_ULTRASCALE);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 1) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 1) * WF_ULTRASCALE);		// Last Frame
			if (coordinates.at(4) == (KCU105_Y1 + 1)) { words.push_back(WF_ULTRASCALE - 1); }
			else { words.push_back((KCU105_MAX_Y - coordinates.at(4)) * 2); }																	// First Word
			words.push_back(WF_ULTRASCALE - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == (KCU105_Y2 + 1)) { words.push_back(WF_ULTRASCALE - 1); }
			else { words.push_back((KCU105_Y1 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 2;
		}
		// Y Lo belongs to CLOCK REGION Y4 and Y Hi belongs to CLOCK REGION Y2
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= KCU105_Y4)) && ((coordinates.at(4) > KCU105_Y3) && (coordinates.at(4) <= KCU105_Y2))) {
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 2) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 2) * WF_ULTRASCALE);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 3) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 3) * WF_ULTRASCALE);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 4) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 4) * WF_ULTRASCALE);		// Last Frame
			if (coordinates.at(4) == (KCU105_Y3 + 1)) { words.push_back(WF_ULTRASCALE - 1); }
			else { words.push_back((KCU105_Y2 - coordinates.at(4)) * 2); }																		// First Word
			words.push_back(WF_ULTRASCALE - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == 0) { words.push_back(WF_ULTRASCALE - 1); }
			else { words.push_back((KCU105_Y4 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 3;
		}
		// Y Lo belongs to CLOCK REGION Y3 and Y Hi belongs to CLOCK REGION Y1
		else if (((coordinates.at(2) > KCU105_Y4) && (coordinates.at(2) <= KCU105_Y3)) && ((coordinates.at(4) > KCU105_Y2) && (coordinates.at(4) <= KCU105_Y1))) {
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 1) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 1) * WF_ULTRASCALE);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 2) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 2) * WF_ULTRASCALE);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 3) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 3) * WF_ULTRASCALE);		// Last Frame
			if (coordinates.at(4) == (KCU105_Y2 + 1)) { words.push_back(WF_ULTRASCALE - 1); }
			else { words.push_back((KCU105_Y1 - coordinates.at(4)) * 2); }																		// First Word
			words.push_back(WF_ULTRASCALE - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == (KCU105_Y4 + 1)) { words.push_back(WF_ULTRASCALE - 1); }
			else { words.push_back((KCU105_Y3 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 3;
		}
		// Y Lo belongs to CLOCK REGION Y2 and Y Hi belongs to CLOCK REGION Y0
		else if (((coordinates.at(2) > KCU105_Y3) && (coordinates.at(2) <= KCU105_Y2)) && ((coordinates.at(4) > KCU105_Y1) && (coordinates.at(4) <= KCU105_MAX_Y))) {
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 0) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 0) * WF_ULTRASCALE);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 1) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 1) * WF_ULTRASCALE);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 2) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 2) * WF_ULTRASCALE);		// Last Frame
			if (coordinates.at(4) == (KCU105_Y1 + 1)) { words.push_back(WF_ULTRASCALE - 1); }
			else { words.push_back((KCU105_MAX_Y - coordinates.at(4)) * 2); }																	// First Word
			words.push_back(WF_ULTRASCALE - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == (KCU105_Y3 + 1)) { words.push_back(WF_ULTRASCALE - 1); }
			else { words.push_back((KCU105_Y2 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 3;
		}
		// Y Lo belongs to CLOCK REGION Y4 and Y Hi belongs to CLOCK REGION Y1
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= KCU105_Y4)) && ((coordinates.at(4) > KCU105_Y2) && (coordinates.at(4) <= KCU105_Y1))) {
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 1) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 1) * WF_ULTRASCALE);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 2) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 2) * WF_ULTRASCALE);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 3) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 3) * WF_ULTRASCALE);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 4) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 4) * WF_ULTRASCALE);		// Last Frame
			if (coordinates.at(4) == (KCU105_Y2 + 1)) { words.push_back(WF_ULTRASCALE - 1); }
			else { words.push_back((KCU105_Y1 - coordinates.at(4)) * 2); }																		// First Word
			words.push_back(WF_ULTRASCALE - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == 0) { words.push_back(WF_ULTRASCALE - 1); }
			else { words.push_back((KCU105_Y4 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 4;
		}
		// Y Lo belongs to CLOCK REGION Y3 and Y Hi belongs to CLOCK REGION Y0
		else if (((coordinates.at(2) > KCU105_Y4) && (coordinates.at(2) <= KCU105_Y3)) && ((coordinates.at(4) > KCU105_Y1) && (coordinates.at(4) <= KCU105_MAX_Y))) {
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 0) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 0) * WF_ULTRASCALE);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 1) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 1) * WF_ULTRASCALE);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 2) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 2) * WF_ULTRASCALE);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 3) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 3) * WF_ULTRASCALE);		// Last Frame
			if (coordinates.at(4) == (KCU105_Y1 + 1)) { words.push_back(WF_ULTRASCALE - 1); }
			else { words.push_back((KCU105_MAX_Y - coordinates.at(4)) * 2); }																	// First Word
			words.push_back(WF_ULTRASCALE - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == (KCU105_Y4 + 1)) { words.push_back(WF_ULTRASCALE - 1); }
			else { words.push_back((KCU105_Y3 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 4;
		}
		// Y Lo belongs to CLOCK REGION Y4 and Y Hi belongs to CLOCK REGION Y0
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= KCU105_Y4)) && ((coordinates.at(4) > KCU105_Y1) && (coordinates.at(4) <= KCU105_MAX_Y))) {
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 0) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 0) * WF_ULTRASCALE);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 1) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 1) * WF_ULTRASCALE);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 2) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 2) * WF_ULTRASCALE);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 3) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 3) * WF_ULTRASCALE);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - KCU105_OFFSET_X) * KCU105_FX + KCU105_FY * 4) * WF_ULTRASCALE);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - KCU105_OFFSET_X) * KCU105_FX + (KCU105_FX - 1) + KCU105_FY * 4) * WF_ULTRASCALE);		// Last Frame
			if (coordinates.at(4) == (KCU105_Y1 + 1)) { words.push_back(WF_ULTRASCALE - 1); }
			else { words.push_back((KCU105_MAX_Y - coordinates.at(4)) * 2); }																	// First Word
			words.push_back(WF_ULTRASCALE - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == 0) { words.push_back(WF_ULTRASCALE - 1); }
			else { words.push_back((KCU105_Y4 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 5;
		}
		// Erroneus Data
		else {
			cout << "-> ERROR, incorrect range" << endl;
			exit(EXIT_FAILURE);
		}
	}
  // Obtain Device Type
	else if (coordinates.at(0) == 2) {
		//----------
		// Ultra96-V2
		//----------
		// Y Lo and Y Hi belong to CLOCK REGION Y2
		if ((coordinates.at(2) >= 0) && (coordinates.at(4) <= ULTRA96_2_Y2)) {
			frameRanges.push_back(((coordinates.at(1) - ULTRA96_2_OFFSET_X) * ULTRA96_2_FX + ULTRA96_2_FY * 2) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ULTRA96_2_OFFSET_X) * ULTRA96_2_FX + (ULTRA96_2_FX - 1) + ULTRA96_2_FY * 2) * WF_ULTRASCALE_P);		// Last Frame
			words.push_back((ULTRA96_2_Y2 - coordinates.at(4)) * 2);																				// First Word
			if (coordinates.at(2) == 0) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ULTRA96_2_Y2 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 1;
		}
		// Y Lo and Y Hi belong to CLOCK REGION Y1
		else if ((coordinates.at(2) > ULTRA96_2_Y2) && (coordinates.at(4) <= ULTRA96_2_Y1)) {
			frameRanges.push_back(((coordinates.at(1) - ULTRA96_2_OFFSET_X) * ULTRA96_2_FX + ULTRA96_2_FY * 1) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ULTRA96_2_OFFSET_X) * ULTRA96_2_FX + (ULTRA96_2_FX - 1) + ULTRA96_2_FY * 1) * WF_ULTRASCALE_P);		// Last Frame
			words.push_back((ULTRA96_2_Y1 - coordinates.at(4)) * 2);																				// First Word
			if (coordinates.at(2) == (ULTRA96_2_Y2 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ULTRA96_2_Y1 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 1;
		}
		// Y Lo and Y Hi belong to CLOCK REGION Y0
		else if ((coordinates.at(2) > ULTRA96_2_Y1) && (coordinates.at(4) <= ULTRA96_2_MAX_Y)) {
			frameRanges.push_back(((coordinates.at(1) - ULTRA96_2_OFFSET_X) * ULTRA96_2_FX + ULTRA96_2_FY * 0) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ULTRA96_2_OFFSET_X) * ULTRA96_2_FX + (ULTRA96_2_FX - 1) + ULTRA96_2_FY * 0) * WF_ULTRASCALE_P);		// Last Frame
			words.push_back((ULTRA96_2_MAX_Y - coordinates.at(4)) * 2);																			// First Word
			if (coordinates.at(2) == (ULTRA96_2_Y1 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ULTRA96_2_MAX_Y - coordinates.at(2)) * 2 + 1); }																// Last Word
			clk_regions = 1;
		}
		// Y Lo belongs to CLOCK REGION Y2 and Y Hi belongs to CLOCK REGION Y1
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= ULTRA96_2_Y2)) && ((coordinates.at(4) > ULTRA96_2_Y2) && (coordinates.at(4) <= ULTRA96_2_Y1))) {
      frameRanges.push_back(((coordinates.at(1) - ULTRA96_2_OFFSET_X) * ULTRA96_2_FX + ULTRA96_2_FY * 1) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ULTRA96_2_OFFSET_X) * ULTRA96_2_FX + (ULTRA96_2_FX - 1) + ULTRA96_2_FY * 1) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ULTRA96_2_OFFSET_X) * ULTRA96_2_FX + ULTRA96_2_FY * 2) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ULTRA96_2_OFFSET_X) * ULTRA96_2_FX + (ULTRA96_2_FX - 1) + ULTRA96_2_FY * 2) * WF_ULTRASCALE_P);		// Last Frame
			if (coordinates.at(4) == (ULTRA96_2_Y2 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ULTRA96_2_Y1 - coordinates.at(4)) * 2); }																		// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == 0) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ULTRA96_2_Y2 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 2;
		}
		// Y Lo belongs to CLOCK REGION Y1 and Y Hi belongs to CLOCK REGION Y0
		else if (((coordinates.at(2) > ULTRA96_2_Y2) && (coordinates.at(2) <= ULTRA96_2_Y1)) && ((coordinates.at(4) > ULTRA96_2_Y1) && (coordinates.at(4) <= ULTRA96_2_MAX_Y))) {
      frameRanges.push_back(((coordinates.at(1) - ULTRA96_2_OFFSET_X) * ULTRA96_2_FX + ULTRA96_2_FY * 0) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ULTRA96_2_OFFSET_X) * ULTRA96_2_FX + (ULTRA96_2_FX - 1) + ULTRA96_2_FY * 0) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ULTRA96_2_OFFSET_X) * ULTRA96_2_FX + ULTRA96_2_FY * 1) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ULTRA96_2_OFFSET_X) * ULTRA96_2_FX + (ULTRA96_2_FX - 1) + ULTRA96_2_FY * 1) * WF_ULTRASCALE_P);		// Last Frame
			if (coordinates.at(4) == (ULTRA96_2_Y1 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ULTRA96_2_MAX_Y - coordinates.at(4)) * 2); }																	// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == (ULTRA96_2_Y2 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ULTRA96_2_Y1 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 2;
		}
		// Y Lo belongs to CLOCK REGION Y2 and Y Hi belongs to CLOCK REGION Y0
		else if (((coordinates.at(2) > 0) && (coordinates.at(2) <= ULTRA96_2_Y2)) && ((coordinates.at(4) > ULTRA96_2_Y1) && (coordinates.at(4) <= ULTRA96_2_MAX_Y))) {
      frameRanges.push_back(((coordinates.at(1) - ULTRA96_2_OFFSET_X) * ULTRA96_2_FX + ULTRA96_2_FY * 0) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ULTRA96_2_OFFSET_X) * ULTRA96_2_FX + (ULTRA96_2_FX - 1) + ULTRA96_2_FY * 0) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ULTRA96_2_OFFSET_X) * ULTRA96_2_FX + ULTRA96_2_FY * 1) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ULTRA96_2_OFFSET_X) * ULTRA96_2_FX + (ULTRA96_2_FX - 1) + ULTRA96_2_FY * 1) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ULTRA96_2_OFFSET_X) * ULTRA96_2_FX + ULTRA96_2_FY * 2) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ULTRA96_2_OFFSET_X) * ULTRA96_2_FX + (ULTRA96_2_FX - 1) + ULTRA96_2_FY * 2) * WF_ULTRASCALE_P);		// Last Frame
			if (coordinates.at(4) == (ULTRA96_2_Y1 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ULTRA96_2_MAX_Y - coordinates.at(4)) * 2); }																	// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == (0 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ULTRA96_2_Y2 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 3;
		}
    // Erroneus Data
    else {
      cout << "-> ERROR, incorrect range" << endl;
      exit(EXIT_FAILURE);
    }
  }
  // Obtain Device Type
  else if (coordinates.at(0) == 3) {
    //----------
    // PYNQ-Z2
    //----------
    // Y Lo and Y Hi belong to CLOCK REGION Y2
    if ((coordinates.at(2) >= 0) && (coordinates.at(4) <= PYNQ_Y2)) {
      frameRanges.push_back(((coordinates.at(1) - PYNQ_OFFSET_X) * PYNQ_FX + PYNQ_FY * 2) * WF_7SERIES);							// First Frame
      frameRanges.push_back(((coordinates.at(3) - PYNQ_OFFSET_X) * PYNQ_FX + (PYNQ_FX - 1) + PYNQ_FY * 2) * WF_7SERIES);		// Last Frame
      words.push_back((PYNQ_Y2 - coordinates.at(4)) * 2);																				// First Word
      if (coordinates.at(2) == 0) { words.push_back(WF_7SERIES - 1); }
      else { words.push_back((PYNQ_Y2 - coordinates.at(2)) * 2 + 1); }																	// Last Word
      clk_regions = 1;
    }
    // Y Lo and Y Hi belong to CLOCK REGION Y1
    else if ((coordinates.at(2) > PYNQ_Y2) && (coordinates.at(4) <= PYNQ_Y1)) {
      frameRanges.push_back(((coordinates.at(1) - PYNQ_OFFSET_X) * PYNQ_FX + PYNQ_FY * 1) * WF_7SERIES);							// First Frame
      frameRanges.push_back(((coordinates.at(3) - PYNQ_OFFSET_X) * PYNQ_FX + (PYNQ_FX - 1) + PYNQ_FY * 1) * WF_7SERIES);		// Last Frame
      words.push_back((PYNQ_Y1 - coordinates.at(4)) * 2);																				// First Word
      if (coordinates.at(2) == (PYNQ_Y2 + 1)) { words.push_back(WF_7SERIES - 1); }
      else { words.push_back((PYNQ_Y1 - coordinates.at(2)) * 2 + 1); }																	// Last Word
      clk_regions = 1;
    }
    // Y Lo and Y Hi belong to CLOCK REGION Y0
    else if ((coordinates.at(2) > PYNQ_Y1) && (coordinates.at(4) <= PYNQ_MAX_Y)) {
      frameRanges.push_back(((coordinates.at(1) - PYNQ_OFFSET_X) * PYNQ_FX + PYNQ_FY * 0) * WF_7SERIES);							// First Frame
      frameRanges.push_back(((coordinates.at(3) - PYNQ_OFFSET_X) * PYNQ_FX + (PYNQ_FX - 1) + PYNQ_FY * 0) * WF_7SERIES);		// Last Frame
      words.push_back((PYNQ_MAX_Y - coordinates.at(4)) * 2);																			// First Word
      if (coordinates.at(2) == (PYNQ_Y1 + 1)) { words.push_back(WF_7SERIES - 1); }
      else { words.push_back((PYNQ_MAX_Y - coordinates.at(2)) * 2 + 1); }																// Last Word
      clk_regions = 1;
    }
    // Y Lo belongs to CLOCK REGION Y2 and Y Hi belongs to CLOCK REGION Y1
    else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= PYNQ_Y2)) && ((coordinates.at(4) > PYNQ_Y2) && (coordinates.at(4) <= PYNQ_Y1))) {
      frameRanges.push_back(((coordinates.at(1) - PYNQ_OFFSET_X) * PYNQ_FX + PYNQ_FY * 1) * WF_7SERIES);							// First Frame
      frameRanges.push_back(((coordinates.at(3) - PYNQ_OFFSET_X) * PYNQ_FX + (PYNQ_FX - 1) + PYNQ_FY * 1) * WF_7SERIES);		// Last Frame
      frameRanges.push_back(((coordinates.at(1) - PYNQ_OFFSET_X) * PYNQ_FX + PYNQ_FY * 2) * WF_7SERIES);							// First Frame
      frameRanges.push_back(((coordinates.at(3) - PYNQ_OFFSET_X) * PYNQ_FX + (PYNQ_FX - 1) + PYNQ_FY * 2) * WF_7SERIES);		// Last Frame
      if (coordinates.at(4) == (PYNQ_Y2 + 1)) { words.push_back(WF_7SERIES - 1); }
      else { words.push_back((PYNQ_Y1 - coordinates.at(4)) * 2); }																		// First Word
      words.push_back(WF_7SERIES - 1);																									// Last Word
      words.push_back(0);																													// First Word
      if (coordinates.at(2) == 0) { words.push_back(WF_7SERIES - 1); }
      else { words.push_back((PYNQ_Y2 - coordinates.at(2)) * 2 + 1); }																	// Last Word
      clk_regions = 2;
    }
    // Y Lo belongs to CLOCK REGION Y1 and Y Hi belongs to CLOCK REGION Y0
    else if (((coordinates.at(2) > PYNQ_Y2) && (coordinates.at(2) <= PYNQ_Y1)) && ((coordinates.at(4) > PYNQ_Y1) && (coordinates.at(4) <= PYNQ_MAX_Y))) {
      frameRanges.push_back(((coordinates.at(1) - PYNQ_OFFSET_X) * PYNQ_FX + PYNQ_FY * 0) * WF_7SERIES);							// First Frame
      frameRanges.push_back(((coordinates.at(3) - PYNQ_OFFSET_X) * PYNQ_FX + (PYNQ_FX - 1) + PYNQ_FY * 0) * WF_7SERIES);		// Last Frame
      frameRanges.push_back(((coordinates.at(1) - PYNQ_OFFSET_X) * PYNQ_FX + PYNQ_FY * 1) * WF_7SERIES);							// First Frame
      frameRanges.push_back(((coordinates.at(3) - PYNQ_OFFSET_X) * PYNQ_FX + (PYNQ_FX - 1) + PYNQ_FY * 1) * WF_7SERIES);		// Last Frame
      if (coordinates.at(4) == (PYNQ_Y1 + 1)) { words.push_back(WF_7SERIES - 1); }
      else { words.push_back((PYNQ_MAX_Y - coordinates.at(4)) * 2); }																	// First Word
      words.push_back(WF_7SERIES - 1);																									// Last Word
      words.push_back(0);																													// First Word
      if (coordinates.at(2) == (PYNQ_Y2 + 1)) { words.push_back(WF_7SERIES - 1); }
      else { words.push_back((PYNQ_Y1 - coordinates.at(2)) * 2 + 1); }																	// Last Word
      clk_regions = 2;
    }
    // Y Lo belongs to CLOCK REGION Y2 and Y Hi belongs to CLOCK REGION Y0
    else if (((coordinates.at(2) > 0) && (coordinates.at(2) <= PYNQ_Y2)) && ((coordinates.at(4) > PYNQ_Y1) && (coordinates.at(4) <= PYNQ_MAX_Y))) {
      frameRanges.push_back(((coordinates.at(1) - PYNQ_OFFSET_X) * PYNQ_FX + PYNQ_FY * 0) * WF_7SERIES);							// First Frame
      frameRanges.push_back(((coordinates.at(3) - PYNQ_OFFSET_X) * PYNQ_FX + (PYNQ_FX - 1) + PYNQ_FY * 0) * WF_7SERIES);		// Last Frame
      frameRanges.push_back(((coordinates.at(1) - PYNQ_OFFSET_X) * PYNQ_FX + PYNQ_FY * 1) * WF_7SERIES);							// First Frame
      frameRanges.push_back(((coordinates.at(3) - PYNQ_OFFSET_X) * PYNQ_FX + (PYNQ_FX - 1) + PYNQ_FY * 1) * WF_7SERIES);		// Last Frame
      frameRanges.push_back(((coordinates.at(1) - PYNQ_OFFSET_X) * PYNQ_FX + PYNQ_FY * 2) * WF_7SERIES);							// First Frame
      frameRanges.push_back(((coordinates.at(3) - PYNQ_OFFSET_X) * PYNQ_FX + (PYNQ_FX - 1) + PYNQ_FY * 2) * WF_7SERIES);		// Last Frame
      if (coordinates.at(4) == (PYNQ_Y1 + 1)) { words.push_back(WF_7SERIES - 1); }
      else { words.push_back((PYNQ_MAX_Y - coordinates.at(4)) * 2); }																	// First Word
      words.push_back(WF_7SERIES - 1);																									// Last Word
      words.push_back(0);																													// First Word
      words.push_back(WF_7SERIES - 1);																									// Last Word
      words.push_back(0);																													// First Word
      if (coordinates.at(2) == (0 + 1)) { words.push_back(WF_7SERIES - 1); }
      else { words.push_back((PYNQ_Y2 - coordinates.at(2)) * 2 + 1); }																	// Last Word
      clk_regions = 3;
    }
    // Erroneus Data
    else {
      cout << "-> ERROR, incorrect range" << endl;
      exit(EXIT_FAILURE);
    }
  }
  // Obtain Device Type
	else if (coordinates.at(0) == 4) {
		//----------
		// ZCU104
		//----------

    // Y Lo and Y Hi belong to CLOCK REGION Y5
		if ((coordinates.at(2) >= 0) && (coordinates.at(4) <= ZCU104_Y5)) {
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 5) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 5) * WF_ULTRASCALE_P);		// Last Frame
			words.push_back((ZCU104_Y5 - coordinates.at(4)) * 2);																				// First Word
			if (coordinates.at(2) == 0) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y5 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 1;
		}
		// Y Lo and Y Hi belong to CLOCK REGION Y4
		else if ((coordinates.at(2) >= ZCU104_Y5) && (coordinates.at(4) <= ZCU104_Y4)) {
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 4) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 4) * WF_ULTRASCALE_P);		// Last Frame
			words.push_back((ZCU104_Y4 - coordinates.at(4)) * 2);																				// First Word
			if (coordinates.at(2) == 0) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y4 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 1;
		}
		// Y Lo and Y Hi belong to CLOCK REGION Y3
		else if ((coordinates.at(2) > ZCU104_Y4) && (coordinates.at(4) <= ZCU104_Y3)) {
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 3) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 3) * WF_ULTRASCALE_P);		// Last Frame
			words.push_back((ZCU104_Y3 - coordinates.at(4)) * 2);																				// First Word
			if (coordinates.at(2) == (ZCU104_Y4 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y3 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 1;
		}
		// Y Lo and Y Hi belong to CLOCK REGION Y2
		else if ((coordinates.at(2) > ZCU104_Y3) && (coordinates.at(4) <= ZCU104_Y2)) {
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 2) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 2) * WF_ULTRASCALE_P);		// Last Frame
			words.push_back((ZCU104_Y2 - coordinates.at(4)) * 2);																				// First Word
			if (coordinates.at(2) == (ZCU104_Y3 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y2 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 1;
		}
		// Y Lo and Y Hi belong to CLOCK REGION Y1
		else if ((coordinates.at(2) > ZCU104_Y2) && (coordinates.at(4) <= ZCU104_Y1)) {
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 1) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 1) * WF_ULTRASCALE_P);		// Last Frame
			words.push_back((ZCU104_Y1 - coordinates.at(4)) * 2);																				// First Word
			if (coordinates.at(2) == (ZCU104_Y2 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y1 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 1;
		}
		// Y Lo and Y Hi belong to CLOCK REGION Y0
		else if ((coordinates.at(2) > ZCU104_Y1) && (coordinates.at(4) <= ZCU104_MAX_Y)) {
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 0) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 0) * WF_ULTRASCALE_P);		// Last Frame
			words.push_back((ZCU104_MAX_Y - coordinates.at(4)) * 2);																			// First Word
			if (coordinates.at(2) == (ZCU104_Y1 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_MAX_Y - coordinates.at(2)) * 2 + 1); }																// Last Word
			clk_regions = 1;
		}


    // Y Lo belongs to CLOCK REGION Y5 and Y Hi belongs to CLOCK REGION Y4
    else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= ZCU104_Y5)) && ((coordinates.at(4) > ZCU104_Y5) && (coordinates.at(4) <= ZCU104_Y4))) {
      frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 4) * WF_ULTRASCALE_P);							// First Frame
      frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 4) * WF_ULTRASCALE_P);		// Last Frame
      frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 5) * WF_ULTRASCALE_P);							// First Frame
      frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 5) * WF_ULTRASCALE_P);		// Last Frame
      if (coordinates.at(4) == (ZCU104_Y5 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
      else { words.push_back((ZCU104_Y4 - coordinates.at(4)) * 2); }																		// First Word
      words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
      words.push_back(0);																													// First Word
      if (coordinates.at(2) == 0) { words.push_back(WF_ULTRASCALE_P - 1); }
      else { words.push_back((ZCU104_Y5 - coordinates.at(2)) * 2 + 1); }																	// Last Word
      clk_regions = 2;
    }
		// Y Lo belongs to CLOCK REGION Y4 and Y Hi belongs to CLOCK REGION Y3
		else if (((coordinates.at(2) >= ZCU104_Y5) && (coordinates.at(2) <= ZCU104_Y4)) && ((coordinates.at(4) > ZCU104_Y4) && (coordinates.at(4) <= ZCU104_Y3))) {
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 3) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 3) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 4) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 4) * WF_ULTRASCALE_P);		// Last Frame
			if (coordinates.at(4) == (ZCU104_Y4 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y3 - coordinates.at(4)) * 2); }																		// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == ZCU104_Y5) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y4 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 2;
		}
		// Y Lo belongs to CLOCK REGION Y3 and Y Hi belongs to CLOCK REGION Y2
		else if (((coordinates.at(2) > ZCU104_Y4) && (coordinates.at(2) <= ZCU104_Y3)) && ((coordinates.at(4) > ZCU104_Y3) && (coordinates.at(4) <= ZCU104_Y2))) {
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 2) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 2) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 3) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 3) * WF_ULTRASCALE_P);		// Last Frame
			if (coordinates.at(4) == (ZCU104_Y3 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y2 - coordinates.at(4)) * 2); }																		// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == (ZCU104_Y4 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y3 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 2;
		}
		// Y Lo belongs to CLOCK REGION Y2 and Y Hi belongs to CLOCK REGION Y1
		else if (((coordinates.at(2) > ZCU104_Y3) && (coordinates.at(2) <= ZCU104_Y2)) && ((coordinates.at(4) > ZCU104_Y2) && (coordinates.at(4) <= ZCU104_Y1))) {
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 1) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 1) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 2) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 2) * WF_ULTRASCALE_P);		// Last Frame
			if (coordinates.at(4) == (ZCU104_Y2 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y1 - coordinates.at(4)) * 2); }																		// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == (ZCU104_Y3 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y2 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 2;
		}
		// Y Lo belongs to CLOCK REGION Y1 and Y Hi belongs to CLOCK REGION Y0
		else if (((coordinates.at(2) > ZCU104_Y2) && (coordinates.at(2) <= ZCU104_Y1)) && ((coordinates.at(4) > ZCU104_Y1) && (coordinates.at(4) <= ZCU104_MAX_Y))) {
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 0) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 0) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 1) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 1) * WF_ULTRASCALE_P);		// Last Frame
			if (coordinates.at(4) == (ZCU104_Y1 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_MAX_Y - coordinates.at(4)) * 2); }																	// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == (ZCU104_Y2 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y1 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 2;
		}


    // Y Lo belongs to CLOCK REGION Y5 and Y Hi belongs to CLOCK REGION Y3
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= ZCU104_Y5)) && ((coordinates.at(4) > ZCU104_Y4) && (coordinates.at(4) <= ZCU104_Y3))) {
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 3) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 3) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 4) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 4) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 5) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 5) * WF_ULTRASCALE_P);		// Last Frame
			if (coordinates.at(4) == (ZCU104_Y4 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y3 - coordinates.at(4)) * 2); }																		// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == 0) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y5 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 3;
		}
		// Y Lo belongs to CLOCK REGION Y4 and Y Hi belongs to CLOCK REGION Y2
		else if (((coordinates.at(2) >= ZCU104_Y5) && (coordinates.at(2) <= ZCU104_Y4)) && ((coordinates.at(4) > ZCU104_Y3) && (coordinates.at(4) <= ZCU104_Y2))) {
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 2) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 2) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 3) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 3) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 4) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 4) * WF_ULTRASCALE_P);		// Last Frame
			if (coordinates.at(4) == (ZCU104_Y3 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y2 - coordinates.at(4)) * 2); }																		// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == ZCU104_Y5) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y4 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 3;
		}
		// Y Lo belongs to CLOCK REGION Y3 and Y Hi belongs to CLOCK REGION Y1
		else if (((coordinates.at(2) > ZCU104_Y4) && (coordinates.at(2) <= ZCU104_Y3)) && ((coordinates.at(4) > ZCU104_Y2) && (coordinates.at(4) <= ZCU104_Y1))) {
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 1) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 1) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 2) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 2) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 3) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 3) * WF_ULTRASCALE_P);		// Last Frame
			if (coordinates.at(4) == (ZCU104_Y2 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y1 - coordinates.at(4)) * 2); }																		// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == (ZCU104_Y4 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y3 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 3;
		}
		// Y Lo belongs to CLOCK REGION Y2 and Y Hi belongs to CLOCK REGION Y0
		else if (((coordinates.at(2) > ZCU104_Y3) && (coordinates.at(2) <= ZCU104_Y2)) && ((coordinates.at(4) > ZCU104_Y1) && (coordinates.at(4) <= ZCU104_MAX_Y))) {
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 0) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 0) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 1) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 1) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 2) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 2) * WF_ULTRASCALE_P);		// Last Frame
			if (coordinates.at(4) == (ZCU104_Y1 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_MAX_Y - coordinates.at(4)) * 2); }																	// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == (ZCU104_Y3 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y2 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 3;
		}


    // Y Lo belongs to CLOCK REGION Y5 and Y Hi belongs to CLOCK REGION Y2
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= ZCU104_Y5)) && ((coordinates.at(4) > ZCU104_Y3) && (coordinates.at(4) <= ZCU104_Y2))) {
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 2) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 2) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 3) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 3) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 4) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 4) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 5) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 5) * WF_ULTRASCALE_P);		// Last Frame
			if (coordinates.at(4) == (ZCU104_Y3 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y2 - coordinates.at(4)) * 2); }																		// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == 0) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y5 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 4;
		}
		// Y Lo belongs to CLOCK REGION Y4 and Y Hi belongs to CLOCK REGION Y1
		else if (((coordinates.at(2) >= ZCU104_Y5) && (coordinates.at(2) <= ZCU104_Y4)) && ((coordinates.at(4) > ZCU104_Y2) && (coordinates.at(4) <= ZCU104_Y1))) {
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 1) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 1) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 2) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 2) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 3) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 3) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 4) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 4) * WF_ULTRASCALE_P);		// Last Frame
			if (coordinates.at(4) == (ZCU104_Y2 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y1 - coordinates.at(4)) * 2); }																		// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == ZCU104_Y5 + 1) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y4 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 4;
		}
		// Y Lo belongs to CLOCK REGION Y3 and Y Hi belongs to CLOCK REGION Y0
		else if (((coordinates.at(2) > ZCU104_Y4) && (coordinates.at(2) <= ZCU104_Y3)) && ((coordinates.at(4) > ZCU104_Y1) && (coordinates.at(4) <= ZCU104_MAX_Y))) {
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 0) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 0) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 1) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 1) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 2) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 2) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 3) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 3) * WF_ULTRASCALE_P);		// Last Frame
			if (coordinates.at(4) == (ZCU104_Y1 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_MAX_Y - coordinates.at(4)) * 2); }																	// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == (ZCU104_Y4 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y3 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 4;
		}


    // Y Lo belongs to CLOCK REGION Y5 and Y Hi belongs to CLOCK REGION Y1
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= ZCU104_Y5)) && ((coordinates.at(4) > ZCU104_Y2) && (coordinates.at(4) <= ZCU104_Y1))) {
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 1) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 1) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 2) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 2) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 3) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 3) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 4) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 4) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 5) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 5) * WF_ULTRASCALE_P);		// Last Frame
			if (coordinates.at(4) == (ZCU104_Y2 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y1 - coordinates.at(4)) * 2); }																	// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == 0) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y5 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 5;
		}
		// Y Lo belongs to CLOCK REGION Y4 and Y Hi belongs to CLOCK REGION Y0
		else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= ZCU104_Y4)) && ((coordinates.at(4) > ZCU104_Y1) && (coordinates.at(4) <= ZCU104_MAX_Y))) {
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 0) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 0) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 1) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 1) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 2) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 2) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 3) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 3) * WF_ULTRASCALE_P);		// Last Frame
			frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 4) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 4) * WF_ULTRASCALE_P);		// Last Frame
			if (coordinates.at(4) == (ZCU104_Y1 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_MAX_Y - coordinates.at(4)) * 2); }																	// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
			words.push_back(0);																													// First Word
			if (coordinates.at(2) == ZCU104_Y5) { words.push_back(WF_ULTRASCALE_P - 1); }
			else { words.push_back((ZCU104_Y4 - coordinates.at(2)) * 2 + 1); }																	// Last Word
			clk_regions = 5;
		}

    // TODO: Stopped here
    // Y Lo belongs to CLOCK REGION Y5 and Y Hi belongs to CLOCK REGION Y0
    else if (((coordinates.at(2) >= 0) && (coordinates.at(2) <= ZCU104_Y5)) && ((coordinates.at(4) > ZCU104_Y1) && (coordinates.at(4) <= ZCU104_MAX_Y))) {
      frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 0) * WF_ULTRASCALE_P);							// First Frame
			frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 0) * WF_ULTRASCALE_P);		// Last Frame
      frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 1) * WF_ULTRASCALE_P);							// First Frame
      frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 1) * WF_ULTRASCALE_P);		// Last Frame
      frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 2) * WF_ULTRASCALE_P);							// First Frame
      frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 2) * WF_ULTRASCALE_P);		// Last Frame
      frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 3) * WF_ULTRASCALE_P);							// First Frame
      frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 3) * WF_ULTRASCALE_P);		// Last Frame
      frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 4) * WF_ULTRASCALE_P);							// First Frame
      frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 4) * WF_ULTRASCALE_P);		// Last Frame
      frameRanges.push_back(((coordinates.at(1) - ZCU104_OFFSET_X) * ZCU104_FX + ZCU104_FY * 5) * WF_ULTRASCALE_P);							// First Frame
      frameRanges.push_back(((coordinates.at(3) - ZCU104_OFFSET_X) * ZCU104_FX + (ZCU104_FX - 1) + ZCU104_FY * 5) * WF_ULTRASCALE_P);		// Last Frame
      if (coordinates.at(4) == (ZCU104_Y1 + 1)) { words.push_back(WF_ULTRASCALE_P - 1); }
      else { words.push_back((ZCU104_MAX_Y - coordinates.at(4)) * 2); }																	// First Word
      words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
      words.push_back(0);																													// First Word
      words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
      words.push_back(0);																													// First Word
      words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
      words.push_back(0);																													// First Word
      words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
      words.push_back(0);																													// First Word
      words.push_back(WF_ULTRASCALE_P - 1);																									// Last Word
      words.push_back(0);
      if (coordinates.at(2) == 0) { words.push_back(WF_ULTRASCALE_P - 1); }
      else { words.push_back((ZCU104_Y5 - coordinates.at(2)) * 2 + 1); }																	// Last Word
      clk_regions = 6;
    }
		// Erroneus Data
		else {
			cout << "-> ERROR, incorrect range" << endl;
			exit(EXIT_FAILURE);
		}
	}
	else {
		cout << "-> ERROR, incorrect device" << endl;
		exit(EXIT_FAILURE);
	}
	return frameRanges;
}
