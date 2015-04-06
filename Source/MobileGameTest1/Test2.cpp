// Fill out your copyright notice in the Description page of Project Settings.

#include "MobileGameTest1.h"
#include "Test2.h"


// Sets default values
ATest2::ATest2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isConnected = false;
}

// Called when the game starts or when spawned
void ATest2::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATest2::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

bool ATest2::PostJSONHttp(FString login)
{
	// Create a writer and hold it in this FString
	FString JsonStr;
	TSharedRef< TJsonWriter<TCHAR, TCondensedJsonPrintPolicy<TCHAR> > > JsonWriter = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR> >::Create(&JsonStr);
	JsonWriter->WriteObjectStart();
	JsonWriter->WriteValue(TEXT("login"), login);
	JsonWriter->WriteObjectEnd();
	// Close the writer and finalize the output such that JsonStr has what we want
	JsonWriter->Close();

	TSharedRef<IHttpRequest> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json; charset=utf-8"));
	HttpRequest->SetURL(TEXT("http://192.168.1.30:1337"));
	HttpRequest->SetVerb(TEXT("POST"));
	HttpRequest->SetContentAsString(JsonStr);
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &ATest2::HttpCompleteCallback);
	HttpRequest->ProcessRequest();
	return true;
}

void ATest2::HttpCompleteCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	FString MessageBody = "";

	// If HTTP fails client-side, this will still be called but with a NULL shared pointer!
	if (!Response.IsValid())
	{
		MessageBody = "{\"success\":\"Error: Unable to process HTTP Request!\"}";
	}
	else if (EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		MessageBody = Response->GetContentAsString();
	}
	else
	{
		MessageBody = FString::Printf(TEXT("{\"success\":\"HTTP Error: %d\"}"), Response->GetResponseCode());
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, MessageBody);
	ATest2::ParseJSON(MessageBody);
}

void ATest2::ParseJSON(FString message)
{
	FString JsonRaw = message;
	TSharedPtr<FJsonObject> JsonParsed;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonRaw);
	if (FJsonSerializer::Deserialize(JsonReader, JsonParsed))
	{
		FString ResMessage = JsonParsed->GetStringField("message");
		FString ResHealth = JsonParsed->GetStringField("health");
		Health = FCString::Atof(*ResHealth);
		Mana = FCString::Atof(*JsonParsed->GetStringField("mana"));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::White, ResMessage + " " + ResHealth);
		isConnected = true;
	}
}