Comecemos com uma pequena revisão daquilo a que o Casey chama de "platform API design". The idea is that there are two separate service layers. On one, we have the platform service layer, which deals with requests issued by the game engine. It can be some file that needs to be loaded and the platform needs to know how to do that, some sound that the game wants to play, putting stuff on the screen, access the system clock, etc.
On the other side, we have the game service. Yeah, that's it.


