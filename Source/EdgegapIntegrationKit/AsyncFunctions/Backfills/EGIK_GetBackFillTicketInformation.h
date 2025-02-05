﻿// Copyright (c) Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "EGIK_GetBackFillTicketInformation.generated.h"

USTRUCT(BlueprintType)
struct FEGIK_GetBackFillTicketInformationResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Edgegap Integration Kit | Backfill")
	FString Id;

	UPROPERTY(BlueprintReadWrite, Category = "Edgegap Integration Kit | Backfill")
	FString Profile;

	UPROPERTY(BlueprintReadWrite, Category = "Edgegap Integration Kit | Backfill")
	TMap<FString, FString> Tickets;

	UPROPERTY(BlueprintReadWrite, Category = "Edgegap Integration Kit | Backfill")
	FString Status;

	UPROPERTY(BlueprintReadWrite, Category = "Edgegap Integration Kit | Backfill")
	FString AssignedTicket;

	UPROPERTY(BlueprintReadWrite, Category = "Edgegap Integration Kit | Backfill")
	FString GroupId;

	UPROPERTY(BlueprintReadWrite, Category = "Edgegap Integration Kit | Backfill")
	FString CreatedAt;
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetBackFillTicketInformationResponse, const FEGIK_GetBackFillTicketInformationResponse&, Response, const FEGIK_ErrorStruct&, Error);
UCLASS()
class EDGEGAPINTEGRATIONKIT_API UEGIK_GetBackFillTicketInformation : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Edgegap Integration Kit | Backfill")
	static UEGIK_GetBackFillTicketInformation* GetBackFillTicketInformation(const FString& backfillId, const FString& MatchmakingURL, const FString& AuthToken);

	void OnResponseReceived(TSharedPtr<IHttpRequest> HttpRequest, TSharedPtr<IHttpResponse> HttpResponse, bool bArg);
	virtual void Activate() override;

	UPROPERTY(BlueprintAssignable, Category = "Edgegap Integration Kit | Backfill")
	FGetBackFillTicketInformationResponse OnSuccess;

	UPROPERTY(BlueprintAssignable, Category = "Edgegap Integration Kit | Backfill")
	FGetBackFillTicketInformationResponse OnFailure;

private:
	FString Var_BackfillId;
	FString Var_MatchmakingURL;
	FString Var_AuthToken;
};
