// Rahul Chandra All Rights Reserved

#pragma once

#include "RPG/DataAssets/Input/DataAsset_InputConfig.h"

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "RPGInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYMECHANICS_API URPGInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserObject,typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func);
	
};

template <class UserObject, typename CallbackFunc>
void URPGInputComponent::BindNativeInputAction(const UDataAsset_InputConfig InInputConfig,
	const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc Func)
{
	//checkf(InInputConfig,TEXT("Cannot proceed with binding"));

	//if(InInputConfig.FindNativeInputActionByTag(InInputTag);
	
}
