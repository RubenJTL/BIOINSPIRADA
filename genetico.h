#ifndef GENETICO_H
#define GENETICO_H

#include <iostream>
#include <vector>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include <fstream>


#define RANDOM_RANGE 31


using namespace std;

typedef double Num;
 
string convert_to_binary(int,int);
int convert_to_decimal(string);


Num function(int , int);
Num function(int);


typedef double numReales;

Num random(Num max){
	return static_cast <Num> (rand()) / (static_cast <Num> (RAND_MAX/max));
}

int random(int min, int max){
	return (rand() % max + min);
}

typedef struct 
{
	int cod_vuelo;
	numReales hPartida;
	numReales hLlegada;
	numReales Tiempo;
	int aPartida;
	int aLlegada;
	numReales distancia;
	int factorDemanda;
	
}vuelo; 

typedef struct
{
	int codTFlota;
	char nomTFlota;
	int cantAsientos;
	numReales consComb;
	numReales velCrucero;
	int NumDisp;
	numReales bondad;
}tFlota;

typedef struct
{
	int Avion;
	//codigodeVuelos
	vector<int> secuencia;
}ruta;

typedef struct 
{
	EtapaVuelo;
	vector<Arco> conexiones;
}Conexion;


typedef vector<int> Gen;
typedef vector<Gen> individuo;
typedef vector<vuelo> IVuelos;
typedef vector<tFlota> ITFlota;
typedef vector<Conexion> redTiempoEspacio;
typedef vector<individuo> poblacion;
typedef vector<numReales> fitPob;
typedef vector<redTiempoEspacio> redPoblacion;

numReales FO(individuo X,IVuelos Vuelos,ITFlota Flotas){
	int n=X.size();
	numReales sum=0;
	for (int i = 0; i < n; ++i)
	{
		int CDP=Vuelos[i].factorDemanda;
		int m=X[i].size();
		for (int j = 0; j < m; ++j)
		{
			int CAA=Flotas[j].cantAsientos;
			numReales CC=Flotas[j].consComb;
			numReales D=Vuelos[i].distancia;
			numReales VC=Flotas[j].velCrucero;
			sum+=X[i][j]*((CDP*CAA)/(CC*(D/VC)));
		}
	}
	return sum;
}

class Mejores_Vuelos{
public:
	
	Mejores_Vuelos();
	void Algoritmo_GRASP();
	void inicializar(redTiempoEspacio &RTS);
	void buscar_candidatos();

	vector<individuo> CS;

	int MI;
	ITFlota CA;
	IVuelos CAA;
	ITFlota RCL;
	vuelo V;
	tFlota A;
	numReales MXB;
	numReales MNB;
	ITFlota LTF;
	ITFlota LTFR;
	IVuelos RTS;
};

Mejores_Vuelos::Mejores_Vuelos(){
	
}

tFlota seleccion_aleatoria(ITFlota RCL){
	return RCL[random(0,RCL.size())];
}

vuelo obtener_siguiente_vuelo(IVuelos &RTS){
	return RTS.pop_back();
}

void Mejores_Vuelos::Algoritmo_GRASP(){
	S;
	int num_iteraciones=0;
	while(num_iteraciones<MI){
		auto tempRTS=RTS;
		while(tempRTS.size()!=0){
			V=obtener_siguiente_vuelo(tempRTS);
			CA=buscar_candidatos();
			RCL=generar_RCL();
			A=seleccion_aleatoria(RCL);
			
		}
		HallarBondad(S);
		Actualizar_solucion(CS,S);
		num_iteraciones++;
	}
}

numReales CalcularBondad(tFlota C, vuelo V){
	return ((C.cantAsientos*V.factorDemanda)/(C.consComb*V.distancia));
}

void ordenar(ITFlota &CA){
	//sort()
}

numReales bondad(tFlota C){
	return C.bondad;
}

numReales max_bondad(ITFlota CA){
	return CA.front().bondad;
}

numReales min_bondad(ITFlota CA){
	return CA.back().bondad;
}

tFlota obtener_siguiente_candidato(ITFlota CA){
	return CA.front();
}

void remover_candidato(ITFlota CA, tFlota C){

}

void Mejores_Vuelos::buscar_candidatos(){
	CAA=obtenerAeronaveDisponible(RTS,V);
	LTFR=FiltrarAviones(LTF,V);
	CAA=Actualizar(CAA,LTFR);
	tFlota C;
	while(CAA.size()!=0){
		C=obtener_siguiente_candidato(CAA);
		C.bondad=CalcularBondad(C,V);
		CA.push_back(C);
		remover_candidato(CAA,C);
	}
	ordenar(CA);
}


void Mejores_Vuelos::generar_RCL(){
	MXB=max_bondad(CA);
	MNB=min_bondad(CA);
	numReales LI=MXB-alfa*(MXB-MNB);
	tFlota C;
	while(CA.size()!=0){
		C=obtener_siguiente_candidato(CA);
		if(bondad(C)>LI){
			RCL.push_back(C);
		}
		remover_candidato(CA,C);
	}
}




class genetico{
public:
};
/* struct {
	string cromosomas;
	int genotipo;
	Num aptitud;
}Individuos;
*/


struct Comp
{
   bool operator()(Individuo & s1, Individuo & s2)
   {
       return s1.aptitud < s2.aptitud;
   }
}; ////comparador para maxheap de hijos

struct Comp1
{
   bool operator()(tuple<string,int,Num>& s1, tuple<string,int,Num>& s2)
   {
       return get<2>(s1) < get<2>(s2);
   }
}; ////

struct Comp2
{
   bool operator()(tuple<int,Num>& s1, tuple<int,Num>& s2)
   {
       return get<1>(s1) < get<1>(s2);
   }
}; ////




class genetico{
public:
	
	genetico(int poblacion);
	genetico(int poblacion,int cromosomas,int iteraciones, Num mutacion, int punto);
	genetico(int poblacion,int cromosomas,int iteraciones,Num cross, Num mutacion, int punto1,int punto2,int participantes);
	
	vector<Gen> Individuo;
	vector<vuelo>IVuelos;
	vector<tFlota> ITFlota;
	void run();
	void mostrar_poblacion();
	void mostrar_poblacion_e();
	void mostrar_hijos_e();
	void reproducir();
	bool Mutar(tuple<string>&,Num);
	void new_generation();
	tuple<bool,tuple<string,int,Num>> crear_hijo(tuple<string>,Num);
	void save();

	vector<tuple<string>> CrossOver(int,int);

	int buscar_ganador();


	vector<Individuo> I;

	Num mutacion=0.5;
	Num prob_cross=0.9;
	int iteraciones=10;
	int cromosomas=5;
	int participantes=5;
	int punto;
	int punto1;
	int puntoC=0;
	int poblacion; 
	vector<tuple<string,int,Num>> hijos;

};

void genetico::run(){
	cout<<"Tamanho de la poblacion: "<<this->poblacion<<endl;
	cout<<"Tamanho de los cromosomas: "<<this->cromosomas<<endl;
	cout<<"Cantidad de iteraciones: "<<this->iteraciones<<endl;
	cout<<"Cruzamiento de dos puntos: Punto1: "<<this->punto<<" Punto2: "<<this->punto<<endl;
	cout<<"Probabilidad de mutacion: "<<this->mutacion<<endl<<"Mutacion Simple"<<endl<<endl;
	cout<<"Probabilidad de cruzamiento: "<<this->prob_cross<<endl;
	//buscar_ganador();
	for (int i = 0; i < this->iteraciones; ++i)
   	{
   		if(i==0){
   			cout<<endl<<"Generando Poblacion Inicial"<<endl;
   		}
   		mostrar_poblacion();
   		cout<<endl<<"Iteracion: "<<i<<endl;
   		cout<<endl<<"Evaluando individuos "<<endl;
   		mostrar_poblacion_e();
   		cout<<endl<<"Selecion de individuos - Metodo de Enfrentamiento"<<endl;
   		

	    reproducir();
	    cout<<endl<<"Seleccionando Siguiente Poblacion"<<endl;
	    mostrar_poblacion_e();
	    mostrar_hijos_e();		    
	    new_generation();
	    cout<<endl;
	    //a.save();
		//}	
   	}

   	cout<<endl<<"Ultima Poblacion"<<endl;
   	mostrar_poblacion_e();
}

genetico::genetico(int poblacion,int cromosomas,int iteraciones,Num cross, Num mutacion,int punto1, int punto2,int participantes){
	this->poblacion=poblacion;
	this->iteraciones=iteraciones;
	this->mutacion=mutacion;
	this->cromosomas=cromosomas;
	this->participantes=participantes;
	if(punto1>punto2){
		this->punto=punto2;
		this->punto1=punto1;	
	}
	this->punto=punto1;
	this->punto1=punto2;
	
	this->puntoC=1;
	Individuo I1;
	string tam="";
	for (int i = 0; i < this->cromosomas; ++i)
	{
		tam+="1";
	}
	
	for(unsigned i=0;i<poblacion;++i){

		I1.genotipo=rand() % convert_to_decimal(tam);
		I1.cromosomas=convert_to_binary(I1.genotipo,cromosomas);
		I1.aptitud=function(I1.genotipo);
		
		I.push_back(I1);
	}
}

/*
void genetico::save(){
	char* stri=(char*)"puntos.dat";
	
	ofstream myfile (stri);//, std::ios_base::app
    for(unsigned i=0;i<poblacion;++i){
		myfile <<(I[i]).genotipo[0] <<"\t";
		myfile <<(I[i]).genotipo[1] <<"\t";    		
		myfile <<setprecision(20) <<(I[i]).aptitud<<"\t";
    	myfile <<"\n";
    }   
    myfile.close();
}*/

vector<tuple<string>> genetico::CrossOver(int pos1,int pos2){
	vector<tuple<string>> CromosomasXY(2);
	int pos=punto;
	string X1="", X2="", Y1="", Y2="";
	if(puntoC==0){
		for(unsigned i=0; i<pos; ++i){
			X1+=((I[pos2]).cromosomas)[i];
			X2+=((I[pos1]).cromosomas)[i];
		}
		for(unsigned i=pos; i<I[pos1].cromosomas.length(); ++i){
			X1+=((I[pos1]).cromosomas)[i];
			X2+=((I[pos2]).cromosomas)[i];
		}
	}
	if(puntoC==1){
		for(unsigned i=0; i<I[pos1].cromosomas.length(); ++i){
			if(this->punto-1<=i and i<this->punto1){
				X1+=((I[pos2]).cromosomas)[i];
				X2+=((I[pos1]).cromosomas)[i];
			}else{
				X1+=((I[pos1]).cromosomas)[i];
				X2+=((I[pos2]).cromosomas)[i];
			}
			
		}	
	}
	CromosomasXY[0]=make_tuple(X1);
	CromosomasXY[1]=make_tuple(X2);
	
	return CromosomasXY;
}
tuple<bool,tuple<string,int,Num>> genetico::crear_hijo(tuple<string> CromosomasXY,Num randomc){
	bool muto=Mutar(CromosomasXY,randomc);
	int CromosomaX=convert_to_decimal( get<0>(CromosomasXY) );
	Num fit=function(CromosomaX);
	auto hijo=make_tuple( get<0>(CromosomasXY), CromosomaX, fit );
	hijos.push_back(hijo); //push_heap ( hijos.begin(), hijos.end(), Comp());
	//std::sort (hijos.begin(), hijos.end(), Comp());
	return make_tuple(muto,hijo);
}

bool genetico::Mutar(tuple<string> &cromosoma, Num alpha1){
	
	int randomp1;
	if(this->mutacion>=alpha1){
		randomp1=rand()%(get<0>(cromosoma)).length();
		if(get<0>(cromosoma)[randomp1]=='1'){
			get<0>(cromosoma)[randomp1]='0';
		}else{
			get<0>(cromosoma)[randomp1]='1';
		}
		return true;
	}
	return false;
	
}

void genetico::new_generation(){
	bool t=true;
	unsigned j=0,l=hijos.size()-1;
	if(hijos.size()!=0){
	while(j<I.size() and l>0 ){
		if(I[j].aptitud<get<2>(hijos[l])){
			I[j].genotipo=get<1>(hijos[l]);
			I[j].cromosomas=get<0>(hijos[l]);
			I[j].aptitud=get<2>(hijos[l]);
			l--;
			j++;
		}else{
			break;
		}
	}
	}
	hijos.clear();
}

void genetico::mostrar_poblacion(){
	cout<<endl;
	for(unsigned i=0;i<poblacion;++i){
		cout<<i+1<<")"<<I[i].cromosomas<<"\t"<<I[i].genotipo<<endl;
	}
	
}

void genetico::mostrar_poblacion_e(){
	for(unsigned i=0;i<poblacion;++i){
		cout<<i+1<<")\t"<<I[i].cromosomas<<"\t"<< I[i].genotipo<<"\t"<< I[i].aptitud<<endl;;
	}
	
}

void genetico::mostrar_hijos_e(){
	for(unsigned i=0;i<hijos.size();++i){
		cout<<poblacion+1+i<<")\t"<<get<0>(hijos[i])<<"\t"<< get<1>(hijos[i])<<"\t"<< get<2>(hijos[i])<<endl;
	}
}

void genetico::reproducir(){
	Num random1,random2,random_cross;
	int pos1,pos2;
	vector<tuple<string>> CromosomasXY;
	Num randomc;
	
	for (unsigned i = 0; i < poblacion/2; ++i)
	{
		cout<<endl<<"Participantes Padre"<<endl;
		pos1=buscar_ganador();//retorna la pocision
		//cout<<"HOla"<<endl;
		cout<<endl<<"Participantes Madre"<<endl;
		pos2=buscar_ganador();//retorna la pocision 
		while(pos2==pos1){
			cout<<endl<<"Participantes Madre"<<endl;
			pos2=buscar_ganador();//retorna la pocision 
		}
		random_cross=(Num)(rand()%100)/100.0;
		cout<<endl<<"Padre: "<<pos1+1<<endl<<"Madre: "<<pos2+1<<endl;
		
		cout<<endl<<"Cruzamiento"<<endl;
			if(prob_cross>=random_cross){
			CromosomasXY=CrossOver(pos1,pos2);
			//CromosomasXY2=CrossOver(pos2,pos1);
			randomc=(Num)(rand()%100)/100.0;	
			auto muto=crear_hijo(CromosomasXY[0],randomc);
			if(get<0>(muto)==true){
				cout<<"muto hijo 1"<<endl;
				cout<<get<0>(get<1>(muto))<<endl;
			}else{
				cout<<get<0>(get<1>(muto))<<endl;
			}
			randomc=(Num)(rand()%100)/100.0;
			muto= crear_hijo(CromosomasXY[1],randomc);	
			if(get<0>(muto)==true){
				cout<<"muto hijo 2"<<endl;
				cout<<get<0>(get<1>(muto))<<endl;
			}else{
				cout<<get<0>(get<1>(muto))<<endl;
			}
		}
	}
	std::sort (hijos.begin(), hijos.end(), Comp1());
	std::sort (I.begin(), I.end(),Comp());
	//std::make_heap(hijos.begin(), hijos.end(), Comp());
	//Mutar();
	
}

int genetico::buscar_ganador(){
	std::vector<tuple<int,Num>> seleccionados;
	int selec;
	while(seleccionados.size()<this->participantes){
		selec=(int)(rand()%this->poblacion);
		auto it = std::find_if(seleccionados.begin(), seleccionados.end(), [selec](const std::tuple<int,Num>& e) {return std::get<0>(e) == selec;});
		while (it != seleccionados.end()) {
	  		selec=(int)(rand()%this->poblacion);
	  		it = std::find_if(seleccionados.begin(), seleccionados.end(), [selec](const std::tuple<int,Num>& e) {return std::get<0>(e) == selec;});
		}
		auto s=make_tuple(selec,(I[selec]).aptitud);
		seleccionados.push_back(s);
	}
	std::sort (seleccionados.begin(), seleccionados.end(),Comp2());
	


	for (int i = 0; i < participantes; ++i)
	{
		cout<<i<<")"<<get<0>(seleccionados[i])+1<<" "<<get<1>(seleccionados[i])<<endl;
	}

	return (get<0>(seleccionados[participantes-1]));
}


Num function(int x ){
	//return(pow(x,2));
	return(((pow(-x,2))/10)+(3*x));
}

string convert_to_binary(int a,int cromosomas){
	string bin="";
	unsigned int var = (unsigned int)a;
    unsigned int contador, inicio = pow(2,cromosomas-1); // 2^(8-1) = 128

    for(contador = inicio; contador > 0; contador >>= 1){ // El contador se desplaza un bit a la derecha cada ciclo
        if(contador & var) // Si contador AND var == 1
            bin+="1";
        else
            bin+="0";
    }
    return bin;
}

int convert_to_decimal(string str){
	int decimal=0;
	int a=str.length()-1;
	for(int i=0;i<str.length();i++){
		switch(str[i]){
			case '1':
				decimal+=1*pow(2,a);
				a--;
				break;
			case '0':
				a--;
				break;
		}
	}
	return decimal;
}




#endif	
