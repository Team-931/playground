/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <Joystick.h>
#include <Buttons/JoystickButton.h>

class OI {
public:
	Joystick stick{0};
	JoystickButton HighGearBtn{&stick, 4};
	JoystickButton LowGearBtn{&stick, 2};
	OI();
};
