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

// Google Test Headers
#include <gtest/gtest.h>

// EnergyPlus Headers
#include <EnergyPlus/Data/EnergyPlusData.hh>
#include <EnergyPlus/DataVectorTypes.hh>
#include <EnergyPlus/TARCOGParams.hh>
#include <EnergyPlus/TarcogShading.hh>

#include "Fixtures/EnergyPlusFixture.hh"

using namespace EnergyPlus;
using namespace EnergyPlus::TarcogShading;
using namespace EnergyPlus::TARCOGParams;

TEST_F(EnergyPlusFixture, WindowRoutines_EffectiveOpennessHorizontalVenetianBlind_0_deg)
{
    {
        int constexpr nlayer = 1;
        Real64 constexpr width = 1;
        Real64 constexpr height = 1;
        Array1D<TARCOGLayerType> LayerType(nlayer);

        Array1D<Real64> Atop_eff(nlayer, 0.0);
        Array1D<Real64> Abot_eff(nlayer, 0.0);
        Array1D<Real64> Al_eff(nlayer, 0.0);
        Array1D<Real64> Ar_eff(nlayer, 0.0);
        Array1D<Real64> Ah_eff(nlayer, 0.0);

        static constexpr std::array<Real64, nlayer> Atop = {0.1};
        static constexpr std::array<Real64, nlayer> Abot = {0.1};
        static constexpr std::array<Real64, nlayer> Al = {0.0};
        static constexpr std::array<Real64, nlayer> Ar = {0.0};
        static constexpr std::array<Real64, nlayer> Ah = {0.2};
        LayerType(1) = TARCOGLayerType::VENETBLIND_HORIZ;
        static constexpr std::array<Real64, nlayer> SlatAngle = {0.0};

        updateEffectiveMultipliers(nlayer, width, height, Atop, Abot, Al, Ar, Ah, Atop_eff, Abot_eff, Al_eff, Ar_eff, Ah_eff, LayerType, SlatAngle);

        EXPECT_NEAR(Al_eff(1), 0, 1e-6);
        EXPECT_NEAR(Ar_eff(1), 0, 1e-6);
        EXPECT_NEAR(Atop_eff(1), 0.1, 1e-6);
        EXPECT_NEAR(Abot_eff(1), 0.1, 1e-6);
        EXPECT_NEAR(Ah_eff(1), 0.006818, 1e-6);
    }
}

TEST_F(EnergyPlusFixture, WindowRoutines_EffectiveOpennessVerticalVenetianBlind_0_deg)
{
    {
        int constexpr nlayer = 1;
        Real64 constexpr width = 1;
        Real64 constexpr height = 1;
        Array1D<TARCOGLayerType> LayerType(nlayer);

        Array1D<Real64> Atop_eff(nlayer, 0.0);
        Array1D<Real64> Abot_eff(nlayer, 0.0);
        Array1D<Real64> Al_eff(nlayer, 0.0);
        Array1D<Real64> Ar_eff(nlayer, 0.0);
        Array1D<Real64> Ah_eff(nlayer, 0.0);

        static constexpr std::array<Real64, nlayer> Atop = {0.1};
        static constexpr std::array<Real64, nlayer> Abot = {0.1};
        static constexpr std::array<Real64, nlayer> Al = {0.0};
        static constexpr std::array<Real64, nlayer> Ar = {0.0};
        static constexpr std::array<Real64, nlayer> Ah = {0.2};
        LayerType(1) = TARCOGLayerType::VENETBLIND_VERT;
        static constexpr std::array<Real64, nlayer> SlatAngle = {0.0};

        updateEffectiveMultipliers(nlayer, width, height, Atop, Abot, Al, Ar, Ah, Atop_eff, Abot_eff, Al_eff, Ar_eff, Ah_eff, LayerType, SlatAngle);

        EXPECT_NEAR(Al_eff(1), 0, 1e-6);
        EXPECT_NEAR(Ar_eff(1), 0, 1e-6);
        EXPECT_NEAR(Atop_eff(1), 0.1, 1e-6);
        EXPECT_NEAR(Abot_eff(1), 0.1, 1e-6);
        EXPECT_NEAR(Ah_eff(1), 0.026550, 1e-6);
    }
}

TEST_F(EnergyPlusFixture, WindowRoutines_EffectiveOpennessHorizontalVenetianBlind_45_deg)
{
    {
        int constexpr nlayer = 1;
        Real64 constexpr width = 1;
        Real64 constexpr height = 1;
        Array1D<TARCOGLayerType> LayerType(nlayer);

        Array1D<Real64> Atop_eff(nlayer, 0.0);
        Array1D<Real64> Abot_eff(nlayer, 0.0);
        Array1D<Real64> Al_eff(nlayer, 0.0);
        Array1D<Real64> Ar_eff(nlayer, 0.0);
        Array1D<Real64> Ah_eff(nlayer, 0.0);

        static constexpr std::array<Real64, nlayer> Atop = {0.1};
        static constexpr std::array<Real64, nlayer> Abot = {0.1};
        static constexpr std::array<Real64, nlayer> Al = {0.0};
        static constexpr std::array<Real64, nlayer> Ar = {0.0};
        static constexpr std::array<Real64, nlayer> Ah = {0.2};
        LayerType(1) = TARCOGLayerType::VENETBLIND_HORIZ;
        static constexpr std::array<Real64, nlayer> SlatAngle = {45.0};

        updateEffectiveMultipliers(nlayer, width, height, Atop, Abot, Al, Ar, Ah, Atop_eff, Abot_eff, Al_eff, Ar_eff, Ah_eff, LayerType, SlatAngle);

        EXPECT_NEAR(Al_eff(1), 0, 1e-6);
        EXPECT_NEAR(Ar_eff(1), 0, 1e-6);
        EXPECT_NEAR(Atop_eff(1), 0.1, 1e-6);
        EXPECT_NEAR(Abot_eff(1), 0.1, 1e-6);
        EXPECT_NEAR(Ah_eff(1), 0.007655, 1e-6);
    }
}

TEST_F(EnergyPlusFixture, WindowRoutines_EffectiveOpennessVerticalVenetianBlind_45_deg)
{
    {
        int constexpr nlayer = 1;
        Real64 constexpr width = 1;
        Real64 constexpr height = 1;
        Array1D<TARCOGLayerType> LayerType(nlayer);

        Array1D<Real64> Atop_eff(nlayer, 0.0);
        Array1D<Real64> Abot_eff(nlayer, 0.0);
        Array1D<Real64> Al_eff(nlayer, 0.0);
        Array1D<Real64> Ar_eff(nlayer, 0.0);
        Array1D<Real64> Ah_eff(nlayer, 0.0);

        static constexpr std::array<Real64, nlayer> Atop = {0.1};
        static constexpr std::array<Real64, nlayer> Abot = {0.1};
        static constexpr std::array<Real64, nlayer> Al = {0.0};
        static constexpr std::array<Real64, nlayer> Ar = {0.0};
        static constexpr std::array<Real64, nlayer> Ah = {0.2};
        LayerType(1) = TARCOGLayerType::VENETBLIND_VERT;
        static constexpr std::array<Real64, nlayer> SlatAngle = {45.0};

        updateEffectiveMultipliers(nlayer, width, height, Atop, Abot, Al, Ar, Ah, Atop_eff, Abot_eff, Al_eff, Ar_eff, Ah_eff, LayerType, SlatAngle);

        EXPECT_NEAR(Al_eff(1), 0, 1e-6);
        EXPECT_NEAR(Ar_eff(1), 0, 1e-6);
        EXPECT_NEAR(Atop_eff(1), 0.1, 1e-6);
        EXPECT_NEAR(Abot_eff(1), 0.1, 1e-6);
        EXPECT_NEAR(Ah_eff(1), 0.026550, 1e-6);
    }
}

TEST_F(EnergyPlusFixture, WindowRoutines_EffectiveOpennessOtherShades)
{
    {
        int constexpr nlayer = 1;
        Real64 constexpr width = 1;
        Real64 constexpr height = 1;
        Array1D<TARCOGLayerType> LayerType(nlayer);

        Array1D<Real64> Atop_eff(nlayer, 0.0);
        Array1D<Real64> Abot_eff(nlayer, 0.0);
        Array1D<Real64> Al_eff(nlayer, 0.0);
        Array1D<Real64> Ar_eff(nlayer, 0.0);
        Array1D<Real64> Ah_eff(nlayer, 0.0);

        static constexpr std::array<Real64, nlayer> Atop = {0.1};
        static constexpr std::array<Real64, nlayer> Abot = {0.1};
        static constexpr std::array<Real64, nlayer> Al = {0.0};
        static constexpr std::array<Real64, nlayer> Ar = {0.0};
        static constexpr std::array<Real64, nlayer> Ah = {0.2};
        LayerType(1) = TARCOGLayerType::DIFFSHADE;
        static constexpr std::array<Real64, nlayer> SlatAngle = {0.0};

        updateEffectiveMultipliers(nlayer, width, height, Atop, Abot, Al, Ar, Ah, Atop_eff, Abot_eff, Al_eff, Ar_eff, Ah_eff, LayerType, SlatAngle);

        EXPECT_NEAR(Al_eff(1), 0, 1e-6);
        EXPECT_NEAR(Ar_eff(1), 0, 1e-6);
        EXPECT_NEAR(Atop_eff(1), 0.05, 1e-6);
        EXPECT_NEAR(Abot_eff(1), 0.05, 1e-6);
        EXPECT_NEAR(Ah_eff(1), 0.008792, 1e-6);
    }
}
