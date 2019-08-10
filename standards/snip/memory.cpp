void DontWasteMemory(const AActor& Actor)
{
    // [ue.container] Mind your allocations!
    //  don't go to the heap, go to the stack!
    TInlineComponentArray<UPrimitiveComponent*> PrimComponents; // 24 item reser
    Actor.GetComponents(PrimComponents);

    // [ue.container] [ue.ecs.get] Customize the get-ers for this purpose!
    using TCustomAlloc = TInlineAllocator<32>;
    TArray<UActorComponent *, TCustomAlloc> LocalItems;
    Actor.GetComponents<UActorComponent, TCustomAlloc>(LocalItems);

    // [ue.container.reserve] Prepare upfront the containers
    //  cut down on the need to allocate per-item
    PrimComponents.Reserve(64);
    PrimComponents.Init(nullptr, 64);

    // [ue.container.reset] Don't empty, just reset!
    PrimComponents.Empty(); // BAD - deallocates for new 0 size
    PrimComponents.Reset(); // GOOD - same effect, but instant, no realloc
    PrimComponents.Empty(64); // PASSABLE - empty with slack

    // [hardware.cache] be mindful of cache access and plan your memory access
    //
    //  1 CPU cycle
    //  o
    //
    //  L1 cache access
    //  ooo
    //
    //  L2 cache access
    //  ooooooooo
    //
    //  L3 cache access
    //  oooooooooooooooooooooooooooooooooooooooooo
    //
    //  Main memory access
    //  oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
    //  oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
    //  oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
    //  oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
    //  oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo
    //
    //  from https://twitter.com/srigi/status/917998817051541504
    //
    //  Some general tips
    //  - prefer linear data structures, don't jump via pointers too much etc
    //  - all cache access is through lines 64 bytes long, have that in mind!
    //  - in classes put related data together, group them by algorithm/logic ac
    //  - be mindful of the invisible packing the compiler will do behind your b
    //      don't intermingle bool's or small types willy nilly with bigger ones
}