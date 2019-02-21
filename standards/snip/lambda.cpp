void USDCodingStandardExampleComponent::LambdaStyle(AActor *ExternalEntity)
{
    // [cpp.lambda.general] use lambda's to your advantage
    //    especially when they will isolate work in the implementation
    //    rather than pollute the interface with helper methods
    //
    //    but don't abuse them - if their body becomes complex enough
    //    extract into separate function/method

    // [cpp.lambda.dangling] biggest problem in production is creating dangling
    //    by capturing objects by reference that die before the lambda gets called
    auto lambda_dangling = [ExternalEntity]()
    {
        // will ExternalEntity still be valid at this point?
    };

    // [cpp.lambda.this] don't capture `this`!
    //    instead use the named captures to cherry pick
    auto lambda_this = [LocalCopy = this->BlueprintGroup.ShowCameraWidget]()
    {
        // LocalCopy available irregardless of the fate of parent
    };

    // [cpp.lambda.=&] avoid capturing everything by value or worse, by reference!
    auto lambda_avoid = [&]()
    {
        // HERE BE DRAGONS!
    };

    // [cpp.lambda.auto] the type deduction for the captures are quite convoluted
    //    - by reference: uses template rules; will preserve `const` and `&`
    //    - by value: uses template rules; will preserve `const`
    //    - init capture: uses `auto` rules; WILL MESS UP `const` and `&`
    const int Original = 0;
    const int &Reference = Original;
    auto lambda_auto = [Original, Duplicate = Original, &RefDuplicate = Original
                        , NotReference = Reference]()
    {
        // Original => `const int`
        // Duplicate => `int`
        // RefDuplicate => `const int &`
        // NotReference => `int`
    };
}
