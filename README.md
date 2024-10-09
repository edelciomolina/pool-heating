# Solar Pool Heating Controller

## Como compilar
- Ctrl + Shift + P e escolha `PlatformIO: Build`
- Ctrl + Shift + P e escolha `Wokwi: Start Simulator`
- O Wokwi com o simulador vai executar com a versão recém compilada

## Como depurar pelo Wokwi
- Remova o cabo USB do ESP32
- Ctrl + Shift + P e escolha `Wokwi: Start Simulator and Wait for Debugger`
- O Wokwi com o simulador vai ficar em pausa (botão amarelo)
- Ctrl + Shift + D, selecione `PIO Debug` e F5 para executar o projeto   
- Utilize breakpoints para depurar o código.
- Pressione o botão amarelo no simulador para continuar a execução
> Tudo funciona meio lento enquanto em debugging, é normal.
> Mantenha o Wokwi Simulator sempre visivel

## Como fazer upload
- Desligue o cabo USB do esp32
- Segure o botão da esquerda e conecte o cabo USB
- Ainda não solte!
- Abra o ícone do PlatformIO no menu de ferramentas do VSCode
- Selecione a aba de `Project Tasks > esp32 > General` e clique em `Upload`
- Assim que aparecer as mensagens de 'Writing' o botão pode ser solto

## Monitorando logs
- Abra o ícone do PlatformIO no menu de ferramentas do VSCode
- Selecione a aba de `Project Tasks > esp32 > General` e clique em `Monitor`
- Pronto os logs serão exibidos no terminal


## Dicas
- Fique ligado na quantidade de terminais abertos, se muitos, pode ocasionar maluquices


