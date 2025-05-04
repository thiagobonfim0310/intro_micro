#include <genlib.h>
#define POWER "vdde","vdd","vsse","vss",NULL

int main(void){
	int i;
	
	GENLIB_DEF_LOFIG("chip_urna");

	GENLIB_LOCON("reg_a[4:0]", OUT, "reg_a[4:0]"); 
	GENLIB_LOCON("reg_b[4:0]", OUT, "reg_b[4:0]");
	GENLIB_LOCON("reset", IN, "reset"); 
	GENLIB_LOCON("candidato", IN, "candidato");
  GENLIB_LOCON("votar", IN, "votar");
	GENLIB_LOCON("vdd", IN, "vdd");
	GENLIB_LOCON("vss", IN, "vss");
	GENLIB_LOCON("vdde", IN, "vdde");
	GENLIB_LOCON("vsse", IN, "vsse");
	GENLIB_LOINSE("core_urna", "core",
	"vdd => vdd",
	"vss => vss",
	"candidato => candidato_i",
	"votar => votar_c",
	"reset => reset_i",

	"reg_a[4:0] => reg_ai[4:0]",
	"reg_b[4:0] => reg_bi[4:0]",
	NULL); 

	for(i = 0; i < 5; i++) {
		GENLIB_LOINS("po_sp", GENLIB_NAME("p_reg_a%d",i), GENLIB_ELM("reg_ai",i), GENLIB_ELM("reg_a",i), "votar_i", POWER);
		GENLIB_LOINS("po_sp", GENLIB_NAME("p_reg_b%d",i), GENLIB_ELM("reg_bi",i), GENLIB_ELM("reg_b",i), "votar_i", POWER);
	}

	GENLIB_LOINS("pck_sp", "p_votar", "votar", "votar_i", POWER);
	GENLIB_LOINS("pi_sp", "p_candidato", "candidato", "candidato_i", "votar_i", POWER);
	GENLIB_LOINS("pi_sp", "p_reset", "reset", "reset_i", "votar_i", POWER);

  GENLIB_LOINS("pvddick_sp","p_vddick0","votar_c","votar_i","vdde","vdd","vsse","vss",NULL);
  GENLIB_LOINS("pvssick_sp","p_vssick0","votar_c","votar_i","vdde","vdd","vsse","vss",NULL);
  GENLIB_LOINS("pvddeck_sp","p_vddeck0","votar_c","votar_i","vdde","vdd","vsse","vss",NULL);
  GENLIB_LOINS("pvsseck_sp","p_vsseck0","votar_c","votar_i","vdde","vdd","vsse","vss",NULL);

	GENLIB_SAVE_LOFIG();

	return 0;
}