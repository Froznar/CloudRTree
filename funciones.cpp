#include "funciones.h"


Rectangle::Rectangle(punto a, punto b)
{
    if(a==b){m_A=m_B=a;}
    if(a.first<=b.first and a.second>b.second){
        m_A=a;
        m_B=b;
    }
    if(a.first<=b.first and a.second<b.second){
        m_A=make_pair(a.first,b.second);
        m_B=make_pair(b.first,a.second);
    }
    if(a.first>=b.first and a.second<b.second){
        m_A=b;
        m_B=a;
    }
    if(a.first>=b.first and a.second>b.second){
        m_A=make_pair(b.first,a.second);
        m_B=make_pair(a.first,b.second);
    }

}

void Rectangle::Drow(ALLEGRO_COLOR color=al_map_rgb(81,69,147))
{
    if(m_A.first==m_B.first and m_A.second==m_B.second){
        al_draw_filled_circle(m_A.first,m_A.second,3,al_map_rgb(107,184,72));
    }
    else{
        al_draw_rectangle(m_A.first,m_A.second,m_B.first,m_B.second,color,2);
    }

}

bool overlapRectangle(Rectangle* a, Rectangle* b)
{
    if(isInside(a,b->m_A)) return true;
    if(isInside(a,b->m_B)) return true;
    return false;
}

Nodo::Nodo()
{
    m_cant = 0;
    m_level = 1;
    m_leaf = true;
    m_padre = NULL;
}

void Nodo::Child_to_leaf()
{
    for(int i=0;i<m_childs.size();i++){m_childs[i]->m_leaf=true;}
}

RTree::RTree(int M)
{
    m_head=NULL;
    m_M=M;
    m_m=M/2;
}

Nodo* RTree::Split(Nodo *N)
{
    //Pick seeds
    int R1,R2;
    Nodo *Last = new Nodo();
    Nodo* RR1 = new Nodo();
    Nodo *RR2 = new Nodo();


    rasmus mayd=-1;
    for(int i=0;i<N->m_rectangles.size();i++)
    {
        for(int j=i+1;j<N->m_rectangles.size();j++)
        {
            rasmus d=area(Fuse(N->m_rectangles[i],N->m_rectangles[j]))-area(N->m_rectangles[i])-area(N->m_rectangles[j]);
            if(d>=mayd)
            {
                R1=i;
                R2=j;
                mayd=d;
            }
        }
    }

    vector<Rectangle*> restantes;
    for(int i=0;i<N->m_rectangles.size();i++)
    {
        if(i!=R1 and i!=R2)
        {
            restantes.push_back(N->m_rectangles[i]);
        }
    }
    //Pick next
    list<Rectangle*> next_recta;

    while(!restantes.empty())
    {
        vector<rasmus> diff;
        rasmus dif;
        dif=0;
        for(int i=0;i<restantes.size();i++)
        {
            rasmus d1=area(Fuse(restantes[i],N->m_rectangles[R1]))-area(restantes[i])-area(N->m_rectangles[R1]);
            rasmus d2=area(Fuse(restantes[i],N->m_rectangles[R2]))-area(restantes[i])-area(N->m_rectangles[R2]);
            dif=abs(d1-d2);
            diff.push_back(dif);
        }
        int ind=eval(diff,1);
        next_recta.push_back(restantes[ind]);
        swap(restantes[ind],restantes[restantes.size()-1]);
        restantes.pop_back();
    }
    //---todo-listo---

    RR1->m_padre=Last;
    RR2->m_padre=Last;
    Last->m_leaf=false;
    RR1->m_leaf=true;
    RR2->m_leaf=true;
    RR1->m_rectangles.push_back(N->m_rectangles[R1]);
    RR2->m_rectangles.push_back(N->m_rectangles[R2]);
    Last->m_childs.push_back(RR1);
    Last->m_childs.push_back(RR2);
    Last->m_rectangles.push_back(N->m_rectangles[R1]);
    Last->m_rectangles.push_back(N->m_rectangles[R2]);
    Last->m_cant=2;
    Last->m_childs[0]->m_cant=1;
    Last->m_childs[1]->m_cant=1;
    while (!next_recta.empty())
    {
        if(Last->m_childs[0]->m_cant+next_recta.size() == this->m_m)
        {
            Last->m_childs[0]->m_rectangles.push_back(next_recta.front());
            Last->m_rectangles[0]=Fuse(Last->m_rectangles[0],next_recta.front());
            Last->m_childs[0]->m_cant++;
            next_recta.pop_front();
            continue;
        }
        if(Last->m_childs[1]->m_cant+next_recta.size() == this->m_m)
        {
            Last->m_childs[1]->m_rectangles.push_back(next_recta.front());
            Last->m_rectangles[1]=Fuse(Last->m_rectangles[1],next_recta.front());
            Last->m_childs[1]->m_cant++;
            next_recta.pop_front();
            continue;
        }
        if(area(Fuse(next_recta.front(),Last->m_rectangles[0])) > area(Fuse(next_recta.front(),Last->m_rectangles[1])))
        {
            Last->m_childs[1]->m_rectangles.push_back(next_recta.front());
            Last->m_rectangles[1]=Fuse(Last->m_rectangles[1],next_recta.front());
            next_recta.pop_front();
            Last->m_childs[1]->m_cant++;
            continue;
        }
        if(area(Fuse(next_recta.front(),Last->m_rectangles[0])) <= area(Fuse(next_recta.front(),Last->m_rectangles[1])))
        {
            Last->m_childs[0]->m_rectangles.push_back(next_recta.front());
            Last->m_rectangles[0]=Fuse(Last->m_rectangles[0],next_recta.front());
            next_recta.pop_front();
            Last->m_childs[0]->m_cant++;
            continue;
        }
    }
    return Last;
}

Nodo* RTree::Split_no_leaf(Nodo *N)
{
    //Pick seeds
    int R1,R2;

    rasmus mayd=-1;
    for(int i=0;i<N->m_rectangles.size();i++)
    {
        for(int j=i+1;j<N->m_rectangles.size();j++)
        {
            rasmus d=area(Fuse(N->m_rectangles[i],N->m_rectangles[j]))-area(N->m_rectangles[i])-area(N->m_rectangles[j]);
            if(d>=mayd)
            {
                R1=i;
                R2=j;
                mayd=d;
            }
        }
    }

    vector<Rectangle*> restantes;
    vector<Nodo*> nodos_restntes;
    for(int i=0;i<N->m_rectangles.size();i++)
    {
        if(i!=R1 and i!=R2)
        {
            restantes.push_back(N->m_rectangles[i]);
            nodos_restntes.push_back(N->m_childs[i]);
        }
    }
    //Pick next
    list<Rectangle*> next_recta;
    list<Nodo*> next_child;
    while(!restantes.empty())
    {
        vector<rasmus> diff;
        rasmus dif;
        dif=0;
        for(int i=0;i<restantes.size();i++)
        {
            rasmus d1=area(Fuse(restantes[i],N->m_rectangles[R1]))-area(restantes[i])-area(N->m_rectangles[R1]);
            rasmus d2=area(Fuse(restantes[i],N->m_rectangles[R2]))-area(restantes[i])-area(N->m_rectangles[R2]);
            dif=abs(d1-d2);
            diff.push_back(dif);
        }
        int ind=eval(diff,1);
        next_recta.push_back(restantes[ind]);
        next_child.push_back(nodos_restntes[ind]);
        swap(restantes[ind],restantes[restantes.size()-1]);
        swap(nodos_restntes[ind],nodos_restntes[restantes.size()-1]);
        restantes.pop_back();
        nodos_restntes.pop_back();
    }
    //---todo-listo---
    Nodo *Last = new Nodo();
    Nodo* RR1 = new Nodo();
    Nodo *RR2 = new Nodo();
    RR1->m_padre=Last;
    RR2->m_padre=Last;
    Last->m_leaf=false;
    RR1->m_leaf=false;
    RR2->m_leaf=false;
    RR1->m_rectangles.push_back(N->m_rectangles[R1]);
    RR2->m_rectangles.push_back(N->m_rectangles[R2]);
    RR1->m_childs.push_back(N->m_childs[R1]);
    RR2->m_childs.push_back(N->m_childs[R2]);
    RR1->m_childs[0]->m_padre=RR1;
    RR2->m_childs[0]->m_padre=RR2;
    for(int c=0;c<RR1->m_childs[0]->m_childs.size();c++)
    {
        RR1->m_childs[0]->m_childs[c]->m_padre=RR1;
    }
    for(int c=0;c<RR2->m_childs[0]->m_childs.size();c++)
    {
        RR2->m_childs[0]->m_childs[c]->m_padre=RR2;
    }
    Last->m_childs.push_back(RR1);
    Last->m_childs.push_back(RR2);
    Last->m_rectangles.push_back(N->m_rectangles[R1]);
    Last->m_rectangles.push_back(N->m_rectangles[R2]);
    Last->m_cant=2;
    Last->m_childs[0]->m_cant=1;
    Last->m_childs[1]->m_cant=1;
    while (!next_recta.empty())
    {
        if(Last->m_childs[0]->m_cant+next_recta.size() == this->m_m)
        {
            Last->m_childs[0]->m_rectangles.push_back(next_recta.front());
            Last->m_childs[0]->m_childs.push_back(next_child.front());
            Last->m_childs[0]->m_childs[Last->m_childs[0]->m_childs.size()-1]->m_padre=Last->m_childs[0];
            for(int c=0;c<RR1->m_childs[0]->m_childs.size();c++)
            {
                RR1->m_childs[0]->m_childs[c]->m_padre=RR1;
            }
            Last->m_rectangles[0]=Fuse(Last->m_rectangles[0],next_recta.front());
            next_recta.pop_front();
            next_child.pop_front();
            Last->m_childs[0]->m_cant++;
            continue;
        }
        if(Last->m_childs[1]->m_cant+next_recta.size() == this->m_m)
        {
            Last->m_childs[1]->m_rectangles.push_back(next_recta.front());
            Last->m_childs[1]->m_childs.push_back(next_child.front());
            Last->m_childs[1]->m_childs[Last->m_childs[1]->m_childs.size()-1]->m_padre=Last->m_childs[1];
            for(int c=0;c<RR2->m_childs[0]->m_childs.size();c++)
            {
                RR2->m_childs[0]->m_childs[c]->m_padre=RR2;
            }
            Last->m_rectangles[1]=Fuse(Last->m_rectangles[1],next_recta.front());
            next_recta.pop_front();
            next_child.pop_front();
            Last->m_childs[1]->m_cant++;
            continue;
        }
        if(area(Fuse(next_recta.front(),Last->m_rectangles[0])) > area(Fuse(next_recta.front(),Last->m_rectangles[1])))
        {
            Last->m_childs[1]->m_rectangles.push_back(next_recta.front());
            Last->m_childs[1]->m_childs.push_back(next_child.front());
            Last->m_childs[1]->m_childs[Last->m_childs[1]->m_childs.size()-1]->m_padre=Last->m_childs[1];
            for(int c=0;c<RR2->m_childs[0]->m_childs.size();c++)
            {
                RR2->m_childs[0]->m_childs[c]->m_padre=RR2;
            }
            Last->m_rectangles[1]=Fuse(Last->m_rectangles[1],next_recta.front());
            next_recta.pop_front();
            next_child.pop_front();
            Last->m_childs[1]->m_cant++;
            continue;
        }
        if(area(Fuse(next_recta.front(),Last->m_rectangles[0])) <= area(Fuse(next_recta.front(),Last->m_rectangles[1])))
        {
            Last->m_childs[0]->m_rectangles.push_back(next_recta.front());
            Last->m_childs[0]->m_childs.push_back(next_child.front());
            Last->m_childs[0]->m_childs[Last->m_childs[0]->m_childs.size()-1]->m_padre=Last->m_childs[0];
            for(int c=0;c<RR1->m_childs[0]->m_childs.size();c++)
            {
                RR1->m_childs[0]->m_childs[c]->m_padre=RR1;
            }
            Last->m_rectangles[0]=Fuse(Last->m_rectangles[0],next_recta.front());
            next_recta.pop_front();
            next_child.pop_front();
            Last->m_childs[0]->m_cant++;
            continue;
        }
    }
    return Last;
}

void RTree::Inssert(Rectangle *R)
{

    if(m_head == NULL)
    {
        m_head=new Nodo();
        m_head->m_rectangles.push_back(R);
        m_head->m_cant++;
    }
    else if(m_head->m_leaf)
    {
        if(m_head->m_cant < m_M)
        {
            m_head->m_rectangles.push_back(R);
            m_head->m_cant++;
        }
        else if(m_head->m_cant == m_M)
        {
            m_head->m_rectangles.push_back(R);
            Nodo * X=Split(m_head);
            m_head=X;
            m_head->m_leaf=false;
        }
    }
    else
    {
        Nodo *S=m_head;
        int ind=0;
        while (S->m_leaf==false)
        {
            ind=0;
            rasmus men=area(Fuse(R,S->m_rectangles[0]));
            for(int i=1;i<S->m_rectangles.size();i++)
            {
                rasmus d=area(Fuse(R,S->m_rectangles[i]));
                if(d<=men)
                {
                    ind=i;
                    men=d;
                }
            }
            S=S->m_childs[ind];
        }
        if(S->m_cant < m_M)
        {
            S->m_rectangles.push_back(R);
            RefusePadres(S);
            S->m_cant++;
        }
        else if(S->m_cant == m_M)
        {
            S->m_rectangles.push_back(R);
            Nodo * X=Split(S);
            swap(S->m_padre->m_rectangles[ind],S->m_padre->m_rectangles[S->m_padre->m_rectangles.size()-1]);
            swap(S->m_padre->m_childs[ind],S->m_padre->m_childs[S->m_padre->m_childs.size()-1]);
            S->m_padre->m_rectangles.pop_back();
            S->m_padre->m_childs.pop_back();
            S->m_padre->m_rectangles.push_back(X->m_rectangles[0]);
            S->m_padre->m_rectangles.push_back(X->m_rectangles[1]);
            X->m_childs[0]->m_padre = X->m_childs[1]->m_padre = S->m_padre;
            S->m_padre->m_childs.push_back(X->m_childs[0]);
            S->m_padre->m_childs.push_back(X->m_childs[1]);
            S->m_padre->m_cant++;

        }
        Nodo *F;
        F=S->m_padre;
        while(F->m_cant > m_M)
        {
            Nodo* X= Split_no_leaf(F);
            if(F->m_padre==NULL)
            {
                X->m_padre=NULL;
                X->m_childs[0]->m_padre = X->m_childs[1]->m_padre = X;
                m_head=X;
                F=X;
            }
            else
            {
                int ind;
                for(int i=0;i<F->m_padre->m_childs.size();i++)
                {
                    if(F==F->m_padre->m_childs[i])
                    {
                        ind=i;
                        break;
                    }
                }
                swap(F->m_padre->m_rectangles[ind],F->m_padre->m_rectangles[F->m_padre->m_rectangles.size()-1]);
                swap(F->m_padre->m_childs[ind],F->m_padre->m_childs[F->m_padre->m_childs.size()-1]);
                F->m_padre->m_rectangles.pop_back();
                F->m_padre->m_childs.pop_back();
                F->m_padre->m_rectangles.push_back(X->m_rectangles[0]);
                F->m_padre->m_rectangles.push_back(X->m_rectangles[1]);
                X->m_childs[0]->m_padre = X->m_childs[1]->m_padre = F->m_padre;
                F->m_padre->m_childs.push_back(X->m_childs[0]);
                F->m_padre->m_childs.push_back(X->m_childs[1]);
                F->m_padre->m_cant++;
                RefusePadres(F->m_padre->m_childs[F->m_padre->m_childs.size()-1]);
                RefusePadres(F->m_padre->m_childs[F->m_padre->m_childs.size()-2]);
                F=F->m_padre;


            }

        }
        ReParent(m_head);
    }
}
//--------------FUNCIONES-----------------
int eval(vector<rasmus> v,int metodo)
{
    rasmus may,men;
    may=men=0;
    if(metodo==1)
    {
        for(int i=1;i<v.size();i++){if(v[i]>v[may]){may=0;}}
        return may;
    }
    if(metodo==2)
    {
        for(int i=1;i<v.size();i++){if(v[i]<v[men]){men=i;}}
        return men;
    }
}

bool isInside(Rectangle* a, punto k)
{
    if(k.first >= a->m_A.first and k.first <= a->m_B.first and
            k.second <= a->m_A.second and k.second >= a->m_B.second){
        return true;
    }
    return false;
}
bool InsideRectangle(Rectangle* a, Rectangle* b)
{
    if(isInside(a,b->m_A) and isInside(a,b->m_B)){return true;}
    else{return false;}
}

bool colide(Rectangle* a, Rectangle* b)
{
    if(isInside(a,b->m_A) or isInside(a,b->m_B))
    {
        return true;
    }
    return false;
}

rasmus area(Rectangle* R)
{
    return abs(R->m_B.first - R->m_A.first) * abs(R->m_B.second - R->m_A.second);
}

void RTree::Search(Rectangle *R, Nodo* n)
{
    for(int i=0;i<n->m_rectangles.size();i++)
    {

        if(colide(R,n->m_rectangles[i]) or InsideRectangle(n->m_rectangles[i], R))
        {
            n->m_rectangles[i]->Drow(al_map_rgb(45,230,241));
        }

        if(colide(R,n->m_rectangles[i]) and n->m_leaf==true)
        {
            n->m_rectangles[i]->Drow(al_map_rgb(238,52,153));

        }
        this->representative = n->m_rectangles[i];
    }
    for(int i=0;i<n->m_childs.size();i++)
    {
        Search(R,n->m_childs[i]);
    }
}

void RTree::Print(Nodo* n)
{
    for(int i=0;i<n->m_rectangles.size();i++)
    {
        if(n->m_leaf){n->m_rectangles[i]->Drow(al_map_rgb(213,136,83));}
        else{n->m_rectangles[i]->Drow();}
    }
    for(int i=0;i<n->m_childs.size();i++)
    {
        Print(n->m_childs[i]);
    }
}

void RTree::m_Datos()
{
    cout<<"M : "<<m_M<<endl;
    cout<<"m : "<<m_m<<endl;
}



//--------------FUNCIONES-----------------
/*int eval(vector<rasmus> v,int metodo)
{
    rasmus may,men;
    may=men=0;
    if(metodo==1)
    {
        for(int i=1;i<v.size();i++){if(v[i]>v[may]){may=0;}}
        return may;
    }
    if(metodo==2)
    {
        for(int i=1;i<v.size();i++){if(v[i]<v[men]){men=i;}}
        return men;
    }
}

bool isInside(Rectangle* a, punto k)
{
    if(k.first >= a->m_A.first and k.first <= a->m_B.first and
            k.second <= a->m_A.second and k.second >= a->m_B.second){
        return true;
    }
    return false;
}
bool InsideRectangle(Rectangle* a, Rectangle* b)
{
    if(isInside(a,b->m_A) and isInside(a,b->m_B)){return true;}
    else{return false;}
}

bool colide(Rectangle* a, Rectangle* b)
{
    if(isInside(a,b->m_A) or isInside(a,b->m_B))
    {
        return true;
    }
    return false;
}

rasmus area(Rectangle* R)
{
    return abs(R->m_B.first - R->m_A.first) * abs(R->m_B.second - R->m_A.second);
}*/

Rectangle* Fuse(Rectangle* A, Rectangle* B)
{
    punto a,b;
    a.first=min(A->m_A.first,B->m_A.first);
    a.second=max(A->m_A.second,B->m_A.second);
    b.first=max(A->m_B.first,B->m_B.first);
    b.second=min(A->m_B.second,B->m_B.second);
    return new Rectangle(a,b);
}
Rectangle* Resize(Nodo* X)
{
    Rectangle* xd=X->m_rectangles[0];
    for(int i=1;i<X->m_rectangles.size();i++)
    {
        xd=Fuse(xd,X->m_rectangles[i]);
    }
    return xd;
}
void RefusePadres(Nodo* N)
{
    Nodo *Com=N;
    while (Com->m_padre!=NULL)
    {
        int nind;
        for(int i=0;i<Com->m_padre->m_childs.size();i++)
        {
            if(Com==Com->m_padre->m_childs[i])
            {
                nind=i;
                break;
            }
        }
        Com->m_padre->m_rectangles[nind]=Resize(Com);
        Com=Com->m_padre;
    }
}

void ReParent(Nodo* N)
{
    for(int i=0;i<N->m_childs.size();i++)
    {
        N->m_childs[i]->m_padre=N;
    }
    for(int i=0;i<N->m_childs.size();i++)
    {
        ReParent(N->m_childs[i]);
    }
}

vector<Rectangle*> RandRectangleGenerator(int n)
{
    rasmus x,xx,y,yy;
    vector<Rectangle*> resp;
    for(int i=0;i<n;i++)
    {
        x=(rand() % 1000) - 500;
        xx=(rand() % 1000) - 5000;
        y=(rand() % 680) - 340;
        yy=(rand() % 680) -340;
        punto a=make_pair(x,y);
        punto b=make_pair(x+10,y+10);
        resp.push_back(new Rectangle(a,b));
    }
    return resp;
}

void IndexPublishing(RTree Rt, int a, int b, int aa, int bb)
{
    Rectangle* SSearch=new Rectangle(make_pair(a,b),make_pair(aa,bb));
    Rt.Search(SSearch,Rt.m_head);
    cout<<Rt.representative->m_A.first<<endl;
    cout<<Rt.representative->m_A.second<<endl;
    cout<<Rt.representative->m_B.first<<endl;
    cout<<Rt.representative->m_B.second<<endl;
    /*for(int i=-32;i<32;i++)
    {
        int b1,b2;
        b1 = i*10;
        b2 = i*10+10;
        for(int i=-32;i<32;i++)
        {

        }
    }*/
    //vector<pair<int,int>> global_index;

}

void GraficarServer(int x, int y){
    int x_size = (X_MAX/8);
    int y_size = (Y_MAX/8);
    ALLEGRO_COLOR color=al_map_rgb(255,241,58);
    al_draw_rectangle((x-1)*x_size,y_size*(y-1),(x_size*x),(y_size*y),color,2);
}

void GraficarMetaServer(int x, int y, int size){
    int x_size = (X_MAX/size);
    int y_size = (Y_MAX/size);
    ALLEGRO_COLOR color=al_map_rgb(75,241,58);
    al_draw_rectangle(((x-1)*x_size)+10,(y_size*(y-1))+10,(x_size*x)-10,(y_size*y)-10,color,2);
}


SN::SN(punto a, int size){
    position = a;
    size_graf = size;

}
void SN::Drow(){
    GraficarMetaServer(position.first,position.second,size_graf);
}
