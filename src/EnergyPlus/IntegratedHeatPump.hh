#ifndef IntegratedHeatPumps_hh_INCLUDED
#define IntegratedHeatPumps_hh_INCLUDED

// ObjexxFCL Headers
#include <ObjexxFCL/Array1D.hh>
#include <ObjexxFCL/Optional.hh>

// EnergyPlus Headers
#include <EnergyPlus.hh>
#include <VariableSpeedCoils.hh>
#include <DataSizing.hh>
#include <DataGlobals.hh>
#include <DataHVACGlobals.hh>

namespace EnergyPlus {

namespace IntegratedHeatPumps {

	// Using/Aliasing
	// Using/Aliasing
	using VariableSpeedCoils::MaxSpedLevels;

	// Data
	//MODULE PARAMETER DEFINITIONS

	// Identifier is VarSpeedCoil
	extern int NumIHPs; //counter for all integrated heat pumps including air-source and water-source
	extern bool GetCoilsInputFlag; // Flag set to make sure you get input once

	// operation mode
	int const IdleMode(0);
	int const SCMode(1);
	int const SHMode(2);
	int const DWHMode(3);
	int const SCWHMatchSCMode(4);
	int const SCWHMatchWHMode(5);
	int const SCDWHMode(6);
	int const SHDWHElecHeatOffMode(7);
	int const SHDWHElecHeatOnMode(8);

	// SUBROUTINE SPECIFICATIONS FOR MODULE

	// Driver/Manager Routines

	// Get Input routines for module

	// Initialization routines for module

	// Update routines to check convergence and update nodes

	// Update routine

	// Utility routines
	//SHR, bypass factor routines

	// Types

	struct IntegratedHeatPumpData // variable speed coil
	{
		// Members
		std::string Name; // Name of the  Coil
		std::string IHPtype; // type of coil

		std::string SCCoilType; // Numeric Equivalent for SC Coil Type
		std::string SCCoilName;
		int SCCoilIndex; // Index to SC coil

		std::string SHCoilType; // Numeric Equivalent for SH Coil Type
		std::string SHCoilName;
		int SHCoilIndex; // Index to SH coil

		std::string SCWHCoilType; // Numeric Equivalent for SCWH Coil Type
		std::string SCWHCoilName; 
		int SCWHCoilIndex; // Index to SCWH coil

		std::string DWHCoilType; // Numeric Equivalent for DWH Coil Type
		std::string DWHCoilName;
		int DWHCoilIndex; // Index to DWH coil

		std::string SCDWHCoolCoilType; // Numeric Equivalent for SCDWH Coil Type, cooling part
		std::string SCDWHCoolCoilName;
		int SCDWHCoolCoilIndex; // Index to SCDWH coil, cooling part

		std::string SCDWHWHCoilType; // Numeric Equivalent for SCDWH Coil Type, water heating part
		std::string SCDWHWHCoilName;
		int SCDWHWHCoilIndex; // Index to SCDWH coil, water heating part

		std::string SHDWHHeatCoilType; // Numeric Equivalent for SHDWH Coil Type, heating part
		std::string SHDWHHeatCoilName;
		int SHDWHHeatCoilIndex; // Index to SHDWH coil, heating part

		std::string SHDWHWHCoilType; // Numeric Equivalent for SHDWH Coil Type, water heating part
		std::string SHDWHWHCoilName;
		int SHDWHWHCoilIndex; // Index to SHDWH coil, water heating part

		int AirCoolInletNodeNum; // Node Number of the Air cooling coil Inlet
		int AirHeatInletNodeNum; // Node Number of the Air cooling coil Inlet
		int AirOutletNodeNum; // Node Number of the Air Outlet
		int WaterInletNodeNum; // Node Number of the Water Onlet
		int WaterOutletNodeNum; // Node Number of the Water Outlet
		int WaterTankoutNod; // water node to monitor the supply water flow amount

		int ModeMatchSCWH;//- 0: match cooling load, 1 : match water heating load in SCWH mode
		int MinSpedSCWH; //-minimum speed level for SCWH mode
		int MinSpedSCDWH; //- minimum speed level for SCDWH mode
		int MinSpedSHDWH;//- minimum speed level for SHDWH mode
		Real64 TindoorOverCoolAllow;  //- [C], indoor temperature above which indoor overcooling is allowed
		Real64 TambientOverCoolAllow; //- [C], ambient temperature above which indoor overcooling is allowed
		Real64 TindoorWHHighPriority;  //- [C], indoor temperature above which water heating has the higher priority
		Real64 TambientWHHighPriority; //ambient temperature above which water heating has the higher priority

		Real64 WaterVolSCDWH;// limit of water volume before switching from SCDWH to SCWH
		Real64 TimeLimitSHDWH; //time limit before turning from SHDWH to electric heating 

		int WHtankType;
		std::string WHtankName; 
		int WHtankID; 
		bool IsWHCallAvail;//whether water heating call available
		bool CheckWHCall; 
		int CurMode; //current working mode
		Real64 ControlledZoneTemp; 
		Real64 WaterFlowAccumVol;// water flow accumulated volume
		Real64 SHDWHRunTime; 
		bool NodeConnected; 
		Real64 TotalHeatingEnergyRate; 
		Real64 CoolVolFlowScale;// max fan cooling volumetric flow rate
		Real64 HeatVolFlowScale;// max fan heating volumetric flow rate
		Real64 MaxHeatAirMassFlow;//maximum air mass flow rate for heating mode
		Real64 MaxHeatAirVolFlow;//maximum air volume flow rate for heating mode
		Real64 MaxCoolAirMassFlow;//maximum air mass flow rate for heating mode
		Real64 MaxCoolAirVolFlow;//maximum air volume flow rate for heating mode
		bool IHPCoilsSized;//whether IHP coils have been sized

		std::string IDFanName;//IHP indoor fan name
		int IDFanID;//IHP indoor fan index
		int IDFanPlace;//indoor fan placement
				
		// Default Constructor
		IntegratedHeatPumpData() :
			SCCoilIndex(0),
			SHCoilIndex(0),
			SCWHCoilIndex(0),
			DWHCoilIndex(0),
			SCDWHCoolCoilIndex(0),
			SCDWHWHCoilIndex(0),
			SHDWHHeatCoilIndex(0),
			SHDWHWHCoilIndex(0),
			AirCoolInletNodeNum(0),
			AirHeatInletNodeNum(0),
			AirOutletNodeNum(0),
			WaterInletNodeNum(0),
			WaterOutletNodeNum(0),
			WaterTankoutNod(0),
			ModeMatchSCWH(0),
			MinSpedSCWH(1),
			MinSpedSCDWH(1),
			MinSpedSHDWH(1),
			TindoorOverCoolAllow(0.0),
			TambientOverCoolAllow(0.0),
			TindoorWHHighPriority(0.0),
			TambientWHHighPriority(0.0),
			WaterVolSCDWH(0.0),
			TimeLimitSHDWH(0.0),
			WHtankType(0),
			WHtankID(0),
			IsWHCallAvail(false),
			CheckWHCall(false),
			CurMode(0),
			ControlledZoneTemp(0),
			WaterFlowAccumVol(0),
			SHDWHRunTime(0),
			NodeConnected(false),
			TotalHeatingEnergyRate(0),
			CoolVolFlowScale(0),
			HeatVolFlowScale(0),
			MaxHeatAirMassFlow(0),
			MaxHeatAirVolFlow(0),
			MaxCoolAirMassFlow(0),
			MaxCoolAirVolFlow(0),
			IHPCoilsSized(false),
			IDFanID(0),
			IDFanPlace(0)
		{}

		// Member Constructor
			IntegratedHeatPumpData(
			std::string const & Name, // Name of the  Coil
			std::string const & IHPCoilType, // type of coil
			std::string const &SCCoilType_Num, // Numeric Equivalent for SC Coil Type
			std::string const &SCCoilName, // Numeric Equivalent for SC Coil Type
			int const SCCoilIndex, // Index to SC coil
			std::string const &SHCoilType_Num, // Numeric Equivalent for SH Coil Type
			std::string const &SHCoilName, // Numeric Equivalent for SH Coil Type
			int const SHCoilIndex, // Index to SH coil
			std::string const &SCWHCoilType_Num, // Numeric Equivalent for SCWH Coil Type
			std::string const &SCWHCoilName, // Numeric Equivalent for SCWH Coil Type
			int const SCWHCoilIndex, // Index to SCWH coil
			std::string const &DWHCoilType_Num, // Numeric Equivalent for DWH Coil Type
			std::string const &DWHCoilName, // Numeric Equivalent for DWH Coil Type
			int const DWHCoilIndex, // Index to DWH coil
			std::string const &SCDWHCoolCoilType_Num, // Numeric Equivalent for SCDWH Coil Type, cooling part
			std::string const &SCDWHCoolCoilName, // Numeric Equivalent for SCDWH Coil Type, cooling part
			int const SCDWHCoolCoilIndex, // Index to SCDWH coil, cooling part
			std::string const &SCDWHWHCoilType_Num, // Numeric Equivalent for SCDWH Coil Type, water heating part
			std::string const &SCDWHWHCoilName, // Numeric Equivalent for SCDWH Coil Type, water heating part
			int const SCDWHWHCoilIndex, // Index to SCDWH coil, water heating part
			std::string const &SHDWHHeatCoilType_Num, // Numeric Equivalent for SHDWH Coil Type, heating part
			std::string const &SHDWHHeatCoilName, // Numeric Equivalent for SHDWH Coil Type, heating part
			int const SHDWHHeatCoilIndex, // Index to SHDWH coil, heating part
			std::string const &SHDWHWHCoilType_Num, // Numeric Equivalent for SHDWH Coil Type, water heating part
			std::string const &SHDWHWHCoilName, // Numeric Equivalent for SHDWH Coil Type, water heating part
			std::string const &IDFanName,// IHP indoor fan name
			int const SHDWHWHCoilIndex, // Index to SHDWH coil, water heating part
			int const AirCoolInletNodeNum, // Node Number of the Air Inlet
			int const AirHeatInletNodeNum, // Node Number of the Air Inlet
			int const AirOutletNodeNum, // Node Number of the Air Outlet
			int const WaterInletNodeNum, // Node Number of the Water Onlet
			int const WaterOutletNodeNum, // Node Number of the Water Outlet
			int const WaterTankoutNod, //node to monitor hot water flow rate
			int const ModeMatchSCWH,//- 0: match cooling load, 1 : match water heating load in SCWH mode
			int const MinSpedSCWH, //-minimum speed level for SCWH mode
			int const MinSpedSCDWH, //- minimum speed level for SCDWH mode
			int const MinSpedSHDWH,//- minimum speed level for SHDWH mode
			Real64 const TindoorOverCoolAllow,  //- [C], indoor temperature above which indoor overcooling is allowed
			Real64 const TambientOverCoolAllow, //- [C], ambient temperature above which indoor overcooling is allowed
			Real64 const TindoorWHHighPriority,  //- [C], indoor temperature above which water heating has the higher priority
			Real64 const TambientWHHighPriority, //ambient temperature above which water heating has the higher priority
			Real64 const WaterVolSCDWH,// limit of water volume before switching from SCDWH to SCWH
			Real64 const TimeLimitSHDWH, //time limit before turning from SHDWH to electric heating 
			int const WHtankType,
			std::string const &WHtankName,
			int const WHtankID,
			bool const IsWHCallAvail,//whether water heating call available
			bool const CheckWHCall,
			int const CurMode, //current working mode
			Real64 const ControlledZoneTemp,
			Real64 const WaterFlowAccumVol,// water flow accumulated volume
			Real64 const SHDWHRunTime,
			bool const NodeConnected,
			Real64 const TotalHeatingEnergyRate,
			Real64 const CoolVolFlowScale,// max fan cooling volumetric flow rate
			Real64 const HeatVolFlowScale,// max fan heating volumetric flow rate
			Real64 const MaxHeatAirMassFlow,//maximum air mass flow rate for heating mode
			Real64 const MaxHeatAirVolFlow,//maximum air volume flow rate for heating mode
			Real64 const MaxCoolAirMassFlow,//maximum air mass flow rate for heating mode
			Real64 const MaxCoolAirVolFlow,//maximum air volume flow rate for heating mode
			bool const IHPCoilsSized,//whether IHP coils have been sized
			int const IDFanID, //indoor fan id
			int const IDFanPlace//indoor fan placement
		) :
			Name( Name ),
			IHPtype(IHPCoilType),
			SCCoilType(SCCoilType_Num), 
			SCCoilName(SCCoilName),
			SCCoilIndex(SCCoilIndex), 
			SHCoilType(SHCoilType_Num), 
			SHCoilName(SHCoilName),
			SHCoilIndex(SHCoilIndex), 
			SCWHCoilType(SCWHCoilType_Num), 
			SCWHCoilName(SCWHCoilName),
			SCWHCoilIndex(SCWHCoilIndex), 
			DWHCoilType(DWHCoilType_Num), 
			DWHCoilName(DWHCoilName),
			DWHCoilIndex(DWHCoilIndex), 
			SCDWHCoolCoilType(SCDWHCoolCoilType_Num), 
			SCDWHCoolCoilName(SCDWHCoolCoilName),
			SCDWHCoolCoilIndex(SCDWHCoolCoilIndex),
			SCDWHWHCoilType(SCDWHWHCoilType_Num), 
			SCDWHWHCoilName(SCDWHWHCoilName),
			SCDWHWHCoilIndex(SCDWHWHCoilIndex), 
			SHDWHHeatCoilType(SHDWHHeatCoilType_Num), 
			SHDWHHeatCoilName(SHDWHHeatCoilName),
			SHDWHHeatCoilIndex(SHDWHHeatCoilIndex),
			SHDWHWHCoilType(SHDWHWHCoilType_Num), 
			SHDWHWHCoilName(SHDWHWHCoilName),
			IDFanName(IDFanName),
			SHDWHWHCoilIndex(SHDWHWHCoilIndex), 
			AirCoolInletNodeNum(AirCoolInletNodeNum), 
			AirHeatInletNodeNum(AirHeatInletNodeNum),
			AirOutletNodeNum(AirOutletNodeNum),
			WaterInletNodeNum(WaterInletNodeNum), 
			WaterOutletNodeNum(WaterOutletNodeNum), 
			WaterTankoutNod(WaterTankoutNod),
			ModeMatchSCWH(ModeMatchSCWH),
			MinSpedSCWH(MinSpedSCWH), 
			MinSpedSCDWH(MinSpedSCDWH),
			MinSpedSHDWH(MinSpedSHDWH),
			TindoorOverCoolAllow(TindoorOverCoolAllow),  
			TambientOverCoolAllow(TambientOverCoolAllow), 
			TindoorWHHighPriority(TindoorWHHighPriority),  
			TambientWHHighPriority(TambientWHHighPriority), 
			WaterVolSCDWH(WaterVolSCDWH),
			TimeLimitSHDWH(TimeLimitSHDWH), 
			WHtankType(WHtankType),
			WHtankName(WHtankName),
			WHtankID(WHtankID),
			IsWHCallAvail(IsWHCallAvail),//whether water heating call available
			CheckWHCall(CheckWHCall),
			CurMode(CurMode), //current working mode
			ControlledZoneTemp(ControlledZoneTemp),
			WaterFlowAccumVol(WaterFlowAccumVol),// water flow accumulated volume
			SHDWHRunTime(SHDWHRunTime),
			NodeConnected(NodeConnected),
			TotalHeatingEnergyRate(TotalHeatingEnergyRate),
			CoolVolFlowScale(CoolVolFlowScale),// max fan cooling volumetric flow rate
			HeatVolFlowScale(HeatVolFlowScale),// max fan heating volumetric flow rate
			MaxHeatAirMassFlow(MaxHeatAirMassFlow),//maximum air mass flow rate for heating mode
			MaxHeatAirVolFlow(MaxHeatAirVolFlow),//maximum air volume flow rate for heating mode
			MaxCoolAirMassFlow(MaxCoolAirMassFlow),//maximum air mass flow rate for heating mode
			MaxCoolAirVolFlow(MaxCoolAirVolFlow),//maximum air volume flow rate for heating mode
			IHPCoilsSized(IHPCoilsSized),//whether IHP coils have been sized
			IDFanID(IDFanID),
			IDFanPlace(IDFanPlace)
		{}

	};

	// Object Data
	extern Array1D< IntegratedHeatPumpData > IntegratedHeatPumpUnits;

	// Functions
	void
		clear_state();

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
		bool const FirstHVACIteration, // TRUE if First iteration of simulation
		Optional< Real64 const > OnOffAirFlowRat = _ // ratio of comp on to comp off air flow rate
	);

	void
	GetIHPInput();


	void
	SizeIHP( int const CoilNum );
	
	void
	InitializeIHP( int const DXCoilNum); 

	void
	UpdateIHP( int const DXCoilNum );

	void
		DecideWorkMode(int const DXCoilNum,
		Real64 const SensLoad, // Sensible demand load [W]
		Real64 const LatentLoad // Latent demand load [W]
		);

	int 
		GetCurWorkMode(int const DXCoilNum);

	int
		GetLowSpeedNumIHP(int const DXCoilNum);
	int
		GetMaxSpeedNumIHP(int const DXCoilNum);

	Real64
		GetAirVolFlowRateIHP(int const DXCoilNum, int const SpeedNum, Real64 const SpeedRatio, 
		bool const IsCallbyWH //whether the call from the water heating loop or air loop, true = from water heating loop
		);

	Real64
		GetWaterVolFlowRateIHP(int const DXCoilNum, int const SpeedNum, Real64 const SpeedRatio,
		bool const IsCallbyWH //whether the call from the water heating loop or air loop, true = from water heating loop
		);

	Real64
		GetAirMassFlowRateIHP(int const DXCoilNum, int const SpeedNum, Real64 const SpeedRatio,
		bool const IsCallbyWH //whether the call from the water heating loop or air loop, true = from water heating loop
		);

	int
		GetCoilIndexIHP(
		std::string const & CoilType, // must match coil types in this module
		std::string const & CoilName, // must match coil names for the coil type
		bool & ErrorsFound // set to true if problem
		);

	int
		GetCoilInletNodeIHP(
		std::string const & CoilType, // must match coil types in this module
		std::string const & CoilName, // must match coil names for the coil type
		bool & ErrorsFound // set to true if problem
		);

	Real64
		GetDWHCoilCapacityIHP(
		std::string const & CoilType, // must match coil types in this module
		std::string const & CoilName, // must match coil names for the coil type
		int const Mode,//mode coil type
		bool & ErrorsFound // set to true if problem
		);

	int
		GetIHPDWHCoilPLFFPLR(
		std::string const & CoilType, // must match coil types in this module
		std::string const & CoilName, // must match coil names for the coil type
		int const Mode,//mode coil type
		bool & ErrorsFound // set to true if problem
		);

	void
		ConnectIHP(
		int const WhichCoil // must match coil names for the coil type
		);

	void
		DisconnectIHP(
		int const WhichCoil // must match coil names for the coil type
		);

	
	//     NOTICE

	//     Copyright � 1996-2014 The Board of Trustees of the University of Illinois
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

#endif
