#include "AnalyticsBlueprintFunctionLibrary.h"
#include "firebase/app.h"

#if PLATFORM_ANDROID
	#include "Android/AndroidJNI.h"
	#include "Android/AndroidApplication.h"
#endif

using namespace firebase;
using namespace firebase::analytics;

void UAnalyticsBlueprintFunctionLibrary::Initialize(FString ApiKey, FString AppID, FString ProjectID, FString StorageBucket)
{
	App* Application;
	AppOptions Options;
	Options.set_api_key(TCHAR_TO_ANSI(*ApiKey));
	Options.set_app_id(TCHAR_TO_ANSI(*AppID));
	Options.set_project_id(TCHAR_TO_ANSI(*ProjectID));
	Options.set_storage_bucket(TCHAR_TO_ANSI(*StorageBucket));

#if PLATFORM_ANDROID

	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		Application = App::Create(Options, Env, FJavaWrapper::GameActivityThis);
		analytics::Initialize(*Application);
	}

#elif PLATFORM_IOS

	Application = App::Create(Options);
	analytics::Initialize(*Application);

#elif PLATFORM_WINDOWS || PLATFORM_MAC || PLATFORM_LINUX

	Application = App::Create(Options);
	analytics::Initialize(*Application);

#endif
}

void UAnalyticsBlueprintFunctionLibrary::InitializeFromConfig()
{
	App* Application;

	const FString JsonFilePath = FPaths::ProjectConfigDir() + "google-services.json";
	FString JsonString;
	FFileHelper::LoadFileToString(JsonString, *JsonFilePath);

	AppOptions Options;
	AppOptions::LoadFromJsonConfig(TCHAR_TO_ANSI(*JsonString), &Options);

#if PLATFORM_ANDROID

	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		Application = App::Create(Options, Env, FJavaWrapper::GameActivityThis);
		analytics::Initialize(*Application);
	}

#elif PLATFORM_IOS

	Application = App::Create(Options);
	analytics::Initialize(*Application);

#elif PLATFORM_WINDOWS || PLATFORM_MAC || PLATFORM_LINUX

	Application = App::Create(Options);
	analytics::Initialize(*Application);

#endif
}

void UAnalyticsBlueprintFunctionLibrary::LogEventWithStringParameter(FString EventName, FString ParameterName, FString ParameterValue)
{
	analytics::LogEvent(TCHAR_TO_ANSI(*EventName), TCHAR_TO_ANSI(*ParameterName), TCHAR_TO_ANSI(*ParameterValue));
}

void UAnalyticsBlueprintFunctionLibrary::LogEventWithFloatParameter(FString EventName, FString ParameterName, float ParameterValue)
{
	analytics::LogEvent(TCHAR_TO_ANSI(*EventName), TCHAR_TO_ANSI(*ParameterName), (double)ParameterValue);
}

void UAnalyticsBlueprintFunctionLibrary::LogEventWithIntegerParameter(FString EventName, FString ParameterName, int ParameterValue)
{
	analytics::LogEvent(TCHAR_TO_ANSI(*EventName), TCHAR_TO_ANSI(*ParameterName), ParameterValue);
}

void UAnalyticsBlueprintFunctionLibrary::LogEvent(FString EventName)
{
	analytics::LogEvent(TCHAR_TO_ANSI(*EventName));
}

void UAnalyticsBlueprintFunctionLibrary::LogEventWithParameters(FString EventName, UPARAM(ref) FParametersStorage& ParametersStorage)
{
	TArray<Parameter>& Parameters = ParametersStorage.Parameters;
	analytics::LogEvent(TCHAR_TO_ANSI(*EventName), Parameters.GetData(), Parameters.Num());
}

void UAnalyticsBlueprintFunctionLibrary::ResetAnalyticsData()
{
	analytics::ResetAnalyticsData();
}

void UAnalyticsBlueprintFunctionLibrary::SetAnalyticsCollectionEnabled(bool Enabled)
{
	analytics::SetAnalyticsCollectionEnabled(Enabled);
}

void UAnalyticsBlueprintFunctionLibrary::SetSessionTimeoutDuration(int Milliseconds)
{
	analytics::SetSessionTimeoutDuration(Milliseconds);
}

void UAnalyticsBlueprintFunctionLibrary::SetUserID(FString UserID)
{
	analytics::SetUserId(TCHAR_TO_ANSI(*UserID));
}

void UAnalyticsBlueprintFunctionLibrary::SetUserProperty(FString PropertyName, FString PropertyValue)
{
	analytics::SetUserProperty(TCHAR_TO_ANSI(*PropertyName), TCHAR_TO_ANSI(*PropertyValue));
}

void UAnalyticsBlueprintFunctionLibrary::Terminate()
{
	analytics::Terminate();
}

void UAnalyticsBlueprintFunctionLibrary::AddStringParameter(UPARAM(ref) FParametersStorage& ParametersStorage, 
															FString ParameterName, 
															FString ParameterValue)
{
	ParametersStorage.Parameters.Add(Parameter(TCHAR_TO_ANSI(*ParameterName), TCHAR_TO_ANSI(*ParameterValue)));
}

void UAnalyticsBlueprintFunctionLibrary::AddFloatParameter(UPARAM(ref) FParametersStorage& ParametersStorage, 
														   FString ParameterName, 
														   float ParameterValue)
{
	ParametersStorage.Parameters.Add(Parameter(TCHAR_TO_ANSI(*ParameterName), (double)ParameterValue));
}

void UAnalyticsBlueprintFunctionLibrary::AddIntegerParameter(UPARAM(ref) FParametersStorage& ParametersStorage, 
															 FString ParameterName, 
															 int ParameterValue)
{
	ParametersStorage.Parameters.Add(Parameter(TCHAR_TO_ANSI(*ParameterName), ParameterValue));
}