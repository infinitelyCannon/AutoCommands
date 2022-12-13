// Copyright (C) 2022 Dakarai Simmons - All Rights Reserved

#include "AutoCommandsSettings.h"

#define LOCTEXT_NAMESPACE "AutoCommandsPlugin"

UAutoCommandsSettings::UAutoCommandsSettings()
{
    CategoryName = TEXT("Plugins");
    SectionName = TEXT("Auto Commands");
}

FText UAutoCommandsSettings::GetSectionText() const
{
    return LOCTEXT("SettingsDisplayName", "Auto Commands");
}

#undef LOCTEXT_NAMESPACE