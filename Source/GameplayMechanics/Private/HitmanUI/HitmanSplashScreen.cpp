// Fill out your copyright notice in the Description page of Project Settings.


#include "HitmanUI/HitmanSplashScreen.h"

#include "Components/AudioComponent.h"
#include "Components/Button.h"



UHitmanSplashScreen::UHitmanSplashScreen()
{
	if(NextBtn)
	{
		NextBtn->OnClicked.AddDynamic(this, &UHitmanSplashScreen::NextBtnClicked);
	}


	//BackgroundMusicAC->Sound = 

}

void UHitmanSplashScreen::NextBtnClicked()
{
	this->RemoveFromParent();
}