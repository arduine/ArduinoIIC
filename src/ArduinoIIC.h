//
// Created by KingS on 2022/3/19.
//

#ifndef __ARDUINO_IIC_H
#define __ARDUINO_IIC_H

#include <Arduino.h>

class ArduinoIIC {

public:
    typedef void(*WriteCallback)(bool state);

    typedef bool (*ReadCallback)();

public:
    ArduinoIIC(uint8_t ioCLK, uint8_t ioDIO, uint8_t delay = 2);

    ArduinoIIC(WriteCallback ioWriteCLK, WriteCallback ioWriteDIO, ReadCallback ioReadDIO, uint8_t delay = 2);

public:
    void begin() const;

    void beginTransmission() const;

    void endTransmission() const;

    uint8_t send(uint8_t value) const;

private:
    const uint8_t mIoCLK, mIoDIO, mDelay;
    const WriteCallback mWriteCallbackCLK, mWriteCallbackDIO;
    const ReadCallback mReadCallbackDIO;

private:
    void digitalWriteCLK(bool state) const;

    void digitalWriteDIO(bool state) const;

    bool digitalReadDIO() const;
};


#endif //__ARDUINO_IIC_H
