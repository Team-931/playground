/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Commands/DriveDefault.h>
#include "ExampleSubsystem.h"
#include "../RobotMap.h"

DriveSystem::DriveSystem()
    : frc::Subsystem("DriveSystem") {
	leftDrive.SetInverted(true);
	leftEncoder.SetReverseDirection(true);
	rightDrive.SetInverted(false);

	navigator.SetInputRange(-180, 180);
	navigator.SetContinuous(true);
}

void DriveSystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new DriveDefault());
}

void DriveSystem::PIDWrite(double PIDturn) {
	turn = PIDturn;
}

void DriveSystem::navigatorPrep() {
	navx.ZeroYaw();
	leftEncoder.Reset();
	rightEncoder.Reset();
	p = frc::SmartDashboard::GetNumber("P", p);
	i = frc::SmartDashboard::GetNumber("I", i);
	d = frc::SmartDashboard::GetNumber("D", d);
	navigator.SetPID(p,i,d);
	navigator.Enable();


}

void DriveSystem::setDirection(double dir) {
	navigator.SetSetpoint(dir);
}

void DriveSystem::driveAtSpeed(double spd) {
	drive.ArcadeDrive(spd, turn);
}

double DriveSystem::readEncoders() {
	return (rightEncoder.Get() + leftEncoder.Get())/2;
}

void DriveSystem::shiftgears(GearState gearState) {
	leftServo.Set(gearState);
	rightServo.Set(gearState);
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
