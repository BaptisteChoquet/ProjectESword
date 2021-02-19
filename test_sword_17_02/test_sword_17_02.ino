// (c) Michael Schoeffler 2017, http://www.mschoeffler.de

#include "Wire.h" // This library allows you to communicate with I2C devices.

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

const float swordLength = 1; // the length of the blade of the sword expressed in meters.
const int swordWeight = 800; // the weight of the blade expressed in grams
const int t = 100; // duration of a time unit, in milliseconds.
const int Min = 1; // minimum speed of the blade for the calcul to be executed.


int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t temperature; // variables for temperature data
int16_t xPosBeg, yPosBeg, xPosEnd, yposEnd, xValue, yValue; // variables relating to the evolution of the sword angle between two time units
int16_t xD, yD, TotalD; // variable relating to the distance crossed by the tip of the blade between two time units
int16_t cinEnr; // variable corresponding to the cinetical energy of the hit

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
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}
void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accelerometer_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  temperature = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  gyro_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)

  // measuring the difference in the position of the blade every 0.1 seconds
  xPosBeg = accelerometer_x;
  yPosBeg = accelerometer_y;
  delay(100);
  xPosEnd = accelerometer_x;
  yPosEnd = accelerometer_y;

  xValue = xPosBeg - xPosEnd;
  yValue = yPosBeg - yPosEnd;

  // ensures the program returns a positive value;
  if (xValue <0){
    xValue = xValue/1;
  }
  else {
    }
   if (yValue <0){
    yValue = yValue/1;
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
    Serial.print("Cinetical energy of the hit was "); Serial.print(convert_int16_to_str(cieEnr)); Serial.print(" Jouls.");
    return(cieEnr);
  }


  
  // print out data
 // Serial.print("aX = "); Serial.print(convert_int16_to_str(accelerometer_x));
 // Serial.print(" | aY = "); Serial.print(convert_int16_to_str(accelerometer_y));
 // Serial.print(" | aZ = "); Serial.print(convert_int16_to_str(accelerometer_z));
  // the following equation was taken from the documentation [MPU-6000/MPU-6050 Register Map and Description, p.30]
 // Serial.print(" | tmp = "); Serial.print(temperature/340.00+36.53);
 // Serial.print(" | gX = "); Serial.print(convert_int16_to_str(gyro_x));
 // Serial.print(" | gY = "); Serial.print(convert_int16_to_str(gyro_y));
 // Serial.print(" | gZ = "); Serial.print(convert_int16_to_str(gyro_z));
 // Serial.println();
  
  // delay
 // delay(1000);
}
