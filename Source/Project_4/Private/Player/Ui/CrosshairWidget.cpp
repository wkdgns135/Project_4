// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Ui/CrosshairWidget.h"

void UCrosshairWidget::UpdateCrosshair(float Speed, float FireRate, float Recoil)
{
    if (!LineTop || !LineBottom || !LineLeft || !LineRight)
        return;

    // ��ġ ��� (������ Speed, FireRate, Recoil ���� ������� ����)
    float Offset = FMath::Clamp(Speed * 0.1f + FireRate * 0.2f + Recoil * 5.0f, 0.0f, 50.0f);

    // �� ������ ��ġ ����
    LineTop->SetRenderTranslation(FVector2D(0, -Offset));
    LineBottom->SetRenderTranslation(FVector2D(0, Offset));
    LineLeft->SetRenderTranslation(FVector2D(-Offset, 0));
    LineRight->SetRenderTranslation(FVector2D(Offset, 0));
}