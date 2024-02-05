// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "JsonObjectConverter.h" //Json으로 변환을 해줄 수 있는 헬퍼 라이브러리가 있음.
#include "UObject/SavePackage.h" //FSavePackageArgs

const FString UMyGameInstance::PackageName = TEXT("/Game/Student");
const FString UMyGameInstance::AssetName = TEXT("TopStudent");

void PrintStudentInfo(const UStudent* InStudent, const FString& InTag) //출력 함수
{
	UE_LOG(LogTemp, Log, TEXT("[%s] 이름 %s 순번 %d"), *InTag, *InStudent->GetName(), InStudent->GetOrder());
}

UMyGameInstance::UMyGameInstance()
{
	const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);
	static ConstructorHelpers::FObjectFinder<UStudent> UASSET_TopStudent(*TopSoftObjectPath);
	if (UASSET_TopStudent.Succeeded())
	{
		PrintStudentInfo(UASSET_TopStudent.Object, TEXT("Constructor"));
	}
}

void UMyGameInstance::Init()
{
	Super::Init();

	FStudentData RawDataSrc(16, TEXT("이득우"));

	const FString SavedDir = FPaths::Combine(FPlatformMisc::ProjectDir(), TEXT("Saved"));
	UE_LOG(LogTemp, Log, TEXT("저장할 파일 폴더 : %s"), *SavedDir);

	{
		const FString RawDataFileName(TEXT("RawData.bin"));
		FString RawDataAbosolutePath = FPaths::Combine(*SavedDir, *RawDataFileName);
		UE_LOG(LogTemp, Log, TEXT("저장할 파일 전체 경로 : %s"), *RawDataAbosolutePath);
		FPaths::MakeStandardFilename(RawDataAbosolutePath); //보기 좋게 만든다
		UE_LOG(LogTemp, Log, TEXT("변경할 파일 전체 경로 : %s"), *RawDataAbosolutePath);

		// FArchive 클래스를 상속을 받기 때문에
		FArchive* RawFileWriterAr = IFileManager::Get().CreateFileWriter(*RawDataAbosolutePath);
		if (nullptr != RawFileWriterAr)
		{
			*RawFileWriterAr << RawDataSrc; // friend로 만드었다
			RawFileWriterAr->Close();
			delete RawFileWriterAr;
			RawFileWriterAr = nullptr;
		}

		FStudentData RawDataDest;
		FArchive* RawFileReaderAr = IFileManager::Get().CreateFileReader(*RawDataAbosolutePath);
		if (nullptr != RawFileReaderAr)
		{
			*RawFileReaderAr << RawDataDest; //RawFileReaderAr이기 때문에 불러오는 것이다
			RawFileReaderAr->Close();
			delete RawFileReaderAr;
			RawFileReaderAr = nullptr;
			UE_LOG(LogTemp, Log, TEXT("[RawData] 이름 %s 순번 %d"), *RawDataDest.Name, RawDataDest.Order);
		}
	}

	StudentSrc = NewObject<UStudent>();
	StudentSrc->SetName(TEXT("이득우"));
	StudentSrc->SetOrder(59);

	{
		const FString ObjectDataFileName(TEXT("ObjectData.bin"));
		FString ObjectDataAbsolutePath = FPaths::Combine(*SavedDir, *ObjectDataFileName);
		FPaths::MakeStandardFilename(ObjectDataAbsolutePath);

		//메모리에다가  저장
		TArray<uint8> BufferArray; 
		FMemoryWriter MemoryWriterAr(BufferArray);
		StudentSrc->Serialize(MemoryWriterAr);
		
		//스마트 포인터를 활용
		if (TUniquePtr<FArchive> FileWriterAr = TUniquePtr<FArchive>(IFileManager::Get().CreateFileWriter(*ObjectDataAbsolutePath)))
		{
			*FileWriterAr << BufferArray;
			FileWriterAr->Close();
		}

		TArray<uint8> BufferArrayFromFile;
		if (TUniquePtr<FArchive> FileReaderAr = TUniquePtr<FArchive>(IFileManager::Get().CreateFileReader(*ObjectDataAbsolutePath)))
		{
			*FileReaderAr << BufferArrayFromFile;
			FileReaderAr->Close();
		}

		FMemoryReader MemoryReaderAr(BufferArrayFromFile);
		UStudent* StudentDest = NewObject<UStudent>();
		StudentDest->Serialize(MemoryReaderAr);
		PrintStudentInfo(StudentDest, TEXT("ObjectData"));
	}


	{
		//Json으로 읽고 써보자.
		const FString JsonDataFileName(TEXT("StudentJsonData.txt"));
		FString JsonDataAbsolutePath = FPaths::Combine(*SavedDir, *JsonDataFileName);
		FPaths::MakeStandardFilename(JsonDataAbsolutePath);

		TSharedRef<FJsonObject> JsonObjectSrc = MakeShared<FJsonObject>(); //이렇게 되면 Null이 아님을 보장을 받게 된다.
		FJsonObjectConverter::UStructToJsonObject(StudentSrc->GetClass(), StudentSrc, JsonObjectSrc);
		//FJsonObjectConverter::UStructToJsonObject(ClassData, Original Object, TargetJsonObject) 이렇게 구성
		//어찌되었던 UClass 자체가 UStruct를 상속을 받다보니, 이를 활용할 수 있다
		
		FString JsonOutString; //쓰기
		TSharedRef<TJsonWriter<TCHAR>> JsonWriterAr = TJsonWriterFactory<TCHAR>::Create(&JsonOutString);
		if (FJsonSerializer::Serialize(JsonObjectSrc, JsonWriterAr))
		{
			FFileHelper::SaveStringToFile(JsonOutString, *JsonDataAbsolutePath); //운영체제에서 인코딩을 신경쓰지 않고 알아서 저장해주기에 유용
		}

		FString JsonInString; //불러오기
		FFileHelper::LoadFileToString(JsonInString, *JsonDataAbsolutePath);

		TSharedRef<TJsonReader<TCHAR>> JsonReaderAr = TJsonReaderFactory<TCHAR>::Create(JsonInString);

		TSharedPtr<FJsonObject> JsonObjectDest; // null이 될 수도 있다 --> 안만들어질 경우
		if (FJsonSerializer::Deserialize(JsonReaderAr, JsonObjectDest))
		{
			UStudent* JsonStudentDest = NewObject<UStudent>();
			if (FJsonObjectConverter::JsonObjectToUStruct(JsonObjectDest.ToSharedRef(), JsonStudentDest->GetClass(), JsonStudentDest))
			{
				PrintStudentInfo(JsonStudentDest, TEXT("JsonData"));
			}
		}
	}

	SaveStudentPackage();
	//LoadStudentPackage();
	//LoadStudentObject();

	const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);
	Handle = StreamableManager.RequestAsyncLoad(TopSoftObjectPath,
		[&]()
		{
			if (Handle.IsValid() && Handle->HasLoadCompleted())
			{
				UStudent* TopStudent = Cast<UStudent>(Handle->GetLoadedAsset());
				if (TopStudent)
				{
					PrintStudentInfo(TopStudent, TEXT("AsyncLoad"));

					Handle->ReleaseHandle();
					Handle.Reset();
				}
			}
		}
	);
}

void UMyGameInstance::SaveStudentPackage() const
{
	//패키지가 있으면 다 로딩을 시킨다
	UPackage* StudentPackage = ::LoadPackage(nullptr, *PackageName, LOAD_None);
	if (StudentPackage)
	{
		StudentPackage->FullyLoad();
	}

	StudentPackage = CreatePackage(*PackageName);
	EObjectFlags ObjectFlag = RF_Public | RF_Standalone; //저장하고자 하는 옵션

	UStudent* TopStudent = NewObject<UStudent>(StudentPackage, UStudent::StaticClass(), *AssetName, ObjectFlag); //인자가 없으면 Transient Package에 들어간다
	TopStudent->SetName(TEXT("이득우"));
	TopStudent->SetOrder(36);

	const int32 NumofSubs = 10;
	for (int32 ix = 1; ix <= NumofSubs; ++ix)
	{
		FString SubObjectName = FString::Printf(TEXT("Student%d"), ix);
		UStudent* SubStudent = NewObject<UStudent>(TopStudent, UStudent::StaticClass(), *SubObjectName, ObjectFlag);
		SubStudent->SetName(FString::Printf(TEXT("학생%d"), ix));
		SubStudent->SetOrder(ix);
	}

	//저장을 하려면 저장을 해줘야 되는 경로와 확장자가 필요하게 된다.
	const FString PackageFileName = FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension()); //GetAssetPackageExtension = uasset의 확장자를 의미한다.
	//PackageName : 프로젝트의 정보를 바탕으로 해서 컨텐츠 폴더를 지정하고 (/Game),이후에 파일이름을 지정하게 된다(Student)
	//그 다음에.uasset이라는 확장자가 붙게 되어 최종 결과가 나온다.
	FSavePackageArgs SaveArgs;
	SaveArgs.TopLevelFlags = ObjectFlag;

	if (UPackage::SavePackage(StudentPackage, nullptr, *PackageFileName, SaveArgs))
	{
		UE_LOG(LogTemp, Log, TEXT("패키지가 성공적으로 저장되었습니다."));
	}

}

void UMyGameInstance::LoadStudentPackage() const
{
	UPackage* StudentPackage = ::LoadPackage(nullptr, *PackageName, LOAD_None);
	if (nullptr == StudentPackage)
	{
		UE_LOG(LogTemp, Warning, TEXT("패키지를 찾을 수 없습니다."));
		return;
	}

	StudentPackage->FullyLoad();// FullyLoad를 이용하여, 패키지에 대한 정보를 모두 가져온다.

	UStudent* TopStudent = FindObject<UStudent>(StudentPackage, *AssetName);
	PrintStudentInfo(TopStudent, TEXT("FindObject Asset"));
}

void UMyGameInstance::LoadStudentObject() const
{
	const FString TopSoftObjectPath = FString::Printf(TEXT("%s.%s"), *PackageName, *AssetName);

	UStudent* TopStudent = LoadObject<UStudent>(nullptr, *TopSoftObjectPath);
	PrintStudentInfo(TopStudent, TEXT("LoadObject Asset"));
}
