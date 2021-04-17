// Fill out your copyright notice in the Description page of Project Settings.


#include "Gui/ExplorationMenuEp.h"

void UExplorationMenuEp::SetPaused(bool i_paused)
{
	OnPaused(i_paused);
}

void UExplorationMenuEp::Prepare(UTextureRenderTarget2D* i_renderTarget)
{
	OnPrepared(i_renderTarget);
}

void UExplorationMenuEp::RequestPauseStateChange()
{
	sig_onPauseChangeRequested.Broadcast();
}

