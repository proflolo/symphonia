// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ExplorationMenuEp.generated.h"

/**
 * 
 */
UCLASS()
class SYMPHONIA_API UExplorationMenuEp : public UUserWidget
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPauseRequestedSignal);
	FPauseRequestedSignal sig_onPauseChangeRequested;


	void SetPaused(bool i_paused);
	void Prepare(UTextureRenderTarget2D* i_renderTarget);

protected:

	UFUNCTION(BlueprintCallable, Category= "Director", DisplayName = "Request Pause")
	void RequestPauseStateChange();

	UFUNCTION(BlueprintImplementableEvent, Category = "Director", DisplayName = "Paused")
	void OnPaused(bool i_paused);

	UFUNCTION(BlueprintImplementableEvent, Category = "Director", DisplayName = "Prepared")
	void OnPrepared(UTextureRenderTarget2D* i_renderTexture);

private:
	
	
};
