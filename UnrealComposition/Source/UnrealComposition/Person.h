// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCOMPOSITION_API UPerson : public UObject
{
	GENERATED_BODY()


public:
	UPerson();

	FORCEINLINE const FString& GetName() const { return Name; }
	FORCEINLINE void SetName(const FString& InName) { Name = InName; }


	FORCEINLINE class UCard* GetCard() const { return Card; }
	FORCEINLINE void SetCard(class UCard* InCard) { Card = InCard; }
protected:
	UPROPERTY()
	FString Name;

	//UPROPERTY() //이게 4버전까지는 정석
	//class UCard* card; //컴포지션의 경우에는 전방선언을 사용하는 것이 좋음.
	////이유 : 어차피 포인터로 선언을 할 것이고 포인터의 크기는 이미 지정이 되어있어서, 의존성을 낮추는 데 용이하기 때문.
	
	UPROPERTY()
	TObjectPtr<class UCard> Card;

};
