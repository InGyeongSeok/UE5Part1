// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
//결정적으로 저 OBJECTREFLECTION_API가 문제가 되는데, 해당 의미가 외부에 있는 모듈을 인식하게 하는 것이었다보니까, 인식 불가로 인해 문제가 생기게 된다.
//따라서 이를 현재 프로젝트의 이름에 맞게 끔 만들어야 한다.
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
