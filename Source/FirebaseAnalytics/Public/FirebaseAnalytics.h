#pragma once

#include "Modules/ModuleManager.h"

class FFirebaseAnalyticsModule : public IModuleInterface
{
public:
	void StartupModule() override;
	void ShutdownModule() override;
};
