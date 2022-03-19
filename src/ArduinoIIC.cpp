/*
 * Copyright (C) 2022. sollyu
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ArduinoIIC.h"

ArduinoIIC::ArduinoIIC(uint8_t ioCLK, uint8_t ioDIO, uint8_t delay) :
        mIoCLK(ioCLK), mIoDIO(ioDIO), mDelay(delay),
        mWriteCallbackCLK(nullptr), mWriteCallbackDIO(nullptr), mReadCallbackDIO(nullptr) {}

ArduinoIIC::ArduinoIIC(ArduinoIIC::WriteCallback ioWriteCLK, ArduinoIIC::WriteCallback ioWriteDIO, ReadCallback ioReadDIO, uint8_t delay) :
        mIoCLK(0xFF), mIoDIO(0xFF), mDelay(delay),
        mWriteCallbackCLK(ioWriteCLK), mWriteCallbackDIO(ioWriteDIO), mReadCallbackDIO(ioReadDIO) {}

void ArduinoIIC::begin() const {
    if (mIoDIO != 0xFF) {
        pinMode(mIoCLK, OUTPUT);
        pinMode(mIoDIO, OUTPUT);
    }
    digitalWriteCLK(false);
    digitalWriteDIO(false);
}

void ArduinoIIC::beginTransmission() const {
    digitalWriteCLK(true);
    digitalWriteDIO(true);
    delayMicroseconds(mDelay);
    digitalWriteDIO(false);
}

void ArduinoIIC::endTransmission() const {
    digitalWriteCLK(false);
    digitalWriteDIO(false);
    digitalWriteCLK(true);
    delayMicroseconds(mDelay);
    digitalWriteDIO(true);
}

uint8_t ArduinoIIC::send(uint8_t value) const {
    uint8_t      ACK;
    for (uint8_t i = 0; i < 8; ++i) {
        digitalWriteCLK(false);
        digitalWriteDIO(value & 0x01);
        delayMicroseconds(mDelay);
        digitalWriteCLK(true);
        delayMicroseconds(mDelay);
        value >>= 1u;
    }
    digitalWriteCLK(false);
    digitalWriteDIO(true);
    digitalWriteCLK(true);
    if (mIoDIO != 0xFF)
        pinMode(mIoDIO, INPUT);

    if ((ACK = digitalReadDIO()) == 0) {
        if (mIoDIO != 0xFF)
            pinMode(mIoDIO, INPUT);
        digitalWriteDIO(false);
    }
    if (mIoDIO != 0xFF)
        pinMode(mIoDIO, OUTPUT);
    return ACK;
}

void ArduinoIIC::digitalWriteCLK(bool state) const {
    if (mIoCLK != 0xFF)
        digitalWrite(mIoCLK, state ? HIGH : LOW);
    else
        mWriteCallbackCLK(state);
}

void ArduinoIIC::digitalWriteDIO(bool state) const {
    if (mIoDIO != 0xFF)
        digitalWrite(mIoDIO, state ? HIGH : LOW);
    else
        mWriteCallbackDIO(state);
}

bool ArduinoIIC::digitalReadDIO() const {
    if (mIoDIO != 0xFF) {
        return digitalRead(mIoDIO);
    } else {
        return mReadCallbackDIO();
    }
}


