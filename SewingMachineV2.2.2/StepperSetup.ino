void StepperSetup()
{
  stepperX.setMaxSpeed(900);
  stepperX.setAcceleration(600);
  stepperX.setMinPulseWidth(100);
  stepperX.setCurrentPosition(0);

  stepperY.setMaxSpeed(900);
  stepperY.setAcceleration(600);
  stepperY.setMinPulseWidth(100);
  stepperY.setCurrentPosition(0);
}
