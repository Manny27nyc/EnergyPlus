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

#ifndef ChillerIndirectAbsorption_hh_INCLUDED
#define ChillerIndirectAbsorption_hh_INCLUDED

// ObjexxFCL Headers
#include <ObjexxFCL/Array1D.hh>

// EnergyPlus Headers
#include <EnergyPlus/Data/BaseData.hh>
#include <EnergyPlus/DataGlobals.hh>
#include <EnergyPlus/EnergyPlus.hh>
#include <EnergyPlus/Plant/DataPlant.hh>
#include <EnergyPlus/PlantComponent.hh>

namespace EnergyPlus {

// Forward declarations
struct EnergyPlusData;

namespace ChillerIndirectAbsorption {

    struct ReportVars
    {
        // Members
        Real64 PumpingPower;         // reporting: W - electric pumping power
        Real64 QGenerator;           // reporting: W - steam heat transfer rate
        Real64 QEvap;                // reporting: W - evaporator heat transfer rate
        Real64 QCond;                // reporting: W - condenser heat transfer rate
        Real64 PumpingEnergy;        // reporting: J - electric pumping power
        Real64 GeneratorEnergy;      // reporting: J - steam heat transfer rate
        Real64 EvapEnergy;           // reporting: J - evaporator heat transfer rate
        Real64 CondEnergy;           // reporting: J - condenser heat transfer rate
        Real64 CondInletTemp;        // reporting: C - condenser inlet temperature
        Real64 EvapInletTemp;        // reporting: C - evaporator inlet temperature
        Real64 CondOutletTemp;       // reporting: C - condenser outlet temperature
        Real64 EvapOutletTemp;       // reporting: C - evaporator outlet temperature
        Real64 Evapmdot;             // reporting: kg/ - evaporator mass flow rate
        Real64 Condmdot;             // reporting: kg/ - condenser mass flow rate
        Real64 Genmdot;              // reporting: generators mass flow rate when connected to plant
        Real64 SteamMdot;            // reporting: kg/s - steam mass flow rate
        Real64 ActualCOP;            // reporting: coefficient of performance = QEvap/QGenerator
        Real64 ChillerPartLoadRatio; // reporting: part-load ratio
        Real64 ChillerCyclingFrac;   // reporting: chiller on/off cycling fraction
        Real64 LoopLoss;             // reporting: W - loop loss from absorber outlet to condensate pump inlet

        // Default Constructor
        ReportVars()
            : PumpingPower(0.0), QGenerator(0.0), QEvap(0.0), QCond(0.0), PumpingEnergy(0.0), GeneratorEnergy(0.0), EvapEnergy(0.0), CondEnergy(0.0),
              CondInletTemp(0.0), EvapInletTemp(0.0), CondOutletTemp(0.0), EvapOutletTemp(0.0), Evapmdot(0.0), Condmdot(0.0), Genmdot(0.0),
              SteamMdot(0.0), ActualCOP(0.0), ChillerPartLoadRatio(0.0), ChillerCyclingFrac(0.0), LoopLoss(0.0)
        {
        }
    };

    struct IndirectAbsorberSpecs : PlantComponent
    {
        // Members
        std::string Name;                 // user identifier
        Real64 NomCap;                    // W - design nominal capacity of Absorber
        bool NomCapWasAutoSized;          // true if Nominal capacity was autosize on input
        Real64 NomPumpPower;              // W - design nominal capacity of Absorber
        bool NomPumpPowerWasAutoSized;    // true if nominal pump power was autosize on input
        Real64 EvapVolFlowRate;           // m3/s - design nominal water volumetric flow rate through the evaporator
        bool EvapVolFlowRateWasAutoSized; // true if evaporator flow rate was autosize on input
        Real64 CondVolFlowRate;           // m3/s - design nominal water volumetric flow rate through the condenser
        bool CondVolFlowRateWasAutoSized; // true if condenser flow rate was autosize on input
        Real64 EvapMassFlowRateMax;       // kg/s - Max Design Evaporator Mass Flow Rate converted from Volume Flow Rate
        Real64 CondMassFlowRateMax;       // Max Design Condenser Mass Flow Rate [kg/s]
        Real64 GenMassFlowRateMax;        // kg/s - Max Design Generator Mass Flow Rate converted from Volume Flow Rate
        Real64 MinPartLoadRat;            // (BLAST MIN) min allowed operating frac full load
        Real64 MaxPartLoadRat;            // (BLAST MAX) max allowed operating frac full load
        Real64 OptPartLoadRat;            // (BLAST BEST) optimal operating frac full load
        Real64 TempDesCondIn;             // C - (BLAST ADJTC(1)The design secondary loop fluid
        // temperature at the Absorber condenser side inlet
        Real64 MinCondInletTemp;                       // C - minimum condenser inlet temperature for chiller operation
        Real64 MinGeneratorInletTemp;                  // C - minimum generator inlet temperature for chiller operation
        Real64 TempLowLimitEvapOut;                    // C - low temperature shut off
        Real64 GeneratorVolFlowRate;                   // m3/s - hot water volumetric flow rate through generator
        bool GeneratorVolFlowRateWasAutoSized;         // true if hot water flow was autosize on input
        Real64 GeneratorSubcool;                       // C - amount of subcooling in steam generator
        Real64 LoopSubcool;                            // C - amount of subcooling in steam generator
        Real64 GeneratorDeltaTemp;                     // C - generator fluid temperature difference (water only)
        bool GeneratorDeltaTempWasAutoSized;           // true if generator delta T was autosize on input
        Real64 SizFac;                                 // Sizing factor
        int EvapInletNodeNum;                          // Node number on the inlet side of the plant
        int EvapOutletNodeNum;                         // Node number on the outlet side of the plant
        int CondInletNodeNum;                          // Node number on the inlet side of the condenser
        int CondOutletNodeNum;                         // Node number on the outlet side of the condenser
        int GeneratorInletNodeNum;                     // Generator inlet node number, steam/water side
        int GeneratorOutletNodeNum;                    // Generator outlet node number, steam/water side
        int GeneratorInputCurvePtr;                    // Index to steam use curve as a function of PLR
        int PumpPowerCurvePtr;                         // Index to pump power curve as a function of PLR
        int CapFCondenserTempPtr;                      // Index to capacity as a function of absorber temp curve
        int CapFEvaporatorTempPtr;                     // Index to capacity as a function of evaporator temp curve
        int CapFGeneratorTempPtr;                      // Index to capacity as a function of generator temp curve
        int HeatInputFCondTempPtr;                     // Index to generator heat input as a function of absorber temp
        int HeatInputFEvapTempPtr;                     // Index to generator heat input as a function of absorber temp
        int ErrCount2;                                 // error counter
        DataLoopNode::NodeFluidType GenHeatSourceType; // Generator heat source type, DataLoopNode::NodeFluidType::Steam=3 or
                                                       // DataLoopNode::NodeFluidType::Water=2
        int SteamFluidIndex;                           // index to generator fluid type
        bool Available;                                // need an array of logicals--load identifiers of available equipment
        bool ON;                                       // simulate the machine at it's operating part load ratio
        DataPlant::FlowMode FlowMode;                  // one of 3 modes for component flow during operation
        bool ModulatedFlowSetToLoop;                   // True if the setpoint is missing at the outlet node
        bool ModulatedFlowErrDone;                     // true if setpoint warning issued
        int MinCondInletTempCtr;                       // Low condenser temp warning message counter
        int MinCondInletTempIndex;                     // Low condenser temp warning message index
        int MinGenInletTempCtr;                        // Low generator temp warning message counter
        int MinGenInletTempIndex;                      // Low generator temp warning message index
        PlantLocation CWPlantLoc;                      // chilled water plant loop component index
        PlantLocation CDPlantLoc;                      // condenser water plant loop component index
        PlantLocation GenPlantLoc;                     // generator plant loop component index
        bool FaultyChillerSWTFlag;                     // True if the chiller has SWT sensor fault
        int FaultyChillerSWTIndex;                     // Index of the fault object corresponding to the chiller
        Real64 FaultyChillerSWTOffset;                 // Chiller SWT sensor offset
        bool PossibleSubcooling;                       // flag to indicate chiller is doing less cooling that requested
        Real64 CondMassFlowRate;                       // Kg/s - condenser mass flow rate, water side
        Real64 EvapMassFlowRate;                       // Kg/s - evaporator mass flow rate, water side
        Real64 GenMassFlowRate;                        // Kg/s - steam mass flow rate, water side
        Real64 CondOutletTemp;                         // C - condenser outlet temperature, water side
        Real64 EvapOutletTemp;                         // C - evaporator outlet temperature, water side
        Real64 GenOutletTemp;                          // C - generator fluid outlet temperature
        Real64 SteamOutletEnthalpy;                    // J/kg - generator fluid outlet enthalpy
        Real64 PumpingPower;                           // W - rate of Absorber energy use
        Real64 PumpingEnergy;                          // J - Absorber energy use
        Real64 QGenerator;                             // W - rate of Absorber steam use
        Real64 GeneratorEnergy;                        // J - Absorber steam use
        Real64 QEvaporator;                            // W - rate of heat transfer to the evaporator coil
        Real64 EvaporatorEnergy;                       // J - heat transfer to the evaporator coil
        Real64 QCondenser;                             // W - rate of heat transfer to the condenser coil
        Real64 CondenserEnergy;                        // J - heat transfer to the condenser coil
        Real64 ChillerONOFFCyclingFrac;                // fraction of time chiller is on
        Real64 EnergyLossToEnvironment;                // J - piping energy loss from generator outlet to pump inlet
        bool GenInputOutputNodesUsed;
        bool MyOneTimeFlag;
        bool MyEnvrnFlag;
        ReportVars Report;
        DataBranchAirLoopPlant::ControlType EquipFlowCtrl;

        // Default Constructor
        IndirectAbsorberSpecs()
            : NomCap(0.0), NomCapWasAutoSized(false), NomPumpPower(0.0), NomPumpPowerWasAutoSized(false), EvapVolFlowRate(0.0),
              EvapVolFlowRateWasAutoSized(false), CondVolFlowRate(0.0), CondVolFlowRateWasAutoSized(false), EvapMassFlowRateMax(0.0),
              CondMassFlowRateMax(0.0), GenMassFlowRateMax(0.0), MinPartLoadRat(0.0), MaxPartLoadRat(0.0), OptPartLoadRat(0.0), TempDesCondIn(0.0),
              MinCondInletTemp(0.0), MinGeneratorInletTemp(0.0), TempLowLimitEvapOut(0.0), GeneratorVolFlowRate(0.0),
              GeneratorVolFlowRateWasAutoSized(false), GeneratorSubcool(0.0), LoopSubcool(0.0), GeneratorDeltaTemp(-99999.0),
              GeneratorDeltaTempWasAutoSized(true), SizFac(0.0), EvapInletNodeNum(0), EvapOutletNodeNum(0), CondInletNodeNum(0), CondOutletNodeNum(0),
              GeneratorInletNodeNum(0), GeneratorOutletNodeNum(0), GeneratorInputCurvePtr(0), PumpPowerCurvePtr(0), CapFCondenserTempPtr(0),
              CapFEvaporatorTempPtr(0), CapFGeneratorTempPtr(0), HeatInputFCondTempPtr(0), HeatInputFEvapTempPtr(0), ErrCount2(0),
              GenHeatSourceType(DataLoopNode::NodeFluidType::Blank), SteamFluidIndex(0), Available(false), ON(false),
              FlowMode(DataPlant::FlowMode::Invalid), ModulatedFlowSetToLoop(false), ModulatedFlowErrDone(false), MinCondInletTempCtr(0),
              MinCondInletTempIndex(0), MinGenInletTempCtr(0), MinGenInletTempIndex(0), CWPlantLoc{}, CDPlantLoc{}, GenPlantLoc{},
              FaultyChillerSWTFlag(false), FaultyChillerSWTIndex(0), FaultyChillerSWTOffset(0.0), PossibleSubcooling(false), CondMassFlowRate(0.0),
              EvapMassFlowRate(0.0), GenMassFlowRate(0.0), CondOutletTemp(0.0), EvapOutletTemp(0.0), GenOutletTemp(0.0), SteamOutletEnthalpy(0.0),
              PumpingPower(0.0), PumpingEnergy(0.0), QGenerator(0.0), GeneratorEnergy(0.0), QEvaporator(0.0), EvaporatorEnergy(0.0), QCondenser(0.0),
              CondenserEnergy(0.0), ChillerONOFFCyclingFrac(0.0), EnergyLossToEnvironment(0.0), GenInputOutputNodesUsed(false), MyOneTimeFlag(true),
              MyEnvrnFlag(true), EquipFlowCtrl(DataBranchAirLoopPlant::ControlType::Invalid)
        {
        }

        static PlantComponent *factory(EnergyPlusData &state, std::string const &objectName);

        void simulate([[maybe_unused]] EnergyPlusData &state,
                      const PlantLocation &calledFromLocation,
                      bool FirstHVACIteration,
                      Real64 &CurLoad,
                      bool RunFlag) override;

        void getDesignCapacities(
            EnergyPlusData &state, const PlantLocation &calledFromLocation, Real64 &MaxLoad, Real64 &MinLoad, Real64 &OptLoad) override;

        void getSizingFactor(Real64 &sizFac) override;

        void onInitLoopEquip([[maybe_unused]] EnergyPlusData &state, const PlantLocation &calledFromLocation) override;

        void oneTimeInit(EnergyPlusData &state) override;

        void initialize(EnergyPlusData &state, bool RunFlag, Real64 MyLoad);

        void setupOutputVars(EnergyPlusData &state);

        void sizeChiller(EnergyPlusData &state);

        void updateRecords(EnergyPlusData &state, Real64 MyLoad, bool RunFlag);

        void calculate(EnergyPlusData &state, Real64 MyLoad, bool RunFlag);
    };

    void GetIndirectAbsorberInput(EnergyPlusData &state);

} // namespace ChillerIndirectAbsorption

struct ChillerIndirectAbsoprtionData : BaseGlobalStruct
{
    int NumIndirectAbsorbers = 0;
    bool GetInput = true;
    Array1D<ChillerIndirectAbsorption::IndirectAbsorberSpecs> IndirectAbsorber;

    void clear_state() override
    {
        this->NumIndirectAbsorbers = 0;
        this->GetInput = true;
        this->IndirectAbsorber.deallocate();
    }
};

} // namespace EnergyPlus

#endif
