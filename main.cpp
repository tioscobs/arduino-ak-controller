// How many bytes this program will receive from serial ("X\n")
#define BYTE_LEN 2

// Libraries
#include <SerialPort.hpp>
#include <SerialPort.cpp>
#include <iostream>
#include <windows.h>

using namespace std;

// Communication port 3
const char *com_port = "\\\\.\\COM3";

// Arduino object
SerialPort *arduino;

// Mouse util functions
void mouse_click(INPUT &inp){
    inp.type = INPUT_MOUSE;
    inp.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &inp, sizeof(inp));
    Sleep(50);
    ZeroMemory(&inp, sizeof(inp));  
    inp.type = INPUT_MOUSE;
    inp.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &inp, sizeof(inp));
}

void mouse_hold(INPUT &inp, bool holding){
    inp.type = INPUT_MOUSE;
    inp.mi.dwFlags = holding ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_LEFTUP;
    SendInput(1, &inp, sizeof(inp));
    ZeroMemory(&inp, sizeof(inp));  
}

// Main function
int main(){
    // Char array to store the incoming data
    char received_data[BYTE_LEN];

    INPUT input = {0};

    // Establish connection on COM3
    arduino = new SerialPort(com_port);
    
    // Start loop 'til disconnect
    while(arduino->isConnected()){
        if(arduino->readSerialPort(received_data, BYTE_LEN)){
            cout << received_data[0] << endl;
            switch (received_data[0]){
                case '1':
                    mouse_click(input);
                    break;
                case '2':
                    mouse_hold(input, true);
                    break;
                case '0':
                    mouse_hold(input, false);
                    break;
            }
        }
    }
    
    // In case of electrical kaboom :)
    arduino->closeSerial(); 
    cerr << "Arduino disconnected!";
    return 0;
}