/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <Joystick.h>
#include <Buttons/JoystickButton.h>

struct MaybeJButton : frc::JoystickButton {
	MaybeJButton (GenericHID* joystick, int buttonNumber, bool condition()) :
		frc::JoystickButton (joystick, buttonNumber), cond(condition) {}
	bool Get() {
		return cond() && frc::JoystickButton::Get();
	}
private:
	bool (*cond)();
};


class OI {
static bool isTwoBtn, OneBtn(), TwoBtn();
friend struct TwoGearBtns;
public:
	Joystick stick{0};
	MaybeJButton HighGearBtn{&stick, 4, TwoBtn};
	MaybeJButton LowGearBtn{&stick, 1, TwoBtn};
	MaybeJButton ToggleGearBtn{&stick, 4, OneBtn};
	OI();
};
