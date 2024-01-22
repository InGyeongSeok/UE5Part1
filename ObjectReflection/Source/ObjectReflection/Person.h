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

	//언리얼에서 해당 함수를 관리할 수 있도록 매크로 설정.
	UFUNCTION()
	virtual void DoLesson();

	//비 공개 멤버들에 접근하여 값을 가져오거나, 변경하는 함수.
	const FString& GetName() const;
	void SetName(const FString& InName);

protected:
	//언리얼에서 해당 멤버 변수를 관리할 수 있도록 매크로 설정.
	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Year;

private:

};
