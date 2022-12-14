// Copyright (C) 2022 Dakarai Simmons - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "Engine/DeveloperSettings.h"
#include "AutoCommandsSettings.generated.h"

/**
 * Edit the list of commands to run
 */
UCLASS(config=Engine, DefaultConfig)
class AUTOCOMMANDS_API UAutoCommandsSettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    UAutoCommandsSettings();

#if WITH_EDITOR
    // UDeveloperSettings Interface
    virtual FText GetSectionText() const override;
#endif

    /** List of commands to run at startup (runs before first tick after the Engine initializes) */
    UPROPERTY(Config, EditAnywhere, Category=Commands, meta=(ConfigRestartRequired=true))
    TArray<FString> CommandList;
};
