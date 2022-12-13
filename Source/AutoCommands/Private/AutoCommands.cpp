// Copyright (C) 2022 Dakarai Simmons - All Rights Reserved

#include "AutoCommands.h"
#include "AutoCommandsSettings.h"
#include "Containers/Ticker.h"
#include "Features/IModularFeatures.h"

#define LOCTEXT_NAMESPACE "FAutoCommandsModule"
DEFINE_LOG_CATEGORY(AutoCommandsPlugin)

void FAutoCommandsModule::StartupModule()
{
	// Initialize the tick handler
    TickHandle = FTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateRaw(this, &FAutoCommandsModule::Tick));
}

bool FAutoCommandsModule::Tick(const float DeltaTime)
{
    if(!bHasTicked)
    {
        bHasTicked = true;

        TArray<IConsoleCommandExecutor*> CommandExecutors = IModularFeatures::Get().GetModularFeatureImplementations<IConsoleCommandExecutor>(IConsoleCommandExecutor::ModularFeatureName());
        IConsoleCommandExecutor *CommandExecutor = nullptr;

        if(CommandExecutors.IsValidIndex(0))
        {
            CommandExecutor = CommandExecutors[0];
        }

        if(CommandExecutor == nullptr)
        {
            UE_LOG(AutoCommandsPlugin, Warning, TEXT("Could not grab default console executor."));
            return true;
        }

        for(const FString &Command : GetDefault<UAutoCommandsSettings>()->CommandList)
        {
            UE_LOG(AutoCommandsPlugin, Log, TEXT("Running Command: %s"), *Command);
            CommandExecutor->Exec(*Command);
        }
    }
    else
    {
        FTicker::GetCoreTicker().RemoveTicker(TickHandle);
    }
    
    return true;
}

void FAutoCommandsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

    // Just in case the handle's still valid somehow
    if(TickHandle.IsValid())
    {
        FTicker::GetCoreTicker().RemoveTicker(TickHandle);
    }
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAutoCommandsModule, AutoCommands)