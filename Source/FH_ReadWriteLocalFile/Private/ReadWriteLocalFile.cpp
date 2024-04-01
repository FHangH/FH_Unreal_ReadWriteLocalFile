#include "ReadWriteLocalFile.h"
#include "Sound/SoundBase.h"

// Enum Convert String
FString UReadWriteLocalFile::ConvPathToString(const EPathDir EPD)
{
	if (EPD == EPathDir::EPD_RootDir) return FPaths::RootDir();
	if (EPD == EPathDir::EPD_ProjectDir) return FPaths::ProjectDir();
	if (EPD == EPathDir::EPD_ProjectConfigDir) return FPaths::ProjectConfigDir();
	if (EPD == EPathDir::EPD_ProjectContentDir) return FPaths::ProjectContentDir();
	if (EPD == EPathDir::EPD_ProjectLogDir) return FPaths::ProjectLogDir();
	if (EPD == EPathDir::EPD_ProjectPluginsDir) return FPaths::ProjectPluginsDir();
	if (EPD == EPathDir::EPD_ProjectSavedDir) return FPaths::ProjectSavedDir();
	if (EPD == EPathDir::EPD_ProjectUserDir) return FPaths::ProjectUserDir();
	if (EPD == EPathDir::EPD_EngineDir) return FPaths::EngineDir();
	if (EPD == EPathDir::EPD_EngineConfigDir) return FPaths::EngineConfigDir();
	if (EPD == EPathDir::EPD_EngineContentDir) return FPaths::EngineContentDir();
	if (EPD == EPathDir::EPD_EnginePluginsDir) return FPaths::EnginePluginsDir();
	if (EPD == EPathDir::EPD_EngineSavedDir) return FPaths::EngineSavedDir();
	if (EPD == EPathDir::EPD_EngineSourceDir) return FPaths::EngineSourceDir();
	if (EPD == EPathDir::EPD_LaunchDir) return FPaths::LaunchDir();
	if (EPD == EPathDir::EPD_GameSourceDir) return FPaths::GameSourceDir();
	return {};
}

// TArray<FString> Convert To FString
FString UReadWriteLocalFile::ConvertArrayToString(const TArray<FString>& TextResults)
{
	FString TextContent;
	for (const auto& result : TextResults)
	{
		TextContent += FString::Printf(TEXT("%s\n"), *result);
	}
	return TextContent;
}

// Check Local File Exists
bool UReadWriteLocalFile::IsLocalFileExistsByStr(const FString& FilePath)
{
	return FPlatformFileManager::Get().GetPlatformFile().FileExists(*FPaths::ConvertRelativePathToFull(FilePath));
}

bool UReadWriteLocalFile::IsLocalFileExistsByEnum(const EPathDir EPD)
{
	return FPlatformFileManager::Get().GetPlatformFile().FileExists(*ConvPathToString(EPD));
}

// Create Local File Path And File
bool UReadWriteLocalFile::CreatePathAndFileByStr(const FString& FilePath, const FString& FileName, FString& Path)
{
	const FString tempName = FileName == "" ? "" : FString::Printf(TEXT("/%s"), *FileName);
	Path = FString::Printf(TEXT("%s%s"), *FilePath, *tempName);
	FPaths::MakeValidFileName(*Path);

	if (IsLocalFileExistsByStr(Path))
	{
		return true;
	}
	return FFileHelper::SaveStringToFile(TEXT(""), *Path, FFileHelper::EEncodingOptions::ForceUTF8);
}

bool UReadWriteLocalFile::CreatePathAndFileByEnum(const EPathDir EPD, const FString& FileName, FString& Path)
{
	Path = FString::Printf(TEXT("%s%s"), *ConvPathToString(EPD), *FileName);
	FPaths::MakeValidFileName(*Path);
	
	if (IsLocalFileExistsByStr(Path))
	{
		return true;
	}
	return FFileHelper::SaveStringToFile(TEXT(""), *Path, FFileHelper::EEncodingOptions::ForceUTF8);
}

// Read Local File
TArray<FString> UReadWriteLocalFile::ReadLocalFileByStr(const FString& FilePath, const FString& FileName)
{
	const FString tempName = FileName == "" ? "" : FString::Printf(TEXT("/%s"), *FileName);
	const auto Path = FString::Printf(TEXT("%s%s"), *FilePath, *tempName);
	FPaths::MakeValidFileName(*Path);
	TArray<FString> TextResults;

	if (IsLocalFileExistsByStr(Path))
	{
		if (FFileHelper::LoadFileToStringArray(TextResults, *Path)) return TextResults;
		return {};
	}
	return {};
}

TArray<FString> UReadWriteLocalFile::ReadLocalFileByEnum(const EPathDir EPD, const FString& FileName)
{
	const auto Path = FString::Printf(TEXT("%s%s"), *ConvPathToString(EPD), *FileName);
	FPaths::MakeValidFileName(*Path);
	TArray<FString> TextResults;

	if (IsLocalFileExistsByStr(Path))
	{
		if (FFileHelper::LoadFileToStringArray(TextResults, *Path)) return TextResults;
		return {};
	}
	return {};
}

// Write Local File
bool UReadWriteLocalFile::WriteLocalFileByStr(const FString& FilePath, const FString& FileName, const FString& Content)
{
	const FString tempName = FileName == "" ? "" : FString::Printf(TEXT("/%s"), *FileName);
	const auto Path = FString::Printf(TEXT("%s%s"), *FilePath, *tempName);
	FPaths::MakeValidFileName(*Path);

	if (IsLocalFileExistsByStr(Path))
	{
		return FFileHelper::SaveStringToFile(Content, *Path, FFileHelper::EEncodingOptions::ForceUTF8);
	}
	return false;
}

bool UReadWriteLocalFile::WriteLocalFileByEnum(const EPathDir EPD, const FString& FileName, const FString& Content)
{
	const auto Path = FString::Printf(TEXT("%s%s"), *ConvPathToString(EPD), *FileName);
	FPaths::MakeValidFileName(*Path);

	if (IsLocalFileExistsByStr(Path))
	{
		return FFileHelper::SaveStringToFile(Content, *Path, FFileHelper::EEncodingOptions::ForceUTF8);
	}
	return false;
}

// Datatable, CSV
UDataTable* UReadWriteLocalFile::ReadCSVToDataTable(const EPathDir EPD, const FString& FileName, const FCSVStruct& TableStruct)
{
	if (FileName == "") return nullptr;
	const auto Path = FPaths::ConvertRelativePathToFull(FString::Printf(TEXT("%s%s.csv"), *ConvPathToString(EPD), *FileName));

	if (FString Data; FFileHelper::LoadFileToString(Data, *Path))
	{
		if (const auto DT = NewObject<UDataTable>())
		{
			DT->RowStruct = TableStruct.StaticStruct();
			DT->CreateTableFromCSVString(Data);
			return DT;
		}
	}
	return nullptr;
}

FCSVStruct& UReadWriteLocalFile::GetDataTableRowByRowName(const UDataTable* DataTable, const FName& RowName)
{
	if (auto* DataRow = DataTable->FindRow<FCSVStruct>(RowName, FString(""), false); DataRow != nullptr)
	{
		return *DataRow;
	}
	static FCSVStruct DefaultRow;
	return DefaultRow;
}