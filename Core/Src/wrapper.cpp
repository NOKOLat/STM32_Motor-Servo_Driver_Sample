#include "wrapper.hpp"
#include "tim.h"
#include "stdio.h"
#include <optional>
#include "motor_controller.hpp"

// グローバルモーターコントローラーインスタンス
std::optional<MotorController> motor_controller;

void init(){

    // モーターコントローラーを初期化（通常モード）
    motor_controller.emplace(&htim1, TIM_CHANNEL_1, MotorMode::NORMAL);

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

    HAL_Delay(500);
}

void loop(){

    // 0%に設定
    motor_controller->setSpeed(0.0f);
    printf("Motor speed: 0 %%\n");
    HAL_Delay(5000);

    // 50%に設定
    motor_controller->setSpeed(50.0f);
    printf("Motor speed: 50 %%\n");
    HAL_Delay(5000);

    // 100%に設定
    motor_controller->setSpeed(100.0f);
    printf("Motor speed: 100 %%\n");
    HAL_Delay(5000);

    // モーターを停止
    motor_controller->stop();
    printf("Motor stopped\n");
    HAL_Delay(5000);
}
