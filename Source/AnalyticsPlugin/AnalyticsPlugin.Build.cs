using UnrealBuildTool;
using System.IO;

public class AnalyticsPlugin : ModuleRules
{
    public AnalyticsPlugin(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });

        string ThirdPartyPath = Path.GetFullPath(Path.Combine(ModuleDirectory, "../ThirdParty/firebase_cpp_sdk/"));
        string LibsPath = Path.Combine(ThirdPartyPath, "libs/");
        PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "include/"));
        PublicDefinitions.Add("INTERNAL_EXPERIMENTAL=0");

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PrivateDependencyModuleNames.Add("Launch");
            PublicLibraryPaths.Add(Path.Combine(LibsPath, "android/gnustl/arm64-v8a/"));
            PublicLibraryPaths.Add(Path.Combine(LibsPath, "android/gnustl/armeabi-v7a/"));
            PublicLibraryPaths.Add(Path.Combine(LibsPath, "android/gnustl/x86/"));
            PublicLibraryPaths.Add(Path.Combine(LibsPath, "android/gnustl/x86_64/"));
        }
        else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            PublicLibraryPaths.Add(Path.Combine(LibsPath, "ios/arm64-v8a/"));
            PublicLibraryPaths.Add(Path.Combine(LibsPath, "ios/armeabi-v7a/"));
            PublicLibraryPaths.Add(Path.Combine(LibsPath, "ios/i386/"));
            PublicLibraryPaths.Add(Path.Combine(LibsPath, "ios/x86_64/"));
            PublicLibraryPaths.Add(Path.Combine(LibsPath, "ios/universal/"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Win32)
        {
            PublicLibraryPaths.Add(Path.Combine(LibsPath, "windows/MD/x86/"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicLibraryPaths.Add(Path.Combine(LibsPath, "windows/MD/x64/"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            PublicLibraryPaths.Add(Path.Combine(LibsPath, "linux/i386/"));
            PublicLibraryPaths.Add(Path.Combine(LibsPath, "linux/x86_64/"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            PublicLibraryPaths.Add(Path.Combine(LibsPath, "darwin/x86_64/"));
            PublicLibraryPaths.Add(Path.Combine(LibsPath, "darwin/universal/"));
        }

        if (Target.Platform == UnrealTargetPlatform.Android)
        {
            PublicAdditionalLibraries.Add("firebase_analytics");
            PublicAdditionalLibraries.Add("firebase_app");
        }
        else if (Target.Platform == UnrealTargetPlatform.IOS || Target.Platform == UnrealTargetPlatform.Linux ||
                 Target.Platform == UnrealTargetPlatform.Mac)
        {
            PublicAdditionalLibraries.Add("libfirebase_analytics.a");
            PublicAdditionalLibraries.Add("libfirebase_app.a");
        }
        else if (Target.Platform == UnrealTargetPlatform.Win32 || Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicAdditionalLibraries.Add("firebase_analytics.lib");
            PublicAdditionalLibraries.Add("firebase_app.lib");
        }
    }
}
