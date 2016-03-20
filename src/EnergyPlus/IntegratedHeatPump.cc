<<<<<<< HEAD
// EnergyPlus, Copyright (c) 1996-2016, The Board of Trustees of the University of Illinois and
// The Regents of the University of California, through Lawrence Berkeley National Laboratory
// (subject to receipt of any required approvals from the U.S. Dept. of Energy). All rights
// reserved.
//
// If you have questions about your rights to use or distribute this software, please contact
// Berkeley Lab's Innovation & Partnerships Office at IPO@lbl.gov.
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
//     similar designation, without Lawrence Berkeley National Laboratory's prior written consent.
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
//
// You are under no obligation whatsoever to provide any bug fixes, patches, or upgrades to the
// features, functionality or performance of the source code ("Enhancements") to anyone; however,
// if you choose to make your Enhancements available either publicly, or directly to Lawrence
// Berkeley National Laboratory, without imposing a separate written license agreement for such
// Enhancements, then you hereby grant the following license: a non-exclusive, royalty-free
// perpetual license to install, use, modify, prepare derivative works, incorporate into other
// computer software, distribute, and sublicense such enhancements or derivative works thereof,
// in binary and source code form.

// C++ Headers

// ObjexxFCL Headers
#include <ObjexxFCL/Array1D.hh>
#include <ObjexxFCL/Optional.hh>
=======
// C++ Headers
#include <cmath>

// ObjexxFCL Headers
#include <ObjexxFCL/Array.functions.hh>
#include <ObjexxFCL/Fmath.hh>
>>>>>>> origin/ASIHPdev3

// EnergyPlus Headers
#include <IntegratedHeatPump.hh>
#include <BranchNodeConnections.hh>
#include <CurveManager.hh>
#include <DataAirSystems.hh>
#include <DataContaminantBalance.hh>
#include <DataEnvironment.hh>
#include <DataLoopNode.hh>
#include <DataPlant.hh>
#include <DataPrecisionGlobals.hh>
#include <DataWater.hh>
#include <FluidProperties.hh>
#include <General.hh>
#include <GeneralRoutines.hh>
#include <GlobalNames.hh>
#include <InputProcessor.hh>
#include <NodeInputManager.hh>
#include <OutAirNodeManager.hh>
#include <OutputProcessor.hh>
#include <OutputReportPredefined.hh>
#include <PlantUtilities.hh>
#include <Psychrometrics.hh>
#include <ReportSizingManager.hh>
#include <ScheduleManager.hh>
#include <UtilityRoutines.hh>
#include <WaterManager.hh>
#include <WaterThermalTanks.hh>
#include <InputProcessor.hh>

namespace EnergyPlus {

<<<<<<< HEAD
	namespace IntegratedHeatPump {
=======
	namespace IntegratedHeatPumps {
>>>>>>> origin/ASIHPdev3

		// USE STATEMENTS:
		// Use statements for data only modules
		// Using/Aliasing
		using namespace DataPrecisionGlobals;
		using namespace DataLoopNode;
		using namespace DataGlobals;
		using General::RoundSigDigits;

		// Use statements for access to subroutines in other modules

		// Data
		//MODULE PARAMETER DEFINITIONS

		static std::string const BlankString;

		// DERIVED TYPE DEFINITIONS

		// MODULE VARIABLE DECLARATIONS:
		// Identifier is VarSpeedCoil
<<<<<<< HEAD
		bool GetCoilsInputFlag( true ); 
=======
		int NumIHPs(0); // The Number of Water to Air Heat Pumps found in the Input
		bool GetCoilsInputFlag(true);
>>>>>>> origin/ASIHPdev3

		// SUBROUTINE SPECIFICATIONS FOR MODULE

		// Driver/Manager Routines

		// Get Input routines for module

		// Initialization routines for module

		// Update routines to check convergence and update nodes

		// Update routine

		// Utility routines
		//SHR, bypass factor routines

		// Object Data
<<<<<<< HEAD
		Array1D< IntegratedHeatPumpData > IntegratedHeatPumps;
=======
		Array1D<IntegratedHeatPumpData> IntegratedHeatPumpUnits;
>>>>>>> origin/ASIHPdev3

		// MODULE SUBROUTINES:
		//*************************************************************************

		// Functions
		void
<<<<<<< HEAD
		clear_state()
		{
			GetCoilsInputFlag = true;
			IntegratedHeatPumps.deallocate();
=======
			clear_state()
		{

			IntegratedHeatPumpUnits.deallocate();
>>>>>>> origin/ASIHPdev3
		}


		void
<<<<<<< HEAD
		SimIHP(
=======
			SimIHP(
>>>>>>> origin/ASIHPdev3
			std::string const & CompName, // Coil Name
			int & CompIndex, // Index for Component name
			int const CyclingScheme, // Continuous fan OR cycling compressor
			Real64 & MaxONOFFCyclesperHour, // Maximum cycling rate of heat pump [cycles/hr]
			Real64 & HPTimeConstant, // Heat pump time constant [s]
			Real64 & FanDelayTime, // Fan delay time, time delay for the HP's fan to
			int const CompOp, // compressor on/off. 0 = off; 1= on
<<<<<<< HEAD
			Real64 const PartLoadFrac,
=======
			Real64 const PartLoadFrac,//part load fraction
>>>>>>> origin/ASIHPdev3
			int const SpeedNum, // compressor speed number
			Real64 const SpeedRatio, // compressor speed ratio
			Real64 const SensLoad, // Sensible demand load [W]
			Real64 const LatentLoad, // Latent demand load [W]
			bool const IsCallbyWH, //whether the call from the water heating loop or air loop, true = from water heating loop
<<<<<<< HEAD
			bool const EP_UNUSED( FirstHVACIteration ), // TRUE if First iteration of simulation
			Optional< Real64 const > OnOffAirFlowRat // ratio of comp on to comp off air flow rate
		)
		{

			//       AUTHOR         Bo Shen, ORNL
			//       DATE WRITTEN   March 2012
			//       MODIFIED       Bo Shen, 12/2014, add variable-speed HPWH
			//       RE-ENGINEERED  na

			// PURPOSE OF THIS SUBROUTINE:
			// This subroutine manages variable-speed Water to Air Heat Pump component simulation.
=======
			bool const FirstHVACIteration, // TRUE if First iteration of simulation
			Optional< Real64 const > OnOffAirFlowRat // ratio of comp on to comp off air flow rate
			)
		{

			//       AUTHOR         Bo Shen, ORNL
			//       DATE WRITTEN   March 2016
			//       RE-ENGINEERED  na

			// PURPOSE OF THIS SUBROUTINE:
			// This subroutine manages variable-speed integrated Air source heat pump simulation.
>>>>>>> origin/ASIHPdev3

			// METHODOLOGY EMPLOYED:

			// REFERENCES:
			// N/A

			// Using/Aliasing
			using InputProcessor::FindItemInList;
			using General::TrimSigDigits;
			using VariableSpeedCoils::SimVariableSpeedCoils;
			using VariableSpeedCoils::VarSpeedCoil;
<<<<<<< HEAD
			using VariableSpeedCoils::UpdateVarSpeedCoil; 
=======
			using VariableSpeedCoils::UpdateVarSpeedCoil;
			using VariableSpeedCoils::InitVarSpeedCoil;
>>>>>>> origin/ASIHPdev3

			// Locals
			// SUBROUTINE ARGUMENT DEFINITIONS:

<<<<<<< HEAD
			// shut off after compressor cycle off  [s]
			// part-load ratio = load/total capacity, passed in by the parent object

=======
>>>>>>> origin/ASIHPdev3
			// SUBROUTINE PARAMETER DEFINITIONS:
			// na

			// INTERFACE BLOCK SPECIFICATIONS
			// na

			// DERIVED TYPE DEFINITIONS
			// na

<<<<<<< HEAD
			
			// SUBROUTINE LOCAL VARIABLE DECLARATIONS:
			int DXCoilNum( 0 ); // The WatertoAirHP that you are currently loading input into
			// int LocNum(0); 
			// bool ErrorFound(false); 
			// Real64 MyLoad(0.0);
			// Real64 MaxCap(0.0);
			// Real64 MinCap(0.0);
			// Real64 OptCap(0.0);

			// Obtains and Allocates WatertoAirHP related parameters from input file
=======

			// SUBROUTINE LOCAL VARIABLE DECLARATIONS:
			int DXCoilNum(0); // The IHP No that you are currently dealing with

			// Obtains and Allocates ASIHP related parameters from input file
>>>>>>> origin/ASIHPdev3
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
				//    WaterIndex=FindGlycol('WATER') !Initialize the WaterIndex once
				GetCoilsInputFlag = false;
			}

			if (CompIndex == 0) {
<<<<<<< HEAD
				DXCoilNum = FindItemInList(CompName, IntegratedHeatPumps);
=======
				DXCoilNum = FindItemInList(CompName, IntegratedHeatPumpUnits);
>>>>>>> origin/ASIHPdev3
				if (DXCoilNum == 0) {
					ShowFatalError("Integrated Heat Pump not found=" + CompName);
				}
				CompIndex = DXCoilNum;
			}
			else {
				DXCoilNum = CompIndex;
<<<<<<< HEAD
				if ( DXCoilNum > static_cast< int >( IntegratedHeatPumps.size() ) || DXCoilNum < 1 ) {
					ShowFatalError("SimIHP: Invalid CompIndex passed=" + TrimSigDigits(DXCoilNum) + 
						", Number of Integrated HPs=" + TrimSigDigits( IntegratedHeatPumps.size() ) + ", IHP name=" + CompName);
				}
				if (!CompName.empty() && CompName != IntegratedHeatPumps(DXCoilNum).Name) {
					ShowFatalError("SimIHP: Invalid CompIndex passed=" + TrimSigDigits(DXCoilNum) + 
						", Integrated HP name=" + CompName + ", stored Integrated HP Name for that index=" + IntegratedHeatPumps(DXCoilNum).Name);
				}
			}; 

			if (IntegratedHeatPumps(DXCoilNum).IHPCoilsSized == false) SizeIHP(DXCoilNum);

			switch (IntegratedHeatPumps(DXCoilNum).CurMode)
			{
			case IHPOperationMode::IdleMode:
				VarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SCCoilIndex ).SimFlag = false; 
				UpdateVarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SCCoilIndex );
				VarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SHCoilIndex ).SimFlag = false;
				UpdateVarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SHCoilIndex );
				VarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).DWHCoilIndex ).SimFlag = false;
				UpdateVarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).DWHCoilIndex );
				break; 
			case IHPOperationMode::SCMode:
				VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCCoilIndex).SimFlag = true;
				if (false == IsCallbyWH)
				{
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumps(DXCoilNum).SCCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
						SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);
				}
				else
				{
					UpdateVarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCCoilIndex);
				}

				VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SHCoilIndex).SimFlag = false;
				UpdateVarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SHCoilIndex);

				VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).DWHCoilIndex).SimFlag = false;
				UpdateVarSpeedCoil(IntegratedHeatPumps(DXCoilNum).DWHCoilIndex);

				break; 
			case IHPOperationMode::SHMode:
				VarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SCCoilIndex ).SimFlag = false;
				UpdateVarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SCCoilIndex );
				VarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SHCoilIndex ).SimFlag = true;

				if (false == IsCallbyWH)
				{
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumps(DXCoilNum).SHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
						SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);
				}
				else
				{
					UpdateVarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SHCoilIndex);
				}

				VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).DWHCoilIndex).SimFlag = false;
				UpdateVarSpeedCoil(IntegratedHeatPumps(DXCoilNum).DWHCoilIndex);
				break; 
			case IHPOperationMode::DWHMode:
				VarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).DWHCoilIndex ).SimFlag = true;

				VarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SCCoilIndex ).SimFlag = false;
				UpdateVarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SCCoilIndex );

				VarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SHCoilIndex ).SimFlag = false;
				UpdateVarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SHCoilIndex );

				if (true == IsCallbyWH)
				{
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumps(DXCoilNum).DWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
						SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);
					IntegratedHeatPumps(DXCoilNum).TotalHeatingEnergyRate = VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).DWHCoilIndex).TotalHeatingEnergyRate;
				}

				break; 
			case IHPOperationMode::SCWHMatchSCMode:
				VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCWHCoilIndex).SimFlag = true;
				if (false == IsCallbyWH)
				{
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumps(DXCoilNum).SCWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
						SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);
					IntegratedHeatPumps(DXCoilNum).TotalHeatingEnergyRate = VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCWHCoilIndex).TotalHeatingEnergyRate;
				}
				else
				{
					UpdateVarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCWHCoilIndex);
				}

				VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SHCoilIndex).SimFlag = false;
				UpdateVarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SHCoilIndex);

				break; 
			case IHPOperationMode::SCWHMatchWHMode:
				VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCWHCoilIndex).SimFlag = true;
				if (true == IsCallbyWH)
				{
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumps(DXCoilNum).SCWHCoilIndex,
					CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
					SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);
					IntegratedHeatPumps(DXCoilNum).TotalHeatingEnergyRate = VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCWHCoilIndex).TotalHeatingEnergyRate;			
				}
				else
				{
					UpdateVarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCWHCoilIndex);
				}

				VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SHCoilIndex).SimFlag = false;
				UpdateVarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SHCoilIndex);

				break; 
			case IHPOperationMode::SCDWHMode:
				VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCDWHCoolCoilIndex).SimFlag = true;
				VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCDWHWHCoilIndex).SimFlag = true;
				if (false == IsCallbyWH)
				{
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumps(DXCoilNum).SCDWHWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
						SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);
					IntegratedHeatPumps(DXCoilNum).TotalHeatingEnergyRate = VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCDWHWHCoilIndex).TotalHeatingEnergyRate;

					SimVariableSpeedCoils(BlankString, IntegratedHeatPumps(DXCoilNum).SCDWHCoolCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
						SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);
				}
				else
				{
					UpdateVarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCDWHWHCoilIndex);
					UpdateVarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCDWHCoolCoilIndex);
				}

				VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SHCoilIndex).SimFlag = false;
				UpdateVarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SHCoilIndex);

				break; 
			case IHPOperationMode::SHDWHElecHeatOffMode:
			case IHPOperationMode::SHDWHElecHeatOnMode:
				VarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SCCoilIndex ).SimFlag = false;
				UpdateVarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SCCoilIndex );
				VarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SHDWHHeatCoilIndex ).SimFlag = true;
				VarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SHDWHWHCoilIndex ).SimFlag = true;

				if (false == IsCallbyWH)
				{
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumps(DXCoilNum).SHDWHWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
						SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);
					IntegratedHeatPumps(DXCoilNum).TotalHeatingEnergyRate = VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SHDWHWHCoilIndex).TotalHeatingEnergyRate;

					SimVariableSpeedCoils(BlankString, IntegratedHeatPumps(DXCoilNum).SHDWHHeatCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
						SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);
				}
				else
				{
					UpdateVarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SHDWHWHCoilIndex);
					UpdateVarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SHDWHHeatCoilIndex);
				}

				break; 
			default:
				VarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SCCoilIndex ).SimFlag = false;
				UpdateVarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SCCoilIndex );

				VarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SHCoilIndex ).SimFlag = false;
				UpdateVarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SHCoilIndex );

				VarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).DWHCoilIndex ).SimFlag = false;
				UpdateVarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).DWHCoilIndex );
				break; 
			}
		}



		void
		GetIHPInput()
=======
				if (DXCoilNum > NumIHPs || DXCoilNum < 1) {
					ShowFatalError("SimIHP: Invalid CompIndex passed=" + TrimSigDigits(DXCoilNum) +
						", Number of Integrated HPs=" + TrimSigDigits(NumIHPs) + ", IHP name=" + CompName);
				}
				if (!CompName.empty() && CompName != IntegratedHeatPumpUnits(DXCoilNum).Name) {
					ShowFatalError("SimIHP: Invalid CompIndex passed=" + TrimSigDigits(DXCoilNum) +
						", Integrated HP name=" + CompName + ", stored Integrated HP Name for that index=" + IntegratedHeatPumpUnits(DXCoilNum).Name);
				}
			};

			if (IntegratedHeatPumpUnits(DXCoilNum).IHPCoilsSized == false) SizeIHP(DXCoilNum);

			InitializeIHP(DXCoilNum);

			switch (IntegratedHeatPumpUnits(DXCoilNum).CurMode)
			{
			case SCMode:
				if (false == IsCallbyWH)//process when called from air loop
				{
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);

					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
						SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);

					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
				}


				break;
			case SHMode:
				if (false == IsCallbyWH)//process when called from air loop
				{
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);

					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
						SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);

					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
				}

				break;
			case DWHMode:
				if (true == IsCallbyWH)//process when called from water loop
				{
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);

					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
						SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);
					//IntegratedHeatPumpUnits(DXCoilNum).TotalHeatingEnergyRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex).TotalHeatingEnergyRate;
				}

				break;
			case SCWHMatchSCMode:
				if (false == IsCallbyWH)//process when called from air loop
				{
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);

					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
						SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
				}


				break;
			case SCWHMatchWHMode:
				if (true == IsCallbyWH)//process when called from water loop
				{
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);

					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
						SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);

					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
				}

				break;
			case SCDWHMode:
				if (false == IsCallbyWH)//process when called from air loop
				{
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);

					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
						SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
						SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);

					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
				}

				break;
			case SHDWHElecHeatOffMode:
			case SHDWHElecHeatOnMode:
				if (false == IsCallbyWH)//process when called from air loop
				{
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);

					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
						SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
						SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);
				}

				break;
			case IdleMode:
			default://clear up
				SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex,
					CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
				SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilIndex,
					CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
				SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilIndex,
					CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
				SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilIndex,
					CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
				SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex,
					CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
				SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex,
					CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
				SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex,
					CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
				SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex,
					CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, 0.0, 1, 0.0, 0.0, 0.0, OnOffAirFlowRat);
				break;
			}

			UpdateIHP(DXCoilNum);

		}


		void
			GetIHPInput()
>>>>>>> origin/ASIHPdev3
		{

			// SUBROUTINE INFORMATION:
			//       AUTHOR         Bo Shen
			//       DATE WRITTEN   December, 2015
			//       RE-ENGINEERED  na

			// PURPOSE OF THIS SUBROUTINE:
			// Obtains input data for Integrated HPs and stores it in IHP data structures

			// METHODOLOGY EMPLOYED:
			// Uses "Get" routines to read in data.

			// REFERENCES:
			// n/a

			// Using/Aliasing
			using namespace InputProcessor;
			using namespace NodeInputManager;
			using BranchNodeConnections::TestCompSet;
<<<<<<< HEAD
			using GlobalNames::VerifyUniqueCoilName;
			using namespace OutputReportPredefined;
			using General::TrimSigDigits;
			using CurveManager::GetCurveIndex;
			using CurveManager::GetCurveType;
			using CurveManager::CurveValue;
			using CurveManager::SetCurveOutputMinMaxValues;
			using OutAirNodeManager::CheckOutAirNodeNumber;
			using WaterManager::SetupTankDemandComponent;
			using WaterManager::SetupTankSupplyComponent;
			using ScheduleManager::GetScheduleIndex;
=======
			using BranchNodeConnections::SetUpCompSets;
			using GlobalNames::VerifyUniqueCoilName;
			using namespace OutputReportPredefined;
			using General::TrimSigDigits;
			using VariableSpeedCoils::VarSpeedCoil; 
>>>>>>> origin/ASIHPdev3
			using VariableSpeedCoils::GetCoilIndexVariableSpeed;
			using VariableSpeedCoils::SetAirNodes;
			using VariableSpeedCoils::SetWaterNodes;

			// Locals
			// SUBROUTINE ARGUMENT DEFINITIONS:
			// na

			// SUBROUTINE PARAMETER DEFINITIONS:
			static std::string const RoutineName("GetIHPInput: "); // include trailing blank space

			// INTERFACE BLOCK SPECIFICATIONS
			// na

			// DERIVED TYPE DEFINITIONS
			// na

			// SUBROUTINE LOCAL VARIABLE DECLARATIONS:
			int DXCoilNum; //No of IHP DX system
<<<<<<< HEAD
			// int IHPNum; // The Water to Air HP that you are currently loading input into
=======
			int IHPNum; // The Water to Air HP that you are currently loading input into
>>>>>>> origin/ASIHPdev3
			int NumASIHPs; // Counter for air-source integrated heat pumps

			int NumAlphas; // Number of variables in String format
			int NumNums; // Number of variables in Numeric format
			int NumParams; // Total number of input fields
			static int MaxNums(0); // Maximum number of numeric input fields
			static int MaxAlphas(0); // Maximum number of alpha input fields
			std::string CoilName; // Name of the  Coil
			std::string Coiltype; // type of coil

			std::string CurrentModuleObject; // for ease in getting objects
<<<<<<< HEAD
=======
			std::string sIHPType; //specify IHP type
>>>>>>> origin/ASIHPdev3
			Array1D_string AlphArray; // Alpha input items for object
			Array1D_string cAlphaFields; // Alpha field names
			Array1D_string cNumericFields; // Numeric field names
			Array1D< Real64 > NumArray; // Numeric input items for object
			Array1D_bool lAlphaBlanks; // Logical array, alpha field input BLANK = .TRUE.
			Array1D_bool lNumericBlanks; // Logical array, numeric field input BLANK = .TRUE.

			static bool ErrorsFound(false); // If errors detected in input	
			int CoilCounter; // Counter

			int IOStat;
			int AlfaFieldIncre; // increment number of Alfa field

			bool IsNotOK; // Flag to verify name
			bool IsBlank; // Flag for blank name
			bool errFlag;
<<<<<<< HEAD
			int InNode(0);
			int OutNode(0);


			NumASIHPs = GetNumObjectsFound("COILSYSTEM:INTEGRATEDHEATPUMP:AIRSOURCE");
			DXCoilNum = 0;

			if ( NumASIHPs <= 0 ) {
				ShowSevereError( "No Equipment found in Integrated Heat Pumps" );
=======
			int InNode(0);//inlet air or water node
			int OutNode(0);//outlet air or water node


			NumASIHPs = GetNumObjectsFound("COILSYSTEM:INTEGRATEDHEATPUMP:AIRSOURCE");
			NumIHPs = NumASIHPs;//later will add water source integrated HPs

			DXCoilNum = 0;

			if (NumIHPs <= 0) {
				ShowSevereError("No Equipment found in Integrated Heat Pumps");
>>>>>>> origin/ASIHPdev3
				ErrorsFound = true;
			}

			// Allocate Arrays
<<<<<<< HEAD
			if ( NumASIHPs > 0 ) {
				IntegratedHeatPumps.allocate( NumASIHPs );
=======
			if (NumIHPs > 0) {
				IntegratedHeatPumpUnits.allocate(NumIHPs);
>>>>>>> origin/ASIHPdev3
			}

			//air-source integrated heat pump
			GetObjectDefMaxArgs("COILSYSTEM:INTEGRATEDHEATPUMP:AIRSOURCE", NumParams, NumAlphas, NumNums);
			MaxNums = max(MaxNums, NumNums);
			MaxAlphas = max(MaxAlphas, NumAlphas);

			AlphArray.allocate(MaxAlphas);
			cAlphaFields.allocate(MaxAlphas);
			lAlphaBlanks.dimension(MaxAlphas, true);
			cNumericFields.allocate(MaxNums);
			lNumericBlanks.dimension(MaxNums, true);
			NumArray.dimension(MaxNums, 0.0);

			// Get the data for air-source IHPs
			CurrentModuleObject = "COILSYSTEM:INTEGRATEDHEATPUMP:AIRSOURCE"; //for reporting
<<<<<<< HEAD
=======
			sIHPType = "COILSYSTEM:INTEGRATEDHEATPUMP:AIRSOURCE"; //for checking
>>>>>>> origin/ASIHPdev3

			for (CoilCounter = 1; CoilCounter <= NumASIHPs; ++CoilCounter) {

				++DXCoilNum;
				AlfaFieldIncre = 1;

				GetObjectItem(CurrentModuleObject, CoilCounter, AlphArray, NumAlphas, NumArray, NumNums, IOStat, lNumericBlanks, lAlphaBlanks, cAlphaFields, cNumericFields);

				IsNotOK = false;
				IsBlank = false;

<<<<<<< HEAD
				VerifyName(AlphArray(1), IntegratedHeatPumps, DXCoilNum - 1, IsNotOK, IsBlank, CurrentModuleObject + " Name");
=======
				VerifyName(AlphArray(1), IntegratedHeatPumpUnits, DXCoilNum - 1, IsNotOK, IsBlank, CurrentModuleObject + " Name");
>>>>>>> origin/ASIHPdev3
				if (IsNotOK) {
					ErrorsFound = true;
					if (IsBlank) AlphArray(1) = "xxxxx";
				}
				VerifyUniqueCoilName(CurrentModuleObject, AlphArray(1), errFlag, CurrentModuleObject + " Name");
				if (errFlag) {
					ErrorsFound = true;
				}

<<<<<<< HEAD
				IntegratedHeatPumps(DXCoilNum).NodeConnected = false;
				IntegratedHeatPumps(DXCoilNum).Name = AlphArray(1);
				IntegratedHeatPumps(DXCoilNum).IHPtype = "AIRSOURCE_IHP";

				IntegratedHeatPumps(DXCoilNum).AirCoolInletNodeNum = 
					GetOnlySingleNode(AlphArray(2), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Air, NodeConnectionType_Inlet, 1, ObjectIsNotParent);
				IntegratedHeatPumps(DXCoilNum).AirHeatInletNodeNum =
					GetOnlySingleNode(AlphArray(3), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Air, NodeConnectionType_Inlet, 1, ObjectIsNotParent);
				IntegratedHeatPumps(DXCoilNum).AirOutletNodeNum = 
					GetOnlySingleNode(AlphArray(4), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Air, NodeConnectionType_Outlet, 1, ObjectIsNotParent);
				IntegratedHeatPumps(DXCoilNum).WaterInletNodeNum = 
					GetOnlySingleNode(AlphArray(5), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Water, NodeConnectionType_Inlet, 2, ObjectIsNotParent);
				IntegratedHeatPumps(DXCoilNum).WaterOutletNodeNum = 
					GetOnlySingleNode(AlphArray(6), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Water, NodeConnectionType_Outlet, 2, ObjectIsNotParent);
				IntegratedHeatPumps(DXCoilNum).WaterTankoutNod =
					GetOnlySingleNode(AlphArray(7), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Water, NodeConnectionType_Outlet, 2, ObjectIsNotParent);

				TestCompSet(CurrentModuleObject, AlphArray(1), AlphArray(2), AlphArray(3), "Air Nodes");
				TestCompSet(CurrentModuleObject, AlphArray(1), AlphArray(3), AlphArray(4), "Air Nodes");
				TestCompSet(CurrentModuleObject, AlphArray(1), AlphArray(5), AlphArray(6), "Water Nodes");
				
				IntegratedHeatPumps(DXCoilNum).SCCoilType = "COIL:COOLING:DX:VARIABLESPEED";
				IntegratedHeatPumps(DXCoilNum).SCCoilName = AlphArray(8);
				Coiltype = IntegratedHeatPumps(DXCoilNum).SCCoilType;
				CoilName = IntegratedHeatPumps(DXCoilNum).SCCoilName;
=======
				IntegratedHeatPumpUnits(DXCoilNum).NodeConnected = false;
				IntegratedHeatPumpUnits(DXCoilNum).Name = AlphArray(1);
				IntegratedHeatPumpUnits(DXCoilNum).IHPtype = "AIRSOURCE_IHP";

				IntegratedHeatPumpUnits(DXCoilNum).AirCoolInletNodeNum =
					GetOnlySingleNode(AlphArray(2), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Air, NodeConnectionType_Inlet, 1, ObjectIsNotParent);
				IntegratedHeatPumpUnits(DXCoilNum).AirHeatInletNodeNum =
					GetOnlySingleNode(AlphArray(3), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Air, NodeConnectionType_Outlet, 1, ObjectIsNotParent);
				IntegratedHeatPumpUnits(DXCoilNum).AirOutletNodeNum =
					GetOnlySingleNode(AlphArray(4), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Air, NodeConnectionType_Outlet, 1, ObjectIsNotParent);
				IntegratedHeatPumpUnits(DXCoilNum).WaterInletNodeNum =
					GetOnlySingleNode(AlphArray(5), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Water, NodeConnectionType_Inlet, 2, ObjectIsNotParent);
				IntegratedHeatPumpUnits(DXCoilNum).WaterOutletNodeNum =
					GetOnlySingleNode(AlphArray(6), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Water, NodeConnectionType_Outlet, 2, ObjectIsNotParent);
				IntegratedHeatPumpUnits(DXCoilNum).WaterTankoutNod =
					GetOnlySingleNode(AlphArray(7), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Water, NodeConnectionType_Outlet, 2, ObjectIsNotParent);
				IntegratedHeatPumpUnits(DXCoilNum).ODAirInletNodeNum =
					GetOnlySingleNode(AlphArray(8), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Air, NodeConnectionType_Inlet, 1, ObjectIsNotParent);
				IntegratedHeatPumpUnits(DXCoilNum).ODAirOutletNodeNum =
					GetOnlySingleNode(AlphArray(9), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Air, NodeConnectionType_Outlet, 1, ObjectIsNotParent);

				//give up checking node connection rules as IHP doesn't apply
				//TestCompSet(CurrentModuleObject, AlphArray(1), AlphArray(2), AlphArray(3), "Air Nodes");
				//TestCompSet(CurrentModuleObject, AlphArray(1), AlphArray(3), AlphArray(4), "Air Nodes");
				//TestCompSet(CurrentModuleObject, AlphArray(1), AlphArray(5), AlphArray(6), "Water Nodes");

				//SetUpCompSets(sIHPType, AlphArray(1), "COIL:COOLING:DX:VARIABLESPEED", AlphArray(8), AlphArray(2), AlphArray(3));//add SC
				//SetUpCompSets(sIHPType, AlphArray(1), "COIL:HEATING:DX:VARIABLESPEED", AlphArray(9), AlphArray(3), AlphArray(4));//add SH
				//SetUpCompSets(sIHPType, AlphArray(1), "COIL:WATERHEATING:AIRTOWATERHEATPUMP:VARIABLESPEED", AlphArray(10), "", "");//add dwh
				//SetUpCompSets(sIHPType, AlphArray(1), "COIL:WATERHEATING:AIRTOWATERHEATPUMP:VARIABLESPEED", AlphArray(11), AlphArray(2), AlphArray(3));//add SCwh
				//SetUpCompSets(sIHPType, AlphArray(1), "COIL:COOLING:DX:VARIABLESPEED", AlphArray(12), AlphArray(2), AlphArray(3));//add SCdwh
				//SetUpCompSets(sIHPType, AlphArray(1), "COIL:WATERHEATING:AIRTOWATERHEATPUMP:VARIABLESPEED", AlphArray(13), "", "");//add dwh
				//SetUpCompSets(sIHPType, AlphArray(1), "COIL:HEATING:DX:VARIABLESPEED", AlphArray(14), AlphArray(3), AlphArray(4));//add SH
				//SetUpCompSets(sIHPType, AlphArray(1), "COIL:WATERHEATING:AIRTOWATERHEATPUMP:VARIABLESPEED", AlphArray(15), "", "");//add dwh

				IntegratedHeatPumpUnits(DXCoilNum).SCCoilType = "COIL:COOLING:DX:VARIABLESPEED";
				IntegratedHeatPumpUnits(DXCoilNum).SCCoilName = AlphArray(10);
				Coiltype = IntegratedHeatPumpUnits(DXCoilNum).SCCoilType;
				CoilName = IntegratedHeatPumpUnits(DXCoilNum).SCCoilName;
>>>>>>> origin/ASIHPdev3

				ValidateComponent(Coiltype, CoilName, IsNotOK, CurrentModuleObject);
				if (IsNotOK) {
					ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
					ErrorsFound = true;
				}
				else {
					errFlag = false;
<<<<<<< HEAD
					IntegratedHeatPumps(DXCoilNum).SCCoilIndex = GetCoilIndexVariableSpeed(Coiltype, CoilName, errFlag);
=======
					IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex = GetCoilIndexVariableSpeed(Coiltype, CoilName, errFlag);
>>>>>>> origin/ASIHPdev3
					if (errFlag) {
						ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
						ErrorsFound = true;
					}
				}
<<<<<<< HEAD
				
				IntegratedHeatPumps(DXCoilNum).SHCoilType = "COIL:HEATING:DX:VARIABLESPEED";
				IntegratedHeatPumps(DXCoilNum).SHCoilName = AlphArray(9);
				Coiltype = IntegratedHeatPumps(DXCoilNum).SHCoilType;
				CoilName = IntegratedHeatPumps(DXCoilNum).SHCoilName;
=======


				IntegratedHeatPumpUnits(DXCoilNum).SHCoilType = "COIL:HEATING:DX:VARIABLESPEED";
				IntegratedHeatPumpUnits(DXCoilNum).SHCoilName = AlphArray(11);
				Coiltype = IntegratedHeatPumpUnits(DXCoilNum).SHCoilType;
				CoilName = IntegratedHeatPumpUnits(DXCoilNum).SHCoilName;
>>>>>>> origin/ASIHPdev3

				ValidateComponent(Coiltype, CoilName, IsNotOK, CurrentModuleObject);
				if (IsNotOK) {
					ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
					ErrorsFound = true;
				}
				else {
					errFlag = false;
<<<<<<< HEAD
					IntegratedHeatPumps(DXCoilNum).SHCoilIndex = GetCoilIndexVariableSpeed(Coiltype, CoilName, errFlag);
=======
					IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex = GetCoilIndexVariableSpeed(Coiltype, CoilName, errFlag);
>>>>>>> origin/ASIHPdev3
					if (errFlag) {
						ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
						ErrorsFound = true;
					}
				}
<<<<<<< HEAD
							
				IntegratedHeatPumps(DXCoilNum).DWHCoilType = "COIL:WATERHEATING:AIRTOWATERHEATPUMP:VARIABLESPEED";
				IntegratedHeatPumps(DXCoilNum).DWHCoilName = AlphArray(10);
				Coiltype = IntegratedHeatPumps(DXCoilNum).DWHCoilType;
				CoilName = IntegratedHeatPumps(DXCoilNum).DWHCoilName;
=======

				IntegratedHeatPumpUnits(DXCoilNum).DWHCoilType = "COIL:WATERHEATING:AIRTOWATERHEATPUMP:VARIABLESPEED";
				IntegratedHeatPumpUnits(DXCoilNum).DWHCoilName = AlphArray(12);
				Coiltype = IntegratedHeatPumpUnits(DXCoilNum).DWHCoilType;
				CoilName = IntegratedHeatPumpUnits(DXCoilNum).DWHCoilName;
>>>>>>> origin/ASIHPdev3

				ValidateComponent(Coiltype, CoilName, IsNotOK, CurrentModuleObject);
				if (IsNotOK) {
					ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
					ErrorsFound = true;
				}
				else {
					errFlag = false;
<<<<<<< HEAD
					IntegratedHeatPumps(DXCoilNum).DWHCoilIndex = GetCoilIndexVariableSpeed(Coiltype, CoilName, errFlag);
=======
					IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex = GetCoilIndexVariableSpeed(Coiltype, CoilName, errFlag);
>>>>>>> origin/ASIHPdev3
					if (errFlag) {
						ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
						ErrorsFound = true;
					}
				}
<<<<<<< HEAD
				
				IntegratedHeatPumps(DXCoilNum).SCWHCoilType = "COIL:WATERHEATING:AIRTOWATERHEATPUMP:VARIABLESPEED";
				IntegratedHeatPumps(DXCoilNum).SCWHCoilName = AlphArray(11);
				Coiltype = IntegratedHeatPumps(DXCoilNum).SCWHCoilType;
				CoilName = IntegratedHeatPumps(DXCoilNum).SCWHCoilName;
=======

				IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilType = "COIL:WATERHEATING:AIRTOWATERHEATPUMP:VARIABLESPEED";
				IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilName = AlphArray(13);
				Coiltype = IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilType;
				CoilName = IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilName;
>>>>>>> origin/ASIHPdev3

				ValidateComponent(Coiltype, CoilName, IsNotOK, CurrentModuleObject);
				if (IsNotOK) {
					ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
					ErrorsFound = true;
				}
				else {
					errFlag = false;
<<<<<<< HEAD
					IntegratedHeatPumps(DXCoilNum).SCWHCoilIndex = GetCoilIndexVariableSpeed(Coiltype, CoilName, errFlag);
=======
					IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex = GetCoilIndexVariableSpeed(Coiltype, CoilName, errFlag);
>>>>>>> origin/ASIHPdev3
					if (errFlag) {
						ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
						ErrorsFound = true;
					}
				}

<<<<<<< HEAD
				IntegratedHeatPumps(DXCoilNum).SCDWHCoolCoilType = "COIL:COOLING:DX:VARIABLESPEED";
				IntegratedHeatPumps(DXCoilNum).SCDWHCoolCoilName = AlphArray(12);
				Coiltype = IntegratedHeatPumps(DXCoilNum).SCDWHCoolCoilType;
				CoilName = IntegratedHeatPumps(DXCoilNum).SCDWHCoolCoilName;
=======

				IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilType = "COIL:COOLING:DX:VARIABLESPEED";
				IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilName = AlphArray(14);
				Coiltype = IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilType;
				CoilName = IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilName;
>>>>>>> origin/ASIHPdev3

				ValidateComponent(Coiltype, CoilName, IsNotOK, CurrentModuleObject);
				if (IsNotOK) {
					ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
					ErrorsFound = true;
				}
				else {
					errFlag = false;
<<<<<<< HEAD
					IntegratedHeatPumps(DXCoilNum).SCDWHCoolCoilIndex = GetCoilIndexVariableSpeed(Coiltype, CoilName, errFlag);
=======
					IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex = GetCoilIndexVariableSpeed(Coiltype, CoilName, errFlag);
>>>>>>> origin/ASIHPdev3
					if (errFlag) {
						ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
						ErrorsFound = true;
					}
				}


<<<<<<< HEAD
				IntegratedHeatPumps(DXCoilNum).SCDWHWHCoilType = "COIL:WATERHEATING:AIRTOWATERHEATPUMP:VARIABLESPEED";
				IntegratedHeatPumps(DXCoilNum).SCDWHWHCoilName = AlphArray(13);
				Coiltype = IntegratedHeatPumps(DXCoilNum).SCDWHWHCoilType;
				CoilName = IntegratedHeatPumps(DXCoilNum).SCDWHWHCoilName;
=======
				IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilType = "COIL:WATERHEATING:AIRTOWATERHEATPUMP:VARIABLESPEED";
				IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilName = AlphArray(15);
				Coiltype = IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilType;
				CoilName = IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilName;
>>>>>>> origin/ASIHPdev3

				ValidateComponent(Coiltype, CoilName, IsNotOK, CurrentModuleObject);
				if (IsNotOK) {
					ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
					ErrorsFound = true;
				}
				else {
					errFlag = false;
<<<<<<< HEAD
					IntegratedHeatPumps(DXCoilNum).SCDWHWHCoilIndex = GetCoilIndexVariableSpeed(Coiltype, CoilName, errFlag);
=======
					IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilIndex = GetCoilIndexVariableSpeed(Coiltype, CoilName, errFlag);
>>>>>>> origin/ASIHPdev3
					if (errFlag) {
						ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
						ErrorsFound = true;
					}
<<<<<<< HEAD
				}
								
				IntegratedHeatPumps(DXCoilNum).SHDWHHeatCoilType = "COIL:HEATING:DX:VARIABLESPEED";
				IntegratedHeatPumps(DXCoilNum).SHDWHHeatCoilName = AlphArray(14);
				Coiltype = IntegratedHeatPumps(DXCoilNum).SHDWHHeatCoilType;
				CoilName = IntegratedHeatPumps(DXCoilNum).SHDWHHeatCoilName;
=======
					else{
						VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilIndex).bIsDesuperheater = true;
					}
				}

				IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilType = "COIL:HEATING:DX:VARIABLESPEED";
				IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilName = AlphArray(16);
				Coiltype = IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilType;
				CoilName = IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilName;
>>>>>>> origin/ASIHPdev3

				ValidateComponent(Coiltype, CoilName, IsNotOK, CurrentModuleObject);
				if (IsNotOK) {
					ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
					ErrorsFound = true;
				}
				else {
					errFlag = false;
<<<<<<< HEAD
					IntegratedHeatPumps(DXCoilNum).SHDWHHeatCoilIndex = GetCoilIndexVariableSpeed(Coiltype, CoilName, errFlag);
=======
					IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilIndex = GetCoilIndexVariableSpeed(Coiltype, CoilName, errFlag);
>>>>>>> origin/ASIHPdev3
					if (errFlag) {
						ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
						ErrorsFound = true;
					}
				}
<<<<<<< HEAD
				
				IntegratedHeatPumps(DXCoilNum).SHDWHWHCoilType = "COIL:WATERHEATING:AIRTOWATERHEATPUMP:VARIABLESPEED";
				IntegratedHeatPumps(DXCoilNum).SHDWHWHCoilName = AlphArray(15);
				Coiltype = IntegratedHeatPumps(DXCoilNum).SHDWHWHCoilType;
				CoilName = IntegratedHeatPumps(DXCoilNum).SHDWHWHCoilName;
=======

				IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilType = "COIL:WATERHEATING:AIRTOWATERHEATPUMP:VARIABLESPEED";
				IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilName = AlphArray(17);
				Coiltype = IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilType;
				CoilName = IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilName;
>>>>>>> origin/ASIHPdev3

				ValidateComponent(Coiltype, CoilName, IsNotOK, CurrentModuleObject);
				if (IsNotOK) {
					ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
					ErrorsFound = true;
				}
				else {
					errFlag = false;
<<<<<<< HEAD
					IntegratedHeatPumps(DXCoilNum).SHDWHWHCoilIndex = GetCoilIndexVariableSpeed(Coiltype, CoilName, errFlag);
=======
					IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilIndex = GetCoilIndexVariableSpeed(Coiltype, CoilName, errFlag);
>>>>>>> origin/ASIHPdev3
					if (errFlag) {
						ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
						ErrorsFound = true;
					}
<<<<<<< HEAD
				}
				
				IntegratedHeatPumps(DXCoilNum).TindoorOverCoolAllow = NumArray(1);
				IntegratedHeatPumps(DXCoilNum).TambientOverCoolAllow = NumArray(2);
				IntegratedHeatPumps(DXCoilNum).TindoorWHHighPriority = NumArray(3);
				IntegratedHeatPumps(DXCoilNum).TambientWHHighPriority = NumArray(4);
				IntegratedHeatPumps(DXCoilNum).ModeMatchSCWH = int(NumArray(5));
				IntegratedHeatPumps(DXCoilNum).MinSpedSCWH = int(NumArray(6));
				IntegratedHeatPumps(DXCoilNum).WaterVolSCDWH = NumArray(7);
				IntegratedHeatPumps(DXCoilNum).MinSpedSCDWH = int(NumArray(8));
				IntegratedHeatPumps(DXCoilNum).TimeLimitSHDWH = NumArray(9);
				IntegratedHeatPumps(DXCoilNum).MinSpedSHDWH = int(NumArray(10));

				if (false == IntegratedHeatPumps(DXCoilNum).NodeConnected)
				{
					//air node connections
					InNode = IntegratedHeatPumps(DXCoilNum).AirCoolInletNodeNum;
					OutNode = IntegratedHeatPumps(DXCoilNum).AirHeatInletNodeNum;
					SetAirNodes(IntegratedHeatPumps(DXCoilNum).SCCoilName, ErrorsFound, InNode, OutNode);
					SetAirNodes(IntegratedHeatPumps(DXCoilNum).SCWHCoilName, ErrorsFound, InNode, OutNode);
					SetAirNodes(IntegratedHeatPumps(DXCoilNum).SCDWHCoolCoilName, ErrorsFound, InNode, OutNode);
					SetAirNodes(IntegratedHeatPumps(DXCoilNum).SCDWHWHCoilName, ErrorsFound, InNode, OutNode);

					InNode = IntegratedHeatPumps(DXCoilNum).AirHeatInletNodeNum;
					OutNode = IntegratedHeatPumps(DXCoilNum).AirOutletNodeNum;
					SetAirNodes(IntegratedHeatPumps(DXCoilNum).SHCoilName, ErrorsFound, InNode, OutNode);
					SetAirNodes(IntegratedHeatPumps(DXCoilNum).SHDWHHeatCoilName, ErrorsFound, InNode, OutNode);

					//SetAirNodes(IntegratedHeatPumps(DXCoilNum).SHDWHWHCoilName, ErrorsFound, InNode, OutNode);//SHDWHWHCoil has outdoor air nodes

					//water node connections
					InNode = IntegratedHeatPumps(DXCoilNum).WaterInletNodeNum;
					OutNode = IntegratedHeatPumps(DXCoilNum).WaterOutletNodeNum;
					SetWaterNodes(IntegratedHeatPumps(DXCoilNum).SCWHCoilName, ErrorsFound, InNode, OutNode);
					SetWaterNodes(IntegratedHeatPumps(DXCoilNum).SCDWHCoolCoilName, ErrorsFound, InNode, OutNode);
					SetWaterNodes(IntegratedHeatPumps(DXCoilNum).SCDWHWHCoilName, ErrorsFound, InNode, OutNode);
					SetWaterNodes(IntegratedHeatPumps(DXCoilNum).SHDWHHeatCoilName, ErrorsFound, InNode, OutNode);
					SetWaterNodes(IntegratedHeatPumps(DXCoilNum).SHDWHWHCoilName, ErrorsFound, InNode, OutNode);
					SetWaterNodes(IntegratedHeatPumps(DXCoilNum).DWHCoilName, ErrorsFound, InNode, OutNode);
					IntegratedHeatPumps(DXCoilNum).NodeConnected = true;
				};


				IntegratedHeatPumps(DXCoilNum).IHPCoilsSized = false; 
				IntegratedHeatPumps(DXCoilNum).CoolVolFlowScale = 1.0; 
				IntegratedHeatPumps(DXCoilNum).HeatVolFlowScale = 1.0;
				IntegratedHeatPumps(DXCoilNum).CurMode = IHPOperationMode::IdleMode; 
				IntegratedHeatPumps(DXCoilNum).MaxHeatAirMassFlow = 1e10;
				IntegratedHeatPumps(DXCoilNum).MaxHeatAirVolFlow = 1e10;
				IntegratedHeatPumps(DXCoilNum).MaxCoolAirMassFlow = 1e10; 
				IntegratedHeatPumps(DXCoilNum).MaxCoolAirVolFlow = 1e10; 
=======
					else{
						VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilIndex).bIsDesuperheater = true;
					}
				}

				IntegratedHeatPumpUnits(DXCoilNum).TindoorOverCoolAllow = NumArray(1);
				IntegratedHeatPumpUnits(DXCoilNum).TambientOverCoolAllow = NumArray(2);
				IntegratedHeatPumpUnits(DXCoilNum).TindoorWHHighPriority = NumArray(3);
				IntegratedHeatPumpUnits(DXCoilNum).TambientWHHighPriority = NumArray(4);
				IntegratedHeatPumpUnits(DXCoilNum).ModeMatchSCWH = int(NumArray(5));
				IntegratedHeatPumpUnits(DXCoilNum).MinSpedSCWH = int(NumArray(6));
				IntegratedHeatPumpUnits(DXCoilNum).WaterVolSCDWH = NumArray(7);
				IntegratedHeatPumpUnits(DXCoilNum).MinSpedSCDWH = int(NumArray(8));
				IntegratedHeatPumpUnits(DXCoilNum).TimeLimitSHDWH = NumArray(9);
				IntegratedHeatPumpUnits(DXCoilNum).MinSpedSHDWH = int(NumArray(10));

				if (false == IntegratedHeatPumpUnits(DXCoilNum).NodeConnected)
				{
					//air node connections
					InNode = IntegratedHeatPumpUnits(DXCoilNum).AirCoolInletNodeNum;
					OutNode = IntegratedHeatPumpUnits(DXCoilNum).AirHeatInletNodeNum;
					//all the SC air coils have indoor air nodes for cooling
					SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SCCoilName, ErrorsFound, InNode, OutNode);
					SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilName, ErrorsFound, InNode, OutNode);
					SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilName, ErrorsFound, InNode, OutNode);

					InNode = IntegratedHeatPumpUnits(DXCoilNum).AirHeatInletNodeNum;
					OutNode = IntegratedHeatPumpUnits(DXCoilNum).AirOutletNodeNum;
					//all the SH air coils have indoor air nodes for heating
					SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SHCoilName, ErrorsFound, InNode, OutNode);
					SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilName, ErrorsFound, InNode, OutNode);

					//water node connections
					InNode = IntegratedHeatPumpUnits(DXCoilNum).WaterInletNodeNum;
					OutNode = IntegratedHeatPumpUnits(DXCoilNum).WaterOutletNodeNum;
					//all the water coils have the same water side node connnections
					SetWaterNodes(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilName, ErrorsFound, InNode, OutNode);
					SetWaterNodes(IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilName, ErrorsFound, InNode, OutNode);
					SetWaterNodes(IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilName, ErrorsFound, InNode, OutNode);
					SetWaterNodes(IntegratedHeatPumpUnits(DXCoilNum).DWHCoilName, ErrorsFound, InNode, OutNode);

					//outdoor air node connections
					//DWH, SCDWH, SHDWH coils have the same outdoor air nodes
					InNode = IntegratedHeatPumpUnits(DXCoilNum).ODAirInletNodeNum;
					OutNode = IntegratedHeatPumpUnits(DXCoilNum).ODAirOutletNodeNum;
					SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).DWHCoilName, ErrorsFound, InNode, OutNode);//SCDWHCoil has outdoor air nodes
					SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilName, ErrorsFound, InNode, OutNode);//SCDWHCoil has outdoor air nodes
					SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilName, ErrorsFound, InNode, OutNode);//SHDWHWHCoil has outdoor air nodes

					IntegratedHeatPumpUnits(DXCoilNum).NodeConnected = true;
				};


				IntegratedHeatPumpUnits(DXCoilNum).IHPCoilsSized = false;
				IntegratedHeatPumpUnits(DXCoilNum).CoolVolFlowScale = 1.0; //scale coil flow rates to match the parent fan object
				IntegratedHeatPumpUnits(DXCoilNum).HeatVolFlowScale = 1.0; //scale coil flow rates to match the parent fan object
				IntegratedHeatPumpUnits(DXCoilNum).CurMode = IdleMode;
				IntegratedHeatPumpUnits(DXCoilNum).MaxHeatAirMassFlow = 1e10;
				IntegratedHeatPumpUnits(DXCoilNum).MaxHeatAirVolFlow = 1e10;
				IntegratedHeatPumpUnits(DXCoilNum).MaxCoolAirMassFlow = 1e10;
				IntegratedHeatPumpUnits(DXCoilNum).MaxCoolAirVolFlow = 1e10;
>>>>>>> origin/ASIHPdev3
			}


			if (ErrorsFound) {
				ShowFatalError(RoutineName + "Errors found in getting " + CurrentModuleObject + " input.  Preceding condition(s) causes termination.");
			}

<<<<<<< HEAD

		}

		void
		SizeIHP(int const DXCoilNum)
		{
			using VariableSpeedCoils::SimVariableSpeedCoils;
			using VariableSpeedCoils::SetVarSpeedCoilData;
			using VariableSpeedCoils::SizeVarSpeedCoil; 
			using VariableSpeedCoils::VarSpeedCoil;
			using DataSizing::AutoSize; 

			static bool ErrorsFound(false); // If errors detected in input
			Real64 RatedCapacity(0.0); //rated building cooling load
			
			// Obtains and Allocates WatertoAirHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
				//    WaterIndex=FindGlycol('WATER') !Initialize the WaterIndex once
				GetCoilsInputFlag = false;
			};

			if ( true == IntegratedHeatPumps(DXCoilNum).IHPCoilsSized ) { return; }

			SetVarSpeedCoilData(IntegratedHeatPumps(DXCoilNum).SCCoilIndex, ErrorsFound, _, IntegratedHeatPumps(DXCoilNum).SHCoilIndex);

			if (ErrorsFound) {
				ShowSevereError("SizeIHP: Could not match cooling coil\"" + IntegratedHeatPumps(DXCoilNum).SCCoilName + 
					"\" with heating coil=\"" + IntegratedHeatPumps(DXCoilNum).SHCoilName + "\"");
				ErrorsFound = false; 
			};
		
			SizeVarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCCoilIndex);//size cooling coil
			if (ErrorsFound) {
				ShowFatalError("SizeIHP: failed to size SC coil\"" + IntegratedHeatPumps(DXCoilNum).SCCoilName + "\"");
=======
		}

		void
			SizeIHP(int const DXCoilNum)
		{
			using VariableSpeedCoils::SimVariableSpeedCoils;
			using VariableSpeedCoils::SetVarSpeedCoilData;
			using VariableSpeedCoils::SizeVarSpeedCoil;
			using VariableSpeedCoils::VarSpeedCoil;
			using DataSizing::AutoSize;
			using General::TrimSigDigits;

			static bool ErrorsFound(false); // If errors detected in input
			Real64 RatedCapacity(0.0); //rated building cooling load

			// Obtains and Allocates AS-IHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
				GetCoilsInputFlag = false;
			};

			if (DXCoilNum > NumIHPs || DXCoilNum < 1) {
				ShowFatalError("SizeIHP: Invalid CompIndex passed=" + TrimSigDigits(DXCoilNum) +
					", Number of Integrated HPs=" + TrimSigDigits(NumIHPs) + ", IHP name=" + "AS-IHP");
			}

			if (true == IntegratedHeatPumpUnits(DXCoilNum).IHPCoilsSized){ return; }

			//associate SC coil with SH coil
			SetVarSpeedCoilData(IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex, ErrorsFound, _, IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex);
			if (ErrorsFound) {
				ShowSevereError("SizeIHP: Could not match cooling coil\"" + IntegratedHeatPumpUnits(DXCoilNum).SCCoilName +
					"\" with heating coil=\"" + IntegratedHeatPumpUnits(DXCoilNum).SHCoilName + "\"");
				ErrorsFound = false;
			};

			SizeVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex);//size cooling coil
			if (ErrorsFound) {
				ShowFatalError("SizeIHP: failed to size SC coil\"" + IntegratedHeatPumpUnits(DXCoilNum).SCCoilName + "\"");
>>>>>>> origin/ASIHPdev3
				ErrorsFound = false;
			}
			else
			{
<<<<<<< HEAD
				RatedCapacity = VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCCoilIndex).RatedCapCoolTotal; 
			};

			SizeVarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SHCoilIndex);//size cooling coil
			if (ErrorsFound) {
				ShowSevereError("SizeIHP: failed to size SH coil\"" + IntegratedHeatPumps(DXCoilNum).SHCoilName + "\"");
				ErrorsFound = false;
			};

			if (VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCDWHCoolCoilIndex).RatedCapCoolTotal == AutoSize)
			{
				VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCDWHCoolCoilIndex).RatedCapCoolTotal = RatedCapacity;
			};

			SetVarSpeedCoilData(IntegratedHeatPumps(DXCoilNum).SCDWHCoolCoilIndex, ErrorsFound, _, IntegratedHeatPumps(DXCoilNum).SHDWHHeatCoilIndex);

			SizeVarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCDWHCoolCoilIndex);

			if (ErrorsFound) {
				ShowSevereError("SizeIHP: failed to size SCDWH cooling coil\"" + IntegratedHeatPumps(DXCoilNum).SCDWHCoolCoilName + "\"");
				ErrorsFound = false;
			};

			SizeVarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SHDWHHeatCoilIndex);
			if (ErrorsFound) {
				ShowSevereError("SizeIHP: failed to size SHDWH heating coil\"" + IntegratedHeatPumps(DXCoilNum).SHDWHHeatCoilName + "\"");
=======
				RatedCapacity = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex).RatedCapCoolTotal;
			};

			SizeVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex);//size heating coil
			if (ErrorsFound) {
				ShowSevereError("SizeIHP: failed to size SH coil\"" + IntegratedHeatPumpUnits(DXCoilNum).SHCoilName + "\"");
				ErrorsFound = false;
			};

			//pass SC coil capacity to SCDWH cool coil
			if (VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex).RatedCapCoolTotal == AutoSize)
			{
				VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex).RatedCapCoolTotal = RatedCapacity;
			};

			//associate SCDWH air coil to SHDWH air coil
			SetVarSpeedCoilData(IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex, ErrorsFound, _, IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilIndex);

			//size SCDWH air coil
			SizeVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex);
			if (ErrorsFound) {
				ShowSevereError("SizeIHP: failed to size SCDWH cooling coil\"" + IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilName + "\"");
				ErrorsFound = false;
			};

			//size SHDWH air coil
			SizeVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilIndex);
			if (ErrorsFound) {
				ShowSevereError("SizeIHP: failed to size SHDWH heating coil\"" + IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilName + "\"");
>>>>>>> origin/ASIHPdev3
				ErrorsFound = false;
			};


<<<<<<< HEAD
			if (VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCWHCoilIndex).RatedCapWH == AutoSize)
			{
				VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCWHCoilIndex).RatedCapWH = 
					RatedCapacity / (1.0 - 1.0 / VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCWHCoilIndex).RatedCOPHeat);
			}

			SizeVarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCWHCoilIndex);
			if (ErrorsFound) {
				ShowSevereError("SizeIHP: failed to size SCWH coil\"" + IntegratedHeatPumps(DXCoilNum).SCWHCoilName + "\"");
				ErrorsFound = false;
			};

			if (VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).DWHCoilIndex).RatedCapWH == AutoSize)
			{
				VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).DWHCoilIndex).RatedCapWH = RatedCapacity ;
			}

			SizeVarSpeedCoil(IntegratedHeatPumps(DXCoilNum).DWHCoilIndex);
			if (ErrorsFound) {
				ShowSevereError("SizeIHP: failed to size DWH coil\"" + IntegratedHeatPumps(DXCoilNum).DWHCoilName + "\"");
				ErrorsFound = false;
			};

			if (VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCDWHWHCoilIndex).RatedCapWH == AutoSize)
			{
				VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCDWHWHCoilIndex).RatedCapWH = RatedCapacity * 0.13;
			}

			SizeVarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCDWHWHCoilIndex);
			if (ErrorsFound) {
				ShowSevereError("SizeIHP: failed to size SCDWH water heating coil\"" + IntegratedHeatPumps(DXCoilNum).SCDWHWHCoilName + "\"");
=======
			//size the water coils below
			//size SCWH water coil
			if (VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex).RatedCapWH == AutoSize)
			{
				VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex).RatedCapWH =
					RatedCapacity / (1.0 - 1.0 / VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex).RatedCOPHeat);
			}

			SizeVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex);
			if (ErrorsFound) {
				ShowSevereError("SizeIHP: failed to size SCWH coil\"" + IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilName + "\"");
				ErrorsFound = false;
			};

			//size DWH water coil
			if (VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex).RatedCapWH == AutoSize)
			{
				VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex).RatedCapWH = RatedCapacity;
			}

			SizeVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex);
			if (ErrorsFound) {
				ShowSevereError("SizeIHP: failed to size DWH coil\"" + IntegratedHeatPumpUnits(DXCoilNum).DWHCoilName + "\"");
				ErrorsFound = false;
			};

			//size SCDWH water coil
			if (VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilIndex).RatedCapWH == AutoSize)
			{
				VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilIndex).RatedCapWH = RatedCapacity * 0.13;
			}

			SizeVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilIndex);
			if (ErrorsFound) {
				ShowSevereError("SizeIHP: failed to size SCDWH water heating coil\"" + IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilName + "\"");
>>>>>>> origin/ASIHPdev3
				ErrorsFound = false;
			};


<<<<<<< HEAD
			if (VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SHDWHWHCoilIndex).RatedCapWH == AutoSize)
			{
				VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SHDWHWHCoilIndex).RatedCapWH = RatedCapacity * 0.1;
			}

			SizeVarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SHDWHWHCoilIndex);

			if (ErrorsFound) {
				ShowSevereError("SizeIHP: failed to size SHDWH water heating coil\"" + IntegratedHeatPumps(DXCoilNum).SHDWHWHCoilName + "\"");
				ErrorsFound = false;
			};

			IntegratedHeatPumps(DXCoilNum).IHPCoilsSized = true; 
		}

	

		void
		UpdateIHP(int const EP_UNUSED( DXCoilNum ) )
		{
		
=======
			//size SHDWH water coil
			if (VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilIndex).RatedCapWH == AutoSize)
			{
				VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilIndex).RatedCapWH = RatedCapacity * 0.1;
			}

			SizeVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilIndex);

			if (ErrorsFound) {
				ShowSevereError("SizeIHP: failed to size SHDWH water heating coil\"" + IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilName + "\"");
				ErrorsFound = false;
			};

			IntegratedHeatPumpUnits(DXCoilNum).IHPCoilsSized = true;
		}



		void
			InitializeIHP(int const DXCoilNum)
		{
			using General::TrimSigDigits;

			// Obtains and Allocates AS-IHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
				GetCoilsInputFlag = false;
			}

			if (DXCoilNum > NumIHPs || DXCoilNum < 1) {
				ShowFatalError("InitializeIHP: Invalid CompIndex passed=" + TrimSigDigits(DXCoilNum) +
					", Number of Integrated HPs=" + TrimSigDigits(NumIHPs) + ", IHP name=" + "AS-IHP");
			}
>>>>>>> origin/ASIHPdev3

		}


		void
<<<<<<< HEAD
		InitializeIHP(int const EP_UNUSED( DXCoilNum ) )
		{
			
		}

		void
		DecideWorkMode(
			int const DXCoilNum,
			Real64 const SensLoad, // Sensible demand load [W]
			Real64 const LatentLoad // Latent demand load [W]
		)//shall be called from a air loop parent
		{
=======
			UpdateIHP(int const DXCoilNum)
		{
			using General::TrimSigDigits;

			// Obtains and Allocates AS-IHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
				GetCoilsInputFlag = false;
			}

			if (DXCoilNum > NumIHPs || DXCoilNum < 1) {
				ShowFatalError("UpdateIHP: Invalid CompIndex passed=" + TrimSigDigits(DXCoilNum) +
					", Number of Integrated HPs=" + TrimSigDigits(NumIHPs) + ", IHP name=" + "AS-IHP");
			}


		}

		void
			DecideWorkMode(int const DXCoilNum,
			Real64 const SensLoad, // Sensible demand load [W]
			Real64 const LatentLoad // Latent demand load [W]
			)//shall be called from a air loop parent
		{
			//       AUTHOR         Bo Shen, ORNL
			//       DATE WRITTEN   March 2016
			//       RE-ENGINEERED  na

			// PURPOSE OF THIS SUBROUTINE:
			// This subroutine determine the IHP working mode in the next time step, 
			// it should be called by an air loop parent object, when FirstHVACIteration == true

			// METHODOLOGY EMPLOYED:

			// REFERENCES:
			// N/A

			// Using/Aliasing

>>>>>>> origin/ASIHPdev3
			using DataHVACGlobals::SmallLoad;
			using DataEnvironment::OutDryBulbTemp;
			using WaterThermalTanks::SimWaterThermalTank;
			using WaterThermalTanks::GetWaterThermalTankInput;
			using DataHVACGlobals::TimeStepSys;
<<<<<<< HEAD
			//using WaterThermalTanks::

			Real64 MyLoad(0.0);
			Real64 MaxCap(0.0); 
=======
			using General::TrimSigDigits;

			Real64 MyLoad(0.0);
			Real64 MaxCap(0.0);
>>>>>>> origin/ASIHPdev3
			Real64 MinCap(0.0);
			Real64 OptCap(0.0);
			Real64 WHHeatTimeSav(0.0);//time accumulation for water heating
			Real64 WHHeatVolSave(0.0);//volume accumulation for water heating

<<<<<<< HEAD
			// Obtains and Allocates WatertoAirHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
				//    WaterIndex=FindGlycol('WATER') !Initialize the WaterIndex once
				GetCoilsInputFlag = false;
			}

			if (IntegratedHeatPumps(DXCoilNum).IHPCoilsSized == false) SizeIHP(DXCoilNum);
						
			//decide working mode at the first moment
			//check if there is a water heating call
			IntegratedHeatPumps(DXCoilNum).IsWHCallAvail = false; 
			IntegratedHeatPumps(DXCoilNum).CheckWHCall = true; 
			if (0 == IntegratedHeatPumps(DXCoilNum).WHtankID)//not initialized yet
			{
				IntegratedHeatPumps(DXCoilNum).IsWHCallAvail = false;
			}
			else
			{
				Node(IntegratedHeatPumps(DXCoilNum).WaterOutletNodeNum).Temp =
					Node(IntegratedHeatPumps(DXCoilNum).WaterInletNodeNum).Temp; 
				SimWaterThermalTank(
					IntegratedHeatPumps(DXCoilNum).WHtankType, IntegratedHeatPumps(DXCoilNum).WHtankName,
					IntegratedHeatPumps(DXCoilNum).WHtankID,
=======
			// Obtains and Allocates AS-IHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
				GetCoilsInputFlag = false;
			}

			if (DXCoilNum > NumIHPs || DXCoilNum < 1) {
				ShowFatalError("DecideWorkMode: Invalid CompIndex passed=" + TrimSigDigits(DXCoilNum) +
					", Number of Integrated HPs=" + TrimSigDigits(NumIHPs) + ", IHP name=" + "AS-IHP");
			}

			if (IntegratedHeatPumpUnits(DXCoilNum).IHPCoilsSized == false) SizeIHP(DXCoilNum);

			//decide working mode at the first moment
			//check if there is a water heating call
			IntegratedHeatPumpUnits(DXCoilNum).IsWHCallAvail = false;
			IntegratedHeatPumpUnits(DXCoilNum).CheckWHCall = true; //set checking flag
			if (0 == IntegratedHeatPumpUnits(DXCoilNum).WHtankID)//not initialized yet
			{
				IntegratedHeatPumpUnits(DXCoilNum).IsWHCallAvail = false;
			}
			else
			{
				Node(IntegratedHeatPumpUnits(DXCoilNum).WaterOutletNodeNum).Temp =
					Node(IntegratedHeatPumpUnits(DXCoilNum).WaterInletNodeNum).Temp;
				SimWaterThermalTank(
					IntegratedHeatPumpUnits(DXCoilNum).WHtankType, IntegratedHeatPumpUnits(DXCoilNum).WHtankName,
					IntegratedHeatPumpUnits(DXCoilNum).WHtankID,
>>>>>>> origin/ASIHPdev3
					false, false,
					MyLoad, MaxCap, MinCap, OptCap, true // TRUE if First iteration of simulation
					);
			}
<<<<<<< HEAD

			IntegratedHeatPumps(DXCoilNum).CheckWHCall = false;

			WHHeatTimeSav = IntegratedHeatPumps(DXCoilNum).SHDWHRunTime; 
			WHHeatVolSave = IntegratedHeatPumps(DXCoilNum).WaterFlowAccumVol; 

			//clear the accumulation amount
			IntegratedHeatPumps(DXCoilNum).SHDWHRunTime = 0.0;
			IntegratedHeatPumps(DXCoilNum).WaterFlowAccumVol = 0.0;

			if (false == IntegratedHeatPumps(DXCoilNum).IsWHCallAvail)//no water heating call
			{
				if ((SensLoad < (-1.0 * SmallLoad)) || (LatentLoad < (-1.0 * SmallLoad)))
				{
					IntegratedHeatPumps(DXCoilNum).CurMode = IHPOperationMode::SCMode;
				}
				else if (SensLoad > SmallLoad)
				{
					if ((IntegratedHeatPumps(DXCoilNum).ControlledZoneTemp > IntegratedHeatPumps(DXCoilNum).TindoorOverCoolAllow) &&
						(OutDryBulbTemp > IntegratedHeatPumps(DXCoilNum).TambientOverCoolAllow))//used for cooling season
						IntegratedHeatPumps(DXCoilNum).CurMode = IHPOperationMode::IdleMode;
					else
						IntegratedHeatPumps(DXCoilNum).CurMode = IHPOperationMode::SHMode;
				}
				else
				{
					IntegratedHeatPumps(DXCoilNum).CurMode = IHPOperationMode::IdleMode;
=======
			IntegratedHeatPumpUnits(DXCoilNum).CheckWHCall = false;//clear checking flag

			//keep the water heating time and volume history
			WHHeatTimeSav = IntegratedHeatPumpUnits(DXCoilNum).SHDWHRunTime;
			if (SCDWHMode == IntegratedHeatPumpUnits(DXCoilNum).CurMode) {
				WHHeatVolSave = IntegratedHeatPumpUnits(DXCoilNum).WaterFlowAccumVol +
				Node(IntegratedHeatPumpUnits(DXCoilNum).WaterTankoutNod).MassFlowRate / 983.0 * TimeStepSys * SecInHour;//983 - water density at 60 C
			}
			else
			{
				WHHeatVolSave = 0.0; 
			}
			
			//clear the accumulation amount for other modes
			IntegratedHeatPumpUnits(DXCoilNum).SHDWHRunTime = 0.0;
			IntegratedHeatPumpUnits(DXCoilNum).WaterFlowAccumVol = 0.0;

			if (false == IntegratedHeatPumpUnits(DXCoilNum).IsWHCallAvail)//no water heating call
			{
				if ((SensLoad < (-1.0 * SmallLoad)) || (LatentLoad < (-1.0 * SmallLoad)))//space cooling mode
				{
					IntegratedHeatPumpUnits(DXCoilNum).CurMode = SCMode;
				}
				else if (SensLoad > SmallLoad)
				{
					if ((IntegratedHeatPumpUnits(DXCoilNum).ControlledZoneTemp > IntegratedHeatPumpUnits(DXCoilNum).TindoorOverCoolAllow) &&
						(OutDryBulbTemp > IntegratedHeatPumpUnits(DXCoilNum).TambientOverCoolAllow))//used for cooling season, avoid heating after SCWH mode
						IntegratedHeatPumpUnits(DXCoilNum).CurMode = IdleMode;
					else
						IntegratedHeatPumpUnits(DXCoilNum).CurMode = SHMode;
				}
				else
				{
					IntegratedHeatPumpUnits(DXCoilNum).CurMode = IdleMode;
>>>>>>> origin/ASIHPdev3
				}
			}
			//below has water heating calls
			else if ((SensLoad < (-1.0 * SmallLoad)) || (LatentLoad < (-1.0 * SmallLoad)))//simultaneous SC and WH calls
			{
<<<<<<< HEAD
				if (WHHeatVolSave < IntegratedHeatPumps(DXCoilNum).WaterVolSCDWH)
				{
					IntegratedHeatPumps(DXCoilNum).CurMode = IHPOperationMode::SCDWHMode;
					IntegratedHeatPumps(DXCoilNum).WaterFlowAccumVol = WHHeatVolSave + 
						Node(IntegratedHeatPumps(DXCoilNum).WaterTankoutNod).MassFlowRate/1000.0 * TimeStepSys * SecInHour;//1000.0 converted to volumetric flow rate
				}
				else
				{
					if (1 == IntegratedHeatPumps(DXCoilNum).ModeMatchSCWH) IntegratedHeatPumps(DXCoilNum).CurMode = IHPOperationMode::SCWHMatchWHMode;
					else IntegratedHeatPumps(DXCoilNum).CurMode = IHPOperationMode::SCWHMatchSCMode;
				};

			}
			else if ((IntegratedHeatPumps(DXCoilNum).ControlledZoneTemp > IntegratedHeatPumps(DXCoilNum).TindoorOverCoolAllow) &&
				(OutDryBulbTemp > IntegratedHeatPumps(DXCoilNum).TambientOverCoolAllow))
			{
				IntegratedHeatPumps(DXCoilNum).CurMode = IHPOperationMode::SCWHMatchWHMode;
			}
			else if ((IntegratedHeatPumps(DXCoilNum).ControlledZoneTemp > IntegratedHeatPumps(DXCoilNum).TindoorWHHighPriority) &&
				(OutDryBulbTemp > IntegratedHeatPumps(DXCoilNum).TambientWHHighPriority))
			{
				IntegratedHeatPumps(DXCoilNum).CurMode = IHPOperationMode::DWHMode;
			}
			else if (SensLoad > SmallLoad)
			{
				if (WHHeatTimeSav > IntegratedHeatPumps(DXCoilNum).TimeLimitSHDWH)
				{
					IntegratedHeatPumps(DXCoilNum).CurMode = IHPOperationMode::SHDWHElecHeatOnMode;
					IntegratedHeatPumps(DXCoilNum).SHDWHRunTime = WHHeatTimeSav + TimeStepSys * SecInHour; 
				}
				else
				{
					IntegratedHeatPumps(DXCoilNum).CurMode = IHPOperationMode::SHDWHElecHeatOffMode;
=======
				if (WHHeatVolSave < IntegratedHeatPumpUnits(DXCoilNum).WaterVolSCDWH)//small water heating amount
				{
					IntegratedHeatPumpUnits(DXCoilNum).CurMode = SCDWHMode;
					IntegratedHeatPumpUnits(DXCoilNum).WaterFlowAccumVol = WHHeatVolSave;
				}
				else
				{
					if (1 == IntegratedHeatPumpUnits(DXCoilNum).ModeMatchSCWH) //water heating priority
						IntegratedHeatPumpUnits(DXCoilNum).CurMode = SCWHMatchWHMode;
					else  //space cooling piority
						IntegratedHeatPumpUnits(DXCoilNum).CurMode = SCWHMatchSCMode;
				};

			}
			else if ((IntegratedHeatPumpUnits(DXCoilNum).ControlledZoneTemp > IntegratedHeatPumpUnits(DXCoilNum).TindoorOverCoolAllow) &&
				(OutDryBulbTemp > IntegratedHeatPumpUnits(DXCoilNum).TambientOverCoolAllow))//over-cooling allowed, water heating priority
			{
				IntegratedHeatPumpUnits(DXCoilNum).CurMode = SCWHMatchWHMode;
			}
			else if ((IntegratedHeatPumpUnits(DXCoilNum).ControlledZoneTemp > IntegratedHeatPumpUnits(DXCoilNum).TindoorWHHighPriority) &&
				(OutDryBulbTemp > IntegratedHeatPumpUnits(DXCoilNum).TambientWHHighPriority)) //ignore space heating request
			{
				IntegratedHeatPumpUnits(DXCoilNum).CurMode = DWHMode;
			}
			else if (SensLoad > SmallLoad)
			{
				IntegratedHeatPumpUnits(DXCoilNum).SHDWHRunTime = WHHeatTimeSav + TimeStepSys * SecInHour;

				if (WHHeatTimeSav > IntegratedHeatPumpUnits(DXCoilNum).TimeLimitSHDWH)
				{
					IntegratedHeatPumpUnits(DXCoilNum).CurMode = SHDWHElecHeatOnMode;
				}
				else
				{
					IntegratedHeatPumpUnits(DXCoilNum).CurMode = SHDWHElecHeatOffMode;
>>>>>>> origin/ASIHPdev3
				};
			}
			else
			{
<<<<<<< HEAD
				IntegratedHeatPumps(DXCoilNum).CurMode = IHPOperationMode::DWHMode;
			}
		}

		IHPOperationMode
		GetCurWorkMode(int const DXCoilNum)
		{
=======
				IntegratedHeatPumpUnits(DXCoilNum).CurMode = DWHMode;
			}

			//clear up, important
			ClearCoils(DXCoilNum);
		}

		void ClearCoils(int const DXCoilNum)
		{
			using VariableSpeedCoils::SimVariableSpeedCoils;
			using General::TrimSigDigits;

			Real64 EMP1(0.0), EMP2(0.0), EMP3(0.0); //place holder to calling clear up function
			int CycFanCycCoil(1);//fan cycl manner place holder

>>>>>>> origin/ASIHPdev3
			// Obtains and Allocates WatertoAirHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
				//    WaterIndex=FindGlycol('WATER') !Initialize the WaterIndex once
				GetCoilsInputFlag = false;
			}

<<<<<<< HEAD
			if (IntegratedHeatPumps(DXCoilNum).IHPCoilsSized == false) SizeIHP(DXCoilNum);

			return IntegratedHeatPumps(DXCoilNum).CurMode;
=======
			if (DXCoilNum > NumIHPs || DXCoilNum < 1) {
				ShowFatalError("ClearCoils: Invalid CompIndex passed=" + TrimSigDigits(DXCoilNum) +
					", Number of Integrated HPs=" + TrimSigDigits(NumIHPs) + ", IHP name=" + "AS-IHP");
			}

			//clear up
			SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex, CycFanCycCoil, EMP1, EMP2, EMP3, 1, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
			SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilIndex, CycFanCycCoil, EMP1, EMP2, EMP3, 1, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
			SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilIndex, CycFanCycCoil, EMP1, EMP2, EMP3, 1, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
			SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilIndex, CycFanCycCoil, EMP1, EMP2, EMP3, 1, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
			SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex, CycFanCycCoil, EMP1, EMP2, EMP3, 1, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
			SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex, CycFanCycCoil, EMP1, EMP2, EMP3, 1, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
			SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex, CycFanCycCoil, EMP1, EMP2, EMP3, 1, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
			SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex, CycFanCycCoil, EMP1, EMP2, EMP3, 1, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);

			return;
		}

		int
			GetCurWorkMode(int const DXCoilNum)
		{
			using General::TrimSigDigits;

			// Obtains and Allocates WatertoAirHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
				//    WaterIndex=FindGlycol('WATER') !Initialize the WaterIndex once
				GetCoilsInputFlag = false;
			}

			if (DXCoilNum > NumIHPs || DXCoilNum < 1) {
				ShowFatalError("GetCurWorkMode: Invalid CompIndex passed=" + TrimSigDigits(DXCoilNum) +
					", Number of Integrated HPs=" + TrimSigDigits(NumIHPs) + ", IHP name=" + "AS-IHP");
			}

			if (IntegratedHeatPumpUnits(DXCoilNum).IHPCoilsSized == false) SizeIHP(DXCoilNum);

			return(IntegratedHeatPumpUnits(DXCoilNum).CurMode);
>>>>>>> origin/ASIHPdev3
		}


		int
<<<<<<< HEAD
		GetCoilIndexIHP(
			std::string const & CoilType, // must match coil types in this module
			std::string const & CoilName, // must match coil names for the coil type
			bool & ErrorsFound // set to true if problem
		)
=======
			GetCoilIndexIHP(
			std::string const & CoilType, // must match coil types in this module
			std::string const & CoilName, // must match coil names for the coil type
			bool & ErrorsFound // set to true if problem
			)
>>>>>>> origin/ASIHPdev3
		{

			// FUNCTION INFORMATION:
			//       AUTHOR         Bo Shen
<<<<<<< HEAD
			//       DATE WRITTEN   Jan 2015
=======
			//       DATE WRITTEN   March 2016
>>>>>>> origin/ASIHPdev3
			//       MODIFIED       na
			//       RE-ENGINEERED  na

			// PURPOSE OF THIS FUNCTION:
			// This function looks up the coil index for the given coil and returns it.  If
			// incorrect coil type or name is given, ErrorsFound is returned as true and index is returned
			// as zero.

			// METHODOLOGY EMPLOYED:
			// na

			// REFERENCES:
			// na

			// Using/Aliasing
			using InputProcessor::FindItemInList;

			// Return value
			int IndexNum; // returned index of matched coil

			// Locals
			// FUNCTION ARGUMENT DEFINITIONS:

			// FUNCTION PARAMETER DEFINITIONS:
			// na

			// INTERFACE BLOCK SPECIFICATIONS:
			// na

			// DERIVED TYPE DEFINITIONS:
			// na

			// FUNCTION LOCAL VARIABLE DECLARATIONS:
			// na

			// Obtains and Allocates WatertoAirHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
				//    WaterIndex=FindGlycol('WATER') !Initialize the WaterIndex once
				GetCoilsInputFlag = false;
			}

<<<<<<< HEAD
			IndexNum = FindItemInList(CoilName, IntegratedHeatPumps);
=======
			IndexNum = FindItemInList(CoilName, IntegratedHeatPumpUnits);
>>>>>>> origin/ASIHPdev3

			if (IndexNum == 0) {
				ShowSevereError("GetCoilIndexIHP: Could not find CoilType=\"" + CoilType + "\" with Name=\"" + CoilName + "\"");
				ErrorsFound = true;
			}

			return IndexNum;
<<<<<<< HEAD

		}

		int
		GetCoilInletNodeIHP(
			std::string const & CoilType, // must match coil types in this module
			std::string const & CoilName, // must match coil names for the coil type
			bool & ErrorsFound // set to true if problem
		)
		{
			// FUNCTION INFORMATION:
			//       AUTHOR         Bo Shen
			//       DATE WRITTEN   Jan 2016
=======
		}

		int
			GetCoilInletNodeIHP(
			std::string const & CoilType, // must match coil types in this module
			std::string const & CoilName, // must match coil names for the coil type
			bool & ErrorsFound // set to true if problem
			)

		{
			// FUNCTION INFORMATION:
			//       AUTHOR         Bo Shen
			//       DATE WRITTEN   March 2016
>>>>>>> origin/ASIHPdev3
			//       MODIFIED       na
			//       RE-ENGINEERED  na

			// PURPOSE OF THIS FUNCTION:
			// This function looks up the given coil and returns the inlet node.  If
			// incorrect coil type or name is given, ErrorsFound is returned as true and value is returned
			// as zero.

			// METHODOLOGY EMPLOYED:
			// na

			// REFERENCES:
			// na

			// Using/Aliasing
			using InputProcessor::FindItemInList;

			// Return value
			int NodeNumber; // returned outlet node of matched coil

			// Locals
			// FUNCTION ARGUMENT DEFINITIONS:
			// FUNCTION PARAMETER DEFINITIONS:
			// na

			// INTERFACE BLOCK SPECIFICATIONS:
			// na

			// DERIVED TYPE DEFINITIONS:
			// na

			// FUNCTION LOCAL VARIABLE DECLARATIONS:
			int WhichCoil;

			// Obtains and Allocates WatertoAirHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
				//    WaterIndex=FindGlycol('WATER') !Initialize the WaterIndex once
				GetCoilsInputFlag = false;
			}

<<<<<<< HEAD
			WhichCoil = FindItemInList(CoilName, IntegratedHeatPumps);
			if (WhichCoil != 0) {
				NodeNumber = IntegratedHeatPumps(WhichCoil).AirCoolInletNodeNum;
=======
			WhichCoil = FindItemInList(CoilName, IntegratedHeatPumpUnits);
			if (WhichCoil != 0) {
				NodeNumber = IntegratedHeatPumpUnits(WhichCoil).AirCoolInletNodeNum;
>>>>>>> origin/ASIHPdev3
			}

			if (WhichCoil == 0) {
				ShowSevereError("GetCoilInletNodeIHP: Could not find CoilType=\"" + CoilType + "\" with Name=\"" + CoilName + "\"");
				ErrorsFound = true;
				NodeNumber = 0;
			}

			return NodeNumber;

		}

		int
<<<<<<< HEAD
		GetIHPDWHCoilPLFFPLR(
			std::string const & CoilType, // must match coil types in this module
			std::string const & CoilName, // must match coil names for the coil type
			IHPOperationMode const EP_UNUSED( Mode ),//mode coil type
			bool & ErrorsFound // set to true if problem
		)
		{
			// FUNCTION INFORMATION:
			//       AUTHOR         Bo Shen
			//       DATE WRITTEN   Jan, 2016
=======
			GetIHPDWHCoilPLFFPLR(
			std::string const & CoilType, // must match coil types in this module
			std::string const & CoilName, // must match coil names for the coil type
			int const Mode,//mode coil type
			bool & ErrorsFound // set to true if problem
			)
		{
			// FUNCTION INFORMATION:
			//       AUTHOR         Bo Shen
			//       DATE WRITTEN   March, 2016
>>>>>>> origin/ASIHPdev3
			//       MODIFIED       na
			//       RE-ENGINEERED  na

			// PURPOSE OF THIS FUNCTION:
			// This function looks up the given coil and returns PLR curve index.  If
			// incorrect coil type or name is given, ErrorsFound is returned as true and value is returned
			// as zero.

			// METHODOLOGY EMPLOYED:
			// na

			// REFERENCES:
			// na

			// Using/Aliasing
			using InputProcessor::FindItemInList;
			using VariableSpeedCoils::GetVSCoilPLFFPLR;

			// Return value
			int PLRNumber; // returned outlet node of matched coil

			// Locals
			// FUNCTION ARGUMENT DEFINITIONS:
			// FUNCTION PARAMETER DEFINITIONS:
			// na

			// INTERFACE BLOCK SPECIFICATIONS:
			// na

			// DERIVED TYPE DEFINITIONS:
			// na

			// FUNCTION LOCAL VARIABLE DECLARATIONS:
			int WhichCoil;

			// Obtains and Allocates WatertoAirHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
				//    WaterIndex=FindGlycol('WATER') !Initialize the WaterIndex once
				GetCoilsInputFlag = false;
			}

<<<<<<< HEAD
			WhichCoil = FindItemInList(CoilName, IntegratedHeatPumps);
			if (WhichCoil != 0) {

				if (IntegratedHeatPumps(WhichCoil).DWHCoilIndex > 0)
					PLRNumber =	GetVSCoilPLFFPLR(IntegratedHeatPumps(WhichCoil).DWHCoilType, IntegratedHeatPumps(WhichCoil).DWHCoilName, ErrorsFound);
				else 
					PLRNumber = GetVSCoilPLFFPLR(IntegratedHeatPumps(WhichCoil).SCWHCoilType, IntegratedHeatPumps(WhichCoil).SCWHCoilName, ErrorsFound);
=======
			WhichCoil = FindItemInList(CoilName, IntegratedHeatPumpUnits);
			if (WhichCoil != 0) {
				//this will be called by HPWH parent
				if (IntegratedHeatPumpUnits(WhichCoil).DWHCoilIndex > 0)
					PLRNumber = GetVSCoilPLFFPLR(IntegratedHeatPumpUnits(WhichCoil).DWHCoilType, IntegratedHeatPumpUnits(WhichCoil).DWHCoilName, ErrorsFound);
				else
					PLRNumber = GetVSCoilPLFFPLR(IntegratedHeatPumpUnits(WhichCoil).SCWHCoilType, IntegratedHeatPumpUnits(WhichCoil).SCWHCoilName, ErrorsFound);
>>>>>>> origin/ASIHPdev3
			}
			else {
				WhichCoil = 0;
			}

			if (WhichCoil == 0) {
				ShowSevereError("GetIHPDWHCoilPLFFPLR: Could not find CoilType=\"" + CoilType + "\" with Name=\"" + CoilName + "\"");
				ErrorsFound = true;
				PLRNumber = 0;
			}

			return PLRNumber;
		}


		Real64
<<<<<<< HEAD
		GetDWHCoilCapacityIHP(
			std::string const & CoilType, // must match coil types in this module
			std::string const & CoilName, // must match coil names for the coil type
			IHPOperationMode const EP_UNUSED( Mode ), //mode coil type
			bool & ErrorsFound // set to true if problem
		)
=======
			GetDWHCoilCapacityIHP(
			std::string const & CoilType, // must match coil types in this module
			std::string const & CoilName, // must match coil names for the coil type
			int const Mode,//mode coil type
			bool & ErrorsFound // set to true if problem
			)
>>>>>>> origin/ASIHPdev3
		{

			// FUNCTION INFORMATION:
			//       AUTHOR         Bo Shen
			//       DATE WRITTEN   Jan 2016
			//       MODIFIED       na
			//       RE-ENGINEERED  na

			// PURPOSE OF THIS FUNCTION:
			// This function looks up the rated coil capacity at the nominal speed level for the given coil and returns it.  If
			// incorrect coil type or name is given, ErrorsFound is returned as true and capacity is returned
			// as negative.

			// METHODOLOGY EMPLOYED:
			// na

			// REFERENCES:
			// na

			// Using/Aliasing
			using InputProcessor::FindItemInList;
<<<<<<< HEAD
			using VariableSpeedCoils::GetCoilCapacityVariableSpeed; 
=======
			using VariableSpeedCoils::GetCoilCapacityVariableSpeed;
>>>>>>> origin/ASIHPdev3

			// Return value
			Real64 CoilCapacity; // returned capacity of matched coil

			// Locals
			// FUNCTION ARGUMENT DEFINITIONS:

			// FUNCTION PARAMETER DEFINITIONS:
			// na

			// INTERFACE BLOCK SPECIFICATIONS:
			// na

			// DERIVED TYPE DEFINITIONS:
			// na

			// FUNCTION LOCAL VARIABLE DECLARATIONS:
			int WhichCoil;

			// Obtains and Allocates WatertoAirHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
				//    WaterIndex=FindGlycol('WATER') !Initialize the WaterIndex once
				GetCoilsInputFlag = false;
			}

<<<<<<< HEAD
			WhichCoil = FindItemInList(CoilName, IntegratedHeatPumps);
			if (WhichCoil != 0) {

				if (IntegratedHeatPumps(WhichCoil).IHPCoilsSized == false) SizeIHP(WhichCoil);

				if (IntegratedHeatPumps(WhichCoil).DWHCoilIndex > 0)
					CoilCapacity =
					GetCoilCapacityVariableSpeed(IntegratedHeatPumps(WhichCoil).DWHCoilType, IntegratedHeatPumps(WhichCoil).DWHCoilName, ErrorsFound);
				else
					CoilCapacity =
					GetCoilCapacityVariableSpeed(IntegratedHeatPumps(WhichCoil).SCWHCoilType, IntegratedHeatPumps(WhichCoil).SCWHCoilName, ErrorsFound);
=======
			WhichCoil = FindItemInList(CoilName, IntegratedHeatPumpUnits);
			if (WhichCoil != 0) {

				if (IntegratedHeatPumpUnits(WhichCoil).IHPCoilsSized == false) SizeIHP(WhichCoil);

				if (IntegratedHeatPumpUnits(WhichCoil).DWHCoilIndex > 0)
				{
					CoilCapacity =
						GetCoilCapacityVariableSpeed(IntegratedHeatPumpUnits(WhichCoil).DWHCoilType, IntegratedHeatPumpUnits(WhichCoil).DWHCoilName, ErrorsFound);
				}
				else{
					CoilCapacity =
						GetCoilCapacityVariableSpeed(IntegratedHeatPumpUnits(WhichCoil).SCWHCoilType, IntegratedHeatPumpUnits(WhichCoil).SCWHCoilName, ErrorsFound);
				}
>>>>>>> origin/ASIHPdev3
			}
			else {
				WhichCoil = 0;
			}

			if (WhichCoil == 0) {
				ShowSevereError("GetCoilCapacityVariableSpeed: Could not find CoilType=\"" + CoilType + "\" with Name=\"" + CoilName + "\"");
				ErrorsFound = true;
				CoilCapacity = -1000.0;
			}

			return CoilCapacity;
<<<<<<< HEAD

		}

		int
		GetLowSpeedNumIHP( int const DXCoilNum )
		{
			int SpeedNum( 0 ); 
=======
		}

		int
			GetLowSpeedNumIHP(int const DXCoilNum)
		{
			using General::TrimSigDigits;

			int SpeedNum(0);
>>>>>>> origin/ASIHPdev3

			// Obtains and Allocates WatertoAirHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
				//    WaterIndex=FindGlycol('WATER') !Initialize the WaterIndex once
				GetCoilsInputFlag = false;
			}

<<<<<<< HEAD

			switch ( IntegratedHeatPumps( DXCoilNum ).CurMode )
			{
			case IHPOperationMode::IdleMode:
				// intentional fallthrough
			case IHPOperationMode::SCMode:
				// intentional fallthrough
			case IHPOperationMode::SHMode:
				// intentional fallthrough
			case IHPOperationMode::DWHMode:
				// intentional fallthrough
			default:
				SpeedNum = 1;
				break;
			case IHPOperationMode::SCWHMatchSCMode:
			case IHPOperationMode::SCWHMatchWHMode:
				SpeedNum = IntegratedHeatPumps( DXCoilNum ).MinSpedSCWH; 
				break;
			case IHPOperationMode::SCDWHMode:
				SpeedNum = IntegratedHeatPumps( DXCoilNum ).MinSpedSCDWH;
				break;
			case IHPOperationMode::SHDWHElecHeatOffMode:
			case IHPOperationMode::SHDWHElecHeatOnMode:
				SpeedNum = IntegratedHeatPumps( DXCoilNum ).MinSpedSHDWH;
				break;
			}

			return SpeedNum; 
		}

		int
		GetMaxSpeedNumIHP( int const DXCoilNum )
		{
			using VariableSpeedCoils::VarSpeedCoil;

			// Obtains and Allocates WatertoAirHP related parameters from input file
			if ( GetCoilsInputFlag ) { //First time subroutine has been entered
=======
			if (DXCoilNum > NumIHPs || DXCoilNum < 1) {
				ShowFatalError("GetLowSpeedNumIHP: Invalid CompIndex passed=" + TrimSigDigits(DXCoilNum) +
					", Number of Integrated HPs=" + TrimSigDigits(NumIHPs) + ", IHP name=" + "AS-IHP");
			}

			switch (IntegratedHeatPumpUnits(DXCoilNum).CurMode)
			{
			case IdleMode:
				SpeedNum = 1;
				break;
			case SCMode:
				SpeedNum = 1;
				break;
			case SHMode:
				SpeedNum = 1;
				break;
			case DWHMode:
				SpeedNum = 1;
				break;
			case SCWHMatchSCMode:
			case SCWHMatchWHMode:
				SpeedNum = IntegratedHeatPumpUnits(DXCoilNum).MinSpedSCWH;
				break;
			case SCDWHMode:
				SpeedNum = IntegratedHeatPumpUnits(DXCoilNum).MinSpedSCDWH;
				break;
			case SHDWHElecHeatOffMode:
			case SHDWHElecHeatOnMode:
				SpeedNum = IntegratedHeatPumpUnits(DXCoilNum).MinSpedSHDWH;
				break;
			default:
				SpeedNum = 1;
				break;
			}

			return(SpeedNum);
		}

		int
			GetMaxSpeedNumIHP(int const DXCoilNum)
		{
			using VariableSpeedCoils::VarSpeedCoil;
			using General::TrimSigDigits;

			// Obtains and Allocates WatertoAirHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
>>>>>>> origin/ASIHPdev3
				GetIHPInput();
				//    WaterIndex=FindGlycol('WATER') !Initialize the WaterIndex once
				GetCoilsInputFlag = false;
			}

<<<<<<< HEAD
			int SpeedNum( 0 );

			switch ( IntegratedHeatPumps( DXCoilNum ).CurMode )
			{
			case IHPOperationMode::IdleMode:
				SpeedNum = VarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SCCoilIndex ).NumOfSpeeds;
				break;
			case IHPOperationMode::SCMode:
				SpeedNum = VarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SCCoilIndex ).NumOfSpeeds;
				break;
			case IHPOperationMode::SHMode:
				SpeedNum = VarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SHCoilIndex ).NumOfSpeeds;
				break;
			case IHPOperationMode::DWHMode:
				SpeedNum = VarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).DWHCoilIndex ).NumOfSpeeds;
				break;
			case IHPOperationMode::SCWHMatchSCMode:
			case IHPOperationMode::SCWHMatchWHMode:
				SpeedNum = VarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SCWHCoilIndex ).NumOfSpeeds;
				break;
			case IHPOperationMode::SCDWHMode:
				SpeedNum = VarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SCDWHCoolCoilIndex ).NumOfSpeeds;
				break;
			case IHPOperationMode::SHDWHElecHeatOffMode:
			case IHPOperationMode::SHDWHElecHeatOnMode:
				SpeedNum = VarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SHDWHHeatCoilIndex ).NumOfSpeeds;
				break;
			default:
				SpeedNum = VarSpeedCoil( IntegratedHeatPumps( DXCoilNum ).SCCoilIndex ).NumOfSpeeds;
				break;
			}
			
			return SpeedNum;
		}

		Real64
		GetAirVolFlowRateIHP(
			int const DXCoilNum,
			int const SpeedNum,
			Real64 const SpeedRatio,
			bool const IsCallbyWH //whether the call from the water heating loop or air loop, true = from water heating loop
		)
		{
			using VariableSpeedCoils::VarSpeedCoil;

			int IHPCoilIndex(0); 
			Real64 AirVolFlowRate(0.0);
			Real64 FlowScale(1.0);
			bool IsResultFlow(false); 
=======
			if (DXCoilNum > NumIHPs || DXCoilNum < 1) {
				ShowFatalError("GetMaxSpeedNumIHP: Invalid CompIndex passed=" + TrimSigDigits(DXCoilNum) +
					", Number of Integrated HPs=" + TrimSigDigits(NumIHPs) + ", IHP name=" + "AS-IHP");
			}

			int SpeedNum(0);

			switch (IntegratedHeatPumpUnits(DXCoilNum).CurMode)
			{
			case IdleMode:
				SpeedNum = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex).NumOfSpeeds;
				break;
			case SCMode:
				SpeedNum = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex).NumOfSpeeds;
				break;
			case SHMode:
				SpeedNum = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex).NumOfSpeeds;
				break;
			case DWHMode:
				SpeedNum = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex).NumOfSpeeds;
				break;
			case SCWHMatchSCMode:
			case SCWHMatchWHMode:
				SpeedNum = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex).NumOfSpeeds;
				break;
			case SCDWHMode:
				SpeedNum = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex).NumOfSpeeds;
				break;
			case SHDWHElecHeatOffMode:
			case SHDWHElecHeatOnMode:
				SpeedNum = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilIndex).NumOfSpeeds;
				break;
			default:
				SpeedNum = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex).NumOfSpeeds;
				break;
			}

			return(SpeedNum);
		}

		Real64
			GetAirVolFlowRateIHP(int const DXCoilNum, int const SpeedNum, Real64 const SpeedRatio,
			bool const IsCallbyWH //whether the call from the water heating loop or air loop, true = from water heating loop
			)
		{
			using VariableSpeedCoils::VarSpeedCoil;
			using General::TrimSigDigits;

			int IHPCoilIndex(0);
			Real64 AirVolFlowRate(0.0);
			Real64 FlowScale(1.0);
			bool IsResultFlow(false); //IsResultFlow = true, the air flow rate will be from a simultaneous mode, won't be re-calculated
>>>>>>> origin/ASIHPdev3

			// Obtains and Allocates WatertoAirHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
<<<<<<< HEAD
				//    WaterIndex=FindGlycol('WATER') !Initialize the WaterIndex once
				GetCoilsInputFlag = false;
			}

			if (IntegratedHeatPumps(DXCoilNum).IHPCoilsSized == false) SizeIHP(DXCoilNum);

			FlowScale = 0.0;
			switch (IntegratedHeatPumps(DXCoilNum).CurMode)
			{
			case IHPOperationMode::IdleMode:
				IHPCoilIndex = IntegratedHeatPumps(DXCoilNum).SCCoilIndex;
				break;
			case IHPOperationMode::SCMode:
				IHPCoilIndex = IntegratedHeatPumps(DXCoilNum).SCCoilIndex;
				if (false == IsCallbyWH)
				{
					FlowScale = IntegratedHeatPumps(DXCoilNum).CoolVolFlowScale;
				}

				break;
			case IHPOperationMode::SHMode:
				IHPCoilIndex = IntegratedHeatPumps(DXCoilNum).SHCoilIndex;
				if (false == IsCallbyWH)
				{
					FlowScale = IntegratedHeatPumps(DXCoilNum).HeatVolFlowScale;
				}				
				break;
			case IHPOperationMode::DWHMode:
				IHPCoilIndex = IntegratedHeatPumps(DXCoilNum).DWHCoilIndex;
				FlowScale = 1.0;
				break;
			case IHPOperationMode::SCWHMatchSCMode:
				IHPCoilIndex = IntegratedHeatPumps(DXCoilNum).SCWHCoilIndex;
				FlowScale = IntegratedHeatPumps(DXCoilNum).CoolVolFlowScale;
				if (true == IsCallbyWH)
				{
					IsResultFlow = true;
					AirVolFlowRate = VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCWHCoilIndex).AirVolFlowRate; 
				}
				break;
			case IHPOperationMode::SCWHMatchWHMode:
				IHPCoilIndex = IntegratedHeatPumps(DXCoilNum).SCWHCoilIndex;
				FlowScale = IntegratedHeatPumps(DXCoilNum).CoolVolFlowScale;
				if (false == IsCallbyWH)
				{
					IsResultFlow = true;
					AirVolFlowRate = VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCWHCoilIndex).AirVolFlowRate;
				}
				break;
			case IHPOperationMode::SCDWHMode:
				IHPCoilIndex = IntegratedHeatPumps(DXCoilNum).SCDWHCoolCoilIndex;
				FlowScale = IntegratedHeatPumps(DXCoilNum).CoolVolFlowScale;
				if (true == IsCallbyWH)
				{
					IsResultFlow = true;
					AirVolFlowRate = VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCDWHCoolCoilIndex).AirVolFlowRate;
				}
				break;
			case IHPOperationMode::SHDWHElecHeatOffMode:
			case IHPOperationMode::SHDWHElecHeatOnMode:
				IHPCoilIndex = IntegratedHeatPumps(DXCoilNum).SHDWHHeatCoilIndex;
				FlowScale = IntegratedHeatPumps(DXCoilNum).HeatVolFlowScale;
				if (true == IsCallbyWH)
				{
					IsResultFlow = true;
					AirVolFlowRate = VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SHDWHHeatCoilIndex).AirVolFlowRate;
				}
				break;
			default:
				IHPCoilIndex = IntegratedHeatPumps(DXCoilNum).SCCoilIndex;
=======
				GetCoilsInputFlag = false;
			}

			if (DXCoilNum > NumIHPs || DXCoilNum < 1) {
				ShowFatalError("GetAirVolFlowRateIHP: Invalid CompIndex passed=" + TrimSigDigits(DXCoilNum) +
					", Number of Integrated HPs=" + TrimSigDigits(NumIHPs) + ", IHP name=" + "AS-IHP");
			}

			if (IntegratedHeatPumpUnits(DXCoilNum).IHPCoilsSized == false) SizeIHP(DXCoilNum);

			FlowScale = 0.0;
			switch (IntegratedHeatPumpUnits(DXCoilNum).CurMode)
			{
			case IdleMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex;
				break;
			case SCMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex;
				if (false == IsCallbyWH)//call from air loop
				{
					FlowScale = IntegratedHeatPumpUnits(DXCoilNum).CoolVolFlowScale;
				}

				break;
			case SHMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex;
				if (false == IsCallbyWH)//call from air loop
				{
					FlowScale = IntegratedHeatPumpUnits(DXCoilNum).HeatVolFlowScale;
				}
				break;
			case DWHMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex;
				FlowScale = 1.0;
				break;
			case SCWHMatchSCMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex;
				FlowScale = IntegratedHeatPumpUnits(DXCoilNum).CoolVolFlowScale;
				if (true == IsCallbyWH)//call from water loop
				{
					IsResultFlow = true;
					AirVolFlowRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex).AirVolFlowRate;
				}
				break;
			case SCWHMatchWHMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex;
				FlowScale = IntegratedHeatPumpUnits(DXCoilNum).CoolVolFlowScale;
				if (false == IsCallbyWH)
				{
					IsResultFlow = true;
					AirVolFlowRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex).AirVolFlowRate;
				}
				break;
			case SCDWHMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex;
				FlowScale = IntegratedHeatPumpUnits(DXCoilNum).CoolVolFlowScale;
				if (true == IsCallbyWH)
				{
					IsResultFlow = true;
					AirVolFlowRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex).AirVolFlowRate;
				}
				break;
			case SHDWHElecHeatOffMode:
			case SHDWHElecHeatOnMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilIndex;
				FlowScale = IntegratedHeatPumpUnits(DXCoilNum).HeatVolFlowScale;
				if (true == IsCallbyWH)
				{
					IsResultFlow = true;
					AirVolFlowRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilIndex).AirVolFlowRate;
				}
				break;
			default:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex;
>>>>>>> origin/ASIHPdev3
				FlowScale = 0.0;
				break;
			}

<<<<<<< HEAD
			
=======

>>>>>>> origin/ASIHPdev3
			if (false == IsResultFlow){
				if (1 == SpeedNum)  AirVolFlowRate = VarSpeedCoil(IHPCoilIndex).MSRatedAirVolFlowRate(SpeedNum);
				else AirVolFlowRate = SpeedRatio * VarSpeedCoil(IHPCoilIndex).MSRatedAirVolFlowRate(SpeedNum) +
					(1.0 - SpeedRatio) * VarSpeedCoil(IHPCoilIndex).MSRatedAirVolFlowRate(SpeedNum - 1);

				AirVolFlowRate = AirVolFlowRate * FlowScale;
			}
<<<<<<< HEAD
						

			if (AirVolFlowRate > IntegratedHeatPumps(DXCoilNum).MaxCoolAirVolFlow) AirVolFlowRate = IntegratedHeatPumps(DXCoilNum).MaxCoolAirVolFlow; 
			if (AirVolFlowRate > IntegratedHeatPumps(DXCoilNum).MaxHeatAirVolFlow) AirVolFlowRate = IntegratedHeatPumps(DXCoilNum).MaxHeatAirVolFlow;
=======


			if (AirVolFlowRate > IntegratedHeatPumpUnits(DXCoilNum).MaxCoolAirVolFlow) AirVolFlowRate = IntegratedHeatPumpUnits(DXCoilNum).MaxCoolAirVolFlow;
			if (AirVolFlowRate > IntegratedHeatPumpUnits(DXCoilNum).MaxHeatAirVolFlow) AirVolFlowRate = IntegratedHeatPumpUnits(DXCoilNum).MaxHeatAirVolFlow;
>>>>>>> origin/ASIHPdev3

			return(AirVolFlowRate);
		}

		Real64
<<<<<<< HEAD
		GetWaterVolFlowRateIHP(
			int const DXCoilNum,
			int const SpeedNum,
			Real64 const SpeedRatio,
			bool const EP_UNUSED( IsCallbyWH ) //whether the call from the water heating loop or air loop, true = from water heating loop
		)
		{
			using VariableSpeedCoils::VarSpeedCoil;
=======
			GetWaterVolFlowRateIHP(int const DXCoilNum, int const SpeedNum, Real64 const SpeedRatio,
			bool const IsCallbyWH //whether the call from the water heating loop or air loop, true = from water heating loop
			)
		{
			using VariableSpeedCoils::VarSpeedCoil;
			using General::TrimSigDigits;
>>>>>>> origin/ASIHPdev3

			int IHPCoilIndex(0);
			Real64 WaterVolFlowRate(0.0);


			// Obtains and Allocates WatertoAirHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
<<<<<<< HEAD
				//    WaterIndex=FindGlycol('WATER') !Initialize the WaterIndex once
				GetCoilsInputFlag = false;
			}

			if (IntegratedHeatPumps(DXCoilNum).IHPCoilsSized == false) SizeIHP(DXCoilNum);

			switch (IntegratedHeatPumps(DXCoilNum).CurMode)
			{
			case IHPOperationMode::IdleMode:
				WaterVolFlowRate = 0.0; 
				break;
			case IHPOperationMode::SCMode:
				WaterVolFlowRate = VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCCoilIndex).WaterVolFlowRate;
				break;
			case IHPOperationMode::SHMode:
				WaterVolFlowRate = VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SHCoilIndex).WaterVolFlowRate;
				break;
			case IHPOperationMode::DWHMode:
				IHPCoilIndex = IntegratedHeatPumps(DXCoilNum).DWHCoilIndex;
=======
				GetCoilsInputFlag = false;
			}

			if (DXCoilNum > NumIHPs || DXCoilNum < 1) {
				ShowFatalError("GetWaterVolFlowRateIHP: Invalid CompIndex passed=" + TrimSigDigits(DXCoilNum) +
					", Number of Integrated HPs=" + TrimSigDigits(NumIHPs) + ", IHP name=" + "AS-IHP");
			}

			if (IntegratedHeatPumpUnits(DXCoilNum).IHPCoilsSized == false) SizeIHP(DXCoilNum);

			switch (IntegratedHeatPumpUnits(DXCoilNum).CurMode)
			{
			case IdleMode:
				WaterVolFlowRate = 0.0;
				break;
			case SCMode:
				WaterVolFlowRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex).WaterVolFlowRate;
				break;
			case SHMode:
				WaterVolFlowRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex).WaterVolFlowRate;
				break;
			case DWHMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex;
>>>>>>> origin/ASIHPdev3
				if (1 == SpeedNum)  WaterVolFlowRate = VarSpeedCoil(IHPCoilIndex).MSRatedWaterVolFlowRate(SpeedNum);
				else WaterVolFlowRate = SpeedRatio * VarSpeedCoil(IHPCoilIndex).MSRatedWaterVolFlowRate(SpeedNum) +
					(1.0 - SpeedRatio) * VarSpeedCoil(IHPCoilIndex).MSRatedWaterVolFlowRate(SpeedNum - 1);
				break;
<<<<<<< HEAD
			case IHPOperationMode::SCWHMatchSCMode:
				WaterVolFlowRate = VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCWHCoilIndex).WaterVolFlowRate;
				break;
			case IHPOperationMode::SCWHMatchWHMode:
				IHPCoilIndex = IntegratedHeatPumps(DXCoilNum).SCWHCoilIndex;
=======
			case SCWHMatchSCMode:
				WaterVolFlowRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex).WaterVolFlowRate;
				break;
			case SCWHMatchWHMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex;
>>>>>>> origin/ASIHPdev3
				if (1 == SpeedNum)  WaterVolFlowRate = VarSpeedCoil(IHPCoilIndex).MSRatedWaterVolFlowRate(SpeedNum);
				else WaterVolFlowRate = SpeedRatio * VarSpeedCoil(IHPCoilIndex).MSRatedWaterVolFlowRate(SpeedNum) +
					(1.0 - SpeedRatio) * VarSpeedCoil(IHPCoilIndex).MSRatedWaterVolFlowRate(SpeedNum - 1);
				break;
<<<<<<< HEAD
			case IHPOperationMode::SCDWHMode:
				WaterVolFlowRate = VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCDWHWHCoilIndex).WaterVolFlowRate;
				break;
			case IHPOperationMode::SHDWHElecHeatOffMode:
			case IHPOperationMode::SHDWHElecHeatOnMode:
				WaterVolFlowRate = VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SHDWHWHCoilIndex).WaterVolFlowRate;
=======
			case SCDWHMode:
				WaterVolFlowRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilIndex).WaterVolFlowRate;
				break;
			case SHDWHElecHeatOffMode:
			case SHDWHElecHeatOnMode:
				WaterVolFlowRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilIndex).WaterVolFlowRate;
>>>>>>> origin/ASIHPdev3
				break;
			default:
				WaterVolFlowRate = 0.0;
				break;
			}

			return(WaterVolFlowRate);
		}

		Real64
<<<<<<< HEAD
		GetAirMassFlowRateIHP(
			int const DXCoilNum,
			int const SpeedNum,
			Real64 const SpeedRatio,
			bool const IsCallbyWH //whether the call from the water heating loop or air loop, true = from water heating loop
		)
		{
			using VariableSpeedCoils::VarSpeedCoil;
=======
			GetAirMassFlowRateIHP(int const DXCoilNum, int const SpeedNum, Real64 const SpeedRatio,
			bool const IsCallbyWH //whether the call from the water heating loop or air loop, true = from water heating loop
			)
		{
			using VariableSpeedCoils::VarSpeedCoil;
			using General::TrimSigDigits;
>>>>>>> origin/ASIHPdev3

			int IHPCoilIndex(0);
			Real64 AirMassFlowRate(0.0);
			Real64 FlowScale(1.0);
<<<<<<< HEAD
			bool IsResultFlow(false); 
=======
			bool IsResultFlow(false); //IsResultFlow = true, the air flow rate will be from a simultaneous mode, won't be re-calculated
>>>>>>> origin/ASIHPdev3

			// Obtains and Allocates WatertoAirHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
<<<<<<< HEAD
				//    WaterIndex=FindGlycol('WATER') !Initialize the WaterIndex once
				GetCoilsInputFlag = false;
			}

			if (IntegratedHeatPumps(DXCoilNum).IHPCoilsSized == false) SizeIHP(DXCoilNum);

			FlowScale = 0.0;
			switch (IntegratedHeatPumps(DXCoilNum).CurMode)
			{
			case IHPOperationMode::IdleMode:
				IHPCoilIndex = IntegratedHeatPumps(DXCoilNum).SCCoilIndex;
				break;
			case IHPOperationMode::SCMode:
				IHPCoilIndex = IntegratedHeatPumps(DXCoilNum).SCCoilIndex;
				if (false == IsCallbyWH)
				{
					FlowScale = IntegratedHeatPumps(DXCoilNum).CoolVolFlowScale;
				}

				break;
			case IHPOperationMode::SHMode:
				IHPCoilIndex = IntegratedHeatPumps(DXCoilNum).SHCoilIndex;
				if (false == IsCallbyWH)
				{
					FlowScale = IntegratedHeatPumps(DXCoilNum).HeatVolFlowScale;
				}
				break;
			case IHPOperationMode::DWHMode:
				IHPCoilIndex = IntegratedHeatPumps(DXCoilNum).DWHCoilIndex;
				FlowScale = 1.0;
				break;
			case IHPOperationMode::SCWHMatchSCMode:
				IHPCoilIndex = IntegratedHeatPumps(DXCoilNum).SCWHCoilIndex;
				FlowScale = IntegratedHeatPumps(DXCoilNum).CoolVolFlowScale;
				if (true == IsCallbyWH)
				{
					IsResultFlow = true;
					AirMassFlowRate = VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCWHCoilIndex).AirMassFlowRate;
				}
				break;
			case IHPOperationMode::SCWHMatchWHMode:
				IHPCoilIndex = IntegratedHeatPumps(DXCoilNum).SCWHCoilIndex;
				FlowScale = IntegratedHeatPumps(DXCoilNum).CoolVolFlowScale;
				if (false == IsCallbyWH)
				{
					IsResultFlow = true;
					AirMassFlowRate = VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCWHCoilIndex).AirMassFlowRate;
				}
				break;
			case IHPOperationMode::SCDWHMode:
				IHPCoilIndex = IntegratedHeatPumps(DXCoilNum).SCDWHCoolCoilIndex;
				FlowScale = IntegratedHeatPumps(DXCoilNum).CoolVolFlowScale;
				if (true == IsCallbyWH)
				{
					IsResultFlow = true;
					AirMassFlowRate = VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SCDWHCoolCoilIndex).AirMassFlowRate;
				}
				break;
			case IHPOperationMode::SHDWHElecHeatOffMode:
			case IHPOperationMode::SHDWHElecHeatOnMode:
				IHPCoilIndex = IntegratedHeatPumps(DXCoilNum).SHDWHHeatCoilIndex;
				FlowScale = IntegratedHeatPumps(DXCoilNum).HeatVolFlowScale;
				if (true == IsCallbyWH)
				{
					IsResultFlow = true;
					AirMassFlowRate = VarSpeedCoil(IntegratedHeatPumps(DXCoilNum).SHDWHHeatCoilIndex).AirMassFlowRate;
				}
				break;
			default:
				IHPCoilIndex = IntegratedHeatPumps(DXCoilNum).SCCoilIndex;
				FlowScale = 1.0;
=======
				GetCoilsInputFlag = false;
			}

			if (DXCoilNum > NumIHPs || DXCoilNum < 1) {
				ShowFatalError("GetAirMassFlowRateIHP: Invalid CompIndex passed=" + TrimSigDigits(DXCoilNum) +
					", Number of Integrated HPs=" + TrimSigDigits(NumIHPs) + ", IHP name=" + "AS-IHP");
			}

			if (IntegratedHeatPumpUnits(DXCoilNum).IHPCoilsSized == false) SizeIHP(DXCoilNum);

			FlowScale = 0.0;
			switch (IntegratedHeatPumpUnits(DXCoilNum).CurMode)
			{
			case IdleMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex;
				break;
			case SCMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex;
				if (false == IsCallbyWH)
				{
					FlowScale = IntegratedHeatPumpUnits(DXCoilNum).CoolVolFlowScale;
				}
				break;
			case SHMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex;
				if (false == IsCallbyWH)
				{
					FlowScale = IntegratedHeatPumpUnits(DXCoilNum).HeatVolFlowScale;
				}
				break;
			case DWHMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex;
				FlowScale = 1.0;
				break;
			case SCWHMatchSCMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex;
				FlowScale = IntegratedHeatPumpUnits(DXCoilNum).CoolVolFlowScale;
				if (true == IsCallbyWH)
				{
					IsResultFlow = true;
					AirMassFlowRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex).AirMassFlowRate;
				}
				break;
			case SCWHMatchWHMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex;
				FlowScale = IntegratedHeatPumpUnits(DXCoilNum).CoolVolFlowScale;
				if (false == IsCallbyWH)
				{
					IsResultFlow = true;
					AirMassFlowRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex).AirMassFlowRate;
				}
				break;
			case SCDWHMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex;
				FlowScale = IntegratedHeatPumpUnits(DXCoilNum).CoolVolFlowScale;
				if (true == IsCallbyWH)
				{
					IsResultFlow = true;
					AirMassFlowRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex).AirMassFlowRate;
				}
				break;
			case SHDWHElecHeatOffMode:
			case SHDWHElecHeatOnMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilIndex;
				FlowScale = IntegratedHeatPumpUnits(DXCoilNum).HeatVolFlowScale;
				if (true == IsCallbyWH)
				{
					IsResultFlow = true;
					AirMassFlowRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilIndex).AirMassFlowRate;
				}
				break;
			default:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex;
				FlowScale = 0.0;
>>>>>>> origin/ASIHPdev3
				break;
			}


			if (false == IsResultFlow){
				if (1 == SpeedNum)  AirMassFlowRate = VarSpeedCoil(IHPCoilIndex).MSRatedAirMassFlowRate(SpeedNum);
				else AirMassFlowRate = SpeedRatio * VarSpeedCoil(IHPCoilIndex).MSRatedAirMassFlowRate(SpeedNum) +
					(1.0 - SpeedRatio) * VarSpeedCoil(IHPCoilIndex).MSRatedAirMassFlowRate(SpeedNum - 1);

				AirMassFlowRate = AirMassFlowRate * FlowScale;
			}
<<<<<<< HEAD
			
			if (AirMassFlowRate > IntegratedHeatPumps(DXCoilNum).MaxCoolAirMassFlow) AirMassFlowRate = IntegratedHeatPumps(DXCoilNum).MaxCoolAirMassFlow;
			if (AirMassFlowRate > IntegratedHeatPumps(DXCoilNum).MaxHeatAirMassFlow) AirMassFlowRate = IntegratedHeatPumps(DXCoilNum).MaxHeatAirMassFlow;

			return(AirMassFlowRate);
		}
		
		void
		ConnectIHP(
			int const WhichCoil // must match coil names for the coil type
		)
		{
			using VariableSpeedCoils::SetAirNodes;
			using VariableSpeedCoils::SetWaterNodes;

=======

			if (AirMassFlowRate > IntegratedHeatPumpUnits(DXCoilNum).MaxCoolAirMassFlow) AirMassFlowRate = IntegratedHeatPumpUnits(DXCoilNum).MaxCoolAirMassFlow;
			if (AirMassFlowRate > IntegratedHeatPumpUnits(DXCoilNum).MaxHeatAirMassFlow) AirMassFlowRate = IntegratedHeatPumpUnits(DXCoilNum).MaxHeatAirMassFlow;

			//set max air flow rate
			Node(IntegratedHeatPumpUnits(DXCoilNum).AirCoolInletNodeNum).MassFlowRateMax = AirMassFlowRate;
			Node(IntegratedHeatPumpUnits(DXCoilNum).AirHeatInletNodeNum).MassFlowRateMax = AirMassFlowRate;
			Node(IntegratedHeatPumpUnits(DXCoilNum).AirOutletNodeNum).MassFlowRateMax = AirMassFlowRate;

			return(AirMassFlowRate);
		}

		void
			ConnectIHP(
			int const WhichCoil // must match coil names for the coil type
			)
		{
			using VariableSpeedCoils::SetAirNodes;
			using VariableSpeedCoils::SetWaterNodes;
			using General::TrimSigDigits;
>>>>>>> origin/ASIHPdev3

			int DXCoilNum(0);
			int InNode(0);
			int OutNode(0);
			bool ErrorsFound(false);

			// Obtains and Allocates WatertoAirHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
<<<<<<< HEAD
				//    WaterIndex=FindGlycol('WATER') !Initialize the WaterIndex once
				GetCoilsInputFlag = false;
			}

			if (WhichCoil != 0) {

				//air node connections
				DXCoilNum = WhichCoil; 
				InNode = IntegratedHeatPumps(DXCoilNum).AirCoolInletNodeNum;
				OutNode = IntegratedHeatPumps(DXCoilNum).AirHeatInletNodeNum;
				SetAirNodes(IntegratedHeatPumps(DXCoilNum).SCCoilName, ErrorsFound, InNode, OutNode);
				SetAirNodes(IntegratedHeatPumps(DXCoilNum).SCWHCoilName, ErrorsFound, InNode, OutNode);
				SetAirNodes(IntegratedHeatPumps(DXCoilNum).SCDWHCoolCoilName, ErrorsFound, InNode, OutNode);
				SetAirNodes(IntegratedHeatPumps(DXCoilNum).SCDWHWHCoilName, ErrorsFound, InNode, OutNode);

				InNode = IntegratedHeatPumps(DXCoilNum).AirHeatInletNodeNum;
				OutNode = IntegratedHeatPumps(DXCoilNum).AirOutletNodeNum;
				SetAirNodes(IntegratedHeatPumps(DXCoilNum).SHCoilName, ErrorsFound, InNode, OutNode);
				SetAirNodes(IntegratedHeatPumps(DXCoilNum).SHDWHHeatCoilName, ErrorsFound, InNode, OutNode);

				//SetAirNodes(IntegratedHeatPumps(DXCoilNum).SHDWHWHCoilName, ErrorsFound, InNode, OutNode);//SHDWHWHCoil has outdoor air nodes

				//water node connections
				InNode = IntegratedHeatPumps(DXCoilNum).WaterInletNodeNum;
				OutNode = IntegratedHeatPumps(DXCoilNum).WaterOutletNodeNum;
				SetWaterNodes(IntegratedHeatPumps(DXCoilNum).SCWHCoilName, ErrorsFound, InNode, OutNode);
				SetWaterNodes(IntegratedHeatPumps(DXCoilNum).SCDWHCoolCoilName, ErrorsFound, InNode, OutNode);
				SetWaterNodes(IntegratedHeatPumps(DXCoilNum).SCDWHWHCoilName, ErrorsFound, InNode, OutNode);
				SetWaterNodes(IntegratedHeatPumps(DXCoilNum).SHDWHHeatCoilName, ErrorsFound, InNode, OutNode);
				SetWaterNodes(IntegratedHeatPumps(DXCoilNum).SHDWHWHCoilName, ErrorsFound, InNode, OutNode);
				SetWaterNodes(IntegratedHeatPumps(DXCoilNum).DWHCoilName, ErrorsFound, InNode, OutNode);
				IntegratedHeatPumps(DXCoilNum).NodeConnected = true;								
=======
				GetCoilsInputFlag = false;
			}

			if (DXCoilNum > NumIHPs || DXCoilNum < 1) {
				ShowFatalError("ConnectIHP: Invalid CompIndex passed=" + TrimSigDigits(DXCoilNum) +
					", Number of Integrated HPs=" + TrimSigDigits(NumIHPs) + ", IHP name=" + "AS-IHP");
			}

			if (WhichCoil != 0) {
				//air node connections
				InNode = IntegratedHeatPumpUnits(DXCoilNum).AirCoolInletNodeNum;
				OutNode = IntegratedHeatPumpUnits(DXCoilNum).AirHeatInletNodeNum;
				//all the SC air coils have indoor air nodes for cooling
				SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SCCoilName, ErrorsFound, InNode, OutNode);
				SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilName, ErrorsFound, InNode, OutNode);
				SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilName, ErrorsFound, InNode, OutNode);

				InNode = IntegratedHeatPumpUnits(DXCoilNum).AirHeatInletNodeNum;
				OutNode = IntegratedHeatPumpUnits(DXCoilNum).AirOutletNodeNum;
				//all the SH air coils have indoor air nodes for heating
				SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SHCoilName, ErrorsFound, InNode, OutNode);
				SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilName, ErrorsFound, InNode, OutNode);

				//water node connections
				InNode = IntegratedHeatPumpUnits(DXCoilNum).WaterInletNodeNum;
				OutNode = IntegratedHeatPumpUnits(DXCoilNum).WaterOutletNodeNum;
				//all the water coils have the same water side node connnections
				SetWaterNodes(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilName, ErrorsFound, InNode, OutNode);
				SetWaterNodes(IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilName, ErrorsFound, InNode, OutNode);
				SetWaterNodes(IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilName, ErrorsFound, InNode, OutNode);
				SetWaterNodes(IntegratedHeatPumpUnits(DXCoilNum).DWHCoilName, ErrorsFound, InNode, OutNode);

				//outdoor air node connections
				//DWH, SCDWH, SHDWH coils have the same outdoor air nodes
				InNode = IntegratedHeatPumpUnits(DXCoilNum).ODAirInletNodeNum;
				OutNode = IntegratedHeatPumpUnits(DXCoilNum).ODAirOutletNodeNum;
				SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).DWHCoilName, ErrorsFound, InNode, OutNode);//SCDWHCoil has outdoor air nodes
				SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilName, ErrorsFound, InNode, OutNode);//SCDWHCoil has outdoor air nodes
				SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilName, ErrorsFound, InNode, OutNode);//SHDWHWHCoil has outdoor air nodes

				IntegratedHeatPumpUnits(DXCoilNum).NodeConnected = true;
>>>>>>> origin/ASIHPdev3
			}

		}

		void
<<<<<<< HEAD
		DisconnectIHP(
			int const WhichCoil // must match coil names for the coil type
		)
		{
			using VariableSpeedCoils::SetAirNodes;
			using VariableSpeedCoils::SetWaterNodes;

=======
			DisconnectIHP(
			int const WhichCoil // must match coil names for the coil type
			)
		{
			using VariableSpeedCoils::SetAirNodes;
			using VariableSpeedCoils::SetWaterNodes;
			using General::TrimSigDigits;
>>>>>>> origin/ASIHPdev3

			int DXCoilNum(0);
			int InNode(0);
			int OutNode(0);
			bool ErrorsFound(false);

			// Obtains and Allocates WatertoAirHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
<<<<<<< HEAD
				//    WaterIndex=FindGlycol('WATER') !Initialize the WaterIndex once
				GetCoilsInputFlag = false;
			}

			if (WhichCoil != 0) {

				//air node connections
				DXCoilNum = WhichCoil;
				InNode = 0;
				OutNode = 0;
				//SetAirNodes(IntegratedHeatPumps(DXCoilNum).SCCoilName, ErrorsFound, InNode, OutNode);
				SetAirNodes(IntegratedHeatPumps(DXCoilNum).SCWHCoilName, ErrorsFound, InNode, OutNode);
				SetAirNodes(IntegratedHeatPumps(DXCoilNum).SCDWHCoolCoilName, ErrorsFound, InNode, OutNode);
				SetAirNodes(IntegratedHeatPumps(DXCoilNum).SCDWHWHCoilName, ErrorsFound, InNode, OutNode);

				InNode = 0;
				OutNode = 0;
				//SetAirNodes(IntegratedHeatPumps(DXCoilNum).SHCoilName, ErrorsFound, InNode, OutNode);
				SetAirNodes(IntegratedHeatPumps(DXCoilNum).SHDWHHeatCoilName, ErrorsFound, InNode, OutNode);
=======
				GetCoilsInputFlag = false;
			}

			if (DXCoilNum > NumIHPs || DXCoilNum < 1) {
				ShowFatalError("DisconnectIHP: Invalid CompIndex passed=" + TrimSigDigits(DXCoilNum) +
					", Number of Integrated HPs=" + TrimSigDigits(NumIHPs) + ", IHP name=" + "AS-IHP");
			}

			if (WhichCoil != 0) {

				//air node connections
				InNode = 0;
				OutNode = 0;
				//all the SC air coils have indoor air nodes for cooling
				SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SCCoilName, ErrorsFound, InNode, OutNode);
				SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilName, ErrorsFound, InNode, OutNode);
				SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilName, ErrorsFound, InNode, OutNode);

				InNode = 0;
				OutNode = 0;
				//all the SH air coils have indoor air nodes for heating
				SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SHCoilName, ErrorsFound, InNode, OutNode);
				SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilName, ErrorsFound, InNode, OutNode);
>>>>>>> origin/ASIHPdev3

				//water node connections
				InNode = 0;
				OutNode = 0;
<<<<<<< HEAD
				SetWaterNodes(IntegratedHeatPumps(DXCoilNum).SCWHCoilName, ErrorsFound, InNode, OutNode);
				//SetWaterNodes(IntegratedHeatPumps(DXCoilNum).DWHCoilName, ErrorsFound, InNode, OutNode);
				IntegratedHeatPumps(DXCoilNum).NodeConnected = false;
=======
				//all the water coils have the same water side node connnections
				SetWaterNodes(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilName, ErrorsFound, InNode, OutNode);
				SetWaterNodes(IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilName, ErrorsFound, InNode, OutNode);
				SetWaterNodes(IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilName, ErrorsFound, InNode, OutNode);
				SetWaterNodes(IntegratedHeatPumpUnits(DXCoilNum).DWHCoilName, ErrorsFound, InNode, OutNode);

				//outdoor air node connections
				//DWH, SCDWH, SHDWH coils have the same outdoor air nodes
				InNode = 0;
				OutNode = 0;
				SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).DWHCoilName, ErrorsFound, InNode, OutNode);//SCDWHCoil has outdoor air nodes
				SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilName, ErrorsFound, InNode, OutNode);//SCDWHCoil has outdoor air nodes
				SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilName, ErrorsFound, InNode, OutNode);//SHDWHWHCoil has outdoor air nodes

				IntegratedHeatPumpUnits(DXCoilNum).NodeConnected = false;
>>>>>>> origin/ASIHPdev3
			}


		}

<<<<<<< HEAD
	} // IntegratedHeatPump

} // EnergyPlus
=======
		//     NOTICE

		//     Copyright (c) 1996-2015 The Board of Trustees of the University of Illinois
		//     and The Regents of the University of California through Ernest Orlando Lawrence
		//     Berkeley National Laboratory.  All rights reserved.

		//     Portions of the EnergyPlus software package have been developed and copyrighted
		//     by other individuals, companies and institutions.  These portions have been
		//     incorporated into the EnergyPlus software package under license.   For a complete
		//     list of contributors, see "Notice" located in main.cc.

		//     NOTICE: The U.S. Government is granted for itself and others acting on its
		//     behalf a paid-up, nonexclusive, irrevocable, worldwide license in this data to
		//     reproduce, prepare derivative works, and perform publicly and display publicly.
		//     Beginning five (5) years after permission to assert copyright is granted,
		//     subject to two possible five year renewals, the U.S. Government is granted for
		//     itself and others acting on its behalf a paid-up, non-exclusive, irrevocable
		//     worldwide license in this data to reproduce, prepare derivative works,
		//     distribute copies to the public, perform publicly and display publicly, and to
		//     permit others to do so.

		//     TRADEMARKS: EnergyPlus is a trademark of the US Department of Energy.

	} // IntegratedHeatPumps

} // EnergyPlus
>>>>>>> origin/ASIHPdev3
