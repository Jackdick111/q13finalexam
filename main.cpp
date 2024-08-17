/*
part of the MTU COMP71004 module
author: Krishna Panduru

the program here performs a serial passthrough operation between USB and serial (p9, p10). 
correct upto 5 errors for proper functionality. 
the 6th error is a runtime error generating the following error. correct that as well.

++ MbedOS Error Info ++ 
Error Status: 0x80010130 Code: 304 Module: 1 
Error Message: pinmap not found for peripheral 
Location: 0x4353 Error Value: 0xFFFFFFFF
*/
#include "mbed.h"


DigitalOut myled(LED1);
BufferedSerial pc(USBTX, USBRX);
BufferedSerial dev(D1, D0);      

void dev_recv() {
    while (dev.readable()) {
        char c;
        dev.read(&c, 1);
        pc.write(&c, 1);
    }    
}

void pc_recv() {
    while (pc.readable()) {
        char c;
        pc.read(&c, 1);
        dev.write(&c, 1);
    }    
}

int main() {
    pc.set_baud(9600);
    dev.set_baud(115200);
     pc.sigio(callback(pc_recv));
    dev.sigio(callback(dev_recv));
    
    pc.write("Hello!! \r\n" ,10);
    
    while(1) {
        myled = 1;
       
         ThisThread::sleep_for(1s); 
        myled = 0;
        ThisThread::sleep_for(1s); 
    }
}
