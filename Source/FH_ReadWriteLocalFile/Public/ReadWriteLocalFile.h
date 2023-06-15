#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReadWriteLocalFile.generated.h"

UENUM(BlueprintType)
enum class EPathDir : uint8
{
	EPD_RootDir UMETA(Displayname="RootDir"),
	EPD_ProjectDir UMETA(Displayname="ProjectDir"),
	EPD_ProjectConfigDir UMETA(Displayname="ProjectConfigDir"),
	EPD_ProjectContentDir UMETA(Displayname="ProjectContentDir"),
	EPD_ProjectLogDir UMETA(Displayname="ProjectLogDir"),
	EPD_ProjectPluginsDir UMETA(Displayname="ProjectPluginsDir"),
	EPD_ProjectSavedDir UMETA(Displayname="ProjectSavedDir"),
	EPD_ProjectUserDir UMETA(Displayname="ProjectUserDir"),
	EPD_EngineDir UMETA(Displayname="EngineDir"),
	EPD_EngineConfigDir UMETA(Displayname="EngineConfigDir"),
	EPD_EngineContentDir UMETA(Displayname="EngineContentDir"),
	EPD_EnginePluginsDir UMETA(Displayname="EnginePluginsDir"),
	EPD_EngineSavedDir UMETA(Displayname="EngineSavedDir"),
	EPD_EngineSourceDir UMETA(Displayname="EngineSourceDir"),
	EPD_LaunchDir UMETA(Displayname="LaunchDir"),
	EPD_GameSourceDir UMETA(Displayname="GameSourceDir")
};

UCLASS(BlueprintType)
class FH_READWRITELOCALFILE_API UReadWriteLocalFile : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

/* My Code */
public:	
	// Enum Convert String
	UFUNCTION(BlueprintPure, Category="FH|ReadWriteLocalFile")
	static FString ConvPathToString(const EPathDir EPD);

	// TArray<FString> Convert To FString
	UFUNCTION(BlueprintPure, Category="FH|ReadWriteLocalFile")
	static FString ConvertArrayToString(const TArray<FString>& TextResults);
	
	// Check Local File Exists
	UFUNCTION(BlueprintPure, Category="FH|ReadWriteLocalFile")
	static bool IsLocalFileExistsByStr(const FString& FilePath);

	UFUNCTION(BlueprintPure, Category="FH|ReadWriteLocalFile")
	static bool IsLocalFileExistsByEnum(const EPathDir EPD);

	// Create Local File Path And File
	UFUNCTION(BlueprintCallable, Category="FH|ReadWriteLocalFile")
	static bool CreatePathAndFileByStr(const FString& FilePath, const FString& FileName, FString& Path);

	UFUNCTION(BlueprintCallable, Category="FH|ReadWriteLocalFile")
	static bool CreatePathAndFileByEnum(const EPathDir EPD, const FString& FileName, FString& Path);

	// Read Local File
	UFUNCTION(BlueprintCallable, Category="FH|ReadWriteLocalFile")
	static TArray<FString> ReadLocalFileByStr(const FString& FilePath, const FString& FileName);

	UFUNCTION(BlueprintCallable, Category="FH|ReadWriteLocalFile")
	static TArray<FString> ReadLocalFileByEnum(const EPathDir EPD, const FString& FileName);
	
	// Write Local File
	UFUNCTION(BlueprintCallable, Category="FH|ReadWriteLocalFile")
	static bool WriteLocalFileByStr(const FString& FilePath, const FString& FileName, const FString& Content);

	UFUNCTION(BlueprintCallable, Category="FH|ReadWriteLocalFile")
	static bool WriteLocalFileByEnum(const EPathDir EPD, const FString& FileName, const FString& Content);
};