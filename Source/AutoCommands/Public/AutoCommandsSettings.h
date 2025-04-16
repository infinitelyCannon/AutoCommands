// Copyright (C) 2025 Dakarai Simmons - All Rights Reserved

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

    /** List of commands to run once after engine startup (runs before first tick after the Engine initializes) */
    UPROPERTY(Config, EditAnywhere, Category=Commands, meta=(ConfigRestartRequired=true))
    TArray<FString> StartupCommands;

	/** List of commands to run every time you play in the editor */
	UPROPERTY(Config, EditAnywhere, Category=Commands)
	TArray<FString> OnPlayCommands;

	/** Should the OnPlay commands run when simulating? */
	UPROPERTY(Config, EditAnywhere, Category=Commands)
	bool bRunPlayCommandsWhileSimulating;
};
