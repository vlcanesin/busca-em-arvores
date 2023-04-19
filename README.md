# Estruturas de Dados 2022/2 - Trabalho Final
<h3 align="center"> Comparação entre arquivos utilizando árvores balanceadas </h3>

<div align="justify">
<p>
&emsp;&emsp;Este trabalho tem como finalidade aplicar o uso de estruturas de dados na tarefa de
quantificar a similaridade entre dois textos.
</p>
<p>
&emsp;&emsp;São fornecidos 3 arquivos de texto como dados de entrada para o problema: dois
deles contêm os textos (A e B) que serão comparados, palavra a palavra, e o terceiro
contém um conjunto de palavras chamadas stopwords. As stopwords são palavras (que são
muito frequentes ou que não têm muito valor semântico) que devem ser ignoradas na leitura
dos dois textos.
</p>
<p>
&emsp;&emsp;O cálculo da similaridade é feito a partir do coeficiente de Jaccard, cuja fórmula está
apresentada abaixo:
</p>
</div>

![image](https://user-images.githubusercontent.com/84688945/233153240-0a2e014e-da82-4778-8b3b-7af295bf822b.png)

<div align="justify">
<p>
&emsp;&emsp;|𝑇𝑒𝑥𝑡𝑜A| e |𝑇𝑒𝑥𝑡𝑜B| são, respectivamente, o número de palavras distintas dos textos A
e B, enquanto |𝑇𝑒𝑥𝑡𝑜A ∩ 𝑇𝑒𝑥𝑡𝑜B| é o número de palavras distintas que ocorrem em ambos os
textos A e B. Logo, o coeficiente de Jaccard computa a taxa de palavras compartilhadas
entre dois textos. O score resultante estará entre 0 e 1, onde 1 representa a similaridade
máxima (textos com as mesmas palavras) e 0 indica que os textos não têm nenhuma
palavra em comum.
</p>
<p>
&emsp;&emsp;Para computar o coeficiente de Jaccard de forma otimizada, foi escolhido
implementar, no programa, o armazenamento das palavras em árvores balanceadas de
pesquisa, ao contrário, por exemplo, de listas.
</p>
<p>
&emsp;&emsp;A inserção de elementos em listas não é ordenada, nenhuma relação é preservada
entre os elementos. Isso torna o acesso a eles, operação utilizada para verificar a
ocorrência prévia de uma palavra no texto, muito ineficiente - de complexidade linear. Em
oposição a isso, a estrutura de árvores (especialmente as balanceadas, que tendem a
manter sua altura mínima) minimiza a quantidade de operações realizadas na busca, já que
os seus elementos são inseridos de tal maneira que geram uma estrutura ordenada (neste
caso, seguindo a própria ordem alfabética das palavras). Isso torna a complexidade do
acesso logarítmica.
</p>

## Árvores Utilizadas - AVLs e Rubro-Negras
<p>
&emsp;&emsp;As árvores binárias de pesquisa (ABPs), por si só, podem assumir qualquer formato;
apenas a ordem dos elementos deve ser preservada. Isso não é algo desejado, já que a
busca em árvores só é eficiente quando elas tendem a manter uma altura ótima (ou próxima
da ótima).
</p>
<p>
&emsp;&emsp;Nesse sentido, são utilizados algoritmos de balanceamento para minimizar a altura
das árvores construídas. Utilizamos dois tipos de árvores balanceadas neste trabalho: as
árvores AVL e as Rubro-Negras.
</p>
<p>
&emsp;&emsp;As árvores AVL são um tipo de ABP em que, para todos os seus nós, a diferença de
altura das subárvores esquerda e direita não pode ser maior do que 1 (essa diferença é
chamada de fator de balanceamento - FB). Tal condição exige que a árvore tenha altura
ótima.
</p>
</div>

![image](https://user-images.githubusercontent.com/84688945/233153800-ce4cb9e6-d309-444f-90a2-a7c479ae1bfb.png)

<div align="justify">
<p>
&emsp;&emsp;Por ter a menor altura possível, esse tipo de árvore é o melhor para a busca de um
elemento. Porém, o recálculo da altura dos nós é muito custoso: sempre que um nó é
inserido, todos os nós do ramo que o contém terão suas alturas potencialmente alteradas.
Isso torna a inserção uma operação um pouco mais lenta.
</p>
<p>
&emsp;&emsp;Já as árvores Rubro-Negras são ABPs que possuem um critério de balanceamento
um pouco mais sofisticado. Cada nó possui uma cor, vermelho ou preto; todos os ramos
devem conter a mesma quantidade de nós pretos, e nenhum nó vermelho pode ter um filho
vermelho. Esse tipo de balanceamento impede que o tamanho do maior ramo seja maior do
que o dobro do menor ramo.
</p>
</div>

![image](https://user-images.githubusercontent.com/84688945/233154085-67b3b3ee-7873-4bed-9f40-5929ff06c633.png)

<div align="justify">
<p>
&emsp;&emsp;A altura de uma árvore Rubro-Negra não é ótima (ainda que seja balanceada), o que
torna a busca uma operação um pouco mais custosa comparada à AVL. Mas as operações
de balanceamento requerem menos buscas recursivas na árvore, que ocorrem somente em
um caso específico do balanceamento - a troca de cores. Portanto, elas são preferíveis
quando forem feitas mais inserções do que buscas na árvore.
</p>

## Descrição do Algoritmo
<p>
&emsp;&emsp;Durante a implementação do nosso programa, declaramos dois tipos de structs para
representar os respectivos nós de cada árvore, mostradas a seguir:
</p>
</div>

![image](https://user-images.githubusercontent.com/84688945/233154307-495cb82f-5b6c-44dc-bff0-eb04e6e7a9ce.png)

<div align="justify">
<p>
&emsp;&emsp;O algoritmo é executado em 3 passos. Primeiramente, é feita a leitura do arquivo
que contém as stopwords e insere-se cada palavra em uma árvore AVL. Isso é feito para
otimizar as consultas futuras, já que todas as palavras dos textos serão comparadas com a
árvore AVL para determinar se são stopwords ou não. Como mencionado, a árvore AVL
garante um tempo de consulta mínimo, e a inserção não precisa ser tão otimizada, já que,
normalmente, a quantidade de stopwords fornecida é pequena.
</p>
<p>
&emsp;&emsp;Em seguida, o algoritmo lê o arquivo de texto A (enquanto ignora as palavras
presentes na árvore de stopwords) e as insere em uma árvore Rubro-Negra. A escolha da
árvore Rubro-Negra se dá pelo fato de que, nesse estágio, é feita apenas a operação de
inserção. Neste passo, é possível contar o número de palavras distintas do texto A: basta
aumentar um contador sempre que um elemento novo for inserido.
</p>
<p>
&emsp;&emsp;Finalmente, é feita a leitura do arquivo de texto B, novamente desconsiderando as
stopwords e fazendo a inserção das palavras restantes na <b>mesma</b> árvore Rubro-Negra. A
inserção na mesma árvore otimiza o processo de escrita, já que se a palavra a ser escrita já
estiver presente na árvore (algo que é possível de se detectar na própria inserção), ela não
é armazenada na estrutura.
</p>
<p>
&emsp;&emsp;Enquanto é feita essa inserção, é realizada a contagem das palavras presentes no
texto B e o tamanho da interseção. Existem três cenários que podem ocorrer ao inserir um
elemento do texto B na árvore:
</p>
<ol>
<li>&emsp;O elemento não está na árvore: o contador de palavras do texto B deve ser
incrementado e é marcado que o elemento veio do texto B (origem = ‘B’);</li>
<li>&emsp;O elemento está na árvore e veio de A: tanto o contador de palavras do texto B
quanto o da interseção são incrementados, e também é marcado que o elemento
veio do texto B para que ele não seja contado novamente;</li>
<li>&emsp;O elemento está na árvore, mas veio de B: nada acontece.</li>
</ol>
<p>
&emsp;&emsp;Feito isso, tem-se as informações necessárias para o cálculo (eficiente) do
coeficiente de Jaccard: |𝑇𝑒𝑥𝑡𝑜A|, |𝑇𝑒𝑥𝑡𝑜B| e |𝑇𝑒𝑥𝑡𝑜A ∩ 𝑇𝑒𝑥𝑡𝑜B|.
</p>

</div>
