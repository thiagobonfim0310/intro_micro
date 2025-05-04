library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity urna_eletronica is
  Port (
    votar        : in std_logic;                     
    candidato    : in std_logic;                     
    reg_a        : out std_logic_vector(4 downto 0); 
    reg_b        : out std_logic_vector(4 downto 0); 
		Vdd : in std_logic;
		Vss : in std_logic;
		reset : in std_logic
);
end urna_eletronica;

architecture Behavioral of urna_eletronica is
    signal reg_A_int : std_logic_vector(4 downto 0) := "00000"; 
    signal reg_B_int : std_logic_vector(4 downto 0) := "00000"; 
begin
    process(votar)
    begin
        if rising_edge(votar) then
          if reset = '1' then
            reg_A_int <= "00000";
            reg_B_int <= "00000";		            
          elsif candidato = '0' then
            reg_A_int <= reg_A_int + "00001"; 
          elsif candidato = '1' then
            reg_B_int <= reg_B_int + "00001"; 
          end if;
        end if;
    end process;

    reg_a <= reg_A_int;
    reg_b <= reg_B_int;

end Behavioral;
