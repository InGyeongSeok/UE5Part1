// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include "Card.h"
#include "CourseInfo.h"

UMyGameInstance::UMyGameInstance()
{
	SchoolName = TEXT("학교");
}

void UMyGameInstance::Init()
{
	Super::Init();

	CourseInfo = NewObject<UCourseInfo>(this); //이번에는 외부에서 선언해보는 방법,  (필요할 때만 생성하는 방법)
	 
	UE_LOG(LogTemp, Log, TEXT("============================"));

	UStudent* Student1 = NewObject<UStudent>();  //이 구문이 실행이 되면 이 오브젝트는 자동으로 소멸 -> 굳이 outer로 설정해 줄 필요 없다.
	Student1->SetName(TEXT("학생1"));
	UStudent* Student2 = NewObject<UStudent>();
	Student2->SetName(TEXT("학생2"));
	UStudent* Student3 = NewObject<UStudent>();
	Student3->SetName(TEXT("학생3"));

	CourseInfo->OnChanged.AddUObject(Student1, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student2, &UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(Student3, &UStudent::GetNotification);
	//AddUObject 자체가 인스턴스를 지정하고 해당 인스턴스 내부에 존재하는 멤버 함수를 묶어주는 방법이다! ⇒ 그래서 이 방법으로 레퍼런스를 지정하는 것임.
	
	CourseInfo->ChangeCourseInfo(SchoolName, TEXT("변경된 학사 정보"));

	UE_LOG(LogTemp, Log, TEXT("============================"));
}
