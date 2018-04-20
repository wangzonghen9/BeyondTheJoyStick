#include<Wire.h>
const int MPU2=0x69,MPU1=0x68;
int16_t AcX1,AcY1,AcZ1,Tmp1,GyX1,GyY1,GyZ1;
int16_t AcX2,AcY2,AcZ2,Tmp2,GyX2,GyY2,GyZ2;

 
void setup(){ 
      Wire.begin(); 
      Wire.beginTransmission(MPU1);
      Wire.write(0x6B);// PWR_MGMT_1 register 
      Wire.write(0); // set to zero (wakes up the MPU-6050)
      Wire.endTransmission(true);Wire.begin(); 
      Wire.beginTransmission(MPU2);
      Wire.write(0x6B);// PWR_MGMT_1 register 
      Wire.write(0); // set to zero (wakes up the MPU-6050)
      Wire.endTransmission(true);
      Serial.begin(9600); 
} 
     
 void loop(){
      //get values for first mpu having address of 0x68   
      GetMpuValue1(MPU1);
      Serial.print("  ");
      Serial.print("|||");
      
      //get values for second mpu having address of 0x69
      GetMpuValue2(MPU2);
      Serial.println("");
      delay(500);
}


void GetMpuValue1(const int MPU){ 
    Wire.beginTransmission(MPU); 
    Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) 
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 14, true); // request a total of 14 registers 
    AcX1=Wire.read()<<8| Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L) 
    AcY1=Wire.read()<<8|  Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    AcZ1=Wire.read()<<8| Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L) 
    Tmp1=Wire.read()<<8| Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L) 
    GyX1=Wire.read()<<8| Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L) 
    GyY1=Wire.read()<<8| Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L) 
    GyZ1=Wire.read()<<8| Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L) 
    Serial.print("AcX1 = ");
    Serial.print(AcX1);
    Serial.print(" | AcY1 = "); 
    Serial.print(AcY1);
    Serial.print(" | AcZ1 = ");
    Serial.print(AcZ1); 
    Serial.print(" | GyX1 = ");
    Serial.print(GyX1); 
    Serial.print(" | GyY1 = "); 
    Serial.print(GyY1);
    Serial.print(" | GyZ1 = ");
    Serial.println(GyZ1); 
}

void GetMpuValue2(const int MPU){ 
    Wire.beginTransmission(MPU); 
    Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) 
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 14, true); // request a total of 14 registers 
    AcX2=Wire.read()<<8| Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L) 
    AcY2=Wire.read()<<8|  Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    AcZ2=Wire.read()<<8| Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L) 
    Tmp2=Wire.read()<<8| Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L) 
    GyX2=Wire.read()<<8| Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L) 
    GyY2=Wire.read()<<8| Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L) 
    GyZ2=Wire.read()<<8| Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L) 
    Serial.print("AcX2 = ");
    Serial.print(AcX2);
    Serial.print(" | AcY2 = "); 
    Serial.print(AcY2);
    Serial.print(" | AcZ2 = ");
    Serial.print(AcZ2);  
    Serial.print(" | GyX2 = ");
    Serial.print(GyX2); 
    Serial.print(" | GyY2 = "); 
    Serial.print(GyY2);
    Serial.print(" | GyZ2 = ");
    Serial.println(GyZ2); 
}



//#include<Wire.h>
//const int MPU_addr=0x68;  // I2C address of the MPU-6050
//int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
//void setup(){
//  Wire.begin();
//  Wire.beginTransmission(MPU_addr);
//  Wire.write(0x6B);  // PWR_MGMT_1 register
//  Wire.write(0);     // set to zero (wakes up the MPU-6050)
//  Wire.endTransmission(true);
//  Serial.begin(9600);
//}
//void loop(){
//  Wire.beginTransmission(MPU_addr);
//  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
//  Wire.endTransmission(false);
//  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
//  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
//  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
//  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
//  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
//  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
//  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
//  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
//  //Serial.print("AcX = "); Serial.print(AcX);
//  //Serial.print(" | AcY = "); Serial.print(AcY);
//  //Serial.print(" | AcZ = "); Serial.print(AcZ);
//  //Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
//  Serial.print(" | GyX = "); Serial.print(GyX);
//  Serial.print(" | GyY = "); Serial.print(GyY);
//  Serial.print(" | GyZ = "); Serial.println(GyZ);
//  delay(333);
//}
