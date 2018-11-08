contract c {
    function f1(mapping(uint => uint) calldata) pure external returns (mapping(uint => uint) memory) {}
}
// ----
// TypeError: (29-59): Mapping types as arguments or return values can only be used in internal or library functions.
// TypeError: (84-112): Mapping types as arguments or return values can only be used in internal or library functions.
