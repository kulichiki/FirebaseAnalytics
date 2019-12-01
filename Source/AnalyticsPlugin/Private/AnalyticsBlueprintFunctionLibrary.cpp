#include "AnalyticsBlueprintFunctionLibrary.h"

#if PLATFORM_ANDROID
	#include "Android/AndroidJNI.h"
	#include "Android/AndroidApplication.h"
#endif

void UAnalyticsBlueprintFunctionLibrary::Initialize(FString ApplicationID, FString APIKey,
													FString DatabaseURL, FString SenderID,
													FString StorageBucket, FString ProjectID)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring JApplicationID = Env->NewStringUTF(TCHAR_TO_UTF8(*ApplicationID));
		jstring JAPIKey		   = Env->NewStringUTF(TCHAR_TO_UTF8(*APIKey));
		jstring JDatabaseURL   = Env->NewStringUTF(TCHAR_TO_UTF8(*DatabaseURL));
		jstring JSenderID	   = Env->NewStringUTF(TCHAR_TO_UTF8(*SenderID));
		jstring JStorageBucket = Env->NewStringUTF(TCHAR_TO_UTF8(*StorageBucket));
		jstring JProjectID	   = Env->NewStringUTF(TCHAR_TO_UTF8(*ProjectID));

		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_Initialize", 
		"(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JApplicationID, JAPIKey,
																				  JDatabaseURL, JSenderID,
																				  JStorageBucket, JProjectID);

		Env->DeleteLocalRef(JApplicationID);
		Env->DeleteLocalRef(JAPIKey);
		Env->DeleteLocalRef(JDatabaseURL);
		Env->DeleteLocalRef(JSenderID);
		Env->DeleteLocalRef(JStorageBucket);
		Env->DeleteLocalRef(JProjectID);
	}
#endif
}

void UAnalyticsBlueprintFunctionLibrary::InitializeFromConfig()
{
#if PLATFORM_ANDROID

	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
	}
#endif
}

void UAnalyticsBlueprintFunctionLibrary::LogEvent(FString EventName)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring JEventName = Env->NewStringUTF(TCHAR_TO_UTF8(*EventName));

		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_LogEvent", "(Ljava/lang/String;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JEventName);

		Env->DeleteLocalRef(JEventName);
	}
#endif
}

void UAnalyticsBlueprintFunctionLibrary::LogEventWithStringParameter(FString EventName, FString ParameterName, FString ParameterValue)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring JEventName		= Env->NewStringUTF(TCHAR_TO_UTF8(*EventName));
		jstring JParameterName	= Env->NewStringUTF(TCHAR_TO_UTF8(*ParameterName));
		jstring JParameterValue = Env->NewStringUTF(TCHAR_TO_UTF8(*ParameterValue));

		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_LogEventWithParameter", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JEventName, JParameterName, JParameterValue);

		Env->DeleteLocalRef(JEventName);
		Env->DeleteLocalRef(JParameterName);
		Env->DeleteLocalRef(JParameterValue);
	}
#endif
}

void UAnalyticsBlueprintFunctionLibrary::LogEventWithFloatParameter(FString EventName, FString ParameterName, float ParameterValue)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring JEventName = Env->NewStringUTF(TCHAR_TO_UTF8(*EventName));
		jstring JParameterName = Env->NewStringUTF(TCHAR_TO_UTF8(*ParameterName));

		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_LogEventWithParameter", "(Ljava/lang/String;Ljava/lang/String;F)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JEventName, JParameterName, ParameterValue);

		Env->DeleteLocalRef(JEventName);
		Env->DeleteLocalRef(JParameterName);
	}
#endif
}

void UAnalyticsBlueprintFunctionLibrary::LogEventWithIntegerParameter(FString EventName, FString ParameterName, int ParameterValue)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring JEventName = Env->NewStringUTF(TCHAR_TO_UTF8(*EventName));
		jstring JParameterName = Env->NewStringUTF(TCHAR_TO_UTF8(*ParameterName));

		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_LogEventWithParameter", "(Ljava/lang/String;Ljava/lang/String;I)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JEventName, JParameterName, ParameterValue);

		Env->DeleteLocalRef(JEventName);
		Env->DeleteLocalRef(JParameterName);
	}
#endif
}

void UAnalyticsBlueprintFunctionLibrary::LogEventWithParameters(FString EventName, UPARAM(ref) FParametersStorage& ParametersStorage)
{
	//TArray<Parameter>& Parameters = ParametersStorage.Parameters;
	//analytics::LogEvent(TCHAR_TO_ANSI(*EventName), Parameters.GetData(), Parameters.Num());
}

void UAnalyticsBlueprintFunctionLibrary::ResetAnalyticsData()
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_ResetAnalyticsData", "()V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method);
	}
#endif
}

void UAnalyticsBlueprintFunctionLibrary::SetAnalyticsCollectionEnabled(bool Enabled)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_SetAnalyticsCollectionEnabled", "(Z)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, Enabled);
	}
#endif
}

void UAnalyticsBlueprintFunctionLibrary::SetSessionTimeoutDuration(int Milliseconds)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_SetSessionTimeoutDuration", "(I)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, Milliseconds);
	}
#endif
}

void UAnalyticsBlueprintFunctionLibrary::SetUserID(FString UserID)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring JUserID = Env->NewStringUTF(TCHAR_TO_UTF8(*UserID));
		
		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_SetUserID", "(Ljava/lang/String;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JUserID);

		Env->DeleteLocalRef(JUserID);
	}
#endif
}

void UAnalyticsBlueprintFunctionLibrary::SetUserProperty(FString PropertyName, FString PropertyValue)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring JPropertyName  = Env->NewStringUTF(TCHAR_TO_UTF8(*PropertyName));
		jstring JPropertyValue = Env->NewStringUTF(TCHAR_TO_UTF8(*PropertyValue));

		static jmethodID Method = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_SetUserProperty", "()V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, Method, JPropertyName, JPropertyValue);

		Env->DeleteLocalRef(JPropertyName);
		Env->DeleteLocalRef(JPropertyValue);
	}
#endif
}

void UAnalyticsBlueprintFunctionLibrary::AddStringParameter(UPARAM(ref) FParametersStorage& ParametersStorage, 
															FString ParameterName, 
															FString ParameterValue)
{
	//ParametersStorage.Parameters.Add(Parameter(TCHAR_TO_ANSI(*ParameterName), TCHAR_TO_ANSI(*ParameterValue)));
}

void UAnalyticsBlueprintFunctionLibrary::AddFloatParameter(UPARAM(ref) FParametersStorage& ParametersStorage, 
														   FString ParameterName, 
														   float ParameterValue)
{
	//ParametersStorage.Parameters.Add(Parameter(TCHAR_TO_ANSI(*ParameterName), (double)ParameterValue));
}

void UAnalyticsBlueprintFunctionLibrary::AddIntegerParameter(UPARAM(ref) FParametersStorage& ParametersStorage, 
															 FString ParameterName, 
															 int ParameterValue)
{
	//ParametersStorage.Parameters.Add(Parameter(TCHAR_TO_ANSI(*ParameterName), ParameterValue));
}