#include <genlib.h>

int main() {
    GENLIB_DEF_LOFIG("fulladder");
    
    GENLIB_LOCON("A", IN, "A");
    GENLIB_LOCON("B", IN, "B");
    GENLIB_LOCON("Cin", IN, "Cin");
    GENLIB_LOCON("S", OUT, "S");
    GENLIB_LOCON("Cout", OUT, "Cout");
    GENLIB_LOCON("vdd", IN, "vdd");
    GENLIB_LOCON("vss", IN, "vss");
    
    char s1[10], c1[10], c2[10];
    
    GENLIB_LOINS("xor2", "xor1", "A", "B", s1, "vdd", "vss", NULL);
    GENLIB_LOINS("xor2", "xor2", s1, "Cin", "S", "vdd", "vss", NULL);
    GENLIB_LOINS("and2", "and1", "A", "B", c1, "vdd", "vss", NULL);
    GENLIB_LOINS("and2", "and2", s1, "Cin", c2, "vdd", "vss", NULL);
    GENLIB_LOINS("or2", "or1", c1, c2, "Cout", "vdd", "vss", NULL);
    
    GENLIB_SAVE_LOFIG();
    return 0;
}