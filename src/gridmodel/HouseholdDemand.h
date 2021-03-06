/* 
Software License Agreement (BSD License)

Copyright (c) 2013, Julian de Hoog <julian@dehoog.ca>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

 * Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above
   copyright notice, this list of conditions and the following
   disclaimer in the documentation and/or other materials provided
   with the distribution.
 * The name of the author may not be used to endorse or promote 
   products derived from this software without specific prior 
   written permission from the author.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE. 
*/

#ifndef HOUSEHOLDDEMAND_H
#define	HOUSEHOLDDEMAND_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
//#include <time.h>
#include <vector>
#include <map>

#include "../simulator/Config.h"
#include "../utility/DateTime.h"
#include "../utility/Utility.h"

struct Z_Triple {
    double Z[3];
};

class HouseholdDemand {
private:
    int simInterval;
    std::string modelType;
    std::string demandDataFile;
    std::string phaseAllocFile;
    double *randomnessVars;
    
public:
    
    HouseholdDemand(Config* config);
    virtual ~HouseholdDemand();
    
    double getDemandAt(DateTime datetime, int nmi);
    
private:
    // For profile-based demand
    std::vector<double> genericDemand[12][2]; // 12 months, weekday vs weekend, vector for intervals of day

    // For data-based demand
    int numHouses[3];   
    int totalHouses;
    std::map<int,int> housePhase;
    std::map<std::string,Z_Triple> exactDemand;


    void inputData(std::string filename, int month, int weekday);
    void inputWeekdayData(int month);
    void inputWeekendData(int month);

    void inputPhaseAllocation();
};

#endif	/* HOUSEHOLDDEMAND_H */

