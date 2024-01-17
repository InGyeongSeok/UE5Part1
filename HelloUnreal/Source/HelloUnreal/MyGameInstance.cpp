// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::Init()
{
	Super::Init(); //부모 클래스에서 상속을 받을 때는 super 키워드!!

	UE_LOG(LogTemp, Log, TEXT("%s"), TEXT("Hello Unreal"));
}
