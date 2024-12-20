#include "king_armin_AX12.h"
void AX12::Init(){
    varSerial->begin(BoundRated);
}
void AX12::LED(int id , int value){
    byte checksum = ~(id + 4 + 3 +0x19+value);
    varSerial->write(0xFF);
    varSerial->write(0xFF);
    varSerial->write(id);
    varSerial->write(4);
    varSerial->write(3);
    varSerial->write(0x19);
    varSerial->write(value);
    varSerial->write(checksum);
}

void AX12::set_speed(int id,int speed){
	setWheelMode(id);
    byte checksum = ~(id + 5 + 3+ 32 +(speed & 0xFF)+((speed >> 8)& 0xFF));
    varSerial->write(0xFF);
    varSerial->write(0xFF);
    varSerial->write(id);
    varSerial->write(5);
    varSerial->write(3);
    varSerial->write(32);
    varSerial->write(speed & 0xFF);
    varSerial->write(((speed >> 8)& 0xFF));
    varSerial->write(checksum);
}
void AX12::setAngleLimit(int id, int cwLimit, int ccwLimit) {
        byte length = 7; // Length of the packet excluding the 0xFF 0xFF header
    byte instruction = 0x03; // Write instruction
    byte cwLowByte = cwLimit & 0xFF;
    byte cwHighByte = (cwLimit >> 8) & 0xFF;
    byte ccwLowByte = ccwLimit & 0xFF;
    byte ccwHighByte = (ccwLimit >> 8) & 0xFF;
        
        // Calculate checksum
    byte checksum = ~(id + length + instruction + 0x06 + cwLowByte + cwHighByte + ccwLowByte + ccwHighByte);
        
        // Send the packet to set CW Angle Limit
    varSerial->write(0xFF);
    varSerial->write(0xFF);
    varSerial->write(id);
    varSerial->write(length);
    varSerial->write(instruction);
    varSerial->write(0x06); // CW Angle Limit address
    varSerial->write(cwLowByte);
    varSerial->write(cwHighByte);
    varSerial->write(ccwLowByte); // CCW Angle Limit address
    varSerial->write(ccwHighByte);
    varSerial->write(checksum);
}

void AX12::setWheelMode(int id) {
    setAngleLimit(id, 0, 0); // Set both CW and CCW Angle Limit to 0
}

void AX12::setJointMode(int id, int cwLimit, int ccwLimit) {
    setAngleLimit(id, cwLimit, ccwLimit); // Set CW and CCW Angle Limits to appropriate values
}
void AX12::set_degree(int id, int degree, int speed) {
        // Ensure the servo is in joint mode
        setJointMode(id, 0, 1023); // Example: CW Limit=0, CCW Limit=1023
        delay(100); // Short delay to ensure the mode is set
        // Set the position
        byte length = 7; // Length of the packet excluding the 0xFF 0xFF header
        byte instruction = 0x03; // Write instruction
        byte address = 0x1E; // Goal Position address
        byte degreeLow = degree & 0xFF;
        byte degreeHigh = (degree >> 8) & 0xFF;
        byte speedLow = speed & 0xFF;
        byte speedHigh = (speed >> 8) & 0xFF;
        
        // Calculate checksum
        byte checksum = ~(id + length + instruction + address + degreeLow + degreeHigh + speedLow + speedHigh);

        // Send the packet to set the goal position
        varSerial->write(0xFF);
        varSerial->write(0xFF);
        varSerial->write(id);
        varSerial->write(length);
        varSerial->write(instruction);
        varSerial->write(address);
        varSerial->write(degreeLow);
        varSerial->write(degreeHigh);
        varSerial->write(speedLow);
        varSerial->write(speedHigh);
        varSerial->write(checksum);
}
void AX12::torque(int id,int Value) {
        byte length = 4; // Length of the packet excluding the 0xFF 0xFF header
        byte instruction = 0x03; // Write instruction
        byte address = 0x18; // Torque Enable address
        byte value = Value; // Value to enable torque
        byte checksum = ~(id + length + instruction + address + value);
        
        // Send the packet to enable torque
        varSerial->write(0xFF);
        varSerial->write(0xFF);
        varSerial->write(id);
        varSerial->write(length);
        varSerial->write(instruction);
        varSerial->write(address);
        varSerial->write(value);
        varSerial->write(checksum);
}