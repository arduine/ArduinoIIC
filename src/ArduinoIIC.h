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

#ifndef __ARDUINO_IIC_H
#define __ARDUINO_IIC_H

#include <Arduino.h>

class ArduinoIIC {

public:
    /**
     * 设置接口电位
     * @param state true表示高电平
     * @since 1.0.0
     */
    typedef void(*WriteCallback)(bool state);

    /**
     * 读取接口电位
     * @return true表示高电平
     * @since 1.0.0
     */
    typedef bool (*ReadCallback)();

public:
    /**
     * 普通IO口初始化
     * @param ioCLK CLK接口
     * @param ioDIO DIO接口
     * @param delay 默认延时
     * @since 1.0.0
     */
    ArduinoIIC(uint8_t ioCLK, uint8_t ioDIO, uint8_t delay = 2);

    /**
     * 进阶使用
     * 可使用此接口在拓展板实现IIC协议
     *
     * @param ioWriteCLK    写入CLK接口
     * @param ioWriteDIO    写入DIO接口
     * @param ioReadDIO     读取DIO接口状态
     * @param delay         默认延时
     * @since 1.0.0
     */
    ArduinoIIC(WriteCallback ioWriteCLK, WriteCallback ioWriteDIO, ReadCallback ioReadDIO, uint8_t delay = 2);

public:
    /**
     * 初始化设置
     * @since 1.0.0
     */
    void begin() const;

    /**
     * 开始传输
     * @since 1.0.0
     */
    void beginTransmission() const;

    /**
     * 结束传输
     * @since 1.0.0
     */
    void endTransmission() const;

    /**
     * 发送数据
     * @param value 数据
     * @return 1表示成功
     * @since 1.0.0
     */
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
