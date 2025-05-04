library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity somador_5 is
port
(
    A     : in  std_logic_vector (4 downto 0);  -- Alterado para 5 bits
    B     : in  std_logic_vector (4 downto 0);  -- Alterado para 5 bits
    Cin   : in  std_logic;
    S     : out std_logic_vector (4 downto 0);  -- Alterado para 5 bits
    Cout  : out std_logic;
    Vdd   : in  std_logic;
    Vss   : in  std_logic
);
end somador_5;

architecture behavioral_high_level of somador_5 is
begin
  process(A, B, Cin)
    variable Sum_temp : std_logic_vector (5 downto 0);  -- Agora é 6 bits (5+1 carry)
    variable Cin_temp : std_logic_vector (5 downto 0);  -- Ajustado para 6 bits
  begin
    Cin_temp    := (others => '0');  -- Forma genérica de zerar
    Cin_temp(0) := Cin;
    Sum_temp    := A + B + Cin_temp;
    Cout        <= Sum_temp(5);       -- Agora pega o bit 5 (MSB)
    S           <= Sum_temp(4 downto 0); -- Saída de 5 bits
  end process;
end behavioral_high_level;