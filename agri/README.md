# Agri
Libreria didattica per la creazione e l'elaborazione di grafi in linguaggio C

## Caratteristiche di Agri
- Rete neurale mulistrato (completamente connessa) in linguaggio C
- Addestramento con Backpropagation
- Facile da usare: bastano 3 chiamate per creare, addestare e provare una rete
- Possibilità di salvare la rete in formato CSV (Tabulazioni al posto delle virgole TSV)
- Caricare una rete da file con una sola chiamata
- Anlizzare la struttra delle connessioni con Calc (o Excel) o con un editor di testo
- Modificare i pesi delle connessioni manualmente per vedere gli effetti
- Valutare l'errore quadratico della rete per sapere quando completere l'addestramento

- Multipiattaforma

## Installazione
Clonare il repository

`git clone https://github.com/francescosisini/ReLe.git`

Entrare nella directory  `ReLe` dalla directory di clone: `cd ReLe`

Lanciare `make`

## Esempi d'uso
Per testare la libreria e provare ad usarla nelle proprie applicazioni guardare gli esempi della cartella [esempi](esempi)


Latin fundamentals
------------------

### The nouns

Latin is a declined language. This means that each noun in the sentence
changes according to the role it plays.\
 What changes is not the whole word, but only its ending.

As an example, let consider the noun "girl" in these two sentences:

1.  The girl is beautiful
2.  I have seen the girl

In the first sentence the girl is the subject.\
 In the second one, the girl is no more the subject. I am the subject,
and she is the direct object of my action.\
 Although the word "girl" played two different roles in the two
sentences, nothing has changed, it is up to the reader to understand the
difference.\

Let now consider the latin translation:

1.  Puella pulchra est
2.  Puellam vidi

*Puella* means "girl". \
 As you cas see, in the two sentences, the final part of the word has
changed.\
 This is the effect of the declension: depending on the role it plays in
the sentence, a noun is declined in different "cases".

#### The cases

There are six cases each one representing one or more roles a noun can
assume:

1.  Nominative: subject\
    ex. "**The girl** is beautiful" -\> *Puella pulchra est*
2.  Genitive: possessive nouns\
    ex. "This is **the girl's** book" -\> *Hic puellae liber est*
3.  Dative: indirect objects\
    ex. "I give a pen **to the girl**" -\> *calamum puellae dono*
4.  Accusative: direct objects\
    ex. "I have seen **the girl**" -\> *Puellam vidi*
5.  Vocative: used for calling\
    ex. "Come here please, **girl**" -\> *Veni, puella*
6.  Ablative: prepositional objects\
    ex. "I went to the seaside **with the girl**" -\> *Ab litori, cum
    puella ivi*

#### The declensions

Seems easy enough right? Depending on the role that a noun plays in the
sentence, we change its ending and that's it.\
 Unfortunately, it is not as easy as it may seem. In reality there is no
single way to decline a name in the six cases, but ... five different
ways.\
 Each of these five ways corresponds to a declension.

In latin each noun belongs to a declension.\
 Let's compare it to an object-oriented programming language.\
 Imagine that the *noun* is an abstract class with an unimplemented
*decline(case)* method that returns the noun declined in the specified
case.\
 Latin has five classes which derive from that abstract class and which
implement the "decline" method differently.

As mentioned above, there are five declensions.\
 A word that belongs to a specific declension will be declined in the
six cases, following the rules of that declension.\
 For example, the genitive of the word "puella", that belongs to the
first declenson, is "puellae", where **ae** is the desinence that
characterizes the genitive of each word that belongs to the first
declension.

#### First declension
<pre>
  Singular   Plural

  Cella      Cellae
  Cellae     Cellarum
  Cellae     Cellis
  Cellam     Cellas
  Cella      Cellae
  Cella      Cellis
</pre>
  ---------- ---------

#### Second declension
<pre>
  Singular   Plural

  Nodus      Nodi
  Nodi       Nodorum
  Nodo       Nodis
  Nodum      Nodos
  Node       Nodi
  Nodi       Nodis
</pre>
  ---------- ---------

#### Third declension
<pre>
  Singular        Plural

  Colligatio      Colligationes
  Colligationis   Colligationum
  Colligationi    Colligationibus
  Colligationem   Colligationes
  Colligatio      Colligationes
  Colligatione    Colligationibus
</pre>
  ---------- ---------

#### Fourth declension
<pre>
  Singular   Plural
  
  Manus      Manus
  Manus      Manuum
  Manui      Manibus
  Manum      Manus
  Manus      Manus
  Manu       Manibus
</pre>
  ---------- ---------

#### Fifth declension
<pre>
  Singular   Plural

  Res        Res
  Rei        Rerum
  Rei        Rebus
  Rem        Res
  Res        Res
  Re         Rebus
</pre>

The library components
----------------------
## Types
##### typedef enum  {SX,DEORSUM,DX,SURSUM,FIXO} versus
- versus,us, decl. 4: direction
- sx stands for sinistra,ae, decl. 1: left
- deorsum, adverb: down
- dx stands for dextra,ae, decl. 1: right

