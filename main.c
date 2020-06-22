#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <sys/time.h>

typedef struct List_body *list_body;
typedef struct List_head *list_head;
typedef struct Label label;
typedef struct Node *node;
typedef struct Structure structure;
typedef struct Amplitude amplitude;
typedef struct node_str *node_str;
typedef struct node_amp *node_amp;
typedef struct QDD QDD;

typedef unsigned long long Long;
typedef double number;

struct List_body
{
    node n;
    list_body lb;
};

struct List_head
{
    struct List_body lb;
    list_head lh;
};

struct Label
{
    int cl, le;
};

struct Node
{
    struct List_head lh;
    label lab;
};

struct Structure
{
    node el, th;
};

struct Amplitude
{
    number re, im;
};

struct node_str
{
    struct Node n;
    structure str;
};

struct node_amp
{
    struct Node n;
    amplitude amp;
};

struct QDD
{
    node n;
    list_body lb;
    char N;
};

typedef unsigned long long Long;

void exit_error(char *s)
{
    printf("\nERROR : %s",s);
    exit(EXIT_FAILURE);
}

#define NODE(POINTER) ((node)POINTER)
#define AMP(POINTER) ((amplitude*)(NODE(POINTER)+1))
#define STR(POINTER) ((structure*)(NODE(POINTER)+1))
#define BODY(POINTER) ((list_body)POINTER)
#define HEAD(POINTER) ((list_head)POINTER)
#define LAB(POINTER) ((label*)(HEAD(POINTER)+1))
#define NNODE(POINTER) (BODY(POINTER)->n)
#define NBODY(POINTER) (BODY(POINTER)->lb)
#define NHEAD(POINTER) (HEAD(POINTER)->lh)
#define NLABEL(POINTER) (LAB(NNODE(POINTER)))

#define IS_AMP(POINTER) (LAB(POINTER)->le == 0)

#define COMPARE_LABEL(LABEL_1, OPERANDO, LABEL_2) (*((long*)LABEL_1) OPERANDO *((long*)LABEL_2))
#define SUBTRACT_POINTER(POINTER_1, POINTER_2) (((void*)POINTER_1) - ((void*)POINTER_2))
#define COPY(POINTER_1, POINTER_2)  memcpy(POINTER_1,POINTER_2,sizeof(*(POINTER_1)))
#define RESET(POINTER) memset(POINTER,0,sizeof(POINTER))

#define R 2
#define V 1
#define C 0

#define ELSE 0
#define THEN 1

#define PRINT(ARGS...) printf(ARGS)

#define DEFAULT "\033[0m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CIANO "\033[0;36m"
#define COLOR(CODE) PRINT(CODE)

#define OPEN do{
#define CLOSE }while(0)
#define LOOP_C(NAME,LIM) for(char NAME = 0; NAME < LIM; NAME++)
#define LOOP_P(NAME) for(;NAME != NULL; NAME = NAME->next)
#define SIDE(NODE1,NODE0) (VEST(N0DE0)[0] != N0DE1)

#define NEWLINE PRINT("\n")

void exit_program(char *s)
{
    NEWLINE;NEWLINE;NEWLINE;NEWLINE;NEWLINE;NEWLINE;
    PRINT("\nERROR");
    if(s != NULL)
        PRINT("\t%s",s);
    exit(EXIT_FAILURE);
}

FILE* open(char *file, char *mode)
{
    FILE *fp;
    fp = fopen(file,mode);
    if(fp == NULL)
        exit_program("UNABLE TO OPEN FILE");

    setbuf(fp,NULL);
    return fp;
}

void init()
{
    setbuf(stdout,NULL);
}

#define DEBUG_S 1
#define HOLD_S 0

#define COND_DEBUG(CODE) if(DEBUG_S == 2 || ((DEBUG_S == 1) && (CODE)))
#define DEBUG(CODE,ARGS...) COND_DEBUG(CODE) PRINT(ARGS)
#define HOLD if(HOLD_S) getchar()

typedef double numero;

#define REPORT_MODE 1
#define FREE(FUNCTION, POINTER) OPEN if(!REPORT_MODE) free(POINTER); else FUNCTION(POINTER); CLOSE

#define CREATE(TYPE,NAME,VAR)       \
    TYPE NAME;                      \
    NAME = calloc(1,sizeof(*NAME));  \
    if(NAME == NULL)    exit_error("#TYPE ALLOCATION"); \
    if(REPORT_MODE)     VAR++

Long iNs;

node node_str_create(int cl, int le)
{
    CREATE(node_str,n,iNs);
    LAB(n)->cl = cl;
    LAB(n)->le = le;
    return NODE(n);
}

node node_str_create_cpy(label lab)
{
    CREATE(node_amp,n,iNs);
    COMPARE_LABEL(LAB(n),=,&lab);
    return NODE(n);
}

Long iNa;

node node_amp_create(numero re, numero im)
{
    CREATE(node_amp,n,iNa);
    AMP(n)->re = re;
    AMP(n)->im = im;
    return NODE(n);
}

node node_amp_copy(amplitude amp)
{
    CREATE(node_amp,n,iNa);
    COPY(AMP(n), &amp);
    return NODE(n);
}

Long iLb;

list_body list_body_create(node n, list_body lb_next)
{
    CREATE(list_body,lb,iLb);
    lb->n  = n;
    lb->lb = lb_next;
    return lb;
}

list_body list_body_create_empty()
{
    CREATE(list_body,lb,iLb);
    return lb;
}

list_body list_body_copy(list_body lb_0)
{
    CREATE(list_body,lb,iLb);
    COPY(lb, lb_0);
    return lb;
}

Long iLh;

list_head list_head_create(node n, list_head lh_next)
{
    CREATE(list_head,lh,iLh);
    NNODE(lh) = n;
    NHEAD(lh) = lh_next;
    return lh;
}

list_head list_head_create_empty()
{
    CREATE(list_head,lh,iLh);
    return lh;
}

list_head list_head_copy(list_head lh_0)
{

    CREATE(list_head,lh,iLh);
    COPY(lh,lh_0);
    return lh;
}

list_head list_head_copy_body(list_body lb, list_head lh_next)
{
    CREATE(list_head,lh,iLh);
    COPY(BODY(lh), lb);
    lh->lh = lh_next;
    return lh;
}

#define DESTROY(TYPE,NAME,VAR) \
    if(!REPORT_MODE)  exit_program("MODE FAULT"); \
    if(VAR == 0) exit_program("FREE #TYPE"); \
    VAR--;\
    free(NAME)

void list_body_free_item(list_body lb)
{
    DESTROY(LIST_BODY,lb,iLb);
}

void list_head_free_item(list_head lh)
{
    DESTROY(LIST_HEAD,lh,iLh);
}



void list_body_free(list_body lb)
{
    list_body lb_aux;
    while(lb != NULL)
    {
        lb_aux = lb->lb;
        FREE(list_body_free_item,lb);
        lb = lb_aux;
    }
}

void list_head_free(list_head lh)
{
    while(lh != NULL)
    {
        list_head lh_aux;
        lh_aux = lh;
        lh     = lh->lh;

        list_body_free(NBODY(lh_aux));
        FREE(list_head_free_item,lh_aux);
    }
}


void node_disconect(node n1, node n2);

#define NODE_DISCONECT(NODE) OPEN node_disconect(NODE,STR(NODE)->el); node_disconect(NODE,STR(NODE)->th); CLOSE

void node_str_free(node n)
{
    DESTROY(NO_STR,n,iNs);
}

void node_amp_free(node n)
{
    DESTROY(NO_AMP,n,iNa);
}

void node_free(node n)
{
    if(IS_AMP(n))   node_amp_free(n);
    else            node_str_free(n);
}

void node_free_tree(node n) {}



void amounts_display()
{
    PRINT("\n\nQUANTIDADES");
    PRINT("\nI.LB : %llu",iLb);
    PRINT("\nI.LH : %llu",iLh);
    PRINT("\nI.NE : %llu",iNs);
    PRINT("\nI.NA : %llu",iNa);
    PRINT("\n");
}

void pointer_display(void *pointer)
{
    if (pointer == NULL)  PRINT("NULL");
    else                  PRINT("%11p", pointer);
}

int header_display(char *s, void *p)
{
    PRINT("\nAddress (%s): ",s);
    pointer_display(p);
    return p == NULL;
}

void label_display(label *lab, int completa)
{
    if(lab->le == 0)
    {
        PRINT("AMPLITUDE");
        return;
    }

    switch(lab->cl)
    {
        case C:
            PRINT("C");
            break;

        case V:
            PRINT("V");
            break;

        case R:
            PRINT("R");
            break;

        default:
            PRINT(" MERDA %d ",lab->cl);
            exit_error("SHIT");
    }
    PRINT("%d",lab->le);
    if(completa)
        PRINT("\t\t");
}



#define FOR_CONTA for(i=0; lb != NULL; i++, lb = lb->lb)

void list_body_display_item(list_body lb)
{
    if(header_display("LISTA BODY",lb))
        return;

    PRINT("\nNode: ");pointer_display(lb->n);
    PRINT("\nlb  : ");pointer_display(lb->lb);
    PRINT("\n");
}

void list_body_display_pointers(list_body lb)
{
    int i;
    FOR_CONTA
    {
        PRINT("\n\tLista %3d : ",i);pointer_display(lb);
    }
}

void list_body_display_node(list_body lb)
{
    int i;
    FOR_CONTA
    {
        PRINT("\n\tNode %3d: ",i);pointer_display(lb->n);
    }
}


number eps;
#define IF_ZERO(NOME) if(NOME < eps)if(NOME > -eps)

void structure_display(structure *est)
{
    pointer_display(est->el);PRINT("\t\t");
    pointer_display(est->th);
}

void amplitude_diplay(amplitude *amp)
{
    PRINT("% .4e",amp->re);
    IF_ZERO(amp->im)
            return;
    PRINT(" % .4e",amp->im);
}

void data_display(node n)
{
    if(IS_AMP(n)) amplitude_diplay(AMP(n));
    else structure_display(STR(n));
}

#define SIMPLE   0
#define COMPACT  1
#define FULL     2
#define EXTENDED 3

void node_display(node n, int CODE);

Long list_body_count(list_body lb)
{
    Long i;
    FOR_CONTA;
    return i;
}

void list_body_display_amp(list_body lb)
{
    int i;
    FOR_CONTA
    {
        PRINT("\n\tNo %2d: ",i);
        if(lb->n == NULL)   PRINT(" NULL");
        else                amplitude_diplay(AMP(lb->n));
    }
}

void list_body_display(list_body lb, int CODE)
{
    if(lb == NULL)
    {
        PRINT("\nNULL List");
        return;
    }

    switch(CODE)
    {
        case SIMPLE:
            PRINT("\nLabel: ");
            label_display(NLABEL(lb), 1);
            PRINT("\ttot: %4llu", list_body_count(lb));
            break;

        case COMPACT:
        case FULL:
            PRINT("\nLABEL: ");
            label_display(NLABEL(lb), 1);
            int i;
            FOR_CONTA
            {
                PRINT("\n\tNo %3d: ",i);
                pointer_display(lb->n);
                if(CODE == FULL)
                {
                    PRINT("\t\t\t\t");
                    data_display(lb->n);
                }
            }
            break;

        case EXTENDED:
            for(; lb->lb != NULL; lb = lb->lb)
            {
                node_display(lb->n, EXTENDED);
                PRINT("\n------------------------------------------");
            }
            node_display(lb->n, EXTENDED);
            break;

        default:
            exit_error("SHIT");
    }
}



void list_head_display_item(list_head lh)
{
    if(header_display("LISTA HEAD", lh))
        return;

    PRINT("\nNode: ");pointer_display(BODY(lh)->n);
    PRINT("\nlb  : ");pointer_display(NBODY(lh));
    PRINT("\nlh  : ");pointer_display(lh->lh);
}

void list_head_display_all(list_head lh)
{
    for(; lh != NULL; lh = lh->lh)
    {
        PRINT("\n");
        list_head_display_item(lh);
    }
}

void list_head_display(list_head lh, int CODE)
{
    for(; lh->lh != NULL; lh = lh->lh)
    {
        list_body_display(BODY(lh), CODE);
        PRINT("\n---------------------");
        for(int i=1; i<CODE; i++) PRINT("---------------------");
    }
    list_body_display(BODY(lh), CODE);
}



void display_antrecessors(node n)
{
    if(NNODE(n) == NULL)
    {
        PRINT("\nNo antecessors");
    }
    else
    {
        PRINT("\nAntecessors: ");
        PRINT("\n---------------------");
        list_head_display(HEAD(n), COMPACT);
        PRINT("\n---------------------");
    }
}

void node_str_display(node n, int CODE)
{
    if(header_display("NODE_STR",n))
        return;

    if(CODE == EXTENDED) display_antrecessors(n);

    PRINT("\nLabel: ");
    label_display(LAB(n),0);
    PRINT("\nSucessors: ");structure_display(STR(n));
    PRINT("\n");
}

void node_amp_display(node n, int CODE)
{
    if(header_display("NODE_AMP", n))
        return;

    if(CODE == EXTENDED)display_antrecessors(n);

    PRINT("\nAmplitude: ");amplitude_diplay(AMP(n));
    PRINT("\n");
}

void node_base_display(node n)
{
    if(header_display("NODE", n))
        return;

    PRINT("\nLabel: ");
    label_display(LAB(n), 0);
}

void node_display(node n, int CODE)
{

    if(n != NULL)
    {
        if(AMP(n))  node_amp_display(n,CODE);
        else        node_str_display(n, CODE);
        return;
    }

    header_display("NO", n);
}



list_head enlista_arvore(node n) {}

void node_display_tree(node n, int CODE)
{
    list_head lh;
    lh = enlista_arvore(n);
    list_head_display(lh, CODE);
    list_head_free(lh);
}

void QDD_display(QDD Q, int CODE)
{
    PRINT("\nQDD");
    PRINT("\nN: %d",Q.N);
    PRINT("\n");
    node_display_tree(Q.n, CODE);
    PRINT("\n");
    if(CODE == SIMPLE)
    {
        PRINT("\nAMPLITUDES");
        list_body_display_amp(Q.lb);
    }
    PRINT("\n");
}



void consistency_test(list_head lh);

void list_include(list_head lh, node n) {}

void list_exclude(list_head lh, node n, list_body *lb_clue) {}



void node_connect(node n1, node n2, char lado) {}

void node_disconect(node n1, node n2) {}

void node_disconnect_clue(node n1, node n2, list_head lh_clue, list_body lb_clue){}

#define CONNECT(NODE1, NODE2, SIDE) OPEN VEST(NODE1)[SIDE] = NODE2; PRIMEIRO(NODE2) = NODE1; CLOSE

#define CONNECT_2(N0,EL,TH) ABRE conecta_UM(N0,EL,ELSE); conecta_UM(N0,TH,THEN); FECHA

void list_merge(list_head lh1, list_head lh2) {}



void QDD_free(QDD Q) {}



int amp_compare(amplitude *amp_1, amplitude *amp_2) {}

int amp_compare_zero(amplitude *amp) {}

void amp_product_real(amplitude *amp, numero re) {}

void amp_product(amplitude *amp1, amplitude *amp2) {}

void QDD_product_real(QDD Q, numero re) {}

void QDD_product_amp(QDD Q, amplitude *amp) {}



amplitude amp_subtraction(amplitude *amp1, amplitude *amp2) {}

list_body  list_search_amp(list_body lb, amplitude *amp, int *res, list_body lb_clue, int *aux) {}

list_body  list_search_str(list_body lb, node n2, int side, int *res, list_body lb_clue) {}


list_body  list_amp_redux(list_body lb_0) {}

list_body  list_str_redux(list_head lh, node n0) {}

QDD QDD_redux(QDD Q) {}



node copia_arvore(node n) {}

QDD copia_QDD(QDD Q0) {}

QDD QDD_tensor(QDD Q1, QDD Q2, int testing) {}



int main(){}