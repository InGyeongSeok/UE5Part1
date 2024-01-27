// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
//���������� �� OBJECTREFLECTION_API�� ������ �Ǵµ�, �ش� �ǹ̰� �ܺο� �ִ� ����� �ν��ϰ� �ϴ� ���̾��ٺ��ϱ�, �ν� �Ұ��� ���� ������ ����� �ȴ�.
//���� �̸� ���� ������Ʈ�� �̸��� �°� �� ������ �Ѵ�.
UCLASS()
class UNREALDELEGATE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();

	virtual void Init() override;


private:
	UPROPERTY()
	TObjectPtr<class UCourseInfo> CourseInfo;

	UPROPERTY()
	FString SchoolName;
};
