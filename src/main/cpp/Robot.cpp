// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

#include <fmt/core.h>

#include <frc/smartdashboard/SmartDashboard.h>

#include <iostream>

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);
  InitializePIDControllers(); 
 // m_motorB.Follow(m_motorA, true);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  // m_stick.SetRumble(frc::GenericHID::RumbleType::kLeftRumble, 1.0); 
  // m_stick.SetRumble(frc::GenericHID::RumbleType::kRightRumble, 1.0);
m_motorAEncoder.SetPosition(0.0);
m_motorBEncoder.SetPosition(0.0);

}
/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  fmt::print("Auto selected: {}\n", m_autoSelected);

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() {
  InitializePIDControllers(); 
}

void Robot::TeleopPeriodic() {
  std::cout << "Velocity 1: " << m_motorAEncoder.GetVelocity() << "\n";
  std::cout << "Velocity 2: " << m_motorBEncoder.GetVelocity() << "\n";
  /*
  if (m_stick.GetYButton()){
  m_motorAPIDEncoder.SetReference(2500.0, rev::ControlType::kVelocity);
  m_motorBPIDEncoder.SetReference(-2500.0, rev::ControlType::kVelocity);
  }
  else {
  m_motorAPIDEncoder.SetReference(0.0, rev::ControlType::kVelocity);
  m_motorBPIDEncoder.SetReference(0.0, rev::ControlType::kVelocity);
  }
*/
if (m_stick.GetLeftBumper()){
  std::cout << "pressed \n";
  m_motorA.Set(-0.5);
 m_motorB.Set(0.5);
  }
else {
    std::cout << "not pressed \n";
  m_motorA.Set(0.0);
m_motorB.Set(0.0);
  }
}


void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

void Robot::InitializePIDControllers() {
  m_motorAPIDEncoder.SetP(m_motorACoeff.kP);
  m_motorAPIDEncoder.SetI(m_motorACoeff.kI);
  m_motorAPIDEncoder.SetD(m_motorACoeff.kD);
  m_motorAPIDEncoder.SetIZone(m_motorACoeff.kIz);
  m_motorAPIDEncoder.SetFF(m_motorACoeff.kFF);
  m_motorAPIDEncoder.SetOutputRange(m_motorACoeff.kMinOutput, m_motorACoeff.kMaxOutput);

  m_motorBPIDEncoder.SetP(m_motorBCoeff.kP);
  m_motorBPIDEncoder.SetI(m_motorBCoeff.kI);
  m_motorBPIDEncoder.SetD(m_motorBCoeff.kD);
  m_motorBPIDEncoder.SetIZone(m_motorBCoeff.kIz);
  m_motorBPIDEncoder.SetFF(m_motorBCoeff.kFF);
  m_motorBPIDEncoder.SetOutputRange(m_motorBCoeff.kMinOutput, m_motorBCoeff.kMaxOutput);
}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif