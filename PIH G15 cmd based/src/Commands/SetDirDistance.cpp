/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/SetDirDistance.h>
#include "../Robot.h"

SetDirDistance::SetDirDistance(double dir, double dist) : direction (dir),
														distance (dist),
														reverse (dist < 0)
{
	// Use Requires() here to declare subsystem dependencies
	Requires(&Robot::driveSystem);

}

// Called just before this Command runs the first time
void SetDirDistance::Initialize() {
	Robot::driveSystem.setDirection(direction);
	Robot::driveSystem.resetEncoders();
	//distance += Robot::driveSystem.readEncoders();
}

// Called repeatedly when this Command is scheduled to run
void SetDirDistance::Execute() {
	if (reverse)
		Robot::driveSystem.driveAtSpeed(-.5);
	else
		Robot::driveSystem.driveAtSpeed(.5);
}

// Make this return true when this Command no longer needs to run execute()
bool SetDirDistance::IsFinished() {
	if (reverse)
	return Robot::driveSystem.readEncoders() <= distance;
	return Robot::driveSystem.readEncoders() >= distance;
}

// Called once after isFinished returns true
void SetDirDistance::End() {}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetDirDistance::Interrupted() {}
