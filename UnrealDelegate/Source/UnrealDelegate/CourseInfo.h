// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CourseInfo.generated.h"


DECLARE_MULTICAST_DELEGATE_TwoParams(FCourseInfoOnChangedSignature, const FString&, const FString&);
//F로 시작, 클래스 이름 넣고 on, 학사정보 변경 -> changed, 델리게이트는 signature(접미사)를 많이 사용함 , 두개 인자 받음

/**
 * 
 */
UCLASS()
class UNREALDELEGATE_API UCourseInfo : public UObject
{
	GENERATED_BODY()
	
public:
	UCourseInfo();

	FCourseInfoOnChangedSignature OnChanged;

	void ChangeCourseInfo(const FString& InSchoolName, const FString& InNewContents);

private:
	FString Contents;
};
