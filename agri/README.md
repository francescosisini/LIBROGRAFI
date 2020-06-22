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

`git clone https://github.com/francescosisini/LIBROGRAFI.git`

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
the word *ager* in Latin means 'field', with the meaning of field of flowers or field of wheat.
Ager belongs to the third declension, so, as you will have learned, *agri* means 'of the field'.

`typedef enum  {SX,DEORSUM,DX,SURSUM,FIXUS} versus`
- <b>versus</b> decl. 4: direction
- <b>sx</b> stands for sinistra decl. 1: left
- <b>deorsum</b> adverb: down
- <b>dx</b> stands for dextra decl. 1: right
- <b>sursum</b> adverb: up
- <b>fuxus</b> adjective: still

`enum genus {MURUS,ALIUS}`
- <b>genus</b> decl. 3: type
- <b>murus</b> decl. 2: wall
- <b>alius</b> adj: something else


`typedef enum genus rei_genus`
- <b>rei_genus</b>: type of object

### Graph as a list of edges

`typedef struct { int linea; int columna; int index; int ianua[PORTE]; } agri_Vertex;`
- <b>vertex</b> decl. 3: vertex
- <b>linea</b> decl. 1: row
- <b>columna</b> decl. 1: column
- <b>index</b> decl. 3: index
- <b>ianua</b> decl. 1: door

`typedef struct colligatio { agri_Vertex ab, ad; versus discessus, meta; int longitudo; } agri_Colligatio;`
- <b>colligatio</b> decl. 3: edge
- <b>discessus</b> decl. 4: starting point
- <b>meta</b> decl. 1: destination 
- <b>longitudo</b> decl.3: length

`typedef struct membrum { agri_Colligatio colligatio; struct  membrum *  next; } agri_Membrum;`
- <b>colligatio</b> decl. 3: edge
- <b>membrum</b> decl. 2: element 

`typedef agri_Membrum * agri_Colligationes_Colligatae;`
- <b>colligationes colligatae</b>: connected edges

`void agri_Colligationem_insero`
- <b>colligationem insero</b>: insert edge

`int agri_Verticem_quaero`
- <b>verticem quaero</b>: look for vertex

### Graph as a list of vertices

`typedef agri_Vertex * agri_Verticum_Dispositio;`
- <b>verticum dispositio</b>: array of vertices

`agri_Vertex agri_Verticem_creo(int index, int linea, int columna);`
- <b>verticem creo</b>: create a vertex

`typedef struct nodus_coda { int index; double prio; struct nodus_coda * post; } Nodus;`
- <b>nodus</b> decl.2: node (element of the queue)
- <b>index</b> decl. 3: index
- <b>prio</b> stands for priorsum adv: priority
- <b>coda</b> decl.1: queue

`typedef Nodus * Ordo;`
- <b>ordo</b> decl.3: list

`typedef int * agri_Via;`
- <b>via</b> decl.1: way
- <b></b>

`void Ordo_amoveo_nodus(Ordo * l, int index);`
- <b>amoveo nodus</b>: remove node
Remove a node from the list

`void Ordo_insero_nodus(Ordo * l,int index, double prio);`
- <b>insero nodus</b>: insert node
Insert a node into the list

`int Ordo_pop(Ordo * pOrdo);`
(English) pop of the element on the top of the list

`agri_Via agri_astar(int start, int goal, agri_Vertex * agri_Vertices_Colligati, double (*spatium)(int ab, int ad), double (*euristica)(int ab, int ad));`
(English) Astar algorithm

`int index_nodus_cella(int riga, int col, agri_Vertex * av);`
- <b>index nudus cella</b>: index node cell

### Graph as a list of cells
`typedef struct dato { int visitata; rei_genus rei; } Attributi;`
- <b>Attributi</b> perfect participle: attributes
- <b>visitata</b> adj: visited

`typedef struct cella { Attributi d; struct cella* dextra; struct cella* deorsum; struct cella* sinistra; struct cella* sursum; } agri_Cella;`
- <b>Cella</b> decl.1: cell

`typedef agri_Cella* agri_Tabella;`
- <b>tabella</b> decl.1: grid

`typedef struct nodo { agri_Cella * locus; struct nodo * next; struct nodo * prev; }agri_Passo;`
- <b>passo</b> from passus decl.2: step
- <b>locus</b> decl.2: place

`typedef agri_Passo* agri_Iter;  `
- <b>iter</b> decl.3: path

`void agri_creo_Tabellam(agri_Tabella* g);`
- <b>creo tabellam</b>: create grid

`agri_Tabella agri_addo_Tabellam(agri_Tabella tabella,Attributi d,versus dir);`
- <b>addo tabellam</b>: add grid
Add a cell into the grid

`void agri_colligo_Cellas(agri_Cella * da, agri_Cella * a, versus da_a);`
- <b>colligo cellas</b>: connect cells

`void agri_creo_Iter(agri_Iter* p_camm);`
- <b>creo iter</b>: create path

`void agri_addo_Iter(agri_Iter * p_camm, agri_Cella * p_cella);`
- <b>addo iter</b>: add path
Add a cell into the path

`agri_Cella* agri_rivela_Cella(agri_Iter ap,versus ricerca);`
- <b>rivela cella</b>: reveal cell

`int  agri_muto(agri_Colligationes_Colligatae ge, agri_Verticum_Dispositio *a);`
- <b>muto</b>: transform

`int agri_dispono(agri_Colligationes_Colligatae list ,agri_Colligationes_Colligatae * array);`
- <b>dispono</b>: arrange

`int Verticem_quaero(agri_Verticum_Dispositio v, int index, int amplitudo);`
- <b>verticem quaero</b>: look for a vertex

`versus agri_Versum_inverto(versus v);`
- <b>versum inverto</b>: reverse direction

`int compar(const void * a, const void * b);`
- <b>compar</b> stands for comparo verb: compare


