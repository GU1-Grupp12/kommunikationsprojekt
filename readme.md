# Vad bör göras?

## Hur saker fungerar

Due kortet ska skicka en trådlös signal(som generas av en signal generator) till mega kortet. Mega kortet ska läsa av den här signalen och sedan skicka tillbaka något via USART.

### Ardurino Mega
- Kunna läsa in ADC värden för att läsa av den tråd lösa signalen.
  - Kräver en interuptt som läser av
- Kunna skicka saker via USART.
  - Har USART_functions modulen.

### Ardurino Due
- Kunna läsa av USART meddeladnet.
  - Har USART_functions modulen som måste portas till due.
- Filtera signalen som kommer från signal generatorn.
  - Har FIR och koffcienter.
- Måste kunna göra dessa saker samtidigt.
  - Använd RTOS för att dela upp dem i olika tasks.
- Felsökning.
