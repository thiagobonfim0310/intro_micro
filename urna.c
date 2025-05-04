#include <genlib.h>

int main(void) {
    // Definir a figura lógica principal
    GENLIB_DEF_LOFIG("sistema_somadores");
    
    // Declarar pinos de entrada/saída
    // Entrada de controle
    GENLIB_LOCON("ctrl", IN, "ctrl");      // Controle (1 ou 0)
    GENLIB_LOCON("clk", IN, "clk");        // Clock global
    GENLIB_LOCON("reset", IN, "reset");    // Reset síncrono
    
    // Saídas dos dois somadores (5 bits cada)
    // Somador 1 (quando ctrl=1)
    GENLIB_LOCON("S1_0", OUT, "S1_0");
    GENLIB_LOCON("S1_1", OUT, "S1_1");
    GENLIB_LOCON("S1_2", OUT, "S1_2");
    GENLIB_LOCON("S1_3", OUT, "S1_3");
    GENLIB_LOCON("S1_4", OUT, "S1_4");
    
    // Somador 0 (quando ctrl=0)
    GENLIB_LOCON("S0_0", OUT, "S0_0");
    GENLIB_LOCON("S0_1", OUT, "S0_1");
    GENLIB_LOCON("S0_2", OUT, "S0_2");
    GENLIB_LOCON("S0_3", OUT, "S0_3");
    GENLIB_LOCON("S0_4", OUT, "S0_4");
    
    // Alimentação
    GENLIB_LOCON("vdd", IN, "vdd");
    GENLIB_LOCON("vss", IN, "vss");
    
    // Sinais internos
    char inv_ctrl[10];                     // ctrl invertido
    char en_somador1[10], en_somador0[10]; // Sinais de enable
    char sum1[5][10], sum0[5][10];         // Saídas dos somadores
    char reg1[5][10], reg0[5][10];         // Registradores
    
    // Lógica de controle
    GENLIB_LOINS("inv_x1", "inv_ctrl", "ctrl", inv_ctrl, "vdd", "vss", NULL);
    GENLIB_LOINS("buf_x2", "buf_ctrl", "ctrl", en_somador1, "vdd", "vss", NULL);
    GENLIB_LOINS("buf_x2", "buf_inv_ctrl", inv_ctrl, en_somador0, "vdd", "vss", NULL);
    
    // Implementação dos somadores com halfadders (células padrão)
    for(int i=0; i<5; i++) {
        // Somador 1 (ctrl=1) - soma +1 ao registrador 1
        char carry1[10];
        GENLIB_LOINS("halfadder", GENLIB_NAME("ha1_%d",i),
                    GENLIB_NAME("reg1_%d",i), "vss",  // B=0, Cin=1 (via carry)
                    sum1[i], carry1,
                    "vdd", "vss", NULL);
        
        // Somador 0 (ctrl=0) - soma +1 ao registrador 0
        char carry0[10];
        GENLIB_LOINS("halfadder", GENLIB_NAME("ha0_%d",i),
                    GENLIB_NAME("reg0_%d",i), "vss",  // B=0, Cin=1 (via carry)
                    sum0[i], carry0,
                    "vdd", "vss", NULL);
        
        // Flip-flops para o somador 1
        char mux1_in[10];
        GENLIB_LOINS("mux21", GENLIB_NAME("mux1_%d",i),
                    GENLIB_NAME("reg1_%d",i), sum1[i], en_somador1,
                    mux1_in, "vdd", "vss", NULL);
        
        GENLIB_LOINS("dffr", GENLIB_NAME("ff1_%d",i),
                    "clk", mux1_in, GENLIB_NAME("S1_%d",i), "open",
                    "reset", "vdd", "vss", NULL);
        
        // Conexão da saída para o registrador
        GENLIB_CONNECT(GENLIB_NAME("reg1_%d",i), GENLIB_NAME("S1_%d",i));
        
        // Flip-flops para o somador 0
        char mux0_in[10];
        GENLIB_LOINS("mux21", GENLIB_NAME("mux0_%d",i),
                    GENLIB_NAME("reg0_%d",i), sum0[i], en_somador0,
                    mux0_in, "vdd", "vss", NULL);
        
        GENLIB_LOINS("dffr", GENLIB_NAME("ff0_%d",i),
                    "clk", mux0_in, GENLIB_NAME("S0_%d",i), "open",
                    "reset", "vdd", "vss", NULL);
        
        // Conexão da saída para o registrador
        GENLIB_CONNECT(GENLIB_NAME("reg0_%d",i), GENLIB_NAME("S0_%d",i));
    }
    
    GENLIB_SAVE_LOFIG();
    return 0;
}