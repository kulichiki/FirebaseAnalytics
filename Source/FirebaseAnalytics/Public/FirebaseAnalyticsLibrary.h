#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FirebaseAnalyticsLibrary.generated.h"

USTRUCT(BlueprintType, Category = "FirebaseAnalytics|Bundle")
struct FBundle
{
	GENERATED_BODY()

	FBundle() {}

	TMap<FString, FString> StringParameters;
	TMap<FString, float> FloatParameters;
	TMap<FString, int> IntegerParameters;
};

UCLASS()
class UFirebaseAnalyticsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Initialize the Analytics API. */
	UFUNCTION(BlueprintCallable, Category = "FirebaseAnalytics")
	static void Initialize();

	/** Log an event with associated parameters.
	 *  @param EventName	Name of the event to log. Should contain 1 to 40 alphanumeric characters
	 *  					or underscores. The name must start with an alphabetic character. Some
	 *  					event names are reserved. See Analytics Events (https://firebase.google.com/
	 *  					docs/reference/cpp/group/event-names.html#group__event__names) for the list
	 *  					of reserved event names. The "firebase_" prefix is reserved and should not
	 *  					be used. Note that event names are case-sensitive and that logging two events
	 *  					whose names differ only in case will result in two distinct events.
	 */
	UFUNCTION(BlueprintCallable, Category = "FirebaseAnalytics")
	static void LogEvent(FString EventName);

	/** Log an event with one string parameter.
	 *  @param EventName		Name of the event to log. Should contain 1 to 40 alphanumeric characters
	 *  						or underscores. The name must start with an alphabetic character. Some
	 *  						event names are reserved. See Analytics Events (https://firebase.google.com/
	 *  						docs/reference/cpp/group/event-names.html#group__event__names) for the list
	 *  						of reserved event names. The "firebase_" prefix is reserved and should not
	 *  						be used. Note that event names are case-sensitive and that logging two events
	 *  						whose names differ only in case will result in two distinct events.
	 *
	 *  @param ParameterName	Name of the parameter to log.
	 *
	 *  @param ParameterValue	Value of the parameter to log.
	 */
	UFUNCTION(BlueprintCallable, Category = "FirebaseAnalytics")
	static void LogEventWithStringParameter(FString EventName, FString ParameterName, FString ParameterValue);

	/** Log an event with one float parameter.
	 *  @param EventName		Name of the event to log. Should contain 1 to 40 alphanumeric characters
	 *  						or underscores. The name must start with an alphabetic character. Some
	 *  						event names are reserved. See Analytics Events (https://firebase.google.com/
	 *  						docs/reference/cpp/group/event-names.html#group__event__names) for the list
	 *  						of reserved event names. The "firebase_" prefix is reserved and should not
	 *  						be used. Note that event names are case-sensitive and that logging two events
	 *  						whose names differ only in case will result in two distinct events.
	 *
	 *  @param ParameterName	Name of the parameter to log.
	 *
	 *  @param ParameterValue	Value of the parameter to log.
	 */
	UFUNCTION(BlueprintCallable, Category = "FirebaseAnalytics")
	static void LogEventWithFloatParameter(FString EventName, FString ParameterName, float ParameterValue);

	/** Log an event with one integer parameter.
	 *  @param EventName		Name of the event to log. Should contain 1 to 40 alphanumeric characters
	 *  						or underscores. The name must start with an alphabetic character. Some
	 *  						event names are reserved. See Analytics Events (https://firebase.google.com/
	 *  						docs/reference/cpp/group/event-names.html#group__event__names) for the list
	 *  						of reserved event names. The "firebase_" prefix is reserved and should not
	 *  						be used. Note that event names are case-sensitive and that logging two events
	 *  						whose names differ only in case will result in two distinct events.
	 *
	 *  @param ParameterName	Name of the parameter to log.
	 *
	 *  @param ParameterValue	Value of the parameter to log.
	 */
	UFUNCTION(BlueprintCallable, Category = "FirebaseAnalytics")
	static void LogEventWithIntegerParameter(FString EventName, FString ParameterName, int ParameterValue);

	/** Log an event with associated parameters.
	 *  @param EventName	Name of the event to log. Should contain 1 to 40 alphanumeric characters
	 *  					or underscores. The name must start with an alphabetic character. Some
	 *  					event names are reserved. See Analytics Events (https://firebase.google.com/
	 *  					docs/reference/cpp/group/event-names.html#group__event__names) for the list
	 *  					of reserved event names. The "firebase_" prefix is reserved and should not
	 *  					be used. Note that event names are case-sensitive and that logging two events
	 *  					whose names differ only in case will result in two distinct events.
	 *
	 *  @param Parameters	Array of FParameter structures.
	 */
	UFUNCTION(BlueprintCallable, Category = "FirebaseAnalytics")
	static void LogEventWithParameters(FString EventName, UPARAM(ref) FBundle& Bundle);

	/** Clears all analytics data for this app from the device and resets the app instance id. */
	UFUNCTION(BlueprintCallable, Category = "FirebaseAnalytics")
	static void ResetAnalyticsData();

	/** Sets whether analytics collection is enabled for this app on this device.
	 *  @param Enabled	"true" to enable analytics collection, "false" to disable.
	 */
	UFUNCTION(BlueprintCallable, Category = "FirebaseAnalytics")
	static void SetAnalyticsCollectionEnabled(bool Enabled);

	/** Sets the duration of inactivity that terminates the current session.
	 *  @param Milliseconds	The duration of inactivity that terminates the current session.
	 */
	UFUNCTION(BlueprintCallable, Category = "FirebaseAnalytics")
	static void SetSessionTimeoutDuration(int Milliseconds);

	/** Sets the user ID property.
	 *  @param UserID	The user ID associated with the user of this app on this device. The user ID
	 *  				must be non-empty and no more than 256 characters long. Setting UserID to
	 *  				NULL or nullptr removes the user ID.
	 */
	UFUNCTION(BlueprintCallable, Category = "FirebaseAnalytics")
	static void SetUserID(FString UserID);

	/** Set a user property to the given value.
	 *  @param PropertyName		Name of the user property to set. This must be a combination of
	 *  						letters and digits (matching the regular expression [a-zA-Z0-9] between 1
	 *  						and 40 characters long starting with a letter [a-zA-Z] character.
	 *
	 *  @param PropertyValue	Value to set the user property to. Set this argument to NULL or
	 * 							nullptr to remove the user property. The value can be between 1
	 * 							to 100 characters long.
	 */
	UFUNCTION(BlueprintCallable, Category = "FirebaseAnalytics")
	static void SetUserProperty(FString PropertyName, FString PropertyValue);

	/** Add a string parameter to Bundle.
	 *	@param Bundle			Bundle reference
	 *
	 *  @param ParameterName	Name of the parameter to log.
	 *
	 *  @param ParameterValue	Value of the parameter to log.
	 */
	UFUNCTION(BlueprintCallable, Category = "FirebaseAnalytics|Bundle")
	static void PutString(UPARAM(ref) FBundle& Bundle, FString ParameterName, FString ParameterValue);
	
	/** Add a floating point parameter to Bundle.
	 *	@param Bundle			Bundle reference
	 *
	 *  @param ParameterName	Name of the parameter to log.
	 *
	 *  @param ParameterValue	Value of the parameter to log.
	 */
	UFUNCTION(BlueprintCallable, Category = "FirebaseAnalytics|Bundle")
	static void PutFloat(UPARAM(ref) FBundle& Bundle, FString ParameterName, float ParameterValue);
	
	/** Add a integer parameter to Bundle.
	 *	@param Bundle			Bundle reference
	 *
	 *  @param ParameterName	Name of the parameter to log.
	 *
	 *  @param ParameterValue	Value of the parameter to log.
	 */
	UFUNCTION(BlueprintCallable, Category="FirebaseAnalytics|Bundle")
	static void PutInteger(UPARAM(ref) FBundle& Bundle, FString ParameterName, int ParameterValue);
};
