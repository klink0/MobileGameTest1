// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Http.h"
#include "Json.h"
#include "Test2.generated.h"


UCLASS()
class MOBILEGAMETEST1_API ATest2 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATest2();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TEST)
	bool isTest;
	
	UFUNCTION(BlueprintCallable, Category = "HTTP")
	void PostJSONHttp();

	void HttpCompleteCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
