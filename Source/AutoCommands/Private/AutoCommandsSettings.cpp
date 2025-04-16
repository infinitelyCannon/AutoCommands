// Copyright (C) 2025 Dakarai Simmons - All Rights Reserved

#include "AutoCommandsSettings.h"

#define LOCTEXT_NAMESPACE "AutoCommandsPlugin"

UAutoCommandsSettings::UAutoCommandsSettings()
{
    CategoryName = TEXT("Plugins");
    SectionName = TEXT("Auto Commands");
	bRunPlayCommandsWhileSimulating = false;
}

#if WITH_EDITOR
FText UAutoCommandsSettings::GetSectionText() const
{
    return LOCTEXT("SettingsDisplayName", "Auto Commands");
}
#endif

#undef LOCTEXT_NAMESPACE