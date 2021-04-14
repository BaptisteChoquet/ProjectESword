#include "Wire.h" // This library allows you to communicate with I2C devices.

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

const float swordLength = 1; // the length of the blade of the sword expressed in meters.
const float swordWeight = 0.8; // the weight of the blade expressed in kiloGrams
const int t = 100; // duration of a time unit, in milliseconds.
const int Min = 1; // minimum speed of the blade for the calcul to be executed.


int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t temperature; // variables for temperature data
int16_t xPosBeg, yPosBeg, zPosBeg, xPosEnd, yPosEnd, zPosEnd, xValue, yValue, zValue; // variables relating to the evolution of the sword angle between two time units
float xD, yD, zD, TotalD; // variable relating to the distance crossed by the tip of the blade between two time units
float cinEnr; // variable corresponding to the cinetical energy of the hit

float xAngleValue, yAngleValue, zAngleValue; // variables used to express angles values

char tmp_str[7]; // temporary variable used in convert function

char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(4); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

void loop(){
  for (int i = 0; i < 1; i++) {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR, 3*2, true);
    // Code below collect values of the accelerometer at time "0"
    accelerometer_x = Wire.read()<<8 | Wire.read();
    //accelerometer_x = accelerometer_x/256;
    xPosBeg = accelerometer_x;
    accelerometer_y = Wire.read()<<8 | Wire.read();
    //accelerometer_y = accelerometer_y/256;
    yPosBeg = accelerometer_y;
    accelerometer_z = Wire.read()<<8 | Wire.read();
    //accelerometer_z = accelerometer_z/256;
    zPosBeg = accelerometer_z;
    // Below some outputs for testing purpose
    /*
    Serial.print("initial value of x = ");
    Serial.print(convert_int16_to_str(xPosBeg));
    Serial.print("   ");
    Serial.print("initial value of y = ");
    Serial.print(convert_int16_to_str(yPosBeg));
    Serial.print("   ");
    Serial.print("initial value of z = ");
    Serial.print(convert_int16_to_str(zPosBeg));
    Serial.print("   ");*/
    delay(t);// Makes the Arduino wait until tome time has passed to take new mesures 
    }
   Wire.beginTransmission(MPU_ADDR);
   Wire.write(0x3B);
   Wire.endTransmission(false);
   Wire.requestFrom(MPU_ADDR, 3*2, true);
   // Here the walues at time "t" are collected
   accelerometer_x = Wire.read()<<8 | Wire.read();
   //accelerometer_x = accelerometer_x/256;
   xPosEnd = accelerometer_x;
   accelerometer_y = Wire.read()<<8 | Wire.read();
   //accelerometer_y = accelerometer_y/256;
   yPosEnd = accelerometer_y;
   accelerometer_z = Wire.read()<<8 | Wire.read();
   //accelerometer_z = accelerometer_z/256;
   zPosEnd = accelerometer_z;
   // Here we determine the difference between the new values and the former ones
   xValue = xPosEnd - xPosBeg;
   yValue = yPosEnd - yPosBeg;
   zValue = zPosEnd - zPosBeg;
   
   // Then we convert the values into angles
   
   xAngleValue = xValue/182;
   yAngleValue = yValue/182;
   zAngleValue = zValue/182;

   // Some more outputs intended for testing
   /*
   Serial.print("new value of x = ");
   Serial.print(convert_int16_to_str(xPosEnd));
   Serial.print("   ");
   Serial.print("differential value of x = ");
   Serial.print(convert_int16_to_str(yValue));
   Serial.print("new value of y = ");
   Serial.print(convert_int16_to_str(yPosEnd));
   Serial.print("   ");
   Serial.print("differential value of y = ");
   Serial.print(convert_int16_to_str(yValue));
   Serial.print("new value of z = ");
   Serial.print(convert_int16_to_str(zPosEnd));
   Serial.print("   ");
   Serial.print("differential value of y = ");
   Serial.print(convert_int16_to_str(zValue));
   Serial.println();
   */

   // Ensures the program returns a positive value;
  if (xAngleValue <0){
    xAngleValue = 0-xAngleValue;
  }
  else {
    }
   if (yAngleValue <0){
    yAngleValue = 0-yAngleValue;
  }
  else {
    }
   if (zAngleValue <0){
    zAngleValue = 0-zAngleValue;
  }
  else {
    };
    
    /*
    Serial.print("x angle = ");
    Serial.print(xAngleValue);
    Serial.print(" y angle = ");
    Serial.print(yAngleValue);
    Serial.print(" z angle = ");
    Serial.print(zAngleValue);
    Serial.println();
    */
   //Defines the distance traveled by the tip of the sword on each axis with Pythagorus theometer
  xD = (xAngleValue/180)*swordLength;
  yD = (yAngleValue/180)*swordLength;
  zD = (zAngleValue/180)*swordLength;
  TotalD = sqrt(sq(xD)+sq(yD));
  TotalD = sqrt(sq(TotalD)+sq(zD));
  /*Serial.print(TotalD);
  Serial.println();*/
  
  //Determines if the hit is strong enough to be noticed.
  if (TotalD > Min){
    cinEnr = sq(TotalD*(1000/t));
    cinEnr = (cinEnr/2)*swordWeight;
    Serial.print("Cinetical energy of the hit was "); Serial.print(cinEnr); Serial.print(" Jouls.");
    Serial.println();
  }
  
   
  }

/*
void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers

  for (int i = 0; i <= 1; i++) {
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accelerometer_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_x = accelerometer_x/256;
  accelerometer_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_y = accelerometer_y/256;
  accelerometer_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  accelerometer_z = accelerometer_z/256;
  temperature = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  gyro_x = Wire.read()<<8 | Wire.read();// reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_x = gyro_x/256;
  //Serial.print(convert_int16_to_str(gyro_x));
  gyro_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_y = gyro_y/256;
  //Serial.print(convert_int16_to_str(gyro_y));
  gyro_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)
  gyro_z = gyro_z/256;
  //Serial.print(convert_int16_to_str(gyro_z));
  //Serial.println();

  // measuring the difference in the position of the blade every 0.1 seconds
  
  xPosBeg = accelerometer_x;
  Serial.print(convert_int16_to_str(xPosBeg));
  yPosBeg = accelerometer_y;
  //Serial.print(convert_int16_to_str(yPosBeg));
  delay(t);
  }
  xPosEnd = accelerometer_x;
  Serial.print(convert_int16_to_str(xPosEnd));
  yPosEnd = accelerometer_y;
  //Serial.print(convert_int16_to_str(yPosEnd));

  xValue = xPosBeg - xPosEnd;
  Serial.print(convert_int16_to_str(xValue));
  yValue = yPosBeg - yPosEnd;
  //Serial.print(convert_int16_to_str(yValue));

  // ensures the program returns a positive value;
  if (xValue <0){
    xValue = 0-xValue;
  }
  else {
    }
   if (yValue <0){
    yValue = 0-yValue;
  }
  else {
    };

  //Defines the distance traveled by the tip of the sword on each axis
  xD = (xValue*180)/swordLength;
  yD = (yValue*180)/swordLength;
  TotalD = sqrt(sq(xD)+sq(yD));

  //Determines if the hit is strong enough to be noticed.
  if (TotalD < Min){
    cinEnr = (1/2)*swordWeight*sq(TotalD*(1000/t));
    Serial.print("Cinetical energy of the hit was "); Serial.print(convert_int16_to_str(cinEnr)); Serial.print(" Jouls.");
    //return(cinEnr);
  }


  
  // print out data
  Serial.print("aX = "); Serial.print(convert_int16_to_str(accelerometer_x));
  Serial.print(" | aY = "); Serial.print(convert_int16_to_str(accelerometer_y));
  Serial.print(" | aZ = "); Serial.print(convert_int16_to_str(accelerometer_z));
  // the following equation was taken from the documentation [MPU-6000/MPU-6050 Register Map and Description, p.30]
 // Serial.print(" | tmp = "); Serial.print(temperature/340.00+36.53);
  Serial.print(" | gX = "); Serial.print(convert_int16_to_str(gyro_x));
  Serial.print(" | gY = "); Serial.print(convert_int16_to_str(gyro_y));
  Serial.print(" | gZ = "); Serial.print(convert_int16_to_str(gyro_z));
  Serial.println();
  
  
  // delay
 // delay(1000);
}
*/
