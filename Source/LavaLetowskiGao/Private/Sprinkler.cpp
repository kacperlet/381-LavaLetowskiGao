#include "Sprinkler.h"

// Sets default values
ASprinkler::ASprinkler()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SprinklerMesh"));
	RootComponent = Mesh;
	
	WaterEffect = CreateDefaultSubobject<UNiagaraComponent>("WaterEffect");
	WaterEffect->SetupAttachment(Mesh);
	WaterEffect->bAutoActivate = false;
}

// Called when the game starts or when spawned
void ASprinkler::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASprinkler::StartSprinkler() const
{
	WaterEffect->Activate(true);
}

void ASprinkler::StopSprinkler() const
{
	WaterEffect->Deactivate();
}


