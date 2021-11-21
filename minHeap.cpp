#include <iostream>
#include <conio.h>
#include <fstream>
using namespace std;
int FatherForeign(int i){
    return (i-1)/2;
}
int leftSonForeign(int i){
    return 2*i+1;
}
int rightSonForeign(int i){
    return 2*i+2;
}

template<typename T>
void HeapFyForeign(int  i,T arr[],int size){
    int hijoDcho=rightSonForeign(i);
    int hijoIzq=leftSonForeign(i);
    int smaller=i;
    if(hijoIzq<size && arr[hijoIzq]<arr[i])smaller=hijoIzq;
    if(hijoDcho<size && arr[hijoDcho]<arr[smaller])smaller=hijoDcho;
    if(smaller!=i){
        swap(arr[i],arr[smaller]);
        HeapFyForeign(smaller,arr,size);
    }
}

template<typename T>
void MakeHeapForeign(T arr[],int size){
    for(int i=size/2;i>=0;i--)HeapFyForeign(i,arr,size);
}

template<typename T>
void printForeign(T arr[],int size){
    for(int i=0;i<size;i++)cout<<arr[i]<<" --> ";
}

template<typename T>
class MinHeap{
    public:
        T *     m_arr;
        int     m_size;
        int     m_capacity;
    
    public:
        MinHeap(int capacity){
            this->m_size=0;
            this->m_capacity=capacity;
            this->m_arr=new T[capacity];
        }

        //---------PADRE O(1)----------- 
        int Father(int i){
            return (i-1)/2;
        }

        //----------HIJO IZQ O(1)--------
        int leftSon(int i){
            return 2*i+1;
        }
        //----------HIJO DCHO O(1)-------
        int rightSon(int i){
            return 2*i+2;
        }

        //--------------GETMIN  O(1)--------------------------------------
        T getMin(){
            return this->m_arr[0];
        }


        //------------HEAPFY O(Log n)-------------------------------------
        //EL HEAPFY SOLO ME SIRVE PARA REESTRUCTURAR
        //LA PROPIEDAD DE MI HEAP CUANDO ESTA DESIQUILIBRADO POR UN SOLO NODO
        //TMBN SIRVE COMO AUXILIAR PARA EL MAKEHEAP
        void HeapFy(int i){//COMPLEJIDAD DEL ALGORITMO  -----> "O(Log n)"
                            //PORQ PUEDE RECORRER LA ALTURA HACIENDO SWAPS HASTA LA HOJA
            int hijoDcho=rightSon(i);
            int hijoIzq=leftSon(i);
            int smaller=i;
            //ESTE ALGORITMO SE DETIENE CUANDO EL SMALLER SE MANTIENE EN EL INDICE  "i"
            //TMBN SE DETIENE CUANDO LLEGA A UNA  HOJA
            // ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
            if(hijoIzq<this->m_size && this->m_arr[hijoIzq]<this->m_arr[i])smaller=hijoIzq;//SI EL HIJO IZQ ES MAYOR Q EL TAMAÑO ENTONCES ESTAMOS 
                                                                                            //EN UNA HOJA
            if(hijoDcho<this->m_size && this->m_arr[hijoDcho]<this->m_arr[smaller])smaller=hijoDcho;//SI EL HIJO DCHO ES MAYOR Q EL TAMAÑO ENTONCES ESTAMOS 
                                                                                            //EN UNA HOJA
            if(smaller!=i){//SI EL SMALLER NO CAMBIA QUIERE DECIR Q ESTA ARREGLADO
                swap(this->m_arr[i],this->m_arr[smaller]);
                HeapFy(smaller);
            }

        }


        void MakeHeapWithoutHeapFy(T arrRand[],int size){
            for(int i=0;i<size;i++)Insertar(arrRand[i]);
        }

        //------------MAKEHEAP " O(n log(n))" ---------------------
        //OJO EN SI DEMORA N/2(LOG N)
        //PERO EN COMPUTACION ES SOLO 
        //N/2 LOG N
        //USAREMOS EL HEAPFY PARA ARREGLAR UN ARRAY
        void MakeHeap(T arr[],int sizeArr){
            for(int i=0;i<sizeArr;i++){
                if(this->m_size==this->m_capacity)break;
                this->m_arr[i]=arr[i];
                this->m_size++;
            }
            for(int i=this->m_size/2;i>=0;i--)HeapFy(i);
        }

        //---------DECREASE_KEY O(log n)------------------
        //DISMINUYE EL VALOR  DE UN KEY DE NUESTRO 
        void decreaseKey(int i,T k){
            this->m_arr[i]=k;
            int pos=i;
            while(pos!=0 && this->m_arr[Father(pos)]>this->m_arr[pos]){
                swap(this->m_arr[Father(pos)],this->m_arr[pos]);
                pos=Father(pos);
            }
        }

        //---------- INSERT O(log n)----------------
        void Insertar(T k){//
            if(this->m_size==this->m_capacity){
                cout<<"Overflow can`t insert a new key "<<k<<endl;
                return;
            }
            this->m_size++;
            this->m_arr[this->m_size-1]=k;
            int i=this->m_size-1;
            while(i!=0 && this->m_arr[Father(i)]>this->m_arr[i]){
                swap(this->m_arr[Father(i)],this->m_arr[i]);
                i=Father(i);
            }
        }
        //------------EXTRACT_MIN O()----------------
        void Extract_min(){
            if(this->m_size==0){
                cout<<"THE HEAP IS EMTPY CAN`T DELETE "<<endl;
                return;
            }
            else if(this->m_size==1){
                this->m_size--;
            }
            swap(this->m_arr[0],this->m_arr[this->m_size-1]);
            this->m_size--;
            HeapFy(0);
        }
        //-------------DELETE_KEY O()-----------------

        void DeleteKey(int i){
            decreaseKey(i,this->m_arr[0]-1);
            Extract_min();
        }
        void print(){
            for(int i=0;i<this->m_size;i++){
            
                cout<<this->m_arr[i]<<" -> ";
            }
            cout<<endl;
        }

        void graficar(int i, ofstream &archivo){
            if(i>=this->m_size) return;
            if(leftSon(i)<this->m_size){
                archivo << this->m_arr[i]<< "--" <<this->m_arr[leftSon(i)]<< ";\n";
            }
            if(rightSon(i)<this->m_size){
                archivo << this->m_arr[i]<< "--" << this->m_arr[rightSon(i)] << ";\n";
            }
            graficar(leftSon(i), archivo);
            graficar(rightSon(i), archivo);
        }
        void graficar(){
            if(this->m_size==0) return;
            ofstream archivo;
            archivo.open("grafo.dot");
            archivo << "graph A{\n";
            graficar(0,archivo);
            archivo << "\n}";
            archivo.close();
            system("dot grafo.dot -o grafo.png -Tpng");
            system("grafo.png");
        }

};



int main(){
    MinHeap<int>test(7);
    // int aux[]={80,7,70,40,500,20,3,15,50};
    //test.MakeHeapWithoutHeapFy(aux,9);
    test.Insertar(80);
    test.Insertar(7);
    test.Insertar(70);
    test.Insertar(40);
    test.Insertar(500);
    test.Insertar(20);
    test.Insertar(3);
    test.Insertar(15);
    test.Insertar(50);
    test.DeleteKey(2);//ELIMINAREMOS EL NODO DE INDICE 2
                        //OSEA EL VALOR 7
    // test.MakeHeap(aux,9);
    //test.print();
    // test.Extract_min();
    // // cout<<"El minimo del heap es "<<test.getMin()<<endl;
    // test.print();
    // // test.decreaseKey(2,1);
    // test.decreaseKey(4,2);//EL NODO CON INDICE 4 SERA 2
                            //ES DECIR TRANSFORMAREMOS
                            //500 A 2
    test.Extract_min();//EXTREAEREMOS EL NODO CON VALOR 2
                        //ES DECIR EL MINIMO
    test.graficar();
    // MakeHeapForeign(aux,9);
    // printForeign(aux,9);
    system("pause");
    return 0;
}