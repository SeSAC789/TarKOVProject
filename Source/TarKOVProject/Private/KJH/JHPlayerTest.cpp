// Fill out your copyright notice in the Description page of Project Settings.


#include "KJH/JHPlayerTest.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

AJHPlayerTest::AJHPlayerTest()
{

    HeadHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "HeadHitbox" ) );
    HeadHitbox->SetupAttachment( GetMesh() , FName( "HeadSocket" ) );
    HeadHitbox->SetCapsuleSize( 15.f , 25.f ); // 캡슐의 크기 설정 (반지름, 높이)
    HeadHitbox->SetRelativeLocation( FVector( 0.f , 0.f , 0.f ) ); // 소켓에 대한 상대 위치 설정

    ThoraxHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "ThoraxHitbox" ) );
    ThoraxHitbox->SetupAttachment( GetMesh() , FName( "ThoraxSocket" ) );
    ThoraxHitbox->SetCapsuleSize( 15.f , 25.f );
    ThoraxHitbox->SetRelativeLocation( FVector( 0.f , 0.f , 0.f ) );

    StomachHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "StomachHitbox" ) );
    StomachHitbox->SetupAttachment( GetMesh() , FName( "StomachSocket" ) );
    StomachHitbox->SetCapsuleSize( 15.f , 25.f );
    StomachHitbox->SetRelativeLocation( FVector( 0.f , 0.f , 0.f ) );

    RightArmHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "RightArmHitbox" ) );
    RightArmHitbox->SetupAttachment( GetMesh() , FName( "RightArmSocket" ) );
    RightArmHitbox->SetCapsuleSize( 15.f , 25.f );
    RightArmHitbox->SetRelativeLocation( FVector( 0.f , 0.f , 0.f ) );

    LeftArmHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "LeftArmHitbox" ) );
    LeftArmHitbox->SetupAttachment( GetMesh() , FName( "LeftArmSocket" ) );
    LeftArmHitbox->SetCapsuleSize( 15.f , 25.f );
    LeftArmHitbox->SetRelativeLocation( FVector( 0.f , 0.f , 0.f ) );

    RightLegHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "RightLegHitbox" ) );
    RightLegHitbox->SetupAttachment( GetMesh() , FName( "RightLegSocket" ) );
    RightLegHitbox->SetCapsuleSize( 15.f , 25.f );
    RightLegHitbox->SetRelativeLocation( FVector( 0.f , 0.f , 0.f ) );

    LeftLegHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "LeftLegHitbox" ) );
    LeftLegHitbox->SetupAttachment( GetMesh() , FName( "LeftLegSocket" ) );
    LeftLegHitbox->SetCapsuleSize( 15.f , 25.f );
    LeftLegHitbox->SetRelativeLocation( FVector( 0.f , 0.f , 0.f ) );


}

void AJHPlayerTest::BeginPlay()
{
	Super::BeginPlay();

}
