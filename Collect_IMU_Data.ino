/*
 *  Gain data from GY-85 which contains the following:
 * 
 *  ADXL345 Accelerometer
 *  ITG3205 Gyroscope and temperature sensor
 *  HMC58X3 Magnetometer
 *  
 *  Libraries that have been used are open source, see
 *  header files for more information. 
 *
 *  @Author Rahul Pathak
 */

#include <Wire.h>
#include <HMC58X3.h>
#include <ADXL345.h>
#include <ITG3200.h>

HMC58X3 magn;
ADXL345 Accel;
ITG3200 gyro = ITG3200();

int packet = 0;     //Keep track of lost data
float fx,fy,fz;     //Magnetometer Variables
float acc_data[3];  //Acceleration Data Variables
float ix, iy, iz;   //Gyroscope data variables
float temperature;  //Gyroscope has Temperature variable


void setup(void) {
  //Setup I2C
  Serial.begin(9600);
  Wire.begin();

  //Setup Accelerometer
  Accel.init(ADXL345_ADDR_ALT_LOW);
  Accel.set_bw(ADXL345_BW_12);
  
  //setup Gyro
  gyro.init(ITG3200_ADDR_AD0_LOW); 
  gyro.zeroCalibrate(2500, 2);
  
  //Setup Magnetometer
  magn.init(false); 
  magn.calibrate(1, 32); 
  magn.setMode(0);
}

void loop() { 
  
  Serial.print(packet);
  Serial.print(" "); 
  //Accelerometer in G's
  Accel.get_Gxyz(acc_data);
    if(Accel.status){
      Serial.print(acc_data[0]);
      Serial.print(" ");
      Serial.print(acc_data[1]);
      Serial.print(" ");
      Serial.print(acc_data[2]);
      Serial.print(" ");
    } else{
      Serial.println("ERROR: ADXL345");
    }

  // Gyroscope Data in deg/Sec. Temperature also available.
  if(gyro.isRawDataReady()){
    gyro.readTemp(&temperature);
    gyro.readGyro(&ix,&iy,&iz);
    Serial.print(ix);
    Serial.print(" ");
    Serial.print(iy);
    Serial.print(" ");
    Serial.print(iz);
    Serial.print(" ");
   // Serial.println(temperature);
  } else{
    Serial.println("ERROR: ITG3200");
  }
  
  //Magnetometer x,y,z
  magn.getValues(&fx,&fy,&fz);
  Serial.print(fx);
  Serial.print(" ");
  Serial.print(fy);
  Serial.print(" ");
  Serial.println(fz);
  packet++;
}

