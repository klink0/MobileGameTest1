// Fill out your copyright notice in the Description page of Project Settings.

#include "MobileGameTest1.h"
#include "Test2.h"


// Sets default values
ATest2::ATest2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isTest = true;
}

// Called when the game starts or when spawned
void ATest2::BeginPlay()
{
	Super::BeginPlay();
	PostJSONHttp();
}

// Called every frame
void ATest2::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ATest2::PostJSONHttp()
{
	// Create a writer and hold it in this FString
	FString JsonStr;
	TSharedRef< TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR> > > JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR> >::Create(&JsonStr);
	JsonWriter->WriteObjectStart();
	JsonWriter->WriteValue(TEXT("login"), TEXT("kamiruu"));
	JsonWriter->WriteObjectEnd();

	// Close the writer and finalize the output such that JsonStr has what we want
	JsonWriter->Close();

	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
	HttpRequest->SetURL(TEXT("http://localhost:1337"));
	HttpRequest->SetVerb(TEXT("POST"));
	HttpRequest->SetContentAsString(JsonStr);
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &ATest2::HttpCompleteCallback);
	HttpRequest->ProcessRequest();
}

void ATest2::HttpCompleteCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{

}