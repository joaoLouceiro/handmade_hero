# Going Square on a ring

Buffers are weird. I'ma be honest, I only started understanding the code when Casey started debugging it, by day 9. It didn't really help that his result up to the end of the first day working with audio (output) was totally different from mine. Mine was glitchy all the way from the beginning, but I had to wait until he added the check for equality between the byte to lock and the play cursor till I got a similar outcome.

The SDL_QueueAudio solution worked quite better out of the box, but I did want to understand Casey's solution, so I went with the ring buffer.

The idea is not that complicated: we have a size (we can think of time) limited amount of space we can write to. It's a very short amount of time, like one second. But sound is not limited to one single second, so we need to figure out a way to squeeze more time into that buffer. So what do we do? We overwrite the data that was already read. As 

1. I set up some generic audio properties in main, before our loop starts. My (secondary) buffer is 192000 bytes long, which translates to 4 bytes per sample, two for the right and two for the left, at 48000 samples per second.
2. On SDLInitAudio, I instantiate AudioSettings and AudioRingBuffer. The first, AudioSettings, is only accessed here. We define it's samples per scond, it's audio format, and, most importantly, we define it's callback (SDLAudioCallback) and what data it's going to use, through the .userdata prop. For this, we pass a pointer to the global struct AudioRingBuffer.
3. Still in the same function, we define the size of the RingBuffer (the same 192000), reserve the necessary memory, and define both it's play and write cursors as 0.
4. Daqui, voltamos à main. A primeira coisa a fazer é dar Lock ao audio buffer. Isto assegura que o callback não será chamado até que o Unlock seja chamado.
5. Temos de definir os tamanhos das regiões. Não vou estar aqui a explicar o como nem porquê das regiões num ring buffer, mas é aqui que o fazemos. Pegamos num pointer para a área a escrever, definido com base nos dados passados para o RingBuffer e numa variável ByteToLock que, acho, nos indica em que byte estamos a bloquear a escrita.
6. Calculamos o tamanho da primeira região com base no tamanho total do buffer.
7. Criamos a segunda região com base na quantidade total de informação que temos para escrever (BytesToWrite) à qual subtraimos o tamanho da primeira região.
8. Aqui libertamos o buffer de audio e deixamos que os dois loops, um para cada região, façam o que têm a fazer.
9. Quando a função de callback é chamada, as regiões são recalculadas, a memória é copiada para as áreas corretas, e o play e write cursors são redefinidos. Há aqui alguma black magic que eu não estou a perceber bem (porque é que o Length que chega à função é 8224, e porque é que isso corresponde a 0x00002020?), portanto vou só seguir caminho.

Seeing him debug is quite interesting. First, he changes the code so that the data is only written to the buffer once. That means he takes any dirty overwrite bug out of the equation. Then, because we are only writing to the first region, he takes note that the error might be in the write to the second region or in the lock mechanism
