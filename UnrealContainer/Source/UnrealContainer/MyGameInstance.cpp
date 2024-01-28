// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Algo/Accumulate.h" //Accumulate 알고리즘

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


}
