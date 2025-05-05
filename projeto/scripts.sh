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

# -V modo verboso, -I para encontrar o aquivo, nome da entidade vhdl gera  urna.vbe
vasy -V -I vhdl -a urna #netlist estrutural
#-A algorimos de bolleanos, -d 100 profunididade de expressoes
boom -A -d 100 urna boom_urna #netlist logica
proof -a -d urna boom_urna #verifica se o circuito eh equivalente
#gera o vst e o xsc, para reoteamento
boog boom_urna boog_urna
#gera o arquivo de com o resultado dos teste de acordo o arquivo de teste
alliance-genpat -v genpat_urna
# faz a comparação  do arquivo de teste com o vbe aplicando as entradas
asimut -b urna genpat_urna_result asimut_urna_result

cp boog_urna.vst core_urna.vst

# gera o aquivo de posicionamento de acordo com o .vst
alliance-ocp -rows 6 -ring -ioc ioc_urna core_urna core_posicionado
# gera o arquivo de roteamento .ap
nero -p core_posicionado core_urna core_roteado

genlib pad_generator