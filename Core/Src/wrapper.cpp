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

    // 10%に設定
    motor_controller->setSpeed(10.0f);
    printf("Motor speed: 10 %%\n");
    HAL_Delay(5000);

    // 20%に設定
    motor_controller->setSpeed(20.0f);
    printf("Motor speed: 20 %%\n");
    HAL_Delay(5000);

    // 30%に設定
    motor_controller->setSpeed(30.0f);
    printf("Motor speed: 30 %%\n");
    HAL_Delay(5000);

    // 40%に設定
    motor_controller->setSpeed(40.0f);
    printf("Motor speed: 40 %%\n");
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
