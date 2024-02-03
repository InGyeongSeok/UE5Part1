// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" //언리얼 오브젝트가 되기 위해서 기본적으로 포함되어야하는 헤더
#include "UObject/NoExportTypes.h" //언리얼 오브젝트가 되기 위해서 기본적으로 포함되어야하는 헤더
#include "MyObject.generated.h" //내가 만든 오브젝트 + .generated.h가 있는데, 이걸 어떻게 끌고 왔냐? ⇒ 다른 폴더에 존재한다.

/**
 * 
 */
//UNREALOBJECT_API 원래는 내가 만든 프로젝트 + _API의 형태인데, 이것의 의미는 바로!
//다른 프로젝트에서도 이걸 사용할 수 있도록 하기 위해서 개방해준다는 걸 의미.
//없애준다면, 다른 곳에서는 사용이 불가능

UCLASS() //Unreal Object임을 명시하기 위해서 UCLASS()를 붙여 놓는다.
class UNREALOBJECT_API UMyObject : public UObject //MyObject의 이름은 접두사 U가 붙은 UMyObject, 파일의 경우에는 접두사를 따로 안씀.
{
	GENERATED_BODY()
	//GENERATED_BODY() ⇒ 헤더를 살펴 보면, 여러 매크로를 여기저기 타는 것을 확인할 수 있음 ⇒ A,B,C,D를 묶은 하나의 단어를 만든다.
	//현재 파일, _, 라인정보, _BODY 정보를 묶어서 하나의 문자열을 만든다는 걸 의미한다.
	//좋은 기능을 언리얼 엔진이 자동으로 만들어서 지원해준다.
	//컴파일 과정에서 자기 알아서 만들어지게 된다!
	//결론 : 언리얼 헤더 툴을 가지고 만들어 낸 클래스들을 포함해서 언리얼 오브젝트가 만들어지게 된다.
};

