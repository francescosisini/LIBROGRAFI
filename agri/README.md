# Agri
Libreria didattica per la creazione e l'elaborazione di grafi in linguaggio C

## Caratteristiche di Agri
- Grafi e algoritmi in linguaggio C
- Rappresentazione del grafo come array di vertici
- Rappresentazione del grafo come lista di archi
- Passaggio rapido tra le rappresentazioni
- Facile da usare
- In lingua latina, per tutte le nazionalità


- Multipiattaforma

## Installazione
Clonare il repository

`git clone https://github.com/francescosisini/LIBROGRAFI/agri.git`

Entrare nella directory  `agri` dalla directory di clone: `cd agri`

Lanciare `make`



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
### Types
`typedef enum  {SX,DEORSUM,DX,SURSUM,FIXUS} versus`
- <b>versus,us</b> decl. 4: direction
- <b>sx</b> stands for sinistra,ae decl. 1: left
- <b>deorsum</b> adverb: down
- <b>dx</b> stands for dextra,ae decl. 1: right
- <b>sursum</b> adverb: up
- <b>fuxus</b> adjective: still

`enum genus {MURUS,ALIUS}`
- <b>genus, generis</b> decl. 3: type
- <b>murus, i</b> decl. 2: wall
- <b>alius</b> adj: something else

##### typedef enum genus rei_genus
- <b>rei_genus</b>: type of object

##### typedef struct { int linea; int columna; int index; int ianua[PORTE]; } agri_Vertex;
- <b>vertex, vertices</b> decl. 3: vertex
- <b>linea,ae</b> decl. 1: row
- <b>columna, ae</b> decl. 1: column
- <b>index, indicis</b> decl. 3: index
- <b>ianua, ae</b> decl. 1: door

##### typedef struct colligatio { agri_Vertex ab, ad; versus discessus, meta; int longitudo; } agri_Colligatio;
- <b>colligatio, colligationis</b> decl. 3: edge
- <b></b>
- <b></b>
- <b></b>
- <b></b>
- <b></b>
- <b></b>
- <b></b>

- <b></b>
- <b></b>
- <b></b>
- <b></b>
- <b></b>
- <b></b>
- <b></b>
- <b></b>

