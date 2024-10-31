#include "HitmanUI/HitmanSplashScreen.h"
#include "Components/Button.h"

void UHitmanSplashScreen::NativeConstruct()
{
	Super::NativeConstruct();

	// Ensure that NextBtn is valid before binding
	if (NextBtn)
	{
		NextBtn->OnClicked.AddDynamic(this, &UHitmanSplashScreen::NextBtnClicked);
	}
}

void UHitmanSplashScreen::NextBtnClicked()
{
	this->RemoveFromParent();
}
