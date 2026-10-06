#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct PureInstruction {
    char Command;
    int Reg1;
    int Destiny;
    int Reg2_Imm;
    unsigned char FlagTipo: 1;
} PureInstruction;

typedef union PCInstruction {
    uint32_t MachineCode;

    struct {
        uint32_t opcode: 8;
        uint32_t reg1: 5;
        uint32_t reg2: 5;
        uint32_t destiny: 5;
        uint32_t unused: 9;
    } typeR;

    struct {
        uint32_t opcode: 8;
        uint32_t reg1: 5;
        uint32_t destiny: 5;
        int32_t immediate: 14;
    } typeI;

} PCInstruction;

PCInstruction Codificar(PureInstruction* Inst) {
    PCInstruction pc;
    pc.MachineCode = 0;

    if (Inst->FlagTipo == 0) {
        pc.typeR.opcode = (uint32_t) Inst->Command;
        pc.typeR.reg1 = (uint32_t) Inst->Reg1;
        pc.typeR.reg2 = (uint32_t) Inst->Reg2_Imm;
        pc.typeR.destiny = (uint32_t) Inst->Destiny;
        pc.typeR.unused = 0;
    }
    else {
        pc.typeI.opcode = (uint32_t) Inst->Command;
        pc.typeI.reg1 = (uint32_t) Inst->Reg1;
        pc.typeI.destiny = (uint32_t) Inst->Destiny;
        pc.typeI.immediate = (uint32_t) Inst->Reg2_Imm;
    }

    return pc;
}

void PrintInstruction(PCInstruction *Inst) {
    printf("0x%08X\n", Inst->MachineCode);
}

int main() {
    int N;
    
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        PureInstruction pure;
        int flag;

        scanf("%d %c %d %d %d", &flag, &pure.Command, &pure.Reg1, &pure.Reg2_Imm, &pure.Destiny);
        pure.FlagTipo = flag;

        PCInstruction pc = Codificar(&pure);
        PrintInstruction(&pc);
    }
    
    return 0;
}