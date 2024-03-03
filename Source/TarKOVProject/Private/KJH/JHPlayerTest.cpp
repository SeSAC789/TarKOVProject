// Fill out your copyright notice in the Description page of Project Settings.


#include "KJH/JHPlayerTest.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

AJHPlayerTest::AJHPlayerTest()
{

    HeadHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "HeadHitbox" ) );
    HeadHitbox->SetupAttachment( GetMesh() , FName( "HeadSocket" ) );
    HeadHitbox->SetCapsuleSize( 11.f , 12.f ); // 캡슐의 크기 설정 (반지름, 높이)
    HeadHitbox->SetRelativeLocationAndRotation( FVector( 0.f , -8.281382f , 4.830602f ) , FRotator(0.f,0.f,90.f) );
	// 소켓에 대한 상대 위치 설정 (X=0.000000,Y=-8.281382,Z=4.830602), (Pitch=0.000000,Yaw=0.000000,Roll=-90.000000)
    // "Head" 태그 추가
    HeadHitbox->ComponentTags.Add( FName( "Head" ) );

    ThoraxHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "ThoraxHitbox" ) );
    ThoraxHitbox->SetupAttachment( GetMesh() , FName( "ThoraxSocket" ) );
    ThoraxHitbox->SetCapsuleSize( 16.f , 17.f );
    ThoraxHitbox->SetRelativeLocationAndRotation( FVector( 0.5f , 1.560810f , 4.163126f ) , FRotator( 0.f , 0.f , 90.f ) );
    // (X=0.500000,Y=1.560810,Z=4.163126) (Pitch=0.000000,Yaw=0.000000,Roll=90.000000) 
    // "Thorax" 태그 추가
    ThoraxHitbox->ComponentTags.Add( FName( "Thorax" ) );

    StomachHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "StomachHitbox" ) );
    StomachHitbox->SetupAttachment( GetMesh() , FName( "StomachSocket" ) );
    StomachHitbox->SetCapsuleSize( 15.f , 15.f );
    StomachHitbox->SetRelativeLocationAndRotation( FVector( 0.5f , 0.640273f , 5.005143f ) , FRotator( 0.f , 0.f , 0.f ) );
    // (X=0.500000,Y=0.640273,Z=5.005143) 
    // "Stomach" 태그 추가
    StomachHitbox->ComponentTags.Add( FName( "Stomach" ) );

    RightArmHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "RightArmHitbox" ) );
    RightArmHitbox->SetupAttachment( GetMesh() , FName( "RightArmSocket" ) );
    RightArmHitbox->SetCapsuleSize( 8.f , 39.f );
    RightArmHitbox->SetRelativeLocationAndRotation( FVector( 5.846544f , -31.196791f , 1.481060f ) , FRotator( 0.f , 20.f , 100.f ) );
    // (X=5.846544,Y=-31.196791,Z=1.481060) (Pitch=0.000000,Yaw=20.000000,Roll=100.000000)
    // "RightArm" 태그 추가
    RightArmHitbox->ComponentTags.Add( FName( "RightArm" ) );

    LeftArmHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "LeftArmHitbox" ) );
    LeftArmHitbox->SetupAttachment( GetMesh() , FName( "LeftArmSocket" ) );
    LeftArmHitbox->SetCapsuleSize( 8.f , 39.f );
    LeftArmHitbox->SetRelativeLocationAndRotation( FVector( -5.566600f , -30.885946f , 1.960790f ) , FRotator( 0.754693f , -12.975975f , 97.921746f ) );
    // (X=-5.566600,Y=-30.885946,Z=1.960790)) (Pitch=0.754693,Yaw=-12.975975,Roll=97.921746)
    // "LeftArm" 태그 추가
    LeftArmHitbox->ComponentTags.Add( FName( "LeftArm" ) );

    RightLegHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "RightLegHitbox" ) );
    RightLegHitbox->SetupAttachment( GetMesh() , FName( "RightLegSocket" ) );
    RightLegHitbox->SetCapsuleSize( 11.f , 55.f );
    RightLegHitbox->SetRelativeLocationAndRotation( FVector( -1.578022f , -0.567122f , -0.139831f ) , FRotator( -0.276899f , 3.509021f , 97.809946f ) );
    // (X=-1.578022,Y=-0.567122,Z=-0.139831) (Pitch=-0.276899,Yaw=3.509021,Roll=97.809946)
    // "RightLeg" 태그 추가
    RightLegHitbox->ComponentTags.Add( FName( "RightLeg" ) );

    LeftLegHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "LeftLegHitbox" ) );
    LeftLegHitbox->SetupAttachment( GetMesh() , FName( "LeftLegSocket" ) );
    LeftLegHitbox->SetCapsuleSize( 11.f , 55.f );
    LeftLegHitbox->SetRelativeLocationAndRotation( FVector( 1.648866f , -3.842011f , -4.662564f ) , FRotator( 0.168281f , -2.991637f , 92.741142f ) );
    // (X=1.648866,Y=-3.842011,Z=-4.662564) (Pitch=0.168281,Yaw=-2.991637,Roll=92.741142)
    // "LeftLeg" 태그 추가
    LeftLegHitbox->ComponentTags.Add( FName( "LeftLeg" ) );


}

void AJHPlayerTest::BeginPlay()
{
	Super::BeginPlay();

}
