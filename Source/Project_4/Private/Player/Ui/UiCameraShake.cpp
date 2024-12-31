// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Ui/UiCameraShake.h"

UUiCameraShake::UUiCameraShake() {
    // 카메라 쉐이크 설정
    OscillationDuration = 0.1f;
    OscillationBlendInTime = 0.05f;
    OscillationBlendOutTime = 0.05f;

    RotOscillation.Pitch.Amplitude = 1.0f;
    RotOscillation.Pitch.Frequency = 25.0f;

    RotOscillation.Yaw.Amplitude = 1.0f;
    RotOscillation.Yaw.Frequency = 25.0f;
}