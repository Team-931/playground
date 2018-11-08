/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/Command.h>
#include <Commands/DriveNowhere.h>
#include <Commands/SetDirDistance.h>
#include <SmartDashboard/SendableChooser.h>
#include <TimedRobot.h>

#include "OI.h"
#include "Subsystems/ExampleSubsystem.h"

class Robot : public frc::TimedRobot {
public:
	static DriveSystem driveSystem;
	static OI oi;

	void RobotInit() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestPeriodic() override;

private:
	// Have it null by default so that if testing teleop it
	// doesn't have undefined behavior and potentially crash.
	frc::Command* autonomousCommand = nullptr;
	DriveNowhere defaultAuto;
	CommandGroup myAuto {"Auto 1"};
	frc::SendableChooser<frc::Command*> autonomous_chooser;
};
