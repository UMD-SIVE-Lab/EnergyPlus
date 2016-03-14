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
#include <cmath>

// ObjexxFCL Headers
#include <ObjexxFCL/Array.functions.hh>
#include <ObjexxFCL/Fmath.hh>

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

	namespace IntegratedHeatPumps {

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
		int NumIHPs(0); // The Number of Water to Air Heat Pumps found in the Input
		bool GetCoilsInputFlag(true); 

		// SUBROUTINE SPECIFICATIONS FOR MODULE

		// Driver/Manager Routines

		// Get Input routines for module

		// Initialization routines for module

		// Update routines to check convergence and update nodes

		// Update routine

		// Utility routines
		//SHR, bypass factor routines

		// Object Data
		Array1D<IntegratedHeatPumpData> IntegratedHeatPumpUnits;

		// MODULE SUBROUTINES:
		//*************************************************************************

		// Functions
		void
		clear_state()
		{
			IntegratedHeatPumpUnits.deallocate();
		}


		void
		SimIHP(
			std::string const & CompName, // Coil Name
			int & CompIndex, // Index for Component name
			int const CyclingScheme, // Continuous fan OR cycling compressor
			Real64 & MaxONOFFCyclesperHour, // Maximum cycling rate of heat pump [cycles/hr]
			Real64 & HPTimeConstant, // Heat pump time constant [s]
			Real64 & FanDelayTime, // Fan delay time, time delay for the HP's fan to
			int const CompOp, // compressor on/off. 0 = off; 1= on
			Real64 const PartLoadFrac,
			int const SpeedNum, // compressor speed number
			Real64 const SpeedRatio, // compressor speed ratio
			Real64 const SensLoad, // Sensible demand load [W]
			Real64 const LatentLoad, // Latent demand load [W]
			bool const IsCallbyWH, //whether the call from the water heating loop or air loop, true = from water heating loop
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

			// METHODOLOGY EMPLOYED:

			// REFERENCES:
			// N/A

			// Using/Aliasing
			using InputProcessor::FindItemInList;
			using General::TrimSigDigits;
			using VariableSpeedCoils::SimVariableSpeedCoils;
			using VariableSpeedCoils::VarSpeedCoil;
			using VariableSpeedCoils::UpdateVarSpeedCoil; 

			// Locals
			// SUBROUTINE ARGUMENT DEFINITIONS:

			// shut off after compressor cycle off  [s]
			// part-load ratio = load/total capacity, passed in by the parent object

			// SUBROUTINE PARAMETER DEFINITIONS:
			// na

			// INTERFACE BLOCK SPECIFICATIONS
			// na

			// DERIVED TYPE DEFINITIONS
			// na

			
			// SUBROUTINE LOCAL VARIABLE DECLARATIONS:
			int DXCoilNum(0); // The WatertoAirHP that you are currently loading input into
			// int LocNum(0); 
			// bool ErrorFound(false); 
			// Real64 MyLoad(0.0);
			// Real64 MaxCap(0.0);
			// Real64 MinCap(0.0);
			// Real64 OptCap(0.0);

			// Obtains and Allocates WatertoAirHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
				//    WaterIndex=FindGlycol('WATER') !Initialize the WaterIndex once
				GetCoilsInputFlag = false;
			}

			if (CompIndex == 0) {
				DXCoilNum = FindItemInList(CompName, IntegratedHeatPumpUnits);
				if (DXCoilNum == 0) {
					ShowFatalError("Integrated Heat Pump not found=" + CompName);
				}
				CompIndex = DXCoilNum;
			}
			else {
				DXCoilNum = CompIndex;
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

			switch (IntegratedHeatPumpUnits(DXCoilNum).CurMode)
			{
			case IHPOperationMode::IdleMode:
				VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex).SimFlag = false; 
				UpdateVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex);
				VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex).SimFlag = false;
				UpdateVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex);
				break; 
			case IHPOperationMode::SCMode:
				VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex).SimFlag = true;
				if (false == IsCallbyWH)
				{
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
						SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);
				}
				else
				{
					UpdateVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex);
				}
				break; 
			case IHPOperationMode::SHMode:
				VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex).SimFlag = true;
				if (false == IsCallbyWH)
				{
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
						SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);
				}
				else
				{
					UpdateVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex);
				}
				break; 
			case IHPOperationMode::DWHMode:
				VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex).SimFlag = true;
				if (true == IsCallbyWH)
				{
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
						SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);
					IntegratedHeatPumpUnits(DXCoilNum).TotalHeatingEnergyRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex).TotalHeatingEnergyRate;
				}
				break; 
			case IHPOperationMode::SCWHMatchSCMode:
				VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex).SimFlag = true;
				if (false == IsCallbyWH)
				{
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
						SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);
					IntegratedHeatPumpUnits(DXCoilNum).TotalHeatingEnergyRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex).TotalHeatingEnergyRate;
				}
				else
				{
					UpdateVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex);
				}

				break; 
			case IHPOperationMode::SCWHMatchWHMode:
				VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex).SimFlag = true;
				if (true == IsCallbyWH)
				{
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex,
					CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
					SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);
					IntegratedHeatPumpUnits(DXCoilNum).TotalHeatingEnergyRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex).TotalHeatingEnergyRate;			
				}
				else
				{
					UpdateVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex);
				}

				break; 
			case IHPOperationMode::SCDWHMode:
				VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex).SimFlag = true;
				VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilIndex).SimFlag = true;
				if (false == IsCallbyWH)
				{
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
						SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);
					IntegratedHeatPumpUnits(DXCoilNum).TotalHeatingEnergyRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilIndex).TotalHeatingEnergyRate;

					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
						SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);
				}
				else
				{
					UpdateVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilIndex);
					UpdateVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex);
				}

				break; 
			case IHPOperationMode::SHDWHElecHeatOffMode:
			case IHPOperationMode::SHDWHElecHeatOnMode:
				VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilIndex).SimFlag = true;
				VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilIndex).SimFlag = true;
				if (false == IsCallbyWH)
				{
					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
						SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);
					IntegratedHeatPumpUnits(DXCoilNum).TotalHeatingEnergyRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilIndex).TotalHeatingEnergyRate;

					SimVariableSpeedCoils(BlankString, IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilIndex,
						CyclingScheme, MaxONOFFCyclesperHour, HPTimeConstant, FanDelayTime, CompOp, PartLoadFrac,
						SpeedNum, SpeedRatio, SensLoad, LatentLoad, OnOffAirFlowRat);
				}
				else
				{
					UpdateVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilIndex);
					UpdateVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilIndex);
				}

				break; 
			default:
				VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex).SimFlag = false;
				UpdateVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex);
				VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex).SimFlag = false;
				UpdateVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex);
				break; 
			}
		}



		void
		GetIHPInput()
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
			// int IHPNum; // The Water to Air HP that you are currently loading input into
			int NumASIHPs; // Counter for air-source integrated heat pumps

			int NumAlphas; // Number of variables in String format
			int NumNums; // Number of variables in Numeric format
			int NumParams; // Total number of input fields
			static int MaxNums(0); // Maximum number of numeric input fields
			static int MaxAlphas(0); // Maximum number of alpha input fields
			std::string CoilName; // Name of the  Coil
			std::string Coiltype; // type of coil

			std::string CurrentModuleObject; // for ease in getting objects
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
			int InNode(0);
			int OutNode(0);


			NumASIHPs = GetNumObjectsFound("COILSYSTEM:INTEGRATEDHEATPUMP:AIRSOURCE");
			NumIHPs = NumASIHPs;

			DXCoilNum = 0;

			if (NumIHPs <= 0) {
				ShowSevereError("No Equipment found in Integrated Heat Pumps");
				ErrorsFound = true;
			}

			// Allocate Arrays
			if (NumIHPs > 0) {
				IntegratedHeatPumpUnits.allocate(NumIHPs);
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

			for (CoilCounter = 1; CoilCounter <= NumASIHPs; ++CoilCounter) {

				++DXCoilNum;
				AlfaFieldIncre = 1;

				GetObjectItem(CurrentModuleObject, CoilCounter, AlphArray, NumAlphas, NumArray, NumNums, IOStat, lNumericBlanks, lAlphaBlanks, cAlphaFields, cNumericFields);

				IsNotOK = false;
				IsBlank = false;

				VerifyName(AlphArray(1), IntegratedHeatPumpUnits, DXCoilNum - 1, IsNotOK, IsBlank, CurrentModuleObject + " Name");
				if (IsNotOK) {
					ErrorsFound = true;
					if (IsBlank) AlphArray(1) = "xxxxx";
				}
				VerifyUniqueCoilName(CurrentModuleObject, AlphArray(1), errFlag, CurrentModuleObject + " Name");
				if (errFlag) {
					ErrorsFound = true;
				}

				IntegratedHeatPumpUnits(DXCoilNum).NodeConnected = false;
				IntegratedHeatPumpUnits(DXCoilNum).Name = AlphArray(1);
				IntegratedHeatPumpUnits(DXCoilNum).IHPtype = "AIRSOURCE_IHP";

				IntegratedHeatPumpUnits(DXCoilNum).AirInletNodeNum = 
					GetOnlySingleNode(AlphArray(2), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Air, NodeConnectionType_Inlet, 1, ObjectIsNotParent);
				IntegratedHeatPumpUnits(DXCoilNum).AirOutletNodeNum = 
					GetOnlySingleNode(AlphArray(3), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Air, NodeConnectionType_Outlet, 1, ObjectIsNotParent);
				IntegratedHeatPumpUnits(DXCoilNum).WaterInletNodeNum = 
					GetOnlySingleNode(AlphArray(4), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Water, NodeConnectionType_Inlet, 2, ObjectIsNotParent);
				IntegratedHeatPumpUnits(DXCoilNum).WaterOutletNodeNum = 
					GetOnlySingleNode(AlphArray(5), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Water, NodeConnectionType_Outlet, 2, ObjectIsNotParent);
				IntegratedHeatPumpUnits(DXCoilNum).WaterTankoutNod =
					GetOnlySingleNode(AlphArray(6), ErrorsFound, CurrentModuleObject, AlphArray(1), NodeType_Water, NodeConnectionType_Outlet, 2, ObjectIsNotParent);

				TestCompSet(CurrentModuleObject, AlphArray(1), AlphArray(2), AlphArray(3), "Air Nodes");
				TestCompSet(CurrentModuleObject, AlphArray(1), AlphArray(4), AlphArray(5), "Water Nodes");
				
				IntegratedHeatPumpUnits(DXCoilNum).SCCoilType = "COIL:COOLING:DX:VARIABLESPEED";
				IntegratedHeatPumpUnits(DXCoilNum).SCCoilName = AlphArray(7);
				Coiltype = IntegratedHeatPumpUnits(DXCoilNum).SCCoilType;
				CoilName = IntegratedHeatPumpUnits(DXCoilNum).SCCoilName;

				ValidateComponent(Coiltype, CoilName, IsNotOK, CurrentModuleObject);
				if (IsNotOK) {
					ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
					ErrorsFound = true;
				}
				else {
					errFlag = false;
					IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex = GetCoilIndexVariableSpeed(Coiltype, CoilName, errFlag);
					if (errFlag) {
						ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
						ErrorsFound = true;
					}
				}
				
				IntegratedHeatPumpUnits(DXCoilNum).SHCoilType = "COIL:HEATING:DX:VARIABLESPEED";
				IntegratedHeatPumpUnits(DXCoilNum).SHCoilName = AlphArray(8);
				Coiltype = IntegratedHeatPumpUnits(DXCoilNum).SHCoilType;
				CoilName = IntegratedHeatPumpUnits(DXCoilNum).SHCoilName;

				ValidateComponent(Coiltype, CoilName, IsNotOK, CurrentModuleObject);
				if (IsNotOK) {
					ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
					ErrorsFound = true;
				}
				else {
					errFlag = false;
					IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex = GetCoilIndexVariableSpeed(Coiltype, CoilName, errFlag);
					if (errFlag) {
						ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
						ErrorsFound = true;
					}
				}
							
				IntegratedHeatPumpUnits(DXCoilNum).DWHCoilType = "COIL:WATERHEATING:AIRTOWATERHEATPUMP:VARIABLESPEED";
				IntegratedHeatPumpUnits(DXCoilNum).DWHCoilName = AlphArray(9);
				Coiltype = IntegratedHeatPumpUnits(DXCoilNum).DWHCoilType;
				CoilName = IntegratedHeatPumpUnits(DXCoilNum).DWHCoilName;

				ValidateComponent(Coiltype, CoilName, IsNotOK, CurrentModuleObject);
				if (IsNotOK) {
					ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
					ErrorsFound = true;
				}
				else {
					errFlag = false;
					IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex = GetCoilIndexVariableSpeed(Coiltype, CoilName, errFlag);
					if (errFlag) {
						ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
						ErrorsFound = true;
					}
				}
				
				IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilType = "COIL:WATERHEATING:AIRTOWATERHEATPUMP:VARIABLESPEED";
				IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilName = AlphArray(10);
				Coiltype = IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilType;
				CoilName = IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilName;

				ValidateComponent(Coiltype, CoilName, IsNotOK, CurrentModuleObject);
				if (IsNotOK) {
					ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
					ErrorsFound = true;
				}
				else {
					errFlag = false;
					IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex = GetCoilIndexVariableSpeed(Coiltype, CoilName, errFlag);
					if (errFlag) {
						ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
						ErrorsFound = true;
					}
				}

				IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilType = "COIL:COOLING:DX:VARIABLESPEED";
				IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilName = AlphArray(11);
				Coiltype = IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilType;
				CoilName = IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilName;

				ValidateComponent(Coiltype, CoilName, IsNotOK, CurrentModuleObject);
				if (IsNotOK) {
					ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
					ErrorsFound = true;
				}
				else {
					errFlag = false;
					IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex = GetCoilIndexVariableSpeed(Coiltype, CoilName, errFlag);
					if (errFlag) {
						ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
						ErrorsFound = true;
					}
				}


				IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilType = "COIL:WATERHEATING:AIRTOWATERHEATPUMP:VARIABLESPEED";
				IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilName = AlphArray(12);
				Coiltype = IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilType;
				CoilName = IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilName;

				ValidateComponent(Coiltype, CoilName, IsNotOK, CurrentModuleObject);
				if (IsNotOK) {
					ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
					ErrorsFound = true;
				}
				else {
					errFlag = false;
					IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilIndex = GetCoilIndexVariableSpeed(Coiltype, CoilName, errFlag);
					if (errFlag) {
						ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
						ErrorsFound = true;
					}
				}
								
				IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilType = "COIL:HEATING:DX:VARIABLESPEED";
				IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilName = AlphArray(13);
				Coiltype = IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilType;
				CoilName = IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilName;

				ValidateComponent(Coiltype, CoilName, IsNotOK, CurrentModuleObject);
				if (IsNotOK) {
					ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
					ErrorsFound = true;
				}
				else {
					errFlag = false;
					IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilIndex = GetCoilIndexVariableSpeed(Coiltype, CoilName, errFlag);
					if (errFlag) {
						ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
						ErrorsFound = true;
					}
				}
				
				IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilType = "COIL:WATERHEATING:AIRTOWATERHEATPUMP:VARIABLESPEED";
				IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilName = AlphArray(14);
				Coiltype = IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilType;
				CoilName = IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilName;

				ValidateComponent(Coiltype, CoilName, IsNotOK, CurrentModuleObject);
				if (IsNotOK) {
					ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
					ErrorsFound = true;
				}
				else {
					errFlag = false;
					IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilIndex = GetCoilIndexVariableSpeed(Coiltype, CoilName, errFlag);
					if (errFlag) {
						ShowContinueError("...specified in " + CurrentModuleObject + "=\"" + AlphArray(1) + "\".");
						ErrorsFound = true;
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
					InNode = IntegratedHeatPumpUnits(DXCoilNum).AirInletNodeNum;
					OutNode = IntegratedHeatPumpUnits(DXCoilNum).AirOutletNodeNum;
					SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SCCoilName, ErrorsFound, InNode, OutNode);
					SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SHCoilName, ErrorsFound, InNode, OutNode);
					SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilName, ErrorsFound, InNode, OutNode);
					SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilName, ErrorsFound, InNode, OutNode);
					SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilName, ErrorsFound, InNode, OutNode);
					SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilName, ErrorsFound, InNode, OutNode);
					//SetAirNodes(IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilName, ErrorsFound, InNode, OutNode);//SHDWHWHCoil has outdoor air nodes

					//water node connections
					InNode = IntegratedHeatPumpUnits(DXCoilNum).WaterInletNodeNum;
					OutNode = IntegratedHeatPumpUnits(DXCoilNum).WaterOutletNodeNum;
					SetWaterNodes(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilName, ErrorsFound, InNode, OutNode);
					SetWaterNodes(IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilName, ErrorsFound, InNode, OutNode);
					SetWaterNodes(IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilName, ErrorsFound, InNode, OutNode);
					SetWaterNodes(IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilName, ErrorsFound, InNode, OutNode);
					SetWaterNodes(IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilName, ErrorsFound, InNode, OutNode);
					SetWaterNodes(IntegratedHeatPumpUnits(DXCoilNum).DWHCoilName, ErrorsFound, InNode, OutNode);
					IntegratedHeatPumpUnits(DXCoilNum).NodeConnected = true;
				};


				IntegratedHeatPumpUnits(DXCoilNum).IHPCoilsSized = false; 
				IntegratedHeatPumpUnits(DXCoilNum).CoolVolFlowScale = 1.0; 
				IntegratedHeatPumpUnits(DXCoilNum).HeatVolFlowScale = 1.0;
				IntegratedHeatPumpUnits(DXCoilNum).CurMode = IHPOperationMode::IdleMode; 
				IntegratedHeatPumpUnits(DXCoilNum).MaxHeatAirMassFlow = 1e10;
				IntegratedHeatPumpUnits(DXCoilNum).MaxHeatAirVolFlow = 1e10;
				IntegratedHeatPumpUnits(DXCoilNum).MaxCoolAirMassFlow = 1e10; 
				IntegratedHeatPumpUnits(DXCoilNum).MaxCoolAirVolFlow = 1e10; 
			}


			if (ErrorsFound) {
				ShowFatalError(RoutineName + "Errors found in getting " + CurrentModuleObject + " input.  Preceding condition(s) causes termination.");
			}


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

			SetVarSpeedCoilData(IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex, ErrorsFound, _, IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex);
			if (ErrorsFound) {
				ShowSevereError("SizeIHP: Could not match cooling coil\"" + IntegratedHeatPumpUnits(DXCoilNum).SCCoilName + 
					"\" with heating coil=\"" + IntegratedHeatPumpUnits(DXCoilNum).SHCoilName + "\"");
				ErrorsFound = false; 
			};
		
			SizeVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex);//size cooling coil
			if (ErrorsFound) {
				ShowFatalError("SizeIHP: failed to size SC coil\"" + IntegratedHeatPumpUnits(DXCoilNum).SCCoilName + "\"");
				ErrorsFound = false;
			}
			else
			{
				RatedCapacity = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex).RatedCapCoolTotal; 
			};

			SizeVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex);//size cooling coil
			if (ErrorsFound) {
				ShowSevereError("SizeIHP: failed to size SH coil\"" + IntegratedHeatPumpUnits(DXCoilNum).SHCoilName + "\"");
				ErrorsFound = false;
			};

			if (VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex).RatedCapCoolTotal == AutoSize)
			{
				VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex).RatedCapCoolTotal = RatedCapacity;
			};

			SetVarSpeedCoilData(IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex, ErrorsFound, _, IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilIndex);

			SizeVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex);

			if (ErrorsFound) {
				ShowSevereError("SizeIHP: failed to size SCDWH cooling coil\"" + IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilName + "\"");
				ErrorsFound = false;
			};

			SizeVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilIndex);
			if (ErrorsFound) {
				ShowSevereError("SizeIHP: failed to size SHDWH heating coil\"" + IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilName + "\"");
				ErrorsFound = false;
			};


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

			if (VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex).RatedCapWH == AutoSize)
			{
				VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex).RatedCapWH = RatedCapacity ;
			}

			SizeVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex);
			if (ErrorsFound) {
				ShowSevereError("SizeIHP: failed to size DWH coil\"" + IntegratedHeatPumpUnits(DXCoilNum).DWHCoilName + "\"");
				ErrorsFound = false;
			};

			if (VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilIndex).RatedCapWH == AutoSize)
			{
				VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilIndex).RatedCapWH = RatedCapacity * 0.13;
			}

			SizeVarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilIndex);
			if (ErrorsFound) {
				ShowSevereError("SizeIHP: failed to size SCDWH water heating coil\"" + IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilName + "\"");
				ErrorsFound = false;
			};


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
		UpdateIHP(int const EP_UNUSED( DXCoilNum ) )
		{
		

		}


		void
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
			using DataHVACGlobals::SmallLoad;
			using DataEnvironment::OutDryBulbTemp;
			using WaterThermalTanks::SimWaterThermalTank;
			using WaterThermalTanks::GetWaterThermalTankInput;
			using DataHVACGlobals::TimeStepSys;
			//using WaterThermalTanks::

			Real64 MyLoad(0.0);
			Real64 MaxCap(0.0); 
			Real64 MinCap(0.0);
			Real64 OptCap(0.0);
			Real64 WHHeatTimeSav(0.0);//time accumulation for water heating
			Real64 WHHeatVolSave(0.0);//volume accumulation for water heating

			// Obtains and Allocates WatertoAirHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
				//    WaterIndex=FindGlycol('WATER') !Initialize the WaterIndex once
				GetCoilsInputFlag = false;
			}

			if (IntegratedHeatPumpUnits(DXCoilNum).IHPCoilsSized == false) SizeIHP(DXCoilNum);
						
			//decide working mode at the first moment
			//check if there is a water heating call
			IntegratedHeatPumpUnits(DXCoilNum).IsWHCallAvail = false; 
			IntegratedHeatPumpUnits(DXCoilNum).CheckWHCall = true; 
			if (0 == IntegratedHeatPumpUnits(DXCoilNum).WHtankID)//not initialized yet
			{
				IntegratedHeatPumpUnits(DXCoilNum).IsWHCallAvail = false;
			}
			else
			{
				SimWaterThermalTank(
					IntegratedHeatPumpUnits(DXCoilNum).WHtankType, IntegratedHeatPumpUnits(DXCoilNum).WHtankName,
					IntegratedHeatPumpUnits(DXCoilNum).WHtankID,
					false, false,
					MyLoad, MaxCap, MinCap, OptCap, true // TRUE if First iteration of simulation
					);
			}

			IntegratedHeatPumpUnits(DXCoilNum).CheckWHCall = false;

			WHHeatTimeSav = IntegratedHeatPumpUnits(DXCoilNum).SHDWHRunTime; 
			WHHeatVolSave = IntegratedHeatPumpUnits(DXCoilNum).WaterFlowAccumVol; 

			//clear the accumulation amount
			IntegratedHeatPumpUnits(DXCoilNum).SHDWHRunTime = 0.0;
			IntegratedHeatPumpUnits(DXCoilNum).WaterFlowAccumVol = 0.0;

			if (false == IntegratedHeatPumpUnits(DXCoilNum).IsWHCallAvail)//no water heating call
			{
				if ((SensLoad < (-1.0 * SmallLoad)) || (LatentLoad < (-1.0 * SmallLoad)))
				{
					IntegratedHeatPumpUnits(DXCoilNum).CurMode = IHPOperationMode::SCMode;
				}
				else if (SensLoad > SmallLoad)
				{
					if ((IntegratedHeatPumpUnits(DXCoilNum).ControlledZoneTemp > IntegratedHeatPumpUnits(DXCoilNum).TindoorOverCoolAllow) &&
						(OutDryBulbTemp > IntegratedHeatPumpUnits(DXCoilNum).TambientOverCoolAllow))//used for cooling season
						IntegratedHeatPumpUnits(DXCoilNum).CurMode = IHPOperationMode::IdleMode;
					else
						IntegratedHeatPumpUnits(DXCoilNum).CurMode = IHPOperationMode::SHMode;
				}
				else
				{
					IntegratedHeatPumpUnits(DXCoilNum).CurMode = IHPOperationMode::IdleMode;
				}
			}
			//below has water heating calls
			else if ((SensLoad < (-1.0 * SmallLoad)) || (LatentLoad < (-1.0 * SmallLoad)))//simultaneous SC and WH calls
			{
				if (WHHeatVolSave < IntegratedHeatPumpUnits(DXCoilNum).WaterVolSCDWH)
				{
					IntegratedHeatPumpUnits(DXCoilNum).CurMode = IHPOperationMode::SCDWHMode;
					IntegratedHeatPumpUnits(DXCoilNum).WaterFlowAccumVol = WHHeatVolSave + 
						Node(IntegratedHeatPumpUnits(DXCoilNum).WaterTankoutNod).MassFlowRate/1000.0 * TimeStepSys * SecInHour;//1000.0 converted to volumetric flow rate
				}
				else
				{
					if (1 == IntegratedHeatPumpUnits(DXCoilNum).ModeMatchSCWH) IntegratedHeatPumpUnits(DXCoilNum).CurMode = IHPOperationMode::SCWHMatchWHMode;
					else IntegratedHeatPumpUnits(DXCoilNum).CurMode = IHPOperationMode::SCWHMatchSCMode;
				};

			}
			else if ((IntegratedHeatPumpUnits(DXCoilNum).ControlledZoneTemp > IntegratedHeatPumpUnits(DXCoilNum).TindoorOverCoolAllow) &&
				(OutDryBulbTemp > IntegratedHeatPumpUnits(DXCoilNum).TambientOverCoolAllow))
			{
				IntegratedHeatPumpUnits(DXCoilNum).CurMode = IHPOperationMode::SCWHMatchWHMode;
			}
			else if ((IntegratedHeatPumpUnits(DXCoilNum).ControlledZoneTemp > IntegratedHeatPumpUnits(DXCoilNum).TindoorWHHighPriority) &&
				(OutDryBulbTemp > IntegratedHeatPumpUnits(DXCoilNum).TambientWHHighPriority))
			{
				IntegratedHeatPumpUnits(DXCoilNum).CurMode = IHPOperationMode::DWHMode;
			}
			else if (SensLoad > SmallLoad)
			{
				if (WHHeatTimeSav > IntegratedHeatPumpUnits(DXCoilNum).TimeLimitSHDWH)
				{
					IntegratedHeatPumpUnits(DXCoilNum).CurMode = IHPOperationMode::SHDWHElecHeatOnMode;
					IntegratedHeatPumpUnits(DXCoilNum).SHDWHRunTime = WHHeatTimeSav + TimeStepSys * SecInHour; 
				}
				else
				{
					IntegratedHeatPumpUnits(DXCoilNum).CurMode = IHPOperationMode::SHDWHElecHeatOffMode;
				};
			}
			else
			{
				IntegratedHeatPumpUnits(DXCoilNum).CurMode = IHPOperationMode::DWHMode;
			}
		}

		IHPOperationMode
		GetCurWorkMode(int const DXCoilNum)
		{
			// Obtains and Allocates WatertoAirHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
				//    WaterIndex=FindGlycol('WATER') !Initialize the WaterIndex once
				GetCoilsInputFlag = false;
			}

			if (IntegratedHeatPumpUnits(DXCoilNum).IHPCoilsSized == false) SizeIHP(DXCoilNum);

			return IntegratedHeatPumpUnits(DXCoilNum).CurMode;
		}


		int
		GetCoilIndexIHP(
			std::string const & CoilType, // must match coil types in this module
			std::string const & CoilName, // must match coil names for the coil type
			bool & ErrorsFound // set to true if problem
		)
		{

			// FUNCTION INFORMATION:
			//       AUTHOR         Bo Shen
			//       DATE WRITTEN   Jan 2015
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

			IndexNum = FindItemInList(CoilName, IntegratedHeatPumpUnits);

			if (IndexNum == 0) {
				ShowSevereError("GetCoilIndexIHP: Could not find CoilType=\"" + CoilType + "\" with Name=\"" + CoilName + "\"");
				ErrorsFound = true;
			}

			return IndexNum;

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

			WhichCoil = FindItemInList(CoilName, IntegratedHeatPumpUnits);
			if (WhichCoil != 0) {
				NodeNumber = IntegratedHeatPumpUnits(WhichCoil).AirInletNodeNum;
			}

			if (WhichCoil == 0) {
				ShowSevereError("GetCoilInletNodeIHP: Could not find CoilType=\"" + CoilType + "\" with Name=\"" + CoilName + "\"");
				ErrorsFound = true;
				NodeNumber = 0;
			}

			return NodeNumber;

		}

		int
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

			WhichCoil = FindItemInList(CoilName, IntegratedHeatPumpUnits);
			if (WhichCoil != 0) {

				if (IntegratedHeatPumpUnits(WhichCoil).DWHCoilIndex > 0)
					PLRNumber =	GetVSCoilPLFFPLR(IntegratedHeatPumpUnits(WhichCoil).DWHCoilType, IntegratedHeatPumpUnits(WhichCoil).DWHCoilName, ErrorsFound);
				else 
					PLRNumber = GetVSCoilPLFFPLR(IntegratedHeatPumpUnits(WhichCoil).SCWHCoilType, IntegratedHeatPumpUnits(WhichCoil).SCWHCoilName, ErrorsFound);
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
		GetDWHCoilCapacityIHP(
			std::string const & CoilType, // must match coil types in this module
			std::string const & CoilName, // must match coil names for the coil type
			IHPOperationMode const EP_UNUSED( Mode ), //mode coil type
			bool & ErrorsFound // set to true if problem
		)
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
			using VariableSpeedCoils::GetCoilCapacityVariableSpeed; 

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

			WhichCoil = FindItemInList(CoilName, IntegratedHeatPumpUnits);
			if (WhichCoil != 0) {

				if (IntegratedHeatPumpUnits(WhichCoil).IHPCoilsSized == false) SizeIHP(WhichCoil);

				if (IntegratedHeatPumpUnits(WhichCoil).DWHCoilIndex > 0)
					CoilCapacity =
					GetCoilCapacityVariableSpeed(IntegratedHeatPumpUnits(WhichCoil).DWHCoilType, IntegratedHeatPumpUnits(WhichCoil).DWHCoilName, ErrorsFound);
				else
					CoilCapacity =
					GetCoilCapacityVariableSpeed(IntegratedHeatPumpUnits(WhichCoil).SCWHCoilType, IntegratedHeatPumpUnits(WhichCoil).SCWHCoilName, ErrorsFound);
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

		}

		int
		GetLowSpeedNumIHP(int const DXCoilNum)
		{
			int SpeedNum(0); 

			// Obtains and Allocates WatertoAirHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
				//    WaterIndex=FindGlycol('WATER') !Initialize the WaterIndex once
				GetCoilsInputFlag = false;
			}


			switch (IntegratedHeatPumpUnits(DXCoilNum).CurMode)
			{
			case IHPOperationMode::IdleMode:
				SpeedNum = 1; 
				break;
			case IHPOperationMode::SCMode:
				SpeedNum = 1;
				break;
			case IHPOperationMode::SHMode:
				SpeedNum = 1;
				break;
			case IHPOperationMode::DWHMode:
				SpeedNum = 1;
				break;
			case IHPOperationMode::SCWHMatchSCMode:
			case IHPOperationMode::SCWHMatchWHMode:
				SpeedNum = IntegratedHeatPumpUnits(DXCoilNum).MinSpedSCWH; 
				break;
			case IHPOperationMode::SCDWHMode:
				SpeedNum = IntegratedHeatPumpUnits(DXCoilNum).MinSpedSCDWH;
				break;
			case IHPOperationMode::SHDWHElecHeatOffMode:
			case IHPOperationMode::SHDWHElecHeatOnMode:
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

			// Obtains and Allocates WatertoAirHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
				//    WaterIndex=FindGlycol('WATER') !Initialize the WaterIndex once
				GetCoilsInputFlag = false;
			}

			int SpeedNum(0);

			switch (IntegratedHeatPumpUnits(DXCoilNum).CurMode)
			{
			case IHPOperationMode::IdleMode:
				SpeedNum = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex).NumOfSpeeds;
				break;
			case IHPOperationMode::SCMode:
				SpeedNum = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex).NumOfSpeeds;
				break;
			case IHPOperationMode::SHMode:
				SpeedNum = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex).NumOfSpeeds;
				break;
			case IHPOperationMode::DWHMode:
				SpeedNum = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex).NumOfSpeeds;
				break;
			case IHPOperationMode::SCWHMatchSCMode:
			case IHPOperationMode::SCWHMatchWHMode:
				SpeedNum = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex).NumOfSpeeds;
				break;
			case IHPOperationMode::SCDWHMode:
				SpeedNum = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex).NumOfSpeeds;
				break;
			case IHPOperationMode::SHDWHElecHeatOffMode:
			case IHPOperationMode::SHDWHElecHeatOnMode:
				SpeedNum = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SHDWHHeatCoilIndex).NumOfSpeeds;
				break;
			default:
				SpeedNum = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex).NumOfSpeeds;
				break;
			}
			
			return(SpeedNum);
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

			// Obtains and Allocates WatertoAirHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
				//    WaterIndex=FindGlycol('WATER') !Initialize the WaterIndex once
				GetCoilsInputFlag = false;
			}

			if (IntegratedHeatPumpUnits(DXCoilNum).IHPCoilsSized == false) SizeIHP(DXCoilNum);

			FlowScale = 0.0;
			switch (IntegratedHeatPumpUnits(DXCoilNum).CurMode)
			{
			case IHPOperationMode::IdleMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex;
				break;
			case IHPOperationMode::SCMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex;
				if (false == IsCallbyWH)
				{
					FlowScale = IntegratedHeatPumpUnits(DXCoilNum).CoolVolFlowScale;
				}

				break;
			case IHPOperationMode::SHMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex;
				if (false == IsCallbyWH)
				{
					FlowScale = IntegratedHeatPumpUnits(DXCoilNum).HeatVolFlowScale;
				}				
				break;
			case IHPOperationMode::DWHMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex;
				FlowScale = 1.0;
				break;
			case IHPOperationMode::SCWHMatchSCMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex;
				FlowScale = IntegratedHeatPumpUnits(DXCoilNum).CoolVolFlowScale;
				if (true == IsCallbyWH)
				{
					IsResultFlow = true;
					AirVolFlowRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex).AirVolFlowRate; 
				}
				break;
			case IHPOperationMode::SCWHMatchWHMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex;
				FlowScale = IntegratedHeatPumpUnits(DXCoilNum).CoolVolFlowScale;
				if (false == IsCallbyWH)
				{
					IsResultFlow = true;
					AirVolFlowRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex).AirVolFlowRate;
				}
				break;
			case IHPOperationMode::SCDWHMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex;
				FlowScale = IntegratedHeatPumpUnits(DXCoilNum).CoolVolFlowScale;
				if (true == IsCallbyWH)
				{
					IsResultFlow = true;
					AirVolFlowRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex).AirVolFlowRate;
				}
				break;
			case IHPOperationMode::SHDWHElecHeatOffMode:
			case IHPOperationMode::SHDWHElecHeatOnMode:
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
				FlowScale = 0.0;
				break;
			}

			
			if (false == IsResultFlow){
				if (1 == SpeedNum)  AirVolFlowRate = VarSpeedCoil(IHPCoilIndex).MSRatedAirVolFlowRate(SpeedNum);
				else AirVolFlowRate = SpeedRatio * VarSpeedCoil(IHPCoilIndex).MSRatedAirVolFlowRate(SpeedNum) +
					(1.0 - SpeedRatio) * VarSpeedCoil(IHPCoilIndex).MSRatedAirVolFlowRate(SpeedNum - 1);

				AirVolFlowRate = AirVolFlowRate * FlowScale;
			}
						

			if (AirVolFlowRate > IntegratedHeatPumpUnits(DXCoilNum).MaxCoolAirVolFlow) AirVolFlowRate = IntegratedHeatPumpUnits(DXCoilNum).MaxCoolAirVolFlow; 
			if (AirVolFlowRate > IntegratedHeatPumpUnits(DXCoilNum).MaxHeatAirVolFlow) AirVolFlowRate = IntegratedHeatPumpUnits(DXCoilNum).MaxHeatAirVolFlow;

			return(AirVolFlowRate);
		}

		Real64
		GetWaterVolFlowRateIHP(
			int const DXCoilNum,
			int const SpeedNum,
			Real64 const SpeedRatio,
			bool const EP_UNUSED( IsCallbyWH ) //whether the call from the water heating loop or air loop, true = from water heating loop
		)
		{
			using VariableSpeedCoils::VarSpeedCoil;

			int IHPCoilIndex(0);
			Real64 WaterVolFlowRate(0.0);


			// Obtains and Allocates WatertoAirHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
				//    WaterIndex=FindGlycol('WATER') !Initialize the WaterIndex once
				GetCoilsInputFlag = false;
			}

			if (IntegratedHeatPumpUnits(DXCoilNum).IHPCoilsSized == false) SizeIHP(DXCoilNum);

			switch (IntegratedHeatPumpUnits(DXCoilNum).CurMode)
			{
			case IHPOperationMode::IdleMode:
				WaterVolFlowRate = 0.0; 
				break;
			case IHPOperationMode::SCMode:
				WaterVolFlowRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex).WaterVolFlowRate;
				break;
			case IHPOperationMode::SHMode:
				WaterVolFlowRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex).WaterVolFlowRate;
				break;
			case IHPOperationMode::DWHMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex;
				if (1 == SpeedNum)  WaterVolFlowRate = VarSpeedCoil(IHPCoilIndex).MSRatedWaterVolFlowRate(SpeedNum);
				else WaterVolFlowRate = SpeedRatio * VarSpeedCoil(IHPCoilIndex).MSRatedWaterVolFlowRate(SpeedNum) +
					(1.0 - SpeedRatio) * VarSpeedCoil(IHPCoilIndex).MSRatedWaterVolFlowRate(SpeedNum - 1);
				break;
			case IHPOperationMode::SCWHMatchSCMode:
				WaterVolFlowRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex).WaterVolFlowRate;
				break;
			case IHPOperationMode::SCWHMatchWHMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex;
				if (1 == SpeedNum)  WaterVolFlowRate = VarSpeedCoil(IHPCoilIndex).MSRatedWaterVolFlowRate(SpeedNum);
				else WaterVolFlowRate = SpeedRatio * VarSpeedCoil(IHPCoilIndex).MSRatedWaterVolFlowRate(SpeedNum) +
					(1.0 - SpeedRatio) * VarSpeedCoil(IHPCoilIndex).MSRatedWaterVolFlowRate(SpeedNum - 1);
				break;
			case IHPOperationMode::SCDWHMode:
				WaterVolFlowRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHWHCoilIndex).WaterVolFlowRate;
				break;
			case IHPOperationMode::SHDWHElecHeatOffMode:
			case IHPOperationMode::SHDWHElecHeatOnMode:
				WaterVolFlowRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SHDWHWHCoilIndex).WaterVolFlowRate;
				break;
			default:
				WaterVolFlowRate = 0.0;
				break;
			}

			return(WaterVolFlowRate);
		}

		Real64
		GetAirMassFlowRateIHP(
			int const DXCoilNum,
			int const SpeedNum,
			Real64 const SpeedRatio,
			bool const IsCallbyWH //whether the call from the water heating loop or air loop, true = from water heating loop
		)
		{
			using VariableSpeedCoils::VarSpeedCoil;

			int IHPCoilIndex(0);
			Real64 AirMassFlowRate(0.0);
			Real64 FlowScale(1.0);
			bool IsResultFlow(false); 

			// Obtains and Allocates WatertoAirHP related parameters from input file
			if (GetCoilsInputFlag) { //First time subroutine has been entered
				GetIHPInput();
				//    WaterIndex=FindGlycol('WATER') !Initialize the WaterIndex once
				GetCoilsInputFlag = false;
			}

			if (IntegratedHeatPumpUnits(DXCoilNum).IHPCoilsSized == false) SizeIHP(DXCoilNum);

			FlowScale = 0.0;
			switch (IntegratedHeatPumpUnits(DXCoilNum).CurMode)
			{
			case IHPOperationMode::IdleMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex;
				break;
			case IHPOperationMode::SCMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SCCoilIndex;
				if (false == IsCallbyWH)
				{
					FlowScale = IntegratedHeatPumpUnits(DXCoilNum).CoolVolFlowScale;
				}

				break;
			case IHPOperationMode::SHMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SHCoilIndex;
				if (false == IsCallbyWH)
				{
					FlowScale = IntegratedHeatPumpUnits(DXCoilNum).HeatVolFlowScale;
				}
				break;
			case IHPOperationMode::DWHMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).DWHCoilIndex;
				FlowScale = 1.0;
				break;
			case IHPOperationMode::SCWHMatchSCMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex;
				FlowScale = IntegratedHeatPumpUnits(DXCoilNum).CoolVolFlowScale;
				if (true == IsCallbyWH)
				{
					IsResultFlow = true;
					AirMassFlowRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex).AirMassFlowRate;
				}
				break;
			case IHPOperationMode::SCWHMatchWHMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex;
				FlowScale = IntegratedHeatPumpUnits(DXCoilNum).CoolVolFlowScale;
				if (false == IsCallbyWH)
				{
					IsResultFlow = true;
					AirMassFlowRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCWHCoilIndex).AirMassFlowRate;
				}
				break;
			case IHPOperationMode::SCDWHMode:
				IHPCoilIndex = IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex;
				FlowScale = IntegratedHeatPumpUnits(DXCoilNum).CoolVolFlowScale;
				if (true == IsCallbyWH)
				{
					IsResultFlow = true;
					AirMassFlowRate = VarSpeedCoil(IntegratedHeatPumpUnits(DXCoilNum).SCDWHCoolCoilIndex).AirMassFlowRate;
				}
				break;
			case IHPOperationMode::SHDWHElecHeatOffMode:
			case IHPOperationMode::SHDWHElecHeatOnMode:
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
				break;
			}


			if (false == IsResultFlow){
				if (1 == SpeedNum)  AirMassFlowRate = VarSpeedCoil(IHPCoilIndex).MSRatedAirMassFlowRate(SpeedNum);
				else AirMassFlowRate = SpeedRatio * VarSpeedCoil(IHPCoilIndex).MSRatedAirMassFlowRate(SpeedNum) +
					(1.0 - SpeedRatio) * VarSpeedCoil(IHPCoilIndex).MSRatedAirMassFlowRate(SpeedNum - 1);

				AirMassFlowRate = AirMassFlowRate * FlowScale;
			}
			
			if (AirMassFlowRate > IntegratedHeatPumpUnits(DXCoilNum).MaxCoolAirMassFlow) AirMassFlowRate = IntegratedHeatPumpUnits(DXCoilNum).MaxCoolAirMassFlow;
			if (AirMassFlowRate > IntegratedHeatPumpUnits(DXCoilNum).MaxHeatAirMassFlow) AirMassFlowRate = IntegratedHeatPumpUnits(DXCoilNum).MaxHeatAirMassFlow;

			return(AirMassFlowRate);
		}

	} // IntegratedHeatPumps

} // EnergyPlus
