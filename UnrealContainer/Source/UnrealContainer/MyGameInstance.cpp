// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Algo/Accumulate.h" //Accumulate 알고리즘

FString MakeRandomName()
{
	TCHAR FirstChar[] = TEXT("김이박최");
	TCHAR MiddleChar[] = TEXT("상혜지성");
	TCHAR LastChar[] = TEXT("수은원연");

	TArray<TCHAR> RandArray;
	RandArray.SetNum(3);
	RandArray[0] = FirstChar[FMath::RandRange(0, 3)];
	RandArray[1] = MiddleChar[FMath::RandRange(0, 3)];
	RandArray[2] = LastChar[FMath::RandRange(0, 3)];

	return RandArray.GetData();
	//다음과 같은 함수를 구성하는데, TArray<TCHAR>의 경우에는 TCHAR 배열을 포함하고 있는 컨테이너라,
	//포인터 값을 넘겨주면 알아서 FString을 만들어 낼 수 있게 된다.
}

void UMyGameInstance::Init()
{
	Super::Init();

	const int32 ArrayNum = 10;
	TArray<int32> Int32Array;

	for (int32 ix = 1; ix <= ArrayNum; ++ix) //1부터 10까지 배열에 추가
	{
		Int32Array.Add(ix);
	}

	Int32Array.RemoveAll( //짝수 제거
		[](int32 Val)
		{
			return Val % 2 == 0;
		}
	);

	Int32Array += {2, 4, 6, 8, 10}; //짝수 추가


	TArray<int32> Int32ArrayCompare;
	int32 CArray[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8 , 10 };
	Int32ArrayCompare.AddUninitialized(ArrayNum); //초기화되지 않는 데이터 10개
	FMemory::Memcpy(Int32ArrayCompare.GetData(), CArray, sizeof(int32) * ArrayNum); //복제

	ensure(Int32Array == Int32ArrayCompare);

	//Development Editor는 추적은 가능하지만(중단점 가능) 최적화되어 있기 때문에 상세 내용을 볼 수 없다.
	//Debug Editor로 바꾸면 상세 내용을 볼 수 있다.

	int32 Sum = 0;
	for (const int32& Int32Elem : Int32Array)
	{
		Sum += Int32Elem;
	}

	ensure(Sum == 55);

	int32 SumByAlgo = Algo::Accumulate(Int32Array, 0);
	ensure(Sum == SumByAlgo);

	TSet<int32> Int32Set;
	for (int32 ix = 1; ix <= ArrayNum; ++ix)
	{
		Int32Set.Add(ix);
	}

	Int32Set.Remove(2);
	Int32Set.Remove(4);
	Int32Set.Remove(6);
	Int32Set.Remove(8);
	Int32Set.Remove(10);
	Int32Set.Add(2); //가장 마지막에 빠진 요소에 대해서 빈틈을 채워 넣는 방식으로 
	Int32Set.Add(4);
	Int32Set.Add(6);
	Int32Set.Add(8);
	Int32Set.Add(10);

	const int32 StudentNum = 300;
	for (int32 ix = 1; ix <= StudentNum; ++ix)
	{
		StudentsData.Emplace(FStudentData(MakeRandomName(), ix));
		//구조체 자체를 반복해서 복사해내는 것은 아무래도 효율적인 문제가 있기 때문에, Add (외부에서 복사) 보다는 Emplace ( 내부에서 생성 )을 활용하기로 한다.
	}

	//Algo::Transform(SourceData, Target, Lambda Function) 
	//소스 데이터에서, 목적지로, 어떤 데이터를 끄집을래? 이런 것
	//위 과정에서 TArray와 TSet의 차이점을 알려고 한다.
	TArray<FString> AllStudentsNames;
	Algo::Transform(StudentsData, AllStudentsNames,
		[](const FStudentData& Val)
		{
			return Val.Name;
		}
	);


	UE_LOG(LogTemp, Log, TEXT("모든 학생 이름의 수 : %d"), AllStudentsNames.Num());

	TSet<FString> AllUniqueNames;
	Algo::Transform(StudentsData, AllUniqueNames,
		[](const FStudentData& Val)
		{
			return Val.Name;
		}
	);

	UE_LOG(LogTemp, Log, TEXT("중복 없는 학생 이름의 수 : %d"), AllUniqueNames.Num());



	// TMap
	Algo::Transform(StudentsData, StudentsMap,
		[](const FStudentData& Val)
		{
			return TPair<int32, FString>(Val.Order, Val.Name);
		}
	);


	UE_LOG(LogTemp, Log, TEXT("순번에 따른 학생 맵의 레코드 수 : %d"), StudentsMap.Num());

	TMap<FString, int32> StudentsMapByUniqueName; //일반 map은 중복을 허용하지 않는다.

	Algo::Transform(StudentsData, StudentsMapByUniqueName,
		[](const FStudentData& Val)
		{
			return TPair<FString, int32>(Val.Name, Val.Order);
		}
	);

	UE_LOG(LogTemp, Log, TEXT("이름에 따른 학생 맵의 레코드 수 : %d"), StudentsMapByUniqueName.Num());

	TMultiMap<FString, int32> StudentMapByName;
	Algo::Transform(StudentsData, StudentMapByName,
		[](const FStudentData& Val)
		{
			return TPair<FString, int32>(Val.Name, Val.Order);
		}
	);

	UE_LOG(LogTemp, Log, TEXT("이름에 따른 학생 멀티맵의 레코드 수 : %d"), StudentMapByName.Num());

	const FString TargetName(TEXT("이혜은"));
	TArray<int32> AllOrders;
	StudentMapByName.MultiFind(TargetName, AllOrders);

	UE_LOG(LogTemp, Log, TEXT("이름이 %s인 학생 수 : %d"), *TargetName, AllOrders.Num());

	//이번에는 FStudentData를 Set에 넣어보자.
	//일반적인 구조체의 형식으로 그냥 넣어버리면 에러가 겁나 많이 뜨는 걸 확인할 수 있음.
	//즉, GetTypeHash가 지정이 안되어 있어서 진행할 수 없다는 것임.
	TSet<FStudentData> StudentsSet;
	for (int32 ix = 1; ix <= StudentNum; ++ix)
	{
		StudentsSet.Emplace(FStudentData(MakeRandomName(), ix));
	}

}
