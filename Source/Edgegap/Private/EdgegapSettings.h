// Copyright (c) 2024 Betide Studio. All Rights Reserved.

#pragma once

#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "APIToken/APITokenSettings.h"
#include "Engine/DeveloperSettings.h"
#include "Settings/ProjectPackagingSettings.h"
#include "EdgegapSettings.generated.h"

USTRUCT(BlueprintType)
struct FEdgegapPortConfig
{
	GENERATED_BODY()

	// The internal port number
	UPROPERTY(Config, EditAnywhere, DisplayName = "Port Number")
	int32 Port = 7777;

	// The protocol for this port (TCP, UDP, TCP/UDP)
	UPROPERTY(Config, EditAnywhere, DisplayName = "Protocol")
	FString Protocol = TEXT("TCP/UDP");

	// Whether to check this port
	UPROPERTY(Config, EditAnywhere, DisplayName = "Check Port") 
	bool bToCheck = false;

	// Whether to upgrade to TLS
	UPROPERTY(Config, EditAnywhere, DisplayName = "TLS Upgrade")
	bool bTLSUpgrade = false;

	// Name of the port
	UPROPERTY(Config, EditAnywhere, DisplayName = "Port Name")
	FString Name = TEXT("gameport");
};

USTRUCT(BlueprintType)
struct FEdgegapEnvironmentVariable
{
	GENERATED_BODY()

	// The environment variable key
	UPROPERTY(Config, EditAnywhere, DisplayName = "Key")
	FString Key;

	// The environment variable value
	UPROPERTY(Config, EditAnywhere, DisplayName = "Value")
	FString Value;

	// Whether this variable contains sensitive information
	UPROPERTY(Config, EditAnywhere, DisplayName = "Is Hidden")
	bool bIsHidden = false;
};

UCLASS(config=EditorPerProjectUserSettings, defaultconfig, meta = (DisplayName = "Edgegap Plugin"))
class UEdgegapSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UEdgegapSettings();

	//~ Begin UObject Interface
#if WITH_EDITOR
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateSettings, UEdgegapSettings const*);
	static FOnUpdateSettings OnSettingsChange;

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent);
#endif
	//~ End UObject Interface

	UPROPERTY(EditAnywhere, Category = "API Key", DisplayName = "Authorization Key")
	FString AuthorizationKey;

	UPROPERTY(Config, EditAnywhere, Category = "API Key", DisplayName = "Deployer Key")
	FAPITokenSettings APIToken;

	UPROPERTY(Config, EditAnywhere, Category = "Docker Settings", DisplayName = "Docker Path")
	FString DockerPath = "C:\\Program Files\\Docker\\Docker\\resources\\bin\\docker.exe";

	UPROPERTY(Config, EditAnywhere, Category = "Build Configurations", DisplayName = "Build Configurations")
	EProjectPackagingBuildConfigurations BuildConfiguration = EProjectPackagingBuildConfigurations::PPBC_Development;
	
	UPROPERTY(Config, EditAnywhere, Category = "Build Configurations", DisplayName = "Build Configurations")
	FString OverridableTargetName = FString::Printf(TEXT("%sServer"), FApp::GetProjectName());

	UPROPERTY(Config, EditAnywhere, Category = "Application Info", Meta = (EditCondition = "bIsTokenVerified"), DisplayName = "Application Name")
	FText ApplicationName;

	UPROPERTY(Config, EditAnywhere, Category = "Application Info", Meta = (EditCondition = "bIsTokenVerified"), DisplayName = "Application Image")
	FFilePath ImagePath;

	//Units of vCPU needed (1024 = 1vcpu)
	UPROPERTY(Config, EditAnywhere, Category = "Application Info|Extra Settings", Meta = (EditCondition = "bIsTokenVerified"), DisplayName = "Required CPU")
	int32 RequiredCPU = 1024;

	//Units of memory in MB needed (1024 = 1GB)
	UPROPERTY(Config, EditAnywhere, Category = "Application Info|Extra Settings", Meta = (EditCondition = "bIsTokenVerified"), DisplayName = "Required Memory")
	int32 RequiredMemory = 1024;

	//Units of GPU needed (1024 = 1 GPU)
	UPROPERTY(Config, EditAnywhere, Category = "Application Info|Extra Settings", Meta = (EditCondition = "bIsTokenVerified"), DisplayName = "Required GPU")
	int32 RequiredGPU = 0;

	//The Max duration of the game in minute. 0 means forever.
	UPROPERTY(Config, EditAnywhere, Category = "Application Info|Extra Settings", Meta = (EditCondition = "bIsTokenVerified"), DisplayName = "Max Duration")
	int32 MaxDuration = 0;

	//Estimated maximum time in seconds to deploy, after this time we will consider it not working and retry.
	UPROPERTY(Config, EditAnywhere, Category = "Application Info|Extra Settings", Meta = (EditCondition = "bIsTokenVerified"), DisplayName = "Estimated Maximum Deploy Time")
	int32 EstimatedDeployTime = 120;

	//Entrypoint/Command override of your Container - Leave empty to use the default one
	UPROPERTY(Config, EditAnywhere, Category = "Application Info|Extra Settings", Meta = (EditCondition = "bIsTokenVerified"), DisplayName = "Entrypoint Override")
	FString EntrypointOverride;
	
	//The Arguments to pass to the command
	UPROPERTY(Config, EditAnywhere, Category = "Application Info|Extra Settings", Meta = (EditCondition = "bIsTokenVerified"), DisplayName = "Command Arguments")
	FString CommandArguments;
	
	// Port configurations to include in every deployment
	UPROPERTY(Config, EditAnywhere, Category = "Application Info|Ports and Environment", Meta = (EditCondition = "bIsTokenVerified"), DisplayName = "Additional Ports")
	TArray<FEdgegapPortConfig> AdditionalPorts;
	
	// Default environment variables to include in every deployment
	UPROPERTY(Config, EditAnywhere, Category = "Application Info|Ports and Environment", Meta = (EditCondition = "bIsTokenVerified"), DisplayName = "Default Environment Variables")
	TArray<FEdgegapEnvironmentVariable> DefaultEnvironmentVariables;

	UPROPERTY(Config, EditAnywhere, Category = "Container Registry")
	bool bUseCustomContainerRegistry = false;

	UPROPERTY(Config, EditAnywhere, Category = "Container Registry", Meta = (EditCondition = "bUseCustomContainerRegistry"), DisplayName = "Registry URL")
	FString Registry;

	UPROPERTY(Config, EditAnywhere, Category = "Container Registry", Meta = (EditCondition = "bUseCustomContainerRegistry"), DisplayName = "Repository")
	FString ImageRepository;

	UPROPERTY(Config, EditAnywhere, Category = "Container Registry", Meta = (EditCondition = "bUseCustomContainerRegistry"), DisplayName = "Username")
	FString PrivateRegistryUsername;

	UPROPERTY(Config, EditAnywhere, Category = "Container Registry", Meta = (EditCondition = "bUseCustomContainerRegistry"), DisplayName = "Token")
	FString PrivateRegistryToken;

	UPROPERTY(Config)
	FString Tag;

	UPROPERTY(Config)
	FString VersionName;

	//@TODO: Check the best way to handle verification and toggle edit conditions accordingly
	UPROPERTY(Config, EditAnywhere, Category = "Application Info")
	bool bIsTokenVerified = true;
};

#if UE_ENABLE_INCLUDE_ORDER_DEPRECATED_IN_5_2
#include "CoreMinimal.h"
#endif
