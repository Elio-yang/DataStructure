#pragma once
#include "graph.h"

template<typename Tv>class Vertex{
public:
        Tv data;int in_deg;int out_deg;v_status status;
        int d_time,f_time;
        int parent;
        int priority;
        expicit Vertex(Tv const &d=(Tv)0):data(d),in_deg(0),out_deg(0),
        status(UNDISCOVERED),d_time(-1),f_time(-1),parent(-1),priority(INT_MAX){}
};

template<typename Te> class Edge{
public:
        Te data;int weight;e_type type;
        explicit Edge(Te const &e,int w):data(e),weight(w),type(UNDETERMINED){}
};

template<typename Tv,typename Te> class GraphMatrix: public Graph<Tv,Te>{
private:
        /*顶点集*/
        vector<Vertex<Tv> >V;
        /*边集:邻接表*/
        vector<vector< Edge<Te>* > >E;
public:
        using Graph<Tv,Te>::n;//顶点数
        using Graph<Tv,Te>::e;//边数
        GraphMatrix() { n=0;e=0;} //构造
        ~GraphMatrix() { //析构
                for ( int j = 0; j < n; j++ ){//所有动态创建的
                        for ( int k = 0; k < n; k++ ) {//边记录
                                delete E[j][k]; //逐条清除
                        }
                }
        }
        virtual Tv& vertex(int i){return V[i].data;}//query the i-th vertex
        virtual int in_degree(int i){return V[i].in_deg;}
        virtual int out_degree(int i){return V[i].out_deg;}
        virtual int first_nbr(int i){return next_nbr(i,n);}
        virtual int next_nbr(int i,int j){while ((j>-1)&&(!exists(i,--j)));return j;}
        virtual v_status &status(int i){return V[i].status;}
        virtual int& dTime ( int i ) {return V[i].d_time;}
        virtual int& fTime ( int i) {return V[i].f_time;}
        virtual int& parent ( int i) {return V[i].parent;}
        virtual int& priority ( int i ) {return V[i].priority;}

        virtual int insert(Tv const &vertex){
                for(int j=0;j<n;j++){
                        E[j].push_back(nullptr);
                }
                n++;
                E.push_back(vector<Edge<Te>*>(n,(Edge<Te>*)nullptr));
                V.push_back(Vertex<Tv>(vertex));
                return n-1;//顶点编号
        }
        virtual Tv remove(int i){//删除第i个顶点和与其相关的边
                for(int j=0;j<n;j++){
                       if(exists(i,j)){//所有的出边
                               delete E[i][j];
                               V[j].in_deg--;
                               e--;
                       }
                }
                E.erase(i);//删除第i行
                n--;//顶点数
                Tv tmp_v=vertex(i);
                V.erase(i);
                for(int j=0;j<n;j++){
                        if( auto x=E[j].erase(j)){//所有的入边
                                delete x;
                                V[j].out_deg--;
                                e--;
                        }
                }
                return tmp_v;

        }
        virtual bool exists(int i,int j){//(i,j)是否存在
                return (i>=0)&&(i<n)&&(j>=0)&&(j<n)&&E[i][j]!= nullptr;
        }

        virtual e_type &type(int i,int j){
                return E[i][j]->type;
        }
        virtual Te &edge(int i,int j){
                return E[i][j]->data;
        }
        virtual int &weight(int i,int j){
                return E[i][j]->weight;
        }

        virtual void insert (Te const &edge,int w,int i,int j){
                if(exists(i,j)) return;
                E[i][j]=new Edge<Te>(edge,w);
                e++;
                V[i].out_deg++;
                V[j].in_deg++;
        }
        virtual Te remove(int i,int j){
                Te tmp_e=edge(i,j);
                delete E[i][j];
                E[i][j]=nullptr;
                e--;
                V[i].out_deg--;
                V[j].in_deg--;
                return tmp_e;
        }
};