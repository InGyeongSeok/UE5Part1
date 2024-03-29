﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::Init()
{
	Super::Init();

	TCHAR LogCharArray[] = TEXT("Hello unreal"); //TCHAR의 배열
	UE_LOG(LogTemp, Log, TEXT("%s"),  LogCharArray);

	FString LogCharString = LogCharArray; // FString으로 넣었다
	UE_LOG(LogTemp, Log, TEXT("%s"), *LogCharString);



	// FString에서 꺼내오면 const TCHAR* 형태로 되어있다. 
	const TCHAR* LogCharPointer = *LogCharString; //FString을 가지고 올때, 고칠 수 없는 형태로 참조하도록 보통 선언되어있다.
	TCHAR* LogCharaDataPtr = LogCharString.GetCharArray().GetData(); // FString을 가지고 올때, 고칠 수 있는 형태로 참조하도록 선언하는 방법 // 내부에 있는 배열에서 데이터를 가져올래



	TCHAR LogCharaArrayWithSize[100]; //배열로 가져오고 싶은 경우
	FCString::Strcpy(LogCharaArrayWithSize, LogCharString.Len(), *LogCharString); //저수준의 복사
	// 어디에? 얼만큼? 어디에서? 의 순서대로 
	// Strcpy(TCHAR * dst, Length, Buffer)


	//유용한 함수

	if (LogCharString.Contains(TEXT("unreal"), ESearchCase::IgnoreCase))  
	{
		int32 index = LogCharString.Find(TEXT("unreal"), ESearchCase::IgnoreCase); //어디에 존재하는지 인덱스를 찾아준다. // Find: 존재한다면 index 찾기
		FString EndString = LogCharString.Mid(index); //unreal이 시작되는 위치에서부터 끝까지 잘라준다. // Mid: index를 기준으로 잘라줄 수 있는 기능
		UE_LOG(LogTemp, Log, TEXT("Find Text : %s"), *EndString);
	}
	//ESearchCase의 경우에는 대소문자를 구별할 것인지 말것인지를 지정할 수 있는, CaseSensitive 와 IgnoreCase가 있다.
	// IgnoreCase: 대소문자 구분 없이.




	FString Left, Right;
	if (LogCharString.Split(TEXT(" "), &Left, &Right)) //왼쪽과 오른쪽을 나눠서 Split을 진행할 수 있음.
	{
		UE_LOG(LogTemp, Log, TEXT("Split Test : %s 와 %s"), *Left, *Right); // 한글 '와' -> 이상하게 출력됨
		//코드를 작성할 때 윈도우에서 한글을 사용했기 때문에, CP949형태의 멀티바이트 String으로 저장이 되었기 때문에 UFT-16을 쓰는 언리얼과 호환이 안된다.
		//Save As.. 를 눌러서, UTF-8 형식으로 바꾸어서 저장해준다. BOM이 붙어있는 유니코드를 사용하도록 하자. -> '와'가 정상적으로 출력됨
	}







	int32 IntValue = 32;
	float FloatValue = 3.141592;

	//로그로 출력하고자 하는 Text로 변환이 가능하다.
	FString FloatIntString = FString::Printf(TEXT("Int %d, Float %f"), IntValue, FloatValue);
	FString FloatString = FString::SanitizeFloat(FloatValue); //float 규약 복잡하다 -> 정화가 필요하다
	FString IntString = FString::FromInt(IntValue);
	//해당 정수를 소수나, 정수로 바꿀 수 있다. => 다소 직관적인 편.
	UE_LOG(LogTemp, Log, TEXT("%s"), *FloatIntString);
	UE_LOG(LogTemp, Log, TEXT("Int %s, Float %s"), *IntString, *FloatString);





	// atoi랑 atof를 이용해서 값을 돌려보는 방법 -> 위험하다!
	int32 IntValueFromString = FCString::Atoi(*IntString);
	float FloatValueFromString = FCString::Atof(*FloatString);
	FString FloatIntString2 = FString::Printf(TEXT("Int %d, Float %f"), IntValueFromString, FloatValueFromString);
	UE_LOG(LogTemp, Log, TEXT("%s"), *FloatIntString2);







	//FName이 대소문자를 구별하지 않는다는 것을 보여주는 Sample 코드. -> 결과 같음
	FName key1(TEXT("PELVIS"));
	FName key2(TEXT("pelvis"));
	UE_LOG(LogTemp, Log, TEXT("FName 비교 결과 : %s"), key1 == key2 ? TEXT("같음") : TEXT("다름"));




	for (int i = 0; i < 10000; ++i)
	{

		// 이렇게 생성자에 문자열을 넣으면, FName이 문자열을 key로 변환한 다음에
		// 이 key가 전역 Pool에 있는지를 조사하는 작업을 거친다.
		FName SearchInNamePool = FName(TEXT("pelvis")); //빈번한 작업이 있으면 오버헤드가 높아진다
		
		
		const static FName StaticOnlyOnce(TEXT("pelvis"));
		// 그러므로 이렇게 한번만 처리해주자
		// 처음 초기화할때 데이터를 저장하고 local static으로 선언했으니 다시 찾을 일이 없다.
		//로컬 static을 이용해서 그냥 한번만 선언하고, 이후에는 그냥 끌어다 쓰겠다는 걸 의미한다.
		//Tick 같은 함수에 FName을 넣으면 오버헤드가 발생할 수 있다.
	}
}
