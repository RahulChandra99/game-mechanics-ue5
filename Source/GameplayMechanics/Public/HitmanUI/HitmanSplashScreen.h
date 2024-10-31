#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HitmanSplashScreen.generated.h"

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
	// Bind Widget properties
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

	// Button click function
	UFUNCTION()
	void NextBtnClicked();

	// Override NativeConstruct
	virtual void NativeConstruct() override;
};
