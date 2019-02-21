// [cpp.auto] use `auto` or not at your discretion but BE CONSISTENT
//    - if a part of code already has an auto style, follow it, don't mix
//    - don't bikeshed over the merits of each style, pick one and stick with it
void AutoStyle()
{
    // [cpp.auto.init] auto forces to have initialization - this is always good
    auto Int = 42; // an int, if explicitly declared it would have garbage value
    auto MoreStuff = 42u; // this is unsigned int;
    auto EvenMore = 42.f; // float
    auto Precision = 42.0; // double
    auto Condition = false; // boolean
    auto Big = 42ll; // long long

    int *PtrInt = &Int;
    int &RefInt = Int;

    // auto on its own NEVER DEDUCES references or const'ness
    auto not_what_you_think = static_cast<int &>(Int); // <- BAD: type is `int`
    auto still_bad = static_cast<const int>(Int); // <- BAD: type is still `int`

    // [cpp.auto.golden-rule] ALWAYS mark auto with the appropriate qualifiers:
    //    const, &, * - even if it's superfluous
    auto &proper_ref = Int;
    auto &enforce_ref = RefInt;
    auto hidden_ptr = &Int; // <- BAD even if it still works
    auto *explicit_ptr = PtrInt;
    const auto &explicit_ref = RefInt;

    // [cpp.auto.init.lbmd] a generalization of the always-initialized is the
    //    self calling lambda technique (bonus: very useful for `const`)
    const auto InitLevel = []()
    {
    // possible example of complicated logic
    // that cannot be easily implemented with the ?: operator
    //
    //    if (auto CamMgr = (static_cast<ACameraManager *>(PC))->GetCameraManager())
    //        return CamMgr->GetCurrentHeightLevel();
    //    else
            return 0;
    }(); // <- called here immediately, so guaranteed to get a default value

    // [cpp.auto.fwd] Don't use `auto &&` unless you know what you are doing
    //    i.e perfect forwarding inside a lambda
}

void NoAutoStyle()
{
    // just don't use it and move on
    //
    // if you work in an area where it started with AutoStyle,
    // continue it or refactor it all without auto
    // mix of the 2 styles leads to poor readability and maintainability
}