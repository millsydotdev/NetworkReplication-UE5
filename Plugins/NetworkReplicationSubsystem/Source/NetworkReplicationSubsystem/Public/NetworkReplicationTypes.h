// Copyright © 2025 Millsy.dev. All Rights Reserved.
//
// NetworkReplicationTypes.h
// Defines types and structs for network replication with hot joining support

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Actor.h"
#include "NetworkReplicationTypes.generated.h"

/**
 * Attachment information for hot joining support
 * When replicated, this struct allows late-joining clients to properly attach actors
 */
USTRUCT(BlueprintType)
struct NETWORKREPLICATIONSUBSYSTEM_API FAttachmentInfo
{
	GENERATED_BODY()

    /** The component to attach */
    UPROPERTY(BlueprintReadWrite, Category = "Attachment")
    TObjectPtr<USceneComponent> Component = nullptr;

	/** Socket name for attachment */
	UPROPERTY(BlueprintReadWrite, Category = "Attachment")
	FName SocketName = NAME_None;

	/** Relative transform for attachment */
	UPROPERTY(BlueprintReadWrite, Category = "Attachment")
	FTransform RelativeTransform = FTransform::Identity;

	/** Owner actor for attachment */
	UPROPERTY(BlueprintReadWrite, Category = "Attachment")
	TObjectPtr<AActor> Owner = nullptr;

	/** Whether to keep world transform when attaching */
	UPROPERTY(BlueprintReadWrite, Category = "Attachment")
	bool bKeepWorldTransform = true;

	/** Whether this attachment is active */
	UPROPERTY(BlueprintReadWrite, Category = "Attachment")
	bool bIsActive = false;

	FAttachmentInfo()
	{
		Component = nullptr;
		SocketName = NAME_None;
		RelativeTransform = FTransform::Identity;
		Owner = nullptr;
		bKeepWorldTransform = true;
		bIsActive = false;
	}
};

/**
 * Prediction state for client-side prediction with server validation
 * Optional hooks for visual prediction without full rewind
 */
USTRUCT(BlueprintType)
struct NETWORKREPLICATIONSUBSYSTEM_API FPredictionState
{
	GENERATED_BODY()

	/** Client send time for latency compensation */
	UPROPERTY(BlueprintReadWrite, Category = "Prediction")
	double ClientSendTime = 0.0;

    /** Input frame number for prediction */
    UPROPERTY(BlueprintReadWrite, Category = "Prediction")
    int32 InputFrame = 0;

	/** Whether prediction is active */
	UPROPERTY(BlueprintReadWrite, Category = "Prediction")
	bool bIsPredicting = false;

	/** Prediction correction factor */
	UPROPERTY(BlueprintReadWrite, Category = "Prediction")
	float CorrectionFactor = 1.0f;

	FPredictionState()
	{
		ClientSendTime = 0.0;
		InputFrame = 0;
		bIsPredicting = false;
		CorrectionFactor = 1.0f;
	}
};

/**
 * Animation prediction data for client-side visual feedback
 */
USTRUCT(BlueprintType)
struct NETWORKREPLICATIONSUBSYSTEM_API FAnimationPredictionData
{
	GENERATED_BODY()

	/** The montage being predicted */
	UPROPERTY(BlueprintReadWrite, Category = "Animation Prediction")
	TObjectPtr<class UAnimMontage> Montage = nullptr;

	/** Play rate for prediction */
	UPROPERTY(BlueprintReadWrite, Category = "Animation Prediction")
	float PlayRate = 1.0f;

	/** Starting position for prediction */
	UPROPERTY(BlueprintReadWrite, Category = "Animation Prediction")
	float StartingPosition = 0.0f;

	/** Client prediction time */
	UPROPERTY(BlueprintReadWrite, Category = "Animation Prediction")
	double PredictionTime = 0.0;

	/** Whether this prediction is valid */
	UPROPERTY(BlueprintReadWrite, Category = "Animation Prediction")
	bool bIsValid = false;

	FAnimationPredictionData()
	{
		Montage = nullptr;
		PlayRate = 1.0f;
		StartingPosition = 0.0f;
		PredictionTime = 0.0;
		bIsValid = false;
	}
};
