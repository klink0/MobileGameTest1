// Fill out your copyright notice in the Description page of Project Settings.

#include "MobileGameTest1.h"
#include "ClassTest.h"

ClassTest::ClassTest()
{
}

ClassTest::~ClassTest()
{
}

/** Get Hello World string. */
UFUNCTION(BlueprintCallable, BlueprintPure, Category = "C++")
FString GetHWString();

FString GetHWString(){
	return "Hello World!";
}