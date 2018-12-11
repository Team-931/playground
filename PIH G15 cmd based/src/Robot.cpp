/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <Commands/Scheduler.h>
#include <SmartDashboard/SmartDashboard.h>

DriveSystem Robot::driveSystem;
OI /***/Robot::oi /*= 0*/;

void Robot::RobotInit() {
	//oi = new OI;//.stick = new Joystick(0);
	frc::SmartDashboard::SetDefaultNumber("P", .01);
	frc::SmartDashboard::SetDefaultNumber("I", 0);
	frc::SmartDashboard::SetDefaultNumber("D", 0);

	autonomous_chooser.AddDefault("Default Auto", &defaultAuto);
	myAuto.AddSequential(new SetDirDistance (0, 10000));
	myAuto.AddSequential(new SetDirDistance (90, 10000));

	autonomous_chooser.AddObject("My Auto", &myAuto);
	frc::SmartDashboard::PutData("Auto Modes", &autonomous_chooser);
	frc::SmartDashboard::PutData(&myAuto);
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString code to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional commands to the
 * chooser code above (like the commented example) or additional comparisons to
 * the if-else structure below with additional strings & commands.
 */
void Robot::AutonomousInit() {
	// std::string autoSelected = frc::SmartDashboard::GetString(
	// 		"Auto Selector", "Default");
	// if (autoSelected == "My Auto") {
	// 	m_autonomousCommand = &m_myAuto;
	// } else {
	// 	m_autonomousCommand = &m_defaultAuto;
	// }

	driveSystem.navigatorPrep();

	autonomousCommand = autonomous_chooser.GetSelected();

	if (autonomousCommand != nullptr) {
		autonomousCommand->Start();
	}
}

void Robot::AutonomousPeriodic() {
	::SmartDashboard::PutNumber("encoder clicks" , Robot::driveSystem.readEncoders());
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// this line or comment it out.
	if (autonomousCommand != nullptr) {
		autonomousCommand->Cancel();
		autonomousCommand = nullptr;
	}
}

void Robot::TeleopPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

void Robot::TestPeriodic() {}

START_ROBOT_CLASS(Robot)
