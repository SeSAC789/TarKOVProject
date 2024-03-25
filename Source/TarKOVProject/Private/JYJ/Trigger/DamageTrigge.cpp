// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/Trigger/DamageTrigge.h"
#include "KJH/HealthComp.h"
#include "JYJ/PlayerBase.h"

void ADamageTrigge::OnHitboxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerBase* player = Cast<APlayerBase>( OtherActor );

	if (OverlappedComponent->ComponentHasTag( "Head" ) || OverlappedComponent->ComponentHasTag( "Thorax" ) || OverlappedComponent->ComponentHasTag( "Stomach" ) || OverlappedComponent->ComponentHasTag( "RightArm" ) || OverlappedComponent->ComponentHasTag( "LeftArm" ) || OverlappedComponent->ComponentHasTag( "RightLeg" ) || OverlappedComponent->ComponentHasTag( "LeftLeg" ))
	{
		FName BodyPart = OverlappedComponent->ComponentTags[0]; // 첫 번째 태그를 신체 부위 이름으로 사용
		if (player->HealthComp)
		{
			FString HitObjectName = OtherActor->GetName(); // 충돌한 객체의 이름
			player->HealthComp->TakeDamage( BodyPart , 5 , HitObjectName ); // 모든 충돌에 대해 5의 데미지를 적용, 충돌한 객체 이름을 전달
		}
	}
}
