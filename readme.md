# STM32 サーボ・モーター制御クラス

- STM32でのPWM出力は、Arduinoライブラリと比較して複雑なセットアップをする必要があります

- このライブラリでは、サーボの角度[deg]やモーターの速度[%]を指定するだけで、PWM信号を生成できるように設計されています

## 1. PWMのセットアップ

- STM32CubeIDEやSTM32CubeMXを使用して、PWM出力用のタイマーとチャネルを設定してください
- タイマーのクロック周波数とプリスケーラーを設定し、PWMの周波数を決定します
  - 一般的なサーボモーターでは50Hz（20ms周期）が使用されます
  - 適切に値を設定して50HzのPWM信号を生成できるようにしてください

## モーターの動かし方

- printf()を有効化するか、UARTに変更して利用してください

- ESC逆進機能を使用する場合は、コンストラクタで設定してください

- ESCへの電源投入時にsetSpeed()メソッドで0%を送信し、ESCの初期化を完了させてください

```cpp
#include "wrapper.hpp"
#include "tim.h"
#include "stdio.h"
#include "motor_controller.hpp"

// グローバルモーターコントローラーポインタ
MotorController* motor_controller = nullptr;

void init(){

    // インスタンスの作成
    motor_controller = new MotorController(&htim1, TIM_CHANNEL_1, MotorMode::NORMAL);

    // 初期化の確認
    if (motor_controller->isInitialized()) {

        printf("MotorController (NORMAL mode) initialized successfully\n");
    }
    else {

        printf("MotorController initialization failed\n");
    }

    // パルス幅の範囲を設定（1000us ~ 2000us）
    motor_controller->setPulseRange(1000, 2000);
    printf("Pulse range set to 1000us ~ 2000us\n");

    // 0%に設定（初期値を送信）
    motor_controller->setSpeed(0.0f);
    printf("Motor speed: 0 %%\n");
    HAL_Delay(10000);
}

void loop(){

    // 25%に設定
    motor_controller->setSpeed(25.0f);
    printf("Motor speed: 25 %%\n");
    HAL_Delay(5000);

    // 50%に設定
    motor_controller->setSpeed(50.0f);
    printf("Motor speed: 50 %%\n");
    HAL_Delay(5000);

    // モーターを停止
    motor_controller->stop();
    printf("Motor stopped\n");
    HAL_Delay(5000);

	printf("All Tests Completed\n");
	while(1);
}
```


## サーボの動かし方

- printf()を有効化するか、UARTに変更して利用してください

- setAngle()メソッドで角度を指定して動かします

```cpp
#include "wrapper.hpp"
#include "tim.h"
#include "stdio.h"
#include "servo_controller.hpp"

// グローバルサーボコントローラーポインタ
ServoController* servo_controller = nullptr;

void init(){

    // インスタンスの作成
    servo_controller = new ServoController(&htim1, TIM_CHANNEL_1);

    // 初期化の確認
    if (servo_controller->isInitialized()) {

        printf("ServoController initialized successfully\n");
    } 
    else {

        printf("ServoController initialization failed\n");
    }

    // パルス幅を定義（サーボモーターに合わせて調整）
    servo_controller->setPulseRange(500, 2400);
    printf("Pulse range set to 500us ~ 2400us\n");

    HAL_Delay(500);
}

void loop(){

    // -90度に設定
    servo_controller->setAngle(-90.0f);
    printf("Angle: -90 deg\n");
    HAL_Delay(1000);

    // 中立位置（0度）に設定
    servo_controller->neutral();
    printf("Angle: 0 deg (neutral)\n");
    HAL_Delay(1000);

    // +90度に設定
    servo_controller->setAngle(90.0f);
    printf("Angle: +90 deg\n");
    HAL_Delay(1000);
}
```
