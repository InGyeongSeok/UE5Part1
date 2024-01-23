// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.generated.h"

/**
 * 
 */
UCLASS()
class OBJECTREFLECTION_API UPerson : public UObject
{
	GENERATED_BODY()
	
public:
	UPerson();

	//�𸮾󿡼� �ش� �Լ��� ������ �� �ֵ��� ��ũ�� ����.
	UFUNCTION()
	virtual void DoLesson();

	//�� ���� ����鿡 �����Ͽ� ���� �������ų�, �����ϴ� �Լ�.
	const FString& GetName() const;
	void SetName(const FString& InName);

protected:
	//�𸮾󿡼� �ش� ��� ������ ������ �� �ֵ��� ��ũ�� ����.
	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Year;

private:

};
