// Fill out your copyright notice in the Description page of Project Settings.


#include "Person.h"
#include "Card.h"

UPerson::UPerson()
{
	Name = TEXT("홍길동");
	Card = CreateDefaultSubobject<UCard>(TEXT("NAME_Card")); //첫번째 인자는 FName이라는 식별자를 넣어줘야 한다 ->고유한 이름이면 된다
	//앞에 Name_ 이라고 하면 FName이라는 것을 알 수 있다.(String이 아니라!)
}	
