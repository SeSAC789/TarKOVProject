// Fill out your copyright notice in the Description page of Project Settings.


#include "KJH/JHPlayerTest.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

AJHPlayerTest::AJHPlayerTest()
{

    HeadHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "HeadHitbox" ) );
    HeadHitbox->SetupAttachment( GetMesh() , FName( "HeadSocket" ) );
    HeadHitbox->SetCapsuleSize( 11.0f , 12.0f ); // 캡슐의 크기 설정 (반지름, 높이)
    HeadHitbox->SetRelativeLocationAndRotation( FVector( 0.0f , -8.281382f , 4.830602f ) , FRotator(0.0f,0.0f,90.0f) );
	// 소켓에 대한 상대 위치 설정 (X=0.000000,Y=-8.281382,Z=4.830602), (Pitch=0.000000,Yaw=0.000000,Roll=-90.000000)
    // "Head" 태그 추가
    HeadHitbox->ComponentTags.Add( FName( "Head" ) );

    ThoraxHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "ThoraxHitbox" ) );
    ThoraxHitbox->SetupAttachment( GetMesh() , FName( "ThoraxSocket" ) );
    ThoraxHitbox->SetCapsuleSize( 16.0f , 17.0f );
    ThoraxHitbox->SetRelativeLocationAndRotation( FVector( 0.5f , 1.560810f , 4.163126f ) , FRotator( 0.0f , 0.0f , 90.0f ) );
    // (X=0.500000,Y=1.560810,Z=4.163126) (Pitch=0.000000,Yaw=0.000000,Roll=90.000000) 
    // "Thorax" 태그 추가
    ThoraxHitbox->ComponentTags.Add( FName( "Thorax" ) );

    StomachHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "StomachHitbox" ) );
    StomachHitbox->SetupAttachment( GetMesh() , FName( "StomachSocket" ) );
    StomachHitbox->SetCapsuleSize( 15.0f , 15.0f );
    StomachHitbox->SetRelativeLocationAndRotation( FVector( 0.5f , 0.640273f , 5.005143f ) , FRotator( 0.0f , 0.0f , 0.0f ) );
    // (X=0.500000,Y=0.640273,Z=5.005143) 
    // "Stomach" 태그 추가
    StomachHitbox->ComponentTags.Add( FName( "Stomach" ) );

    RightArmUpperHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "RightArmUpperHitbox" ) );
    RightArmUpperHitbox->SetupAttachment( GetMesh() , FName( "RightArmUpperSocket" ) );
    RightArmUpperHitbox->SetCapsuleSize( 6.5f , 20.0f );
    RightArmUpperHitbox->SetRelativeLocationAndRotation( FVector( 0.023172f , -12.472641f , -0.557689f ) , FRotator( 2.22837f , 4.517647f , 91.695983f ) );
    // (X=0.023172,Y=-12.472641,Z=-0.557689) (Pitch=2.228372,Yaw=4.517647,Roll=91.695983)
    // "RightArm" 태그 추가
    RightArmUpperHitbox->ComponentTags.Add( FName( "RightArm" ) );

    RightForeArmHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "RightForeArmHitbox" ) );
    RightForeArmHitbox->SetupAttachment( GetMesh() , FName( "RightForeArmSocket" ) );
    RightForeArmHitbox->SetCapsuleSize( 6.0f , 20.0f );
    RightForeArmHitbox->SetRelativeLocationAndRotation( FVector( 0.458593f , -21.358836f , -0.090714f ) , FRotator( 2.275739f , 7.835439f , 86.318466f ) );
    // (X=0.458593,Y=-21.358836,Z=-0.090714) (Pitch=2.275739,Yaw=7.835439,Roll=86.318466)
    // "RightArm" 태그 추가
    RightForeArmHitbox->ComponentTags.Add( FName( "RightArm" ) );

    LeftArmUpperHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "LeftArmUpperHitbox" ) );
    LeftArmUpperHitbox->SetupAttachment( GetMesh() , FName( "LeftArmUpperSocket" ) );
    LeftArmUpperHitbox->SetCapsuleSize( 6.5f , 20.0f );
    LeftArmUpperHitbox->SetRelativeLocationAndRotation( FVector( -0.656969f , -12.241082f , -0.199606f ) , FRotator( 9.024780f , -4.985366f , 92.502085f ) );
    // (X=-0.656969,Y=-12.241082,Z=-0.199606) (Pitch=9.024780,Yaw=-4.985366,Roll=92.502085)
    // "LeftArm" 태그 추가
    LeftArmUpperHitbox->ComponentTags.Add( FName( "LeftArm" ) );

    LeftForeArmHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "LeftForeArmHitbox" ) );
    LeftForeArmHitbox->SetupAttachment( GetMesh() , FName( "LeftForeArmSocket" ) );
    LeftForeArmHitbox->SetCapsuleSize( 6.0f , 20.0f );
    LeftForeArmHitbox->SetRelativeLocationAndRotation( FVector( 0.253245f , -21.7371221f , 0.386370f ) , FRotator( -1.546471f , -6.300808f , 87.828338f ) );
    // (X=0.253245,Y=-21.737122,Z=0.386370) (Pitch=-1.546471,Yaw=-6.300808,Roll=87.828338)
    // "LeftArm" 태그 추가
    LeftForeArmHitbox->ComponentTags.Add( FName( "LeftArm" ) );

    RightLegUpperHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "RightLegUpperHitbox" ) );
    RightLegUpperHitbox->SetupAttachment( GetMesh() , FName( "RightLegUpperSocket" ) );
    RightLegUpperHitbox->SetCapsuleSize( 11.0f , 27.0f );
    RightLegUpperHitbox->SetRelativeLocationAndRotation( FVector( -0.406686f , -18.666032f , 1.906051f ) , FRotator( -0.233612f , 0.556462f , 90.846342f ) );
    // (X=-0.406686,Y=-18.666032,Z=1.906051) (Pitch=-0.233612,Yaw=0.556462,Roll=90.846342)
    // "RightLeg" 태그 추가
    RightLegUpperHitbox->ComponentTags.Add( FName( "RightLeg" ) );

    RightLegLowerHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "RightLegLowerHitbox" ) );
    RightLegLowerHitbox->SetupAttachment( GetMesh() , FName( "RightLegLowerSocket" ) );
    RightLegLowerHitbox->SetCapsuleSize( 9.0f , 25.0f );
    RightLegLowerHitbox->SetRelativeLocationAndRotation( FVector( -0.374272f , -20.185090f , -0.795077f ) , FRotator( 0.786182f , -4.247138f ,90.992866f ) );
    // (X=-0.374272,Y=-20.185090,Z=-0.795077) (Pitch=0.786182,Yaw=-4.247138,Roll=90.992866)
    // "RightLeg" 태그 추가
    RightLegLowerHitbox->ComponentTags.Add( FName( "RightLeg" ) );

    LeftLegUpperHitbox= CreateDefaultSubobject<UCapsuleComponent>( TEXT( "LeftLegUpperHitbox" ) );
    LeftLegUpperHitbox->SetupAttachment( GetMesh() , FName( "LeftLegUpperSocket" ) );
    LeftLegUpperHitbox->SetCapsuleSize( 11.0f , 27.0f );
    LeftLegUpperHitbox->SetRelativeLocationAndRotation( FVector( 0.788391f , -18.530999f , 0.717755f ) , FRotator( 0.168281f , -2.991637f , 87.833028f ) );
    // (X=0.788391,Y=-18.530999,Z=0.717755) (Pitch=0.168281,Yaw=-2.991637,Roll=87.833028)
    // "LeftLeg" 태그 추가
    LeftLegUpperHitbox->ComponentTags.Add( FName( "LeftLeg" ) );

    LeftLegLowerHitbox = CreateDefaultSubobject<UCapsuleComponent>( TEXT( "LeftLegLowerHitbox" ) );
    LeftLegLowerHitbox->SetupAttachment( GetMesh() , FName( "LeftLegLowerSocket" ) );
    LeftLegLowerHitbox->SetCapsuleSize( 9.0f , 25.0f );
    LeftLegLowerHitbox->SetRelativeLocationAndRotation( FVector( -0.343941f , -20.073776f , -0.984876f ) , FRotator( -2.179116f , -0.535826f ,89.314173f ) );
    // (X=-0.343941,Y=-20.073776,Z=-0.984876) (Pitch=-2.179116,Yaw=-0.535826,Roll=89.314173)
    // "LeftLeg" 태그 추가
    LeftLegLowerHitbox->ComponentTags.Add( FName( "LeftLeg" ) );


}

void AJHPlayerTest::BeginPlay()
{
	Super::BeginPlay();

}
