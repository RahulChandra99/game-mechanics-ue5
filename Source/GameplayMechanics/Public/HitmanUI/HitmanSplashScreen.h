// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HitmanSplashScreen.generated.h"

/**
 * 
 */
class UCanvasPanel;
class UImage;
class UHorizontalBox;
class UTextBlock;
class UBorder;
class UButton;

UCLASS()
class GAMEPLAYMECHANICS_API UHitmanSplashScreen : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget)) UCanvasPanel* CanvasPanelMain;
	UPROPERTY(meta=(BindWidget)) UImage* BackgroundImg;
	UPROPERTY(meta=(BindWidget)) UHorizontalBox* TitleHB;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TitleFrontTB;
	UPROPERTY(meta=(BindWidget)) UBorder* SeperatorBorder;
	UPROPERTY(meta=(BindWidget)) UTextBlock* TitleRearTB;
	UPROPERTY(meta=(BindWidget)) UCanvasPanel* CanvasPanelBottomBar;
	UPROPERTY(meta=(BindWidget)) UBorder* BottomBorder;
	UPROPERTY(meta=(BindWidget)) UHorizontalBox* NextButtonContainerHB;
	UPROPERTY(meta=(BindWidget)) UTextBlock* ContinueTB;
	UPROPERTY(meta=(BindWidget)) UButton* NextBtn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	class UAudioComponent* BackgroundMusicAC;

	UFUNCTION()
	void NextBtnClicked();

public:
	UHitmanSplashScreen();	
};
