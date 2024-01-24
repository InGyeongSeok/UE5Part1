// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Card.generated.h"

//만약 UENUM이 없다면 일반적인 C++과 다를 바가 없겠죠.
//이 객체에 대한 정보를 언리얼이 파악해서 유용한 정보를 가져오고,
//필드마다 메타 정보를 집어 넣을 수 있다 (그냥 한 마디로, 추가적 정보를 넣을 수 있게 된다는 것., 매크로로..)

UENUM()
enum class ECardType : uint8 {
	Student = 1 UMETA(DisplayName = "For Student"),
	Teacher UMETA(DisplayName = "For Teacher"),
	Staff UMETA(DisplayName = "For Staff"),
	Invalid
};


/**
 * 
 */
UCLASS()
class UNREALCOMPOSITION_API UCard : public UObject
{
	GENERATED_BODY()
	
public:
	UCard();

	ECardType GetCardType() const { return CardType; }
	void SetCardType(ECardType InCardType) { CardType = InCardType; }
private:
	UPROPERTY()
	ECardType CardType;

	UPROPERTY()
	uint32 Id;
};
