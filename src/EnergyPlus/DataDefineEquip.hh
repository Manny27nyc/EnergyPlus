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

#ifndef DataDefineEquip_hh_INCLUDED
#define DataDefineEquip_hh_INCLUDED

// C++ Headers
#include <memory>
// ObjexxFCL Headers
#include <ObjexxFCL/Array1D.hh>

// EnergyPlus Headers
#include <EnergyPlus/AirTerminalUnit.hh>
#include <EnergyPlus/Data/BaseData.hh>
#include <EnergyPlus/DataGlobals.hh>
#include <EnergyPlus/EnergyPlus.hh>

namespace EnergyPlus {

namespace DataDefineEquip {

    constexpr int MaxZoneAirComponents = 1;

    // Equipment Types covered by ZoneAirLoopEquipment:
    enum class ZnAirLoopEquipType
    {
        Invalid = -1,
        DualDuctConstVolume,
        DualDuctVAV,
        SingleDuctVAVReheat,
        SingleDuctVAVNoReheat,
        SingleDuctConstVolReheat,
        SingleDuctConstVolNoReheat,
        SingleDuct_SeriesPIU_Reheat,
        SingleDuct_ParallelPIU_Reheat,
        SingleDuct_ConstVol_4PipeInduc,
        SingleDuctVAVReheatVSFan,
        SingleDuctCBVAVReheat,
        SingleDuctCBVAVNoReheat,
        SingleDuctConstVolCooledBeam,
        DualDuctVAVOutdoorAir,
        SingleDuctUserDefined,
        SingleDuctATMixer,
        SingleDuctConstVolFourPipeBeam,
        Num
    };

    struct ZoneAirEquip
    {
        // Members
        std::string Name;         // Name or identifier of this piece of equipment
        int OutletNodeNum;        // index of outlet node
        int NumComponents;        // number of subcomponents (=1)
        int NumControls;          // number of controls (not used; =0)
        Array1D_string EquipType; // Pointer identifying type of subcomponent
        Array1D<DataDefineEquip::ZnAirLoopEquipType> EquipTypeEnum;
        ///// Note use of shared_ptr here is not a good pattern, not to be replicated without further discussion.
        std::shared_ptr<AirTerminalUnit> airTerminalPtr;
        Array1D_string EquipName; // name of subcomponent
        Array1D_int EquipIndex;
        int AirTerminalSizingSpecIndex; // index to DesignSpecification:AirTerminal:Sizing obect
        int TermUnitSizingNum;          // index to TermUnitSizing and TermUnitFinalZoneSizing for this air distribution unit
        Real64 UpStreamLeakFrac;        // upstream nominal leakage fraction
        Real64 DownStreamLeakFrac;      // downstream constant leakage fraction
        Real64 MassFlowRateUpStrLk;     // current air mass flow rate of the upstream leak [kg/s]
        Real64 MassFlowRateDnStrLk;     // current air mass flow rate of the downstream leak [kg/s]
        Real64 MassFlowRateTU;          // current air mass flow rate through the terminal unit [kg/s]
        Real64 MassFlowRateZSup;        // current air mass flow rate of zone supply air [kg/s]
        Real64 MassFlowRateSup;         // current air mass flow rate of supply air upstream of upstream leak [kg/s]
        Real64 MassFlowRatePlenInd;     // current air mass flow rate of induced air from plenum [kg/s]
        Real64 MaxAvailDelta;           // change in max avail mass low rate due to leaks [kg/s]
        Real64 MinAvailDelta;           // change in min avail mass low rate due to leaks [kg/s]
        int InletNodeNum;               // index of inlet node 1
        int InletNodeNum2;              // index of inlet node 2 (used for dual duct airterminals)
        int ZoneEqNum;                  // index of zone equipment object for this terminal unit
        int AirLoopNum;                 // index to airloop that this terminal unit is connected to
        Real64 LeakLoadMult;            // zome load multiplier to adjust for downstream leak
        bool UpStreamLeak;              // if true, there is an upstream leak
        bool DownStreamLeak;            // if true, there is an downstream leak
        int RetPlenumNum;               // return plenum number that this ADU can leak to, zero if none
        int ZoneNum;                    // index of the zone object for this terminal unit
        bool AccountForDOAS;            // if true user has asked for DOAS
        Real64 HeatRate;                // [W]
        Real64 CoolRate;                // [W]
        Real64 HeatGain;                // [J]
        Real64 CoolGain;                // [J]

        // Default Constructor
        ZoneAirEquip()
            : OutletNodeNum(0), NumComponents(0), NumControls(0), EquipType(MaxZoneAirComponents),
              EquipTypeEnum(MaxZoneAirComponents, DataDefineEquip::ZnAirLoopEquipType::Invalid), airTerminalPtr(nullptr),
              EquipName(MaxZoneAirComponents), EquipIndex(MaxZoneAirComponents, 0), AirTerminalSizingSpecIndex(0), TermUnitSizingNum(0),
              UpStreamLeakFrac(0.0), DownStreamLeakFrac(0.0), MassFlowRateUpStrLk(0.0), MassFlowRateDnStrLk(0.0), MassFlowRateTU(0.0),
              MassFlowRateZSup(0.0), MassFlowRateSup(0.0), MassFlowRatePlenInd(0.0), MaxAvailDelta(0.0), MinAvailDelta(0.0), InletNodeNum(0),
              InletNodeNum2(0), ZoneEqNum(0), AirLoopNum(0), LeakLoadMult(0.0), UpStreamLeak(false), DownStreamLeak(false), RetPlenumNum(0),
              ZoneNum(0), AccountForDOAS(false), HeatRate(0.0), CoolRate(0.0), HeatGain(0.0), CoolGain(0.0)
        {
        }
    };

} // namespace DataDefineEquip

struct DefineEquipData : BaseGlobalStruct
{

    int NumAirDistUnits = 0;
    Array1D<DataDefineEquip::ZoneAirEquip> AirDistUnit; // Used to specify zone related

    void clear_state() override
    {
        this->NumAirDistUnits = 0;
        this->AirDistUnit.deallocate();
    }
};

} // namespace EnergyPlus

#endif
