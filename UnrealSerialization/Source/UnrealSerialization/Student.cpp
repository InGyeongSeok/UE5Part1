// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"

UStudent::UStudent()
{
	Order = -1;
	Name = TEXT("홍길동");
}

void UStudent::Serialize(FArchive& Ar)
{
	Super::Serialize(Ar); //언ㅇ리얼 오브젝트가 가져야되는 기본적인 정보들을 처리

	Ar << Order;
	Ar << Name;
}
