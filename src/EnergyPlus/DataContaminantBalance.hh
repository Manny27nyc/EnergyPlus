// EnergyPlus, Copyright (c) 1996-2022, The Board of Trustees of the University of Illinois,
// The Regents of the University of California, through Lawrence Berkeley National Laboratory
// (subject to receipt of any required approvals from the U.S. Dept. of Energy), Oak Ridge
// National Laboratory, managed by UT-Battelle, Alliance for Sustainable Energy, LLC, and other
// contributors. All rights reserved.
//
// NOTICE: This Software was developed under funding from the U.S. Department of Energy and the
// U.S. Government consequently retains certain rights. As such, the U.S. Government has been
// granted for itself and others acting on its behalf a paid-up, nonexclusive, irrevocable,
// worldwide license in the Software to reproduce, distribute copies to the public, prepare
// derivative works, and perform publicly and display publicly, and to permit others to do so.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted
// provided that the following conditions are met:
//
// (1) Redistributions of source code must retain the above copyright notice, this list of
//     conditions and the following disclaimer.
//
// (2) Redistributions in binary form must reproduce the above copyright notice, this list of
//     conditions and the following disclaimer in the documentation and/or other materials
//     provided with the distribution.
//
// (3) Neither the name of the University of California, Lawrence Berkeley National Laboratory,
//     the University of Illinois, U.S. Dept. of Energy nor the names of its contributors may be
//     used to endorse or promote products derived from this software without specific prior
//     written permission.
//
// (4) Use of EnergyPlus(TM) Name. If Licensee (i) distributes the software in stand-alone form
//     without changes from the version obtained under this License, or (ii) Licensee makes a
//     reference solely to the software portion of its product, Licensee must refer to the
//     software as "EnergyPlus version X" software, where "X" is the version number Licensee
//     obtained under this License and may not use a different name for the software. Except as
//     specifically required in this Section (4), Licensee shall not use in a company name, a
//     product name, in advertising, publicity, or other promotional activities any name, trade
//     name, trademark, logo, or other designation of "EnergyPlus", "E+", "e+" or confusingly
//     similar designation, without the U.S. Department of Energy's prior written consent.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef DataContaminantBalance_hh_INCLUDED
#define DataContaminantBalance_hh_INCLUDED

// ObjexxFCL Headers
#include <ObjexxFCL/Array1D.hh>

// EnergyPlus Headers
#include <EnergyPlus/Data/BaseData.hh>
#include <EnergyPlus/DataGlobals.hh>
#include <EnergyPlus/EnergyPlus.hh>

namespace EnergyPlus {

// Forward declarations
struct EnergyPlusData;

namespace DataContaminantBalance {

    struct ContaminantData
    {
        // Members
        bool SimulateContaminants;        // A logical flag to determine whether any contaminants are simulated or not
        bool CO2Simulation;               // CO2 simulation flag
        int CO2OutdoorSchedPtr;           // CO2 outdoor level schedule pointer
        bool GenericContamSimulation;     // Generic contaminant simulation flag
        int GenericContamOutdoorSchedPtr; // Generic contaminant outdoor level schedule pointer

        // Default Constructor
        ContaminantData()
            : SimulateContaminants(false), CO2Simulation(false), CO2OutdoorSchedPtr(0), GenericContamSimulation(false),
              GenericContamOutdoorSchedPtr(0)
        {
        }
    };

    struct ZoneContControls
    {
        // Members
        std::string Name;     // Name of the contaminant controller
        std::string ZoneName; // Name of the zone
        int ActualZoneNum;
        std::string AvaiSchedule;           // Availability Schedule name
        int AvaiSchedPtr;                   // Pointer to the correct schedule
        std::string SetPointSchedName;      // Name of the schedule which determines the CO2 setpoint
        int SPSchedIndex;                   // Index for this schedule
        bool EMSOverrideCO2SetPointOn;      // EMS is calling to override CO2 setpoint
        Real64 EMSOverrideCO2SetPointValue; // value EMS is directing to use for CO2 setpoint
        int NumOfZones;                     // Number of controlled zones in the same airloop
        Array1D_int ControlZoneNum;         // Controlled zone number
        std::string ZoneMinCO2SchedName;    // Name of the schedule which determines minimum CO2 concentration
        int ZoneMinCO2SchedIndex;           // Index for this schedule
        std::string ZoneMaxCO2SchedName;    // Name of the schedule which determines maximum CO2 concentration
        int ZoneMaxCO2SchedIndex;           // Index for this schedule
        int ZoneContamControllerSchedIndex; // Index for this schedule
        std::string GCAvaiSchedule;         // Availability Schedule name for generic contamiant
        int GCAvaiSchedPtr;                 // Pointer to the correct generic contaminant availability schedule
        std::string GCSetPointSchedName;    // Name of the schedule which determines the generic contaminant setpoint
        int GCSPSchedIndex;                 // Index for this schedule
        bool EMSOverrideGCSetPointOn;       // EMS is calling to override generic contaminant setpoint
        Real64 EMSOverrideGCSetPointValue;  // value EMS is directing to use for generic contaminant setpoint

        // Default Constructor
        ZoneContControls()
            : ActualZoneNum(0), AvaiSchedPtr(0), SPSchedIndex(0), EMSOverrideCO2SetPointOn(false), EMSOverrideCO2SetPointValue(0.0), NumOfZones(0),
              ZoneMinCO2SchedIndex(0), ZoneMaxCO2SchedIndex(0), ZoneContamControllerSchedIndex(0), GCAvaiSchedPtr(0), GCSPSchedIndex(0),
              EMSOverrideGCSetPointOn(false), EMSOverrideGCSetPointValue(0.0)
        {
        }
    };

    struct ZoneSystemContaminantDemandData // Contaminent loads to be met (kg air per second)
    {
        // Members
        Real64 OutputRequiredToCO2SP;     // Load required to meet CO2 setpoint
        Real64 RemainingOutputReqToCO2SP; // Remaining load required to meet CO2 setpoint
        Real64 OutputRequiredToGCSP;      // Load required to meet generic contaminant setpoint
        Real64 RemainingOutputReqToGCSP;  // Remaining load required to meet generic contaminant setpoint

        // Default Constructor
        ZoneSystemContaminantDemandData()
            : OutputRequiredToCO2SP(0.0), RemainingOutputReqToCO2SP(0.0), OutputRequiredToGCSP(0.0), RemainingOutputReqToGCSP(0.0)
        {
        }
    };

    struct ZoneContamGenericDataConstant
    {
        // Members
        std::string Name;           // Name of the constant generic contaminant source and sink
        std::string ZoneName;       // Name of the zone
        int ActualZoneNum;          // Zone number
        Real64 GCGenerateRate;      // Generic contaminant design generation rate [m3/s]
        int GCGenerateRateSchedPtr; // Generic contaminant design generation rate schedule pointer
        Real64 GCRemovalCoef;       // Generic contaminant design removal coefficient [m3/s]
        int GCRemovalCoefSchedPtr;  // Generic contaminant design removal coefficient schedule pointer
        Real64 GCGenRate;           // Generic contaminant design generation rate [m3/s] for reporting

        // Default Constructor
        ZoneContamGenericDataConstant()
            : ActualZoneNum(0), GCGenerateRate(0.0), GCGenerateRateSchedPtr(0), GCRemovalCoef(0.0), GCRemovalCoefSchedPtr(0), GCGenRate(0.0)
        {
        }
    };

    struct ZoneContamGenericDataPDriven
    {
        // Members
        std::string Name;          // Name of the pressure driven generic contaminant source and sink
        std::string SurfName;      // Name of the surface
        int SurfNum;               // Surface number
        Real64 GCGenRateCoef;      // Generic contaminant design generation rate coefficeint [m3/s]
        int GCGenRateCoefSchedPtr; // Generic contaminant design generation rate schedule pointer
        Real64 GCExpo;             // Generic contaminant exponent []
        Real64 GCGenRate;          // Generic contaminant design generation rate [m3/s] for reporting

        // Default Constructor
        ZoneContamGenericDataPDriven() : SurfNum(0), GCGenRateCoef(0.0), GCGenRateCoefSchedPtr(0), GCExpo(0.0), GCGenRate(0.0)
        {
        }
    };

    struct ZoneContamGenericDataCutoff
    {
        // Members
        std::string Name;           // Name of the cutoff generic contaminant source and sink
        std::string ZoneName;       // Name of the zone
        int ActualZoneNum;          // Zone number
        Real64 GCGenerateRate;      // Generic contaminant design generation rate [m3/s]
        int GCGenerateRateSchedPtr; // Generic contaminant design generation rate schedule pointer
        Real64 GCCutoffValue;       // Cutoff value [ppm]
        Real64 GCGenRate;           // Generic contaminant design generation rate [m3/s] for reporting

        // Default Constructor
        ZoneContamGenericDataCutoff() : ActualZoneNum(0), GCGenerateRate(0.0), GCGenerateRateSchedPtr(0), GCCutoffValue(0.0), GCGenRate(0.0)
        {
        }
    };

    struct ZoneContamGenericDataDecay
    {
        // Members
        std::string Name;      // Name of the decay generic contaminant source and sink
        std::string ZoneName;  // Name of the zone
        int ActualZoneNum;     // Zone number
        Real64 GCInitEmiRate;  // Generic contaminant design generation rate [m3/s]
        int GCEmiRateSchedPtr; // Generic contaminant emission rate schedule pointer
        Real64 GCTime;         // Time since the styart of emission [s]
        Real64 GCDelayTime;    // Delay time constant [s]
        Real64 GCGenRate;      // Generic contaminant design generation rate [m3/s] for reporting

        // Default Constructor
        ZoneContamGenericDataDecay() : ActualZoneNum(0), GCInitEmiRate(0.0), GCEmiRateSchedPtr(0), GCTime(0.0), GCDelayTime(0.0), GCGenRate(0.0)
        {
        }
    };

    struct ZoneContamGenericDataBLDiff
    {
        // Members
        std::string Name; // Name of the boundary layer diffusion generic contaminant source
        // and sink
        std::string SurfName;   // Name of the surface
        int SurfNum;            // Surface number
        Real64 GCTranCoef;      // Generic contaminant mass transfer coefficeint [m/s]
        int GCTranCoefSchedPtr; // Generic contaminant mass transfer coefficeint schedule pointer
        Real64 GCHenryCoef;     // Generic contaminant Henry adsorption constant or
        // partition coefficient []
        Real64 GCGenRate; // Generic contaminant design generation rate [m3/s] for reporting

        // Default Constructor
        ZoneContamGenericDataBLDiff() : SurfNum(0), GCTranCoef(0.0), GCTranCoefSchedPtr(0), GCHenryCoef(0.0), GCGenRate(0.0)
        {
        }
    };

    struct ZoneContamGenericDataDVS
    {
        // Members
        std::string Name;     // Name of the deposition velocity generic contaminant sink
        std::string SurfName; // Name of the surface
        int SurfNum;          // Surface number
        Real64 GCDepoVelo;    // Generic contaminant deposition velocity [m/s]
        int GCDepoVeloPtr;    // Generic contaminant deposition velocity sink schedule pointer
        Real64 GCGenRate;     // Generic contaminant design generation rate [m3/s] for reporting

        // Default Constructor
        ZoneContamGenericDataDVS() : SurfNum(0), GCDepoVelo(0.0), GCDepoVeloPtr(0), GCGenRate(0.0)
        {
        }
    };

    struct ZoneContamGenericDataDRS
    {
        // Members
        std::string Name;     // Name of the deposition rate generic contaminant sink
        std::string ZoneName; // Name of the zone
        int ActualZoneNum;    // Zone number
        Real64 GCDepoRate;    // Generic contaminant deposition rate [m/s]
        int GCDepoRatePtr;    // Generic contaminant deposition rate sink schedule pointer
        Real64 GCGenRate;     // Generic contaminant design generation rate [m3/s] for reporting

        // Default Constructor
        ZoneContamGenericDataDRS() : ActualZoneNum(0), GCDepoRate(0.0), GCDepoRatePtr(0), GCGenRate(0.0)
        {
        }
    };

} // namespace DataContaminantBalance

struct ContaminantBalanceData : BaseGlobalStruct
{

    Array1D<Real64> ZoneCO2SetPoint;
    Array1D<Real64> CO2PredictedRate;

    Array1D<Real64> ZoneCO2Gain;             // CO2 gain from each Zone (People, equipment)
    Array1D<Real64> ZoneCO2GainFromPeople;   // CO2 gain from each Zone (From People only)
    Array1D<Real64> ZoneCO2GainExceptPeople; // Added for hybrid model, CO2 gain from each Zone (except People)

    // Zone Air Contaminant conditions variables
    Array1D<Real64> ZoneAirCO2Avg;       // AIR CO2 averaged over the zone time step
    Array1D<Real64> ZoneAirCO2;          // AIR CO2
    Array1D<Real64> CO2ZoneTimeMinus1;   // CO2 history terms for 3rd order derivative
    Array1D<Real64> CO2ZoneTimeMinus2;   // Time Minus 2 Zone Time Steps Term
    Array1D<Real64> CO2ZoneTimeMinus3;   // Time Minus 3 Zone Time Steps Term
    Array1D<Real64> CO2ZoneTimeMinus4;   // Time Minus 4 Zone Time Steps Term
    Array1D<Real64> DSCO2ZoneTimeMinus1; // DownStepped CO2 history terms for 3rd order derivative
    Array1D<Real64> DSCO2ZoneTimeMinus2; // DownStepped Time Minus 2 Zone Time Steps Term
    Array1D<Real64> DSCO2ZoneTimeMinus3; // DownStepped Time Minus 3 Zone Time Steps Term
    Array1D<Real64> DSCO2ZoneTimeMinus4; // DownStepped Time Minus 4 Zone Time Steps Term

    Array1D<Real64> ZoneAirCO2Temp;        // Temp zone air CO2 at time plus 1
    Array1D<Real64> CO2ZoneTimeMinus1Temp; // Zone air CO2 at previous timestep
    Array1D<Real64> CO2ZoneTimeMinus2Temp; // Zone air CO2 at timestep T-2
    Array1D<Real64> CO2ZoneTimeMinus3Temp; // Zone air CO2 at timestep T-3
    Array1D<Real64> ZoneAirCO2Old;         // Last Time Steps Zone AIR Humidity Ratio

    Array1D<Real64> ZoneCO2MX; // TEMPORARY ZONE CO2 TO TEST CONVERGENCE in Exact and Euler method
    Array1D<Real64> ZoneCO2M2; // TEMPORARY ZONE CO2 at timestep t-2 in Exact and Euler method
    Array1D<Real64> ZoneCO21;  // Zone CO2 at the previous time step used in Exact and Euler method

    Array1D<Real64> CONTRAT;           // Zone CO2 at the previous time step used in Exact and Euler method
    Array1D<Real64> MixingMassFlowCO2; // Mixing MASS FLOW * CO2
    int NumContControlledZones = 0;
    Real64 OutdoorCO2 = 0.0; // Outdoor CO2 level

    Array1D<Real64> ZoneAirDensityCO; // Mixing MASS FLOW * CO2
    Array1D<Real64> AZ;
    Array1D<Real64> BZ;
    Array1D<Real64> CZ;

    Array1D<Real64> ZoneGCSetPoint;
    Array1D<Real64> GCPredictedRate;

    Array1D<Real64> ZoneGCGain; // Generic contaminant gain from each Zone (People, equipment)

    // Zone Air Contaminant conditions variables
    Array1D<Real64> ZoneAirGCAvg;       // AIR generic contaminant averaged over the zone time step
    Array1D<Real64> ZoneAirGC;          // AIR generic contaminant
    Array1D<Real64> GCZoneTimeMinus1;   // Generic contaminant history terms for 3rd order derivative
    Array1D<Real64> GCZoneTimeMinus2;   // Time Minus 2 Zone Time Steps Term
    Array1D<Real64> GCZoneTimeMinus3;   // Time Minus 3 Zone Time Steps Term
    Array1D<Real64> GCZoneTimeMinus4;   // Time Minus 4 Zone Time Steps Term
    Array1D<Real64> DSGCZoneTimeMinus1; // DownStepped generic contaminant history terms for 3rd order
    // derivative
    Array1D<Real64> DSGCZoneTimeMinus2; // DownStepped Time Minus 2 Zone Time Steps Term
    Array1D<Real64> DSGCZoneTimeMinus3; // DownStepped Time Minus 3 Zone Time Steps Term
    Array1D<Real64> DSGCZoneTimeMinus4; // DownStepped Time Minus 4 Zone Time Steps Term

    Array1D<Real64> ZoneAirGCTemp;        // Temp zone air generic contaminant at time plus 1
    Array1D<Real64> GCZoneTimeMinus1Temp; // Zone air generic contaminant at previous timestep
    Array1D<Real64> GCZoneTimeMinus2Temp; // Zone air generic contaminant at timestep T-2
    Array1D<Real64> GCZoneTimeMinus3Temp; // Zone air generic contaminant at timestep T-3
    Array1D<Real64> ZoneAirGCOld;         // Last Time Steps Zone AIR generic contaminant

    Array1D<Real64> ZoneGCMX; // TEMPORARY ZONE CO2 TO TEST CONVERGENCE in Exact and Euler method
    Array1D<Real64> ZoneGCM2; // TEMPORARY ZONE CO2 at timestep t-2 in Exact and Euler method
    Array1D<Real64> ZoneGC1;  // Zone CO2 at the previous time step used in Exact and Euler method

    Array1D<Real64> CONTRATGC; // Zone generic contaminant at the previous time step used in
    // Exact and Euler method

    Array1D<Real64> MixingMassFlowGC; // Mixing MASS FLOW * generic contaminant

    Real64 OutdoorGC = 0.0; // Outdoor generic contaminant level

    Array1D<Real64> ZoneAirDensityGC; // Mixing MASS FLOW * generic contaminant
    Array1D<Real64> AZGC;
    Array1D<Real64> BZGC;
    Array1D<Real64> CZGC;

    Array1D<DataContaminantBalance::ZoneSystemContaminantDemandData> ZoneSysContDemand;
    DataContaminantBalance::ContaminantData
        Contaminant; // A logical flag to determine whether any contaminants are simulated or not | CO2 simulation flag | CO2 outdoor
    // level schedule pointer | Generic contaminant simulation flag | Generic contaminant outdoor level schedule pointer
    Array1D<DataContaminantBalance::ZoneContControls> ContaminantControlledZone;
    Array1D<DataContaminantBalance::ZoneContamGenericDataConstant> ZoneContamGenericConstant;
    Array1D<DataContaminantBalance::ZoneContamGenericDataPDriven> ZoneContamGenericPDriven;
    Array1D<DataContaminantBalance::ZoneContamGenericDataCutoff> ZoneContamGenericCutoff;
    Array1D<DataContaminantBalance::ZoneContamGenericDataDecay> ZoneContamGenericDecay;
    Array1D<DataContaminantBalance::ZoneContamGenericDataBLDiff> ZoneContamGenericBLDiff;
    Array1D<DataContaminantBalance::ZoneContamGenericDataDVS> ZoneContamGenericDVS;
    Array1D<DataContaminantBalance::ZoneContamGenericDataDRS> ZoneContamGenericDRS;

    void clear_state() override
    {
        this->ZoneCO2SetPoint.deallocate();
        this->CO2PredictedRate.deallocate();
        this->ZoneCO2Gain.deallocate();
        this->ZoneCO2GainFromPeople.deallocate();
        this->ZoneCO2GainExceptPeople.deallocate(); // Added for hybrid model
        this->ZoneAirCO2Avg.deallocate();
        this->ZoneAirCO2.deallocate();
        this->CO2ZoneTimeMinus1.deallocate();
        this->CO2ZoneTimeMinus2.deallocate();
        this->CO2ZoneTimeMinus3.deallocate();
        this->CO2ZoneTimeMinus4.deallocate();
        this->DSCO2ZoneTimeMinus1.deallocate();
        this->DSCO2ZoneTimeMinus2.deallocate();
        this->DSCO2ZoneTimeMinus3.deallocate();
        this->DSCO2ZoneTimeMinus4.deallocate();
        this->ZoneAirCO2Temp.deallocate();
        this->CO2ZoneTimeMinus1Temp.deallocate();
        this->CO2ZoneTimeMinus2Temp.deallocate();
        this->CO2ZoneTimeMinus3Temp.deallocate();
        this->ZoneAirCO2Old.deallocate();
        this->ZoneCO2MX.deallocate();
        this->ZoneCO2M2.deallocate();
        this->ZoneCO21.deallocate();
        this->CONTRAT.deallocate();
        this->MixingMassFlowCO2.deallocate();
        this->NumContControlledZones = 0;
        this->OutdoorCO2 = 0.0;
        this->ZoneAirDensityCO.deallocate();
        this->AZ.deallocate();
        this->BZ.deallocate();
        this->CZ.deallocate();
        this->ZoneGCSetPoint.deallocate();
        this->GCPredictedRate.deallocate();
        this->ZoneGCGain.deallocate();
        this->ZoneAirGCAvg.deallocate();
        this->ZoneAirGC.deallocate();
        this->GCZoneTimeMinus1.deallocate();
        this->GCZoneTimeMinus2.deallocate();
        this->GCZoneTimeMinus3.deallocate();
        this->GCZoneTimeMinus4.deallocate();
        this->DSGCZoneTimeMinus1.deallocate();
        this->DSGCZoneTimeMinus2.deallocate();
        this->DSGCZoneTimeMinus3.deallocate();
        this->DSGCZoneTimeMinus4.deallocate();
        this->ZoneAirGCTemp.deallocate();
        this->GCZoneTimeMinus1Temp.deallocate();
        this->GCZoneTimeMinus2Temp.deallocate();
        this->GCZoneTimeMinus3Temp.deallocate();
        this->ZoneAirGCOld.deallocate();
        this->ZoneGCMX.deallocate();
        this->ZoneGCM2.deallocate();
        this->ZoneGC1.deallocate();
        this->CONTRATGC.deallocate();
        this->MixingMassFlowGC.deallocate();
        this->OutdoorGC = 0.0;
        this->ZoneAirDensityGC.deallocate();
        this->AZGC.deallocate();
        this->BZGC.deallocate();
        this->CZGC.deallocate();
        this->ZoneSysContDemand.deallocate();
        this->Contaminant.SimulateContaminants = false;
        this->Contaminant.CO2Simulation = false;
        this->Contaminant.CO2OutdoorSchedPtr = 0;
        this->Contaminant.GenericContamSimulation = false;
        this->Contaminant.GenericContamOutdoorSchedPtr = 0;
        this->ContaminantControlledZone.deallocate();
        this->ZoneContamGenericConstant.deallocate();
        this->ZoneContamGenericPDriven.deallocate();
        this->ZoneContamGenericCutoff.deallocate();
        this->ZoneContamGenericDecay.deallocate();
        this->ZoneContamGenericBLDiff.deallocate();
        this->ZoneContamGenericDVS.deallocate();
        this->ZoneContamGenericDRS.deallocate();
    }
};

} // namespace EnergyPlus

#endif
