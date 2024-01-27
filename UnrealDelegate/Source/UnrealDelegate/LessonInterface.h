// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LessonInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULessonInterface : public UInterface
{
	GENERATED_BODY()
}; //타입 정보를 보관하기 위해서 생성된 클래스

/**
 * 
 */
class UNREALDELEGATE_API ILessonInterface
{
	GENERATED_BODY()

public:
	virtual void DoLesson()
	{
		UE_LOG(LogTemp, Log, TEXT("수업에 입장합니다."));
	}
};

//virtual void DoLesson() = 0; 만약에 추상화를 넣은 함수를 헤더에 선언하지 않으면 빌드 자체가 안됨.
//Pure Virtual Function의 경우, 그냥 이렇게 행동할 것임!이렇게 가이드라인만 줄 뿐 디테일 한 기능이 없기 때문에, 구현이 없다면 문제가 되기 때문.
//언리얼 C++ 인터페이스의 경우에는 사실 굳이 추상화를 유지할 필요는 없다..
//⇒ 인터페이스에서도 구현이 가능하다는 소리!
//근데 이렇게 된다면 인터페이스를 상속받은 클래스의 경우는 굳이 해당 행동 양상에 대해서 구현할 필요는 없다. (아니 그럼 인터페이스의 목적이 은근 갈리겠는데 ? )