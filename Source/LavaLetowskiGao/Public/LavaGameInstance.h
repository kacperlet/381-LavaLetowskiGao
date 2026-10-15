// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LavaGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LAVALETOWSKIGAO_API ULavaGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	int32 Score = 0;
};
