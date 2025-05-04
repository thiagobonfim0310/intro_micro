rm *.pat
rm *.vst
rm *.ap
rm *.vbe
rm *.xsc

rm *.sh~
rm *.pat~
rm *.vst~
rm *.ap~
rm *.vbe~
rm *.xsc~
rm *.rin~
rm *.c~
rm *.vhdl~
rm *.ioc~

vasy -V -I vhdl -a urna
boom -A -d 100 urna boom_urna
proof -a -d urna boom_urna
boog boom_urna boog_urna

alliance-genpat -v genpat_urna
asimut -b urna genpat_urna_result asimut_urna_result

cp boog_urna.vst core_urna.vst
alliance-ocp -rows 6 -ring -ioc ioc_urna core_urna core_posicionado
nero -p core_posicionado core_urna core_roteado
genlib pad_generator