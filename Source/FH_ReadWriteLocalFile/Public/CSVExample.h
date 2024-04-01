#pragma once

#include "Engine/DataTable.h"
#include "CSVExample.generated.h"

USTRUCT(BlueprintType)
struct FCSVStruct : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	FCSVStruct()
	{
		Q = "";
		A = "";
		P = nullptr;
		F = nullptr;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CSV", meta=(AllowPrivateAccess=true))
	FString Q;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CSV", meta=(AllowPrivateAccess=true))
	FString A;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CSV", meta=(AllowPrivateAccess=true))
	USoundBase* P;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="CSV", meta=(AllowPrivateAccess=true))
	UAnimMontage* F;
};