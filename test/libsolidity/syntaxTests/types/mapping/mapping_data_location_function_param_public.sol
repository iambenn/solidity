contract c {
    function f3(mapping(uint => uint) memory) view public {}
}
// ----
// TypeError: (29-57): Mapping types as arguments or return values can only be used in internal or library functions.
