# Arduino IIC
一个将Arduino普通IO口模拟IIC协议。

## 导入

#### PlatformIO

```ini
; Library options
lib_deps =
    https://github.com/arduine/ArduinoIIC.git#main
```

#### ArduinoIDE

```c++
// TODO
```

## 使用

1. 增加头文件导入：

```c++
#include <ArduinoIIC.h>
```

2. 编写代码

```c++
const ArduinoIIC sArduinoIIC(DD2, DD3);

void setup() {
    sArduinoIIC.begin();
}

void onTestButton() {
    mArduinoIIC.beginTransmission();
    mArduinoIIC.send(0b00000111);
    mArduinoIIC.endTransmission();
}
```

## 进阶

如果想在拓展板上使用IIC协议，可使用进阶的构造函数，这里举个例子：

```c++
// 写了半天发现怎么写都不直观
// 反正就是支持拓展板的IO口模拟IIC协议
```
## LICENSE

```c++
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
```
