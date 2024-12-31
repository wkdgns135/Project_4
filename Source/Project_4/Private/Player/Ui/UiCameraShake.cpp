// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Ui/UiCameraShake.h"

UUiCameraShake::UUiCameraShake() {
    // 카메라 쉐이크 설정
    OscillationDuration = 0.25f;
    OscillationBlendInTime = 0.05f;
    OscillationBlendOutTime = 0.05f;

    RotOscillation.Pitch.Amplitude = FMath::RandRange(1.0f, 2.0f);
    RotOscillation.Pitch.Frequency = FMath::RandRange(25.0f, 35.0f);

    RotOscillation.Yaw.Amplitude = FMath::RandRange(1.0f, 2.0f);
    RotOscillation.Yaw.Frequency = FMath::RandRange(25.0f, 35.0f);
}