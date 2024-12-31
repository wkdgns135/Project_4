// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Ui/CrosshairWidget.h"

void UCrosshairWidget::UpdateCrosshairSize(float Speed)
{
    if (!LineTop || !LineBottom || !LineLeft || !LineRight)
        return;

    // 위치 계산 (간격은 Speed, FireRate, Recoil 값을 기반으로 설정)
    float Offset = FMath::Clamp(Speed * 0.1f, 0, 50.0f);

    // 각 라인의 위치 조정
    LineTop->SetRenderTranslation(FVector2D(0, -Offset));
    LineBottom->SetRenderTranslation(FVector2D(0, Offset));
    LineLeft->SetRenderTranslation(FVector2D(-Offset, 0));
    LineRight->SetRenderTranslation(FVector2D(Offset, 0));
}