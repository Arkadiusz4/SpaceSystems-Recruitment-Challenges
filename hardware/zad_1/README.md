# ZADANIE 1

## Schemat znajduje się w PDF (`hardware1.pdf`).

### a)
*Z wykorzystaniem przetwornika analogowo-cyfrowego wbudowanego w mikrokontrolerze musisz dokonać pomiaru sygnału o maksymalnej wartości napięcia do 5V oraz częstotliwości do 1MHz generowanego przez sensor o dużej impedancji wyjściowej.*

Do napięcia 5V podłączone są dwa rezystory R o wartości 50kΩ. Prowadzą one do pinu PB0, które jest wejściem nieodwracającym (plus) wzmacniacza operacyjnego wbudowanego do MCU (jest również wejściem ADC). Pin PB1 jest wyjściem wzmacniacza i jest podpięty do pinu PB2, które jest minusem wzmacniacza operacyjnego.

### b)
*Zaproponuj rozwiązanie, które pozwoli na sterowanie dostarczoną linią zasilania o napięciu 5V. Taki układ miałby za zadanie np. wyłączanie zasilania od pewnej części elektroniki, kiedy nie jest używana. Do tego celu wykorzystaj tranzystor N-MOSFET. Sygnałem sterującym jest dowolny port MCU. Możesz zastosować dodatkowe elementy do poprawnego wysterowania tranzystora.*

Do napięcia 5V jest podłączony rezystor R i bramka D (Drain) tranzystora N-MOSFET.
Bramka G (Gate) jest podłączona do pinu PC14 MCU przez rezystor o wartości 500Ω oraz rezystor uziemiający o wartości 20kΩ.
Bramka S (Source) tranzystora jest podłączona do masy.
Rezystor 20kΩ ten działa jako pull-down resistor, aby utrzymać niski poziom napięcia na bramce tranzystora, gdy port mikrokontrolera jest nieaktywny.
Gdy port mikrokontrolera jest ustawiony na wysoki (1), tranzystor jest w stanie przewodzenia, a zasilanie 5V jest dostarczane do elektroniki. Gdy port mikrokontrolera jest ustawiony na niski (0), tranzystor jest wyłączony, a zasilanie jest odcięte.

### c)
*Zaproponuj rozwiązanie, które pozwoli na pomiar wartości prądu płynącego przez linię zasilania 5V.*

Do napięcia 5V podłączone jest wejście czujnika prądu. Wyjście czujnika jest podłączone do pinu PC0 MCU przez rezystory o wartości 2kΩ i 10kΩ. Zastosowany jest również kondensator, który ma na celu wygładzenie napięcie zasilania.  


### d
*Wyprowadź sygnały potrzebne do zaprogramowania mikrokontrolera i podłącz je na schemacie do złącza STDC14 (header 2x7 o rastrze 1.27mm).*

Napięcie 3V3 jest podłączone do VCC STDC14. SWCLK jest podpięte do pinu PA14, natomiast SWDIO do pinu PA13 MCU (są one używane do debugowania). SWO jest podpięte do pinu PB3. Wyjścia NC mogą pozostać niepodłączone. RX jest podłączone do pinu PA3, natomiast TX do pinu PA2 (odpowiadają one za komunikację). Wyjście RST jest podłączone do PG10.

### e)
*Doprowadź zasilanie do mikrokontrolera.*

Mikrokontroler jest zasilany przez napięcie 3V3. Wejścia VDD są uziemiane przez VSS, natomiast VDDA - przez VSSA.  Zastosowane są również kondensatory, które mają na celu wygładzenie napięcie zasilania doprowadzonych do MCU. Można również skonfigurować wejście VBAT (zasilanie dla rejestrów RTC i zapasowych), jednak ja go nie potrzebowałem, dlatego zostawiłem niepodłączone.
