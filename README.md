## Requirements:
- Unreal Engine >= 4.22
- Android SDK >= 26
- Android NDK r14b
- JDK >= 1.8

## Supported Platforms:
- Android

## Setup:
1. Go to Firebase Console:
  - __Create new Firebase project:__
  > ![NewProject](/Documentation/1.1.PNG)
  - __Make sure you enabled "Google Analytics" for you project ("Project Settings" -> "Integrations"):__  
  > ![GoogleAnalytics](/Documentation/1.2.PNG)
  - __Add your Android Application ("Project Settings" -> "Your Apps"). In "Android Package Name" enter package name from your Project Settings:__ 
  > ![GoogleAnalytics](/Documentation/1.3.1.PNG)  
  - __Download "google-service.json" & put to "${ProjectDir}/Build/Android"__
	
2. Download plugin & put to "${ProjectDir}/Plugins"

## Additional information:
If you want enable analytics in debug mode, execute: 
> adb shell setprop debug.firebase.analytics.app ${YourAndroidPackageName}
