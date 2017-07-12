#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct e_node_tag
{
    int v;
    struct e_node_tag* next;
}e_node;
typedef struct v_node_tag
{
    int v;
    struct v_node_tag* down;
    e_node* next;
}v_node;
typedef struct c_node_tag
{
    int v;
    int count;
    struct c_node_tag* next;
}c_node;
typedef struct visited_node_tag
{
    int v;
    struct visited_node_tag* next;
}visited_node;

bool IfVertExist(v_node** root, int v);
void SubtractOne(c_node**croot,v_node*vroot, int v);

void InitCNode(c_node** croot,v_node* vroot)
{
    c_node* cptr=*croot;
    v_node* vptr=vroot;
    if(vptr!=NULL)
    {
        for(vptr=vroot;vptr!=NULL;vptr=vptr->down)
        {
            c_node* cnptr=(c_node*)malloc(sizeof(c_node));
            cnptr->v=vptr->v;
            cnptr->next=NULL;
            int count=0;
            v_node* vptr1;
            e_node* eptr1;
            for(vptr1=vroot;vptr1!=NULL;vptr1=vptr1->down)
            {
                for(eptr1=vptr1->next;eptr1!=NULL;eptr1=eptr1->next)
                {
                    if(eptr1->v==vptr->v)
                    {
                        count++;
                    }
                }
            }
            cnptr->count=count;
            if(cptr==NULL)
            {
                cptr=cnptr;
                *croot=cnptr;
            }
            else
            {
                cptr->next=cnptr;
                cptr=cnptr;
            }
        }
    }
}

bool IsZeroExist(c_node* root)
{
    bool ret_val=0;
    c_node* ptr=root;
    while(ptr!=NULL&&ret_val!=1)
    {
        if(ptr->count==0)
        {
            ret_val=1;
        }
        else
        {
            ptr=ptr->next;
        }
    }
    return ret_val;
}

void SubtractOne(c_node**croot,v_node*vroot, int v)
{
    c_node* cptr=*croot;
    v_node* vptr=vroot;
    e_node* eptr;
    if(IfVertExist(&vptr,v))
    {
        for(eptr=vptr->next;eptr!=NULL;eptr=eptr->next)
        {
            cptr=*croot;
            while(cptr->v!=eptr->v)
            {
                cptr=cptr->next;
            }
            cptr->count=cptr->count-1;
        }
    }
}

void PushInVisited(visited_node** root, int v)
{
    visited_node*ptr=*root;
    visited_node* nptr=(visited_node*)malloc(sizeof(visited_node));
    nptr->v=v;
    nptr->next=NULL;
    if(ptr==NULL)
    {
        *root=nptr;
    }
    else
    {
        nptr->next=ptr->next;
        ptr->next=nptr;
    }
}

bool IsVisited(visited_node* root, int v)
{
    bool ret_val=0;
    visited_node* ptr=root;
    if(ptr!=NULL)
    {
        while(ret_val==0&&ptr!=NULL)
        {
            if(ptr->v==v)
            {
                ret_val=1;
            }
            else
            {
                ptr=ptr->next;
            }
        }
    }
    return ret_val;
}

bool IfVertExist(v_node** root, int v)
{
    bool ret_val=0;
    v_node* ptr=*root;
    if(ptr!=NULL)
    {
        while(ptr!=NULL&&ret_val==0)
        {
            if(ptr->v==v)
            {
                ret_val=1;
            }
            else
            {
                ptr=ptr->down;
            }
        }
        *root=ptr;
    }
    return ret_val;
}

v_node* InsertAdjList(v_node* root, int v1, int v2)
{
    v_node* ptr=root;
    if(ptr==NULL)
    {
        v_node* vnptr=(v_node*)malloc(sizeof(v_node));
        vnptr->v=v1;
        e_node* enptr=(e_node*)malloc(sizeof(e_node));
        enptr->v=v2;
        enptr->next=NULL;
        vnptr->next=enptr;
        v_node* vnptr2=(v_node*)malloc(sizeof(v_node));
        vnptr2->v=v2;
        vnptr2->down=NULL;
        vnptr2->next=NULL;
        vnptr->down=vnptr2;
        root=vnptr;
    }
    else
    {
        v_node* lptr=root;
        if(IfVertExist(&lptr,v1))
        {
            e_node* enptr=(e_node*)malloc(sizeof(e_node));
            enptr->v=v2;
            enptr->next=lptr->next;
            lptr->next=enptr;
            lptr=root;
            if(!(IfVertExist(&lptr,v2)))
            {
                v_node* vnptr=(v_node*)malloc(sizeof(v_node));
                vnptr->v=v2;
                vnptr->next=NULL;
                vnptr->down=ptr->down;
                ptr->down=vnptr;
            }
        }
        else
        {
            v_node* vnptr=(v_node*)malloc(sizeof(v_node));
            vnptr->v=v1;
            vnptr->down=ptr->down;
            ptr->down=vnptr;
            e_node* enptr=(e_node*)malloc(sizeof(e_node));
            enptr->v=v2;
            enptr->next=NULL;
            vnptr->next=enptr;
            lptr=root;
            if(!(IfVertExist(&lptr,v2)))
            {
                v_node* vnptr2=(v_node*)malloc(sizeof(v_node));
                vnptr2->v=v2;
                vnptr2->next=NULL;
                vnptr2->down=ptr->down;
                ptr->down=vnptr2;
            }
        }
    }
    return root;
}

/*
void PrintVNode(visited_node*root)
{
    visited_node*ptr=root;
    while(ptr!=NULL)
    {
        printf("%d, ",ptr->v);
        ptr=ptr->next;
    }
}
*/

void ToppoSearch(v_node* root, c_node**croot, visited_node**vroot)
{
    visited_node*jstnwvisit=NULL;
    while(IsZeroExist(*croot))
    {
        c_node* cptr=*croot;
        c_node* cprev=*croot;
        while(cptr->count!=0)
        {
            cprev=cptr;
            cptr=cptr->next;
        }
        int v=cptr->v;
        if(!IsVisited(*vroot,v))
        {
            printf("%d, ",v);
            PushInVisited(vroot,v);
            PushInVisited(&jstnwvisit,v);
            if(cptr==*croot)
            {
                *croot=cptr->next;
                free(cptr);
            }
            else
            {
                cprev->next=cptr->next;
                free(cptr);
            }
        }
        else
        {
            if(cptr==*croot)
            {
                *croot=cptr->next;
                free(cptr);
            }
            else
            {
                cprev->next=cptr->next;
                free(cptr);
            }
        }
    }
    visited_node* vptr;
    for(vptr=jstnwvisit;vptr!=NULL;vptr=vptr->next)
    {
        SubtractOne(croot,root,vptr->v);
    }
    if(IsZeroExist(*croot))
    {
        ToppoSearch(root,croot,vroot);
    }
}


v_node* InitAdjList(v_node* root)
{
    v_node* ptr=root;
    int v1, v2;
    FILE* fptr=fopen("data.txt","r");
    fseek(fptr,0,SEEK_END);
    unsigned int len=ftell(fptr);
    if(len>0)
    {
        rewind(fptr);
        while(!feof(fptr))
        {
            fscanf(fptr,"%d",&v1);
            fscanf(fptr,"%d",&v2);
            ptr=InsertAdjList(ptr,v1,v2);
        }
    }
    fclose(fptr);
    return ptr;
}

void ToppologicalTraversal(v_node* root)
{

    c_node*croot=NULL;
    InitCNode(&croot,root);
    visited_node* vroot=NULL;
    ToppoSearch(root,&croot,&vroot);
}

/*
void PrintCNode(c_node*root)
{
    c_node*ptr=root;
    while(ptr!=NULL)
    {
        printf("%d:%d, ",ptr->v,ptr->count);
        ptr=ptr->next;
    }
}
*/

void main()
{
    v_node* root=NULL;
    root=InitAdjList(root);
    ToppologicalTraversal(root);
}
