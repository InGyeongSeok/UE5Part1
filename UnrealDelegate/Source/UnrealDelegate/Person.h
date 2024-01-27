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

	//UPROPERTY() //�̰� 4���������� ����
	//class UCard* card; //���������� ��쿡�� ���漱���� ����ϴ� ���� ����.
	////���� : ������ �����ͷ� ������ �� ���̰� �������� ũ��� �̹� ������ �Ǿ��־, �������� ���ߴ� �� �����ϱ� ����.
	
	UPROPERTY()
	TObjectPtr<class UCard> Card;

};
