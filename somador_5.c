#include <genlib.h>

int main() {
    // Definir a figura lógica do somador de 5 bits
    GENLIB_DEF_LOFIG("somador_5bits");
    
    // Declarar pinos de entrada/saída
    // Entradas A (5 bits)
    GENLIB_LOCON("A0", IN, "A0");
    GENLIB_LOCON("A1", IN, "A1");
    GENLIB_LOCON("A2", IN, "A2");
    GENLIB_LOCON("A3", IN, "A3");
    GENLIB_LOCON("A4", IN, "A4");
    
    // Entradas B (5 bits)
    GENLIB_LOCON("B0", IN, "B0");
    GENLIB_LOCON("B1", IN, "B1");
    GENLIB_LOCON("B2", IN, "B2");
    GENLIB_LOCON("B3", IN, "B3");
    GENLIB_LOCON("B4", IN, "B4");
    
    // Carry de entrada
    GENLIB_LOCON("Cin", IN, "Cin");
    
    // Saídas S (5 bits)
    GENLIB_LOCON("S0", OUT, "S0");
    GENLIB_LOCON("S1", OUT, "S1");
    GENLIB_LOCON("S2", OUT, "S2");
    GENLIB_LOCON("S3", OUT, "S3");
    GENLIB_LOCON("S4", OUT, "S4");
    
    // Carry de saída
    GENLIB_LOCON("Cout", OUT, "Cout");
    
    // Alimentação
    GENLIB_LOCON("vdd", IN, "vdd");
    GENLIB_LOCON("vss", IN, "vss");
    
    // Variáveis para os carries internos (como strings nomeadas)
    char carry0[10] = "carry0";
    char carry1[10] = "carry1";
    char carry2[10] = "carry2";
    char carry3[10] = "carry3";
    char carry4[10] = "carry4";
    char carry5[10] = "carry5";
    
    // Conectar o carry inicial
    GENLIB_CONNECT("Cin", carry0);  // Conexão correta: de "Cin" para carry0
    
    // Instanciar somadores completos de 1 bit para cada estágio
    // Bit 0 (LSB)
    GENLIB_LOINS("fulladder", "fa0", 
                "A0", "B0", carry0, 
                "S0", carry1,
                "vdd", "vss", NULL);
    
    // Bit 1
    GENLIB_LOINS("fulladder", "fa1", 
                "A1", "B1", carry1, 
                "S1", carry2,
                "vdd", "vss", NULL);
    
    // Bit 2
    GENLIB_LOINS("fulladder", "fa2", 
                "A2", "B2", carry2, 
                "S2", carry3,
                "vdd", "vss", NULL);
    
    // Bit 3
    GENLIB_LOINS("fulladder", "fa3", 
                "A3", "B3", carry3, 
                "S3", carry4,
                "vdd", "vss", NULL);
    
    // Bit 4 (MSB)
    GENLIB_LOINS("fulladder", "fa4", 
                "A4", "B4", carry4, 
                "S4", carry5,
                "vdd", "vss", NULL);
    
    // Conectar o carry final à saída Cout
    GENLIB_CONNECT(carry5, "Cout");  // Conexão correta: de carry5 para "Cout"
    
    // Salvar a figura lógica
    GENLIB_SAVE_LOFIG();
    return 0;
}