# Gomoku

en gros y a deux facons de gagner.

Soit en alignant 5 pierres qui ne peuvent pas etre prises au prochain tour
genre si le mec doit poser deux pierres pour casser le pattern des cinq de l'adversaire, c'est foutu

soit en capturant dix pierres de l'adversaire

donc en gros pour capturer deux pierres, il faut les encadrer.
genre :
....
xoo.
....

si le mec place un x comme là c'est gagné:
....
xoox
....

ce qui donne :
....
.x..x
....

Par contre, il faut que les deux pierres du milieux soient deja placées. Le cas suivant ne fonctionnera pas
....
xo.x
....

tour suivant :
....
xoox
....

et les deux 'o' ne sont pas pris.

et la deuxieme grande règle est la suivante:
ca s'appelle le double trois
Cette règle stipule qu'il est interdit de poser une pierre conduisant à la formation de deux
alignements libres de trois pierres en ayant une en commun. Attention, cette pierre n'est pas
forcément celle de l'intersection !
pour cette règle, un alignement de trois pierres peut etre
.....
.xxx.
.....
ou
.....
.xx.x
.....

exple: (donc ca on ne peut pas)
.....
....x
.xx.x
.....
.....
ou
.....
..x..
.x.x.
..x..
