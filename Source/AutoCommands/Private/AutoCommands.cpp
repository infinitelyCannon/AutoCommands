// Copyright (C) 2025 Dakarai Simmons - All Rights Reserved

#include "AutoCommands.h"
#include "AutoCommandsSettings.h"
#include "Containers/Ticker.h"
#include "Features/IModularFeatures.h"

#define LOCTEXT_NAMESPACE "FAutoCommandsModule"
DEFINE_LOG_CATEGORY(AutoCommandsPlugin)

void FAutoCommandsModule::StartupModule()
{
	// Initialize the tick handler
    TickHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateRaw(this, &FAutoCommandsModule::Tick));

	// Initialize PIE callback
	PostPIEStartedHandle = FEditorDelegates::PostPIEStarted.AddRaw(this, &FAutoCommandsModule::HandlePIEStarted);
}

void FAutoCommandsModule::HandlePIEStarted(const bool bIsSimulating)
{
	const UAutoCommandsSettings* Settings = GetDefault<UAutoCommandsSettings>();

	TArray<IConsoleCommandExecutor*> CommandExecutors = IModularFeatures::Get().GetModularFeatureImplementations<IConsoleCommandExecutor>(IConsoleCommandExecutor::ModularFeatureName());
	IConsoleCommandExecutor *CommandExecutor = nullptr;

	if(CommandExecutors.IsValidIndex(0))
	{
		CommandExecutor = CommandExecutors[0];
	}

	if(CommandExecutor == nullptr)
	{
		UE_LOG(AutoCommandsPlugin, Warning, TEXT("Could not grab default console executor."));
		return;
	}
	
	if ((bIsSimulating && Settings->bRunPlayCommandsWhileSimulating) || !bIsSimulating)
	{
		for (const FString& Command : Settings->OnPlayCommands)
		{
			UE_LOG(AutoCommandsPlugin, Log, TEXT("Running Command: %s"), *Command);
			CommandExecutor->Exec(*Command);
		}
	}
}

bool FAutoCommandsModule::Tick(const float DeltaTime)
{
    TArray<IConsoleCommandExecutor*> CommandExecutors = IModularFeatures::Get().GetModularFeatureImplementations<IConsoleCommandExecutor>(IConsoleCommandExecutor::ModularFeatureName());
    IConsoleCommandExecutor *CommandExecutor = nullptr;

    if(CommandExecutors.IsValidIndex(0))
    {
        CommandExecutor = CommandExecutors[0];
    }

    if(CommandExecutor == nullptr)
    {
        UE_LOG(AutoCommandsPlugin, Warning, TEXT("Could not grab default console executor."));
        return false;
    }

    for(const FString& Command : GetDefault<UAutoCommandsSettings>()->StartupCommands)
    {
        UE_LOG(AutoCommandsPlugin, Log, TEXT("Running Command: %s"), *Command);
        CommandExecutor->Exec(*Command);
    }
	
    return false;
}

void FAutoCommandsModule::ShutdownModule()
{
    if(TickHandle.IsValid())
    {
        FTSTicker::GetCoreTicker().RemoveTicker(TickHandle);
    }

	if (PostPIEStartedHandle.IsValid())
	{
		FEditorDelegates::PostPIEStarted.Remove(PostPIEStartedHandle);
	}	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAutoCommandsModule, AutoCommands)