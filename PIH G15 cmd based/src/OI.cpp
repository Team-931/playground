/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include <WPILib.h>
# include "Robot.h"

class GearShiftCommand:public Command{
	DriveSystem::GearState gear;

public:
	GearShiftCommand(DriveSystem::GearState togear) : gear(togear)
		{Requires(&Robot::driveSystem);}

	void Initialize() override {Robot::driveSystem.shiftgears(gear);}
//	void Execute() override;
	bool IsFinished() override {return true;}
//	void End() override;
//	void Interrupted() override;

};

OI::OI() {
	HighGearBtn.WhenPressed(new GearShiftCommand(DriveSystem::High));
	LowGearBtn.WhenPressed(new GearShiftCommand(DriveSystem::Low));
	// Process operator interface input here.
}
