// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

USTRUCT()
struct FStudentData
{
	GENERATED_BODY()

	FStudentData()
	{
		Name = TEXT("홍길동");
		Order = -1;
	}

	FStudentData(FString InName, int32 InOrder) : Name(InName), Order(InOrder) {}

	//이번에는 FStudentData를 Set에 넣어보자
	bool operator==(const FStudentData& InOther) const
	{
		return Order == InOther.Order;
	}

	friend FORCEINLINE uint32 GetTypeHash(const FStudentData& InStudentData)
	{
		return GetTypeHash(InStudentData.Order);
	}

	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Order;
};

/**
 * 
 */
UCLASS()
class UNREALCONTAINER_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:

	virtual void Init() override;

private:
	TArray<FStudentData> StudentsData;
	//해당 경우는 값 타입이라서 리플렉션 관리를 하지 않아도 됨 (구조체니까) 
	//UPROPERTY를 굳이나 붙이지 않아도 된다. ⇒ 데이터의 관리 목적을 두기 때문.

	UPROPERTY()
	TArray<TObjectPtr<class UStudent>> Students;
	//다음과 같이 지금 포인터를 관리하는 경우에는 언리얼 엔진에서 메모리를 관리할 수 있도록 하기 위해, UPROPERTY를 사용해준다. ⇒ 선택이 아닌 필수임.

	TMap<int32, FString> StudentsMap;
};
