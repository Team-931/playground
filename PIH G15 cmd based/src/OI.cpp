/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "OI.h"

#include <WPILib.h>
# include "Robot.h"

class GearShiftCommand: public Command {

public:

	void Initialize() override {Robot::driveSystem.shiftgears(DriveSystem::High);}
//	void Execute() override;
	bool IsFinished() override {return false;}
	void End() override {Robot::driveSystem.shiftgears(DriveSystem::Low);}
//	void Interrupted() override;

} gearShiftCommand;

struct TwoGearBtns: Command {
	bool IsFinished() {return false;}
	void Initialize() {OI::isTwoBtn = true;}
	void End() {OI::isTwoBtn = false;}
} twoGearBtns;

/* Notes for future OI:
 * Once a command is assigned to a button-state, it cannot be removed.
 * More than one command can be assigned to the same button-state.
 * One command can be assigned to more than one button-state.
 * One can make a command's behavior depend on an outside variable.
 * One can define a button or trigger whose responses depend on an outside variable.
 */

OI::OI() {
	HighGearBtn.WhenPressed(&gearShiftCommand);
	LowGearBtn.CancelWhenPressed(&gearShiftCommand);
	ToggleGearBtn.ToggleWhenPressed(&gearShiftCommand);
	frc::SmartDashboard::PutData(&gearShiftCommand);
	frc::SmartDashboard::PutData(&twoGearBtns);
	// Process operator interface input here.
}

bool OI::isTwoBtn = false;

inline bool OI::TwoBtn() {
	return isTwoBtn;
}

inline bool OI::OneBtn() {
	return !isTwoBtn;
}
