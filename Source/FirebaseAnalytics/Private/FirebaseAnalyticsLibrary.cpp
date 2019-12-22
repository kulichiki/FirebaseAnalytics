#include "FirebaseAnalyticsLibrary.h"

#if PLATFORM_ANDROID
	#include "Android/AndroidJNI.h"
	#include "Android/AndroidApplication.h"
#endif

void UFirebaseAnalyticsLibrary::Initialize()
{
#if PLATFORM_ANDROID

	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID JMethodID = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_Initialize", "()V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, JMethodID);
	}
#endif
}

void UFirebaseAnalyticsLibrary::LogEvent(FString EventName)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring JEventName = Env->NewStringUTF(TCHAR_TO_UTF8(*EventName));

		static jmethodID JMethodID = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_LogEvent", "(Ljava/lang/String;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, JMethodID, JEventName);

		Env->DeleteLocalRef(JEventName);
	}
#endif
}

void UFirebaseAnalyticsLibrary::LogEventWithStringParameter(FString EventName, FString ParameterName, FString ParameterValue)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring JEventName		= Env->NewStringUTF(TCHAR_TO_UTF8(*EventName));
		jstring JParameterName	= Env->NewStringUTF(TCHAR_TO_UTF8(*ParameterName));
		jstring JParameterValue = Env->NewStringUTF(TCHAR_TO_UTF8(*ParameterValue));

		static jmethodID JMethodID = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_LogEventWithParameter", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, JMethodID, JEventName, JParameterName, JParameterValue);

		Env->DeleteLocalRef(JEventName);
		Env->DeleteLocalRef(JParameterName);
		Env->DeleteLocalRef(JParameterValue);
	}
#endif
}

void UFirebaseAnalyticsLibrary::LogEventWithFloatParameter(FString EventName, FString ParameterName, float ParameterValue)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring JEventName	   = Env->NewStringUTF(TCHAR_TO_UTF8(*EventName));
		jstring JParameterName = Env->NewStringUTF(TCHAR_TO_UTF8(*ParameterName));

		static jmethodID JMethodID = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_LogEventWithParameter", "(Ljava/lang/String;Ljava/lang/String;F)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, JMethodID, JEventName, JParameterName, ParameterValue);

		Env->DeleteLocalRef(JEventName);
		Env->DeleteLocalRef(JParameterName);
	}
#endif
}

void UFirebaseAnalyticsLibrary::LogEventWithIntegerParameter(FString EventName, FString ParameterName, int ParameterValue)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring JEventName		= Env->NewStringUTF(TCHAR_TO_UTF8(*EventName));
		jstring JParameterName	= Env->NewStringUTF(TCHAR_TO_UTF8(*ParameterName));

		static jmethodID JMethodID = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_LogEventWithParameter", "(Ljava/lang/String;Ljava/lang/String;I)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, JMethodID, JEventName, JParameterName, ParameterValue);

		Env->DeleteLocalRef(JEventName);
		Env->DeleteLocalRef(JParameterName);
	}
#endif
}

void UFirebaseAnalyticsLibrary::LogEventWithParameters(FString EventName, UPARAM(ref) FBundle& Bundle)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		// Initialize Bundle class
		jclass JBundleClass			 = Env->FindClass("android/os/Bundle");
		jmethodID JBundleConstructor = Env->GetMethodID(JBundleClass, "<init>", "()V");
		jobject JBundle				 = Env->NewObject(JBundleClass, JBundleConstructor);

		// Adding string parameter to Bundle
		static jmethodID JPutStringMethodID	= FJavaWrapper::FindMethod(Env, JBundleClass, "putString", "(Ljava/lang/String;Ljava/lang/String;)V", false);
		for (auto& Parameter : Bundle.StringParameters)
		{
			jstring ParameterName  = Env->NewStringUTF(TCHAR_TO_UTF8(*Parameter.Key));
			jstring ParameterValue = Env->NewStringUTF(TCHAR_TO_UTF8(*Parameter.Value));
			
			FJavaWrapper::CallVoidMethod(Env, JBundle, JPutStringMethodID, ParameterName, ParameterValue);
		
			Env->DeleteLocalRef(ParameterName);
			Env->DeleteLocalRef(ParameterValue);
		}

		// Adding float parameter to Bundle
		static jmethodID JPutFloatMethodID = FJavaWrapper::FindMethod(Env, JBundleClass, "putFloat", "(Ljava/lang/String;F)V", false);
		for (auto& Parameter : Bundle.FloatParameters)
		{
			jstring ParameterName = Env->NewStringUTF(TCHAR_TO_UTF8(*Parameter.Key));
			FJavaWrapper::CallVoidMethod(Env, JBundle, JPutFloatMethodID, ParameterName, Parameter.Value);
		
			Env->DeleteLocalRef(ParameterName);
		}

		// Adding integer parameter to Bundle
		static jmethodID JPutIntegerMethodID = FJavaWrapper::FindMethod(Env, JBundleClass, "putInt", "(Ljava/lang/String;I)V", false);
		for (auto& Parameter : Bundle.IntegerParameters)
		{
			jstring ParameterName = Env->NewStringUTF(TCHAR_TO_UTF8(*Parameter.Key));
			FJavaWrapper::CallVoidMethod(Env, JBundle, JPutIntegerMethodID, ParameterName, Parameter.Value);
		
			Env->DeleteLocalRef(ParameterName);
		}
		
		jstring JEventName = Env->NewStringUTF(TCHAR_TO_UTF8(*EventName));
		
		static jmethodID JMethodID = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_LogEventWithParameters", "(Ljava/lang/String;Landroid/os/Bundle;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, JMethodID, JEventName, JBundle);
		
		Env->DeleteLocalRef(JBundle);
		Env->DeleteLocalRef(JEventName);
	}
#endif
}

void UFirebaseAnalyticsLibrary::ResetAnalyticsData()
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID JMethodID = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_ResetAnalyticsData", "()V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, JMethodID);
	}
#endif
}

void UFirebaseAnalyticsLibrary::SetAnalyticsCollectionEnabled(bool Enabled)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID JMethodID = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_SetAnalyticsCollectionEnabled", "(Z)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, JMethodID, Enabled);
	}
#endif
}

void UFirebaseAnalyticsLibrary::SetSessionTimeoutDuration(int Milliseconds)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		static jmethodID JMethodID = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_SetSessionTimeoutDuration", "(I)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, JMethodID, Milliseconds);
	}
#endif
}

void UFirebaseAnalyticsLibrary::SetUserID(FString UserID)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring JUserID = Env->NewStringUTF(TCHAR_TO_UTF8(*UserID));
		
		static jmethodID JMethodID = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_SetUserID", "(Ljava/lang/String;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, JMethodID, JUserID);

		Env->DeleteLocalRef(JUserID);
	}
#endif
}

void UFirebaseAnalyticsLibrary::SetUserProperty(FString PropertyName, FString PropertyValue)
{
#if PLATFORM_ANDROID
	if (JNIEnv* Env = FAndroidApplication::GetJavaEnv())
	{
		jstring JPropertyName  = Env->NewStringUTF(TCHAR_TO_UTF8(*PropertyName));
		jstring JPropertyValue = Env->NewStringUTF(TCHAR_TO_UTF8(*PropertyValue));

		static jmethodID JMethodID = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, "AndroidThunkJava_SetUserProperty", "(Ljava/lang/String;Ljava/lang/String;)V", false);
		FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, JMethodID, JPropertyName, JPropertyValue);

		Env->DeleteLocalRef(JPropertyName);
		Env->DeleteLocalRef(JPropertyValue);
	}
#endif
}

void UFirebaseAnalyticsLibrary::PutString(UPARAM(ref) FBundle& Bundle, FString ParameterName, FString ParameterValue)
{
	Bundle.StringParameters.Add(ParameterName, ParameterValue);
}

void UFirebaseAnalyticsLibrary::PutFloat(UPARAM(ref) FBundle& Bundle, FString ParameterName, float ParameterValue)
{
	Bundle.FloatParameters.Add(ParameterName, ParameterValue);
}

void UFirebaseAnalyticsLibrary::PutInteger(UPARAM(ref) FBundle& Bundle, FString ParameterName, int ParameterValue)
{
	Bundle.IntegerParameters.Add(ParameterName, ParameterValue);
}