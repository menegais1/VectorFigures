
Roberto Menegais 201810233

Instruções para o uso do programa:

Para selecionar qual imagem deve ser carregada pelo programa é necessario digitar o nome do arquivo
na criação do objeto BitmapReaderManager, que é criado na main, essa imagem deve estar na pasta rnmenegais/src/Images do projeto. Após isso basta compilar e
executar o programa.

Funcoes:

1. RChannel = Exibe a imagem em tons de vermelho.
2. BChannel = Exibe a imagem em tons de azul.
3. GChannel = Exibe a imagem em tons de verde.
4. Grayscale = Exibe a imagem em tons de cinza com o calculo da luminancia.
5. Histograma = Exibe os histogramas da frequencia dos canais RGB da imagem assim como o histograma da luminância
6. Scale = Slider que permite reescalar a imagem, vai de 1/128 até 2.
7. Rotation = Slider que permite rotacionar a imagem, vai de 0 até 180 graus.
8. FlipX = Inverte as colunas da imagem, portanto a coluna 0 se tornará a coluna w, a coluna 1 se tornara w - 1....
9. FlipY = Inverte as linhas da imagem, portanto a linha 0 se tornará a linha h, a linha 1 se tornara h - 1....
10. Reset = Reseta a imagem para o estado original, quando ela foi carregada.
11. É possivel movimentar a imagem ao clicar em cima dela e arrastar o mouse.
12. O programa carrega bitmaps de 1, 4, 8, 24, 32 bits por pixel sem compressão, com paleta de cores.

OBS:

É possivel uma queda de performance ao se usar o slider de escala e rotação, se a imagem for muito grande ou o slider for movido
muito rápido, é esperado já que os algoritmos foram implementados em sua maneira mais didatica e não estão nada otimizados.
