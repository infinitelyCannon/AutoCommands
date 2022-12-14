// Copyright (C) 2022 Dakarai Simmons - All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(AutoCommandsPlugin, Log, All);

class FAutoCommandsModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
    bool Tick(const float DeltaTime);

    FDelegateHandle TickHandle;
};
