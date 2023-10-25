# Zadania Firmware

W tym folderze znajdziesz dwa zadania związane z firmware do mikrokontrolera STM32G474RET3.

## Zadanie 1 - Obsługa Protokołu UART

**Opis:** Zadanie polega na zaimplementowaniu biblioteki obsługującej protokół UART,

**Pliki:**
- `zad_1/uart_library/Core/Src/main.c` - Główny plik źródłowy projektu.
- `zad_1/uart_library/Libraries/UART_Library` - W tym folderze znajdują się funkcje obsługujące UART.

## Zadanie 2 - Obsługa Diody LED RGB

**Opis:** Zadanie polega na napisaniu kodu w języku C z wykorzystaniem biblioteki HAL, który obsłuży diodę LED RGB w następujący sposób:
- Dioda R zmienia natężenie świecenia sinusoidalnie.
- Dioda G zmienia natężenie świecenia w kształcie piły.
- Dioda B zmienia natężenie świecenia w kształcie trójkąta.
Przyjmujemy okres zmian równy 2 sekundy.

**Pliki:**
- `zad_2/led_lighting/Core/Src/main.c` - Plik źródłowy dla mechanizmu aktualizacji.
