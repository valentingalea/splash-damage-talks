// [basic.rule.brace] FOLLOW UE4 coding style i.e. Allman style
void BraceStyle()
{
    // illustration purpose only - don't do this in live code
    bool FailCondition = false, TrueCondition = true,
        SomethingElse = true, Contract = true, Binding = true;

    if (FailCondition)
    {
        return; // even for one liners
    }

    if (TrueCondition)
    {
        /* ... */
    }
    else if (SomethingElse)
    {
        /* ... */
    }
    else // !SomethingElse and !TrueCondition
    {
        /* ... */
    }

    // for `switch` statements follow Unreal's guideline
    // https://docs.unrealengine.com//Dev/CodingStandard/#switchstatements

    // [basic.rule.parens] parenthesis link with the expression not the keyword
    for (;/*...*/;)
    {
    }
    
    // [cpp.return.early] use early returns to avoid excessive nesting
    //    especially for pre-conditions / contracts
    //    one exception is logic flow where too many early impairs readability
    if (!Contract && !Binding)
    {
        return;
    }
    // versus
    if (Contract)
    {
        if (Binding)
        {
        }
    }

    // [cpp.if.init] use the if-with-initializer idiom
    if (bool IsGame = FApp::IsGame())
    {
        /* ... */
    }
}