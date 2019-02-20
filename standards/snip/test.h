UCLASS()
// [class.name] embed the agreed project codename while following UE4 naming rul
//	- See [module.naming.class]
class ABMCodingStandardExampleActor : public ACharacter
{
    GENERATED_BODY() // GENERATED_UCLASS_BODY is deprecated

    // [ue.gen.access] follow up the reflection macros with access level specifi
    // because they don't modify them anymore (used to be the case)
    // structs do not need to specify public, unless they also specify protected
    // [class.ctor.default] don't write an empty one, remove it
    // due to the way GENERATED_BODY works, `= default`-ing the constructor can 
    //	respect the rule of 3/5/0 http://en.cppreference.com/w/cpp/language/rule
    // [class.virtual] explicitly mark up virtual methods
    //	- always use the `override` specifier
    //  - use the `final` specifier sparingly and with care as it can have large
    // Begin AActor override
    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifeti
    // [class.same-line] DON'T write definitions on the same line as declaration
    // [comment.useless] DON'T write meaningless comments!
    //	they should always reflect bigger purpose or reveal hidden details
    /** Returns Mesh subobject **/
    /* BAD -> */ FORCEINLINE USkeletalMeshComponent* GetMesh() const { return My

protected:
    // [class.order] Do not alternate between functions and variables in the cla

    // [ue.ecs.split] Split functionality into components
    //	avoid creating monolithic giant classes!
    // [header.rule.fwd] example of in-place forward declaration

    // [ue.ecs.gc] never use naked pointers to UObject's, always have UPROPERTY 
    //	Generally, for storing pointers to classes you don't own, use TWeakObjec
    //	Don't initialise TWeakObjectPtr as it will force you to include the head
    TWeakObjectPtr<USkeletalMeshComponent> OtherMesh; /* <- GOOD */
    //TWeakObjectPtr<USkeletalMeshComponent> AnotherMesh = nullptr; /* <- BAD an
    //	Generally, for storing pointers to classes you do own, use UPROPERTY() a
    UPROPERTY(BlueprintReadOnly, Category = Mesh)
    USkeletalMeshComponent* MyMesh = nullptr;
    //	For more information on other forms of UE4 smart pointers see
    //	https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/

    // [class.order.replication] As an exception to [class.ordering], declare re
    // next to the variable that used them to avoid cluttering the interface wit
    // are not called by client code.
    UPROPERTY(Transient, ReplicatedUsing = "OnRep_WantsToSprint")
    bool WantsToSprint = false;
    UFUNCTION()
    void OnRep_WantsToSprint();
};