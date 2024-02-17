// How many bytes this program will receive from serial ("X\n")
#define BYTE_LEN 2

// Libraries
#include <SerialPort.hpp>
#include <SerialPort.cpp>
#include <iostream>

using namespace std;

// Communication port 3
const char *com_port = "\\\\.\\COM3";

// Arduino object
SerialPort *arduino;

int main(){
    // Char array to store the incoming data
    char received_data[BYTE_LEN];

    // Establish connection on COM3
    arduino = new SerialPort(com_port);
    
    // Start loop 'til disconnect
    while(arduino->isConnected()){
        if(arduino->readSerialPort(received_data, BYTE_LEN)){
            cout << received_data[0];
        }
    }
    
    // In case of electrical kaboom :)
    arduino->closeSerial(); 
    cerr << "Arduino disconnected!";
    return 0;
}