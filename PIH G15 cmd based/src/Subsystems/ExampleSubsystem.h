/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

# include <WPILib.h>
# include <AHRS.h>
#include <Commands/Subsystem.h>

# include <ctre/phoenix.h>

class DriveSystem : public frc::Subsystem, frc::PIDOutput {
public:
	DriveSystem();
	void InitDefaultCommand() override;
	void PIDWrite(double) override;// so we can be a PIDOutput

	DifferentialDrive* operator ->()
		{return &drive;}

	void navigatorPrep();

	void setDirection(double);
	void driveAtSpeed(double);

	enum GearState {
		Low, High   //not allowed semicolon in enum
//unless else assigned, low (enum constant 1) = 0, high (enum constant 2) = 1
	};
	void shiftgears(GearState);//uses gearstate as bool
	double readEncoders();
	void resetEncoders();

private:
	::WPI_TalonSRX motor0 {8}, motor1 {3}, motor2{2}, motor3{4};
	frc::SpeedControllerGroup rightDrive {motor0, motor1},
			leftDrive {motor2, motor3};
	frc::DifferentialDrive drive {leftDrive, rightDrive};

	frc::Encoder rightEncoder {2, 3}, leftEncoder {0, 1};
	frc::Servo rightServo {9}, leftServo {8};

	::AHRS navx {::SPI::kMXP};

	double p = .01, i = 0, d = 0;
	frc::PIDController navigator {p, i, d, navx, *this};
	double turn {0}; // the amt output by navigator as direction correction


	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
};
