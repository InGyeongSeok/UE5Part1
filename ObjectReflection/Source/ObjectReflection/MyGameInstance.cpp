// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "Student.h"
#include "Teacher.h"

UMyGameInstance::UMyGameInstance()
{
	SchoolName = TEXT("기본학교"); //이 기본값은 Class Default Object라는 템플릿 객체에 저장이 된 채로 존재
}

void UMyGameInstance::Init()
{
	Super::Init();

	UE_LOG(LogTemp, Log, TEXT("================================="));
	UClass* ClassRuntime = GetClass(); //런타임에서 클래스 정보 얻어옴
	UClass* ClassCompile = UMyGameInstance::StaticClass(); //컴파일 타임에서 클래스 정보 얻어옴
	//check(ClassRuntime == ClassCompile);  //check(expr) => ASSERTION 매크로 함수가 내부적으로 존재한다.
	//ensure(ClassRuntime != ClassCompile); //ensure(expr) => 문제가 생기면 에디터에 투척한다.
	//ensureMsgf(ClassRuntime != ClassCompile, TEXT("일부러 에러를 발생시킨 코드")); //ensureMsgf(expr, TEXT("문자....")) => 문제가 생기면 에디터에 투척하고, TEXT내 문자열을 호출.
	
	UE_LOG(LogTemp, Log, TEXT("학교를 담당하는 클래스 이름 : %s"), *ClassRuntime->GetName());

	SchoolName = TEXT("청강문화산업대학교");

	UE_LOG(LogTemp, Log, TEXT("학교 이름 : %s"), *SchoolName);
	UE_LOG(LogTemp, Log, TEXT("학교 이름 기본값 : %s"), *GetClass()->GetDefaultObject<UMyGameInstance>()->SchoolName);
	//여기 보면 GetClass가 있는데 현재 동작하고 있는 클래스에 대해서 받아주는 거라,
	//가져온 다음에, GetDefaultObject<Type>()->Member을 가져오는 것을 확인할 수 있음.
	//ClassDefaultObject는 에디터가 활성화 되기 이전에 초기화가 되는 순서를 가지고 있음.
	//즉 에디터가 활성화가 되고나서 초기화를 진행한다고 해도 의미가 딱히 없는 것임.
	//그래서 알아야 되는 규칙
	//CDO를 고치는 생성자 코드를 변경하는 경우에는 에디터를 한번 꺼줘야 한다.
	UE_LOG(LogTemp, Log, TEXT("================================="));


	UStudent* Student = NewObject<UStudent>();
	UTeacher* Teacher = NewObject<UTeacher>();
	Student->SetName(TEXT("석인경"));
	UE_LOG(LogTemp, Log, TEXT("새로운 학생 이름 %s"), *Student->GetName());

	FString CurrentTeacherName;
	FString NewTeacherName(TEXT("이득우"));
	//해당 클래스 내부에서 Name이라는 프로퍼티가 존재하는 지를 파악하고.
	FProperty* NameProp = UTeacher::StaticClass()->FindPropertyByName(TEXT("Name"));
	if (NameProp)
	{
		//해당 프로퍼티에 있는 값을 저장하고자 하는 곳에 그대로 끌고 온다.
		NameProp->GetValue_InContainer(Teacher, &CurrentTeacherName);
		UE_LOG(LogTemp, Log, TEXT("현재 선생님 이름 %s"), *CurrentTeacherName);

		NameProp->SetValue_InContainer(Teacher, &NewTeacherName);
		UE_LOG(LogTemp, Log, TEXT("새로운 선생님 이름 %s"), *Teacher->GetName());
	}

	UE_LOG(LogTemp, Log, TEXT("================================="));
	Student->DoLesson();

	UFunction* DoLessonFunc = Teacher->GetClass()->FindFunctionByName(TEXT("DoLesson"));
	if (DoLessonFunc) {
		Teacher->ProcessEvent(DoLessonFunc, nullptr);
	}
	UE_LOG(LogTemp, Log, TEXT("================================="));

}
