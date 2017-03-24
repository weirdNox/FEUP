FEUP
====
Aqui estão as resoluções de exercícios de algumas unidades curriculares, tais como
Programação e LSDI. Tem tudo o que eu considero que possa ser tornado domínio público,
sendo assim possível usar todo o código que está aqui presente sem qualquer restrição nem
obrigação (esta licença aplica-se, claro, ao código que eu fiz, que é a grande maioria).

Para além disso e principalmente na área da programação, há algumas coisas que eu faço
perante as quais muita gente torce o nariz... Um exemplo disso é usar uma *single
compilation unit* (por outras palavras, incluir todos os ficheiros `.c` num só e compilar
apenas esse).

Para compilar os exercícios de programação, eu normalmente uso apenas um `build.sh`, que
(geralmente) recebe, como argumento, o nome do ficheiro para compilar. Eu tenho
configurado o meu editor de texto para pesquisar automaticamente esse `build.sh` na pasta
que contém o ficheiro que estou a editar e, se não encontrar, na pasta anterior e sempre
assim até encontrar o primeiro. Por isso, às vezes posso ter um `build.sh` específico na
pasta dos exercícios que precisem de mais alguma coisa para compilar.

De resto, não garanto nada em relação a tudo o que está aqui. Podem usar o meu código como
quiserem, sem qualquer garantia, e por vossa conta.
