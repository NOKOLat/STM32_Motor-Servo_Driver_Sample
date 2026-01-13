#include "wrapper.hpp"
#include "tim.h"
#include "stdio.h"
#include <optional>
#include "servo_controller.hpp"

// グローバルサーボコントローラーインスタンス
std::optional<ServoController> servo_controller;

void init(){

    // サーボコントローラーを初期化
    servo_controller.emplace(&htim1, TIM_CHANNEL_1);

    // 初期化の確認
    if (servo_controller->isInitialized()) {

        printf("ServoController initialized successfully\n");
    } 
    else {

        printf("ServoController initialization failed\n");
    }

    servo_controller->setPulseRange(500, 2400);

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
