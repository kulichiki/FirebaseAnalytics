#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AnalyticsBlueprintFunctionLibrary.generated.h"

UENUM(BlueprintType, Category = "FirebaseAnalytics")
enum class EReservedParametersEnum : uint8
{
	ACHIEVEMENT_ID 		UMETA(DisplayName = "AchievementID"),
	CHARACTER			UMETA(DisplayName = "Character"),
	TRAVEL_CLASS		UMETA(DisplayName = "TravelClass"),
	CONTENT_TYPE		UMETA(DisplayName = "ContentType"),
	CURRENCY			UMETA(DisplayName = "Currency"),
	COUPON				UMETA(DisplayName = "Coupon"),
	START_DATE			UMETA(DisplayName = "StartDate"),
	END_DATE			UMETA(DisplayName = "EndDate"),
	EXTEND_SESSION		UMETA(DisplayName = "ExtendSession"),
	FLIGHT_NUMBER		UMETA(DisplayName = "FlightNumber"),
	GROUP_ID			UMETA(DisplayName = "GroupID"),
	ITEM_CATEGORY		UMETA(DisplayName = "ItemCategory"),
	ITEM_ID				UMETA(DisplayName = "ItemID"),
	ITEM_LOCATION_ID	UMETA(DisplayName = "ItemLocationID"),
	ITEM_NAME			UMETA(DisplayName = "ItemName"),
	LOCATION			UMETA(DisplayName = "Location"),
	LEVEL				UMETA(DisplayName = "Level"),
	LEVEL_NAME			UMETA(DisplayName = "LevelName")
};

UENUM(BlueprintType, Category = "FirebaseAnalytics")
enum class EReservedEventsEnum : uint8
{
	ADD_PAYMENT_INFO		UMETA(DisplayName = "AddPaymentInfo"),
    ADD_TO_CART				UMETA(DisplayName = "AddToCart"),
    ADD_TO_WISHLIST			UMETA(DisplayName = "AddToWishlist"),
    APP_OPEN				UMETA(DisplayName = "AppOpen"),
    BEGIN_CHECKOUT			UMETA(DisplayName = "BeginCheckout"),
    CAMPAIGN_DETAILS		UMETA(DisplayName = "CampaignDetails"),
    ECOMMERCE_PURCHASE		UMETA(DisplayName = "EcommercePurchase"),
    GENERATE_LEAD			UMETA(DisplayName = "GenerateLead"),
    JOIN_GROUP				UMETA(DisplayName = "JoinGroup"),
    LEVEL_END				UMETA(DisplayName = "LevelEnd"),
    LEVEL_START				UMETA(DisplayName = "LevelStart"),
    LEVEL_UP				UMETA(DisplayName = "LevelUp"),
    LOGIN					UMETA(DisplayName = "Login"),
    POST_SCORE				UMETA(DisplayName = "PostScore"),
    PRESENT_OFFER			UMETA(DisplayName = "PresentOffer"),
    PURCHASE_REFUND			UMETA(DisplayName = "PurchaseRefund"),
    SEARCH					UMETA(DisplayName = "Search"),
    SELECT_CONTENT			UMETA(DisplayName = "SelectContent"),
    SHARE					UMETA(DisplayName = "Share"),
    SIGN_UP					UMETA(DisplayName = "SignUp"),
    SPEND_VIRTUAL_CURRENCY	UMETA(DisplayName = "SpendVirtualCurrency"),
    TUTORIAL_BEGIN			UMETA(DisplayName = "TutorialBegin"),
    TUTORIAL_COMPLETE		UMETA(DisplayName = "TutorialComplete"),
    UNLOCK_ACHIEVEMENT		UMETA(DisplayName = "UnlockAchievment"),
    VIEW_ITEM				UMETA(DisplayName = "ViewItem"),
    VIEW_ITEM_LIST			UMETA(DisplayName = "ViewItemList"),
    VIEW_SEARCH_RESULTS		UMETA(DisplayName = "ViewSearchResults"),
    EARN_VIRTUAL_CURRENCY	UMETA(DisplayName = "EarnVirualCurrency"),
    REMOVE_FROM_CART		UMETA(DisplayName = "RemoveFromCart"),
    CHECKOUT_PROGRESS		UMETA(DisplayName = "CheckoutProgress"),
    SET_CHECKOUT_OPTION		UMETA(DisplayName = "SetCheckoutOption")
};

UENUM(BlueprintType, Category = "FirebaseAnalytics")
enum class EReservedUserPropertiesEnum : uint8
{
	SIGN_UP_METHOD						UMETA(DisplayName = "SignUpMethod"),
	ALLOW_AD_PERSONALIZATION_SIGNALS	UMETA(DisplayName = "AllowPersonalizedAds")
};

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
class UAnalyticsBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Initialize the Analytics API.
	 *	@param AppKey	API key used to authenticate requests from your app.
	 *	@param AppID	App ID used to uniquely identify an instance of an app.
	 */
	UFUNCTION(BlueprintCallable, Category = "FirebaseAnalytics")
	static void Initialize(FString ApplicationID, FString APIKey,
						   FString DatabaseURL, FString SenderID,
						   FString StorageBucket, FString ProjectID);

	/** Initialize the Analytics API. */
	UFUNCTION(BlueprintCallable, Category = "FirebaseAnalytics")
	static void InitializeFromConfig();

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
	*  @param ParameterName	Name of the parameter to log.
	*
	*  @param ParameterValue	Value of the parameter to log.
	*/
	UFUNCTION(BlueprintCallable, Category = "FirebaseAnalytics|Bundle")
	static void PutString(UPARAM(ref) FBundle& Bundle, FString ParameterName, FString ParameterValue);
	
	/** Add a floating point parameter to Bundle.
	 *  @param ParameterName	Name of the parameter to log.
	 *
	 *  @param ParameterValue	Value of the parameter to log.
	 */
	UFUNCTION(BlueprintCallable, Category = "FirebaseAnalytics|Bundle")
	static void PutFloat(UPARAM(ref) FBundle& Bundle, FString ParameterName, float ParameterValue);
	
	/** Add a integer parameter to Bundle.
	 *  @param ParameterName	Name of the parameter to log.
	 *
	 *  @param ParameterValue	Value of the parameter to log.
	 */
	UFUNCTION(BlueprintCallable, Category="FirebaseAnalytics|Bundle")
	static void PutInteger(UPARAM(ref) FBundle& Bundle, FString ParameterName, int ParameterValue);
};
