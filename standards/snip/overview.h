// [header.guard] include guard
#pragma once

// [basic.rule] FOLLOW UE4 coding style! 
//    https://docs.unrealengine.com/latest/INT/Programming/Development/CodingSta
//    especially here in the header/interface
//    in the implementation (.cpp) you are allowed to diverge a bit
//    but NEVER when it comes to things that will be visible from outside
//    aka public variables, functions, names etc

// [header.iwyu] we shall use IWYU (Include-What-You-Use)
#include "CoreMinimal.h"

// [header.engine.incl] list all the Engine dependencies with angle brackets
#include <GameFramework/Character.h>
#include <GameFramework/Pawn.h>
//  group and separate them by shared logic or purpose
//  use full relative path (in relation to Engine/Classes folders)
#include <GameFramework/HUD.h>
#include <GameFramework/HUDHitBox.h>

// [header.rule.gen] always have the .generated files last
#include "SplashDamageCodingStandard.generated.h"

// [header.rule.fwd] list as many forward declaration as you can
//    it's also acceptable to declare them at the usage site
class UInputComponent;
class UCameraComponent;
class USkeletalMeshComponent;

UCLASS()
// [class.name] embed the agreed project codename while following UE4 naming rul
//    - See [module.naming.class]
class ASDCodingStandardExampleActor : public ACharacter
{
    GENERATED_BODY() // GENERATED_UCLASS_BODY is deprecated

    // [ue.gen.access] follow up the reflection macros with access level specifi
    // because they don't modify them anymore (used to be the case)
    // structs do not need to specify public
    // unless they also specify protected/private (see [ue.gen.struct])
public:

    // [class.ctor.default] don't write an empty one, remove it
    // due to the way GENERATED_BODY works, `= default`-ing is problematic

    // [class.dtor] don't write empty one, default or remove it
    //    respect the rule of 3/5/0 http://en.cppreference.com/w/cpp/language/ru
    ~ASDCodingStandardExampleActor() = default; // or just remove

    // [class.virtual] explicitly mark up virtual methods
    //    - always use the `override` specifier
    //  - use the `final` specifier sparingly and with care
    //    as it can have large ramifications on downstream classes.
    //  - group overridden functions by the class that first defines (as below)

    // Begin AActor override
    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps() const override;
    // End AActor override

    // [class.same-line] DON'T write definitions on the same line as declaration
    //    it makes debugging impossible
    // [class.inline.bad] NEVER USE `inline or `FORCEINLINE` inside a class decl
    //    - it's useless and leads to linking errors
    //    - definitions(bodies) inside a class/struct are implicitly inline!
    // [comment.useless] DON'T write meaningless comments!
    //    they should always reflect bigger purpose or reveal hidden details
    /** Returns Mesh subobject **/
    /* BAD */ FORCEINLINE USkeletalMeshComponent* GetMesh() const { return MyMes

    // [class.inline.good] Move the definitions of inline function outside the c
    TWeakObjectPtr<USkeletalMeshComponent> GoodExampleOfInline();

protected:
    // [class.order] Do not alternate functions and variables in the class decla
    // Put all functions first, all variables last

    // [ue.ecs.split] Split functionality into components
    //    avoid creating monolithic giant classes!
    // [header.rule.fwd] example of in-place forward declaration

    // [ue.ecs.gc] never use naked pointers to UObject's, always have UPROPERTY
    //  Generally, for storing pointers to classes you don't own, use TWeakObjec
    TWeakObjectPtr<const USkeletalMeshComponent> OtherMesh = nullptr;
    //  Generally, for storing pointers to classes you do own, use UPROPERTY()
    UPROPERTY(BlueprintReadOnly, Category = Mesh)
    const USkeletalMeshComponent* MyMesh = nullptr;

    // [class.order.replication] As an exception to [class.ordering], 
    // declare replication functions next to the variable that used them to
    // avoid cluttering the interface with non-client code
    UPROPERTY(Transient, ReplicatedUsing = "OnRep_WantsToSprint")
    bool WantsToSprint = false;
    UFUNCTION()
    void OnRep_WantsToSprint();
};

// [ue.gen.struct] [ue.ecs.group] move groups of Blueprint exposed variables
// into separate structures this helps refactoring and unclutters interfaces
// for ex implementation-only functions can just take the group as an argument
// NOTE: this is not always possible, but highly desirable for config-like varia
USTRUCT(BlueprintType)
struct FSDCodingStandardBlueprintVarGroup
{
    GENERATED_BODY()

    // [vs.plugin] some good tools to help manage these special meta attributes
    //    - UE4 Intellisense
    //    - SpecifierTool 
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
    TArray<int> WidgetCameraLevels; // [class.member.def] arrays start empty

    // [class.member.def] always provide defaults for member variables
    //    prefer assigning them here, not in the constructor - that should be re
    //    for more complicated init logic / creation 
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
    float CameraTraceVolumeWidth = 96.0f * 5;

    // [class.member.config] member variables that are used as editor config var
    //  MUST have a comment supplied as it shows up as the tooltip in the Editor
    //  - They should also be marked as EditDefaultsOnly by default.
    //  - If you expect them to be read in blueprints then use BlueprintReadOnly
    //  - Avoid EditAnywhere, EditInstanceOnly or BlueprintReadWrite if possible
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
    float CameraTraceVolumeHeight = 96.0f * 5;

    // [hardware.cache] try to order data members with cache and alignment in mi
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
    bool ShowCameraWidget = true; 

    // [hardware.cache] for ex grouping similar types like this will minimize th
    //    internal padding the compiler will add
    //    general rule of thumb: sort in descending order by size 
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera)
    bool ShowWeaponWidget = true;
};

UCLASS()
class USDCodingStandardExampleComponent : public USceneComponent
{
    GENERATED_BODY()

public:
    // [func.arg.readability] avoid `bool` function arguments, especially succes
    /* BAD -> */ void FuncHardToReadOnCall(int Order, bool bSetCache, bool bUseL

    using TOrder = int;
    enum class ECacheFlags { Use, Disabled, Unspecified };
    enum class ELogging { Yes, No };
    /* GOOD -> */ void FuncNiceToReadOnCall(TOrder, ECacheFlags, ELogging);
    //    argument names in declarations are ignored, try to encode as much mean
    //    also even this simple typedef/using goes a long way readability wise a
    //    ex: FuncNiceToReadOnCall(FOrder(42), FCacheFlags::Use, FLogFlags::Cust

    // [func.arg.readability] avoid consecutive chains of same type, avoid too m
    /* BAD -> */ void FuncWithTooManyArgs(FVector Location, FVector Origin, FVec
        FRotator Rotation, UPrimitiveComponent *Parent, AActor *Owner, float Dam
    // try to add a helper structure, or maybe you can split in more functions t

    // [singleton.no] NEVER USE SINGLETONS!!!
    //    - they are very problematic in multi-threaded scenarios
    //    - they interfere/break with Hot Reload and plugins
    //    - discuss alternatives with your lead
    //    - if you somehow have to add one, first reconsider!
    //    then use the Meyers pattern: https://stackoverflow.com/a/1661564
    /* BAD -> */ static USDCodingStandardExampleComponent* Instance; // defined 
    /* VERY BAD -> */ USDCodingStandardExampleComponent* GetInstance() { return 

    // [ue.alloc] expose the allocation as a policy for new utility methods you 
    //    this way the caller has a chance to decide how memory is utilized
    template<class AllocatorType>
    void GetComponents(TArray<UActorComponent *, AllocatorType>& OutComponents);

    // [cpp.lambda] used later for guidelines
    void LambdaStyle(AActor *ExternalEntity);

    // [cpp.rel_ops] when implementing relation operators, use the binary free f
    //  as it provides the most flexibility with operands order and usage
    //  If they needs to access private members 
    //  make them `friend` and respect [class.inline.good]
    friend bool operator == (
        const USDCodingStandardExampleComponent &lhs,
        const USDCodingStandardExampleComponent &rhs);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FSDCodingStandardBlueprintVarGroup BlueprintGroup;

private:
    // [class.constant] best way to define constants
    constexpr static int SomeDefaultMagicValue = 0xFF00;
    // BAD alternatives:
    //    #define OtherDefaultMagicValue (5)
    //    enum { RandomSeemValue = 434334 };
    //    static int AnotherMagicNumber; // actual value buried in .cpp

    // [naming.bool] Exception from UE4 coding standard:
    //    DON'T add `b` prefix to bool declaration names!
    //    instead use English Modal Verbs and variations like: 
    //  Can, Does, Will, Is, Has, Use, etc
    bool bInGame, bAttack, bLog, bCustomStencil; /* <- BAD */
    bool InGame, CanAttack, UseLog, HasCustomStencil; /* <- GOOD */
};
