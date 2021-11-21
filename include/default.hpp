#pragma once

#include <vector>
using SigEType = int;

namespace first_order_language {
static SigEType executeADD2  (std::vector <SigEType> argv) {
    return argv[0] + argv[1];
}
static SigEType executeS1    (std::vector <SigEType> argv) {
    return argv[0] + 1;
}
static SigEType executeS1M   (std::vector <SigEType> argv) {
    return (argv[1] + 1) % argv[0];
}
static SigEType executeADD2M (std::vector <SigEType> argv) {
    return (argv[1] + argv[2]) % argv[0] ;
}
static SigEType executeMUL2  (std::vector <SigEType> argv) {
    return argv[0] * argv[1];
}
static SigEType executeMUL2M (std::vector <SigEType> argv) {
    return (argv[1] * argv[2]) % argv[0] ;
}
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
static bool executeLess2   (std::vector <SigEType> argv){
    return (argv[0] < argv[1]);
}
static bool executeMore2   (std::vector <SigEType> argv){
    return (argv[0] > argv[1]);
}
static bool executeEqual2  (std::vector <SigEType> argv){
    return (argv[0] == argv[1]);
}
static bool executeNEqual2 (std::vector <SigEType> argv){
    return (argv[0] != argv[1]);
}
static bool executeLessEq2 (std::vector <SigEType> argv){
    return (argv[0] <= argv[1]);
}
static bool executeMoreEq2 (std::vector <SigEType> argv){
    return (argv[0] >= argv[1]);
}

}