#include "driver_func.hpp"
#include "main.h"

void scoreCap(){
  Motor FL (FLport);
  Motor BL (BLport);
  Motor FR (FRport);
  Motor BR (BRport);
  Motor lift(liftPort);

  pausePusher(true);
  setLift(liftScorePosition);
  double startScore = millis();
  while(fabs(liftScorePosition - lift.get_position()) > 5 && millis()-startScore<1300){
    //master.print(2,0,"%3f",lift.get_position());
    FL.move(poleAlignPower);
    BL.move(poleAlignPower);
    FR.move(poleAlignPower);
    BR.move(poleAlignPower);
  }
  int startBackOut = millis();
  while(millis() - startBackOut < backOutTime){
    //master.print(2,0,"%3f",lift.get_position());
    if(millis() - startBackOut >= lowerLiftDelay){
      setLift(0);
    }
    FL.move(-backOutPower);
    BL.move(-backOutPower);
    FR.move(-backOutPower);
    BR.move(-backOutPower);
  }
  setLift(0);
}
void descoreCap(){
  Motor FL (FLport);
  Motor BL (BLport);
  Motor FR (FRport);
  Motor BR (BRport);
  Motor lift(liftPort);

  setPusher(25);
  setLift(liftDescorePosition);
  while(fabs(liftDescorePosition - lift.get_position()) > 5){
  //  master.print(2,0,"%3f",lift.get_position());
    FL.move(0);
    BL.move(0);
    FR.move(0);
    BR.move(0);
  }
  delay(pushInDelay);
  int startPushIn = millis();
  while(millis() - startPushIn < pushInTime){
    FL.move(pushInPower);
    BL.move(pushInPower);
    FR.move(pushInPower);
    BR.move(pushInPower);
  }
  int startPushIn2 = millis();
  while(millis() - startPushIn2 < pushIn2Time){
    FL.move(pushIn2Power);
    BL.move(pushIn2Power);
    FR.move(pushIn2Power);
    BR.move(pushIn2Power);
  }
  setLift(0);
  delay(descoreDelay);
}

void directClimb(){
  Motor FL (FLport);
  Motor BL (BLport);
  Motor FR (FRport);
  Motor BR (BRport);
  Motor lift(liftPort);
  ADIGyro gyro(gyroPort);

  gyro.reset();

  Motor pusher (pusherPort);
  setLift(0);
  FL.tare_position();
  FR.tare_position();
  BL.tare_position();
  BR.tare_position();
  while(BL.get_position()>-15 && BR.get_position()>-15){
    FL.move(-70);
    BL.move(-70);
    FR.move(-70);
    BR.move(-70);
    delay(25);
  }
  FL.move_relative(0, 100);
  BL.move_relative(0, 100);
  FR.move_relative(0, 100);
  BR.move_relative(0, 100);

  setClimb(true);
  //pauseLift(true);

  //nani tf? liddat it'll only print once at the start?
  printf("%f\n",pusher.get_position());
  double startPush = millis();
  while(pusher.get_position() > -680  && millis()-startPush < 1000) {
    printf("%f\n",pusher.get_position());
  /*  if(pusher.get_position() < -650){
      FL.move(100);
      BL.move(100);
      FR.move(100);
      BR.move(100);
      delay(25);
    }
  else{*/
    FL.move(20);
    BL.move(20);
    FR.move(20);
    BR.move(20);
    delay(25);
  }

  delay(50);
  FL.tare_position();
  FR.tare_position();
  BL.tare_position();
  BR.tare_position();
  double startClimb = millis();

  while(gyro.get_value() > 300){  //MARCUS WONG! IT'S IN 1/10 DEGREES
    FL.move(100);
    BL.move(100);
    FR.move(100);
    BR.move(100);
    delay(25);
  }
  while(gyro.get_value() > 50){  //MARCUS WONG! IT'S IN 1/10 DEGREES
    if(millis()-startClimb > 500){
      setClimb(false);
      setPusher(170);
    }
    FL.move(120);
    BL.move(120);
    FR.move(120);
    BR.move(120);
    delay(25);
  }
  delay(75);
  FL.move_relative(0, 80);
  BL.move_relative(0, 80);
  FR.move_relative(0, 80);
  BR.move_relative(0, 80);
  setLift(20);
  delay(200);
}
