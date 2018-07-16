#ifndef AG_H
#define AG_H

#include <iostream>
#include <vector>
#include <ctime>
#include <tuple>
#include <algorithm>
#include <iomanip>
#include <fstream>

using namespace std;
typedef double Num;


Num random(Num max){
	return static_cast <Num> (rand()) / (static_cast <Num> (RAND_MAX/max));
}

int random(int min, int max){
	return (rand() % (max+1) + min);
}

typedef struct 
{
	vector<vector<int>> Gen;
	Num fitness;
}Individuo;

typedef struct 
{
	int cod_Vuelo;
	Num hPartida;
	Num hLlegada;
	char aPartida;
	char aLlegada;
	Num Distancia;
	int factor_Demanda;

}tVuelo;

typedef struct 
{
	int cod_Flota;
	Num nomFlota;
	int cant_asientos;
	Num cons_comb;
	Num VelCrucero;
	int NumDisp;
	Num bondad;
}tFlota;

typedef vector<tVuelo> IVuelos;
typedef vector<tFlota> ITFlota;

struct CompF1
{
   bool operator()(Individuo & s1, Individuo & s2)
   {
       	return s1.fitness>s2.fitness;
   }
}; ////

struct CompF
{
   bool operator()(Individuo & s1, Individuo & s2)
   {
       	return s1.fitness<s2.fitness;
   }
}; ////

struct CompV
{
   bool operator()(tVuelo & s1, tVuelo & s2)
   {
       	return s1.hPartida>s2.hPartida;
   }
}; ////

struct CompB
{
   bool operator()(tFlota & s1, tFlota & s2)
   {
       	return s1.bondad>s2.bondad;
   }
}; ////

Num FO(Individuo X,IVuelos Vuelos,ITFlota Flotas){
	int n=X.Gen.size();
	Num sum=0;
	for (int i = 0; i < n; ++i)
	{
		int CDP=Vuelos[i].factor_Demanda;
		int m=X.Gen[i].size();
		for (int j = 0; j < m; ++j)
		{
			int CAA=Flotas[j].cant_asientos;
			Num CC=Flotas[j].cons_comb;
			Num D=Vuelos[i].Distancia;
			Num VC=Flotas[j].VelCrucero;
			sum+=X.Gen[i][j]*((CDP*CAA)/(CC*(D/VC)));
		}
	}
	return sum;
}

Num Distancias(char a,char b){
	if ((a=='A' and b=='L') or (a=='L' and b=='A'))
	{
		return  765;
	}
	if ((a=='C' and b=='L') or (a=='L' and b=='C'))
	{
		return  1165;
	}
	if ((a=='A' and b=='C') or (a=='C' and b=='A'))
	{
		return  323;
	}
	if ((a=='A' and b=='I') or (a=='I' and b=='A'))
	{
		return  1419;
	}
	if ((a=='I' and b=='L') or (a=='L' and b=='I'))
	{
		return  1011;
	}
	if ((a=='C' and b=='I') or (a=='I' and b=='C'))
	{
		return  1096;
	}
}

char lugar(){
	Num numer=random(1);
	if (numer<0.25)
	{
		return 'C';
	}if(numer<0.5)
	{
		return 'A';
	}if (numer<0.75)
	{
		return 'L';
	}if (numer<1)
	{
		return 'I';
	}
}

vector<tVuelo> Crear_vuelos(int a){
	vector<tVuelo> V;
	for (int i = 0; i < a; ++i)
	{
		tVuelo I;
		I.cod_Vuelo=i;
		I.hPartida=random(24);
		do{
			I.hLlegada=random(24);
		}while(I.hPartida>I.hLlegada);
		I.aPartida=lugar();
		do{
			I.aLlegada=lugar();
		}while(I.aPartida==I.aLlegada);
		I.Distancia=Distancias(I.aPartida,I.aLlegada);
		Num ra=random(1);
		if (ra<0.3)
		{
			I.factor_Demanda=2;
		}else if (ra<0.6)
		{
			I.factor_Demanda=5;
		}else{
			I.factor_Demanda=10;
		}
		V.push_back(I);
	}
	return V;
}

vector<tFlota> Crear_Flotas(int a){
	vector<tFlota> F;
	for (int i = 0; i < a; ++i)
	{
		tFlota I;
		I.cod_Flota=i;
		I.nomFlota=random(100);
		I.cant_asientos=random(15,30);
		do{
		I.cons_comb=random(5);
		}while(I.cons_comb<2);
		do{
			I.VelCrucero=random(950);
		}while(I.VelCrucero<500);
		I.NumDisp=random(1,6);
		F.push_back(I);
	}
	return F;
}

class AG{

public:
	AG(int iteraciones);
	void buscar_candidatos();
	void generar_RCL();
	void Genetico();
	
	void casaminetoM();

	void Memetico();
	vector<Individuo> PM;
	void busqueda_local(Individuo &a);
	Individuo mutacion(Individuo a);
	void mostrarPM();
	int PMT;

	void convertir_cromosomas();
	void mostrarS();
	void mostrarP();
	void casamineto();
	void Mutacion();

	//~AG();

	vector<tuple<int,int>> S;
	vector<vector<tuple<int,int>>> CS;
	int MI=4;
	
	ITFlota CA;
	ITFlota CAA;
	ITFlota RCL;
	tVuelo V;
	tFlota A;
	Num MXB;
	Num MNB;
	ITFlota LTF;
	ITFlota LTFR;
	IVuelos RTS;
	IVuelos Vuelos;
	vector<int> disponibles;
	Num alfa=0.6;

	vector<Individuo> P;
	int TP;
	int iteraciones=20;
	Num sum=0;
	vector<Num> rangos;
	int buscar_rangos(Num numero);

};

void AG::casaminetoM(){
	Individuo Padre;
	Individuo Madre;
	std::vector<std::vector<int>> H1;
	std::vector<std::vector<int>> H2;
	int pos1;
	int pos2;
	for (int it = 0; it < PM.size()*2; ++it)
	{
		pos1=buscar_rangos(random(1));
	
		do{
			pos2=buscar_rangos(random(1));
		}while(pos2==pos1);
		//cout<<pos2<<endl;
		Padre=P[pos1];
		//cout<<"HOLA"<<endl;
		Madre=P[pos2];
		H1=Padre.Gen;
		H2=Madre.Gen;

		for (int i = 0; i < Vuelos.size(); ++i)
		{
			if (random(1)>0.5)
			{
				swap(H1[i],H2[i]);
			}
			
		}
		Padre.Gen=H1;
		Madre.Gen=H2;
		busqueda_local(Padre);
		busqueda_local(Madre);
		Padre.fitness=FO(Padre,Vuelos,LTF);
		Madre.fitness=FO(Madre,Vuelos,LTF);
		P.push_back(Padre);
		P.push_back(Madre);
	}
	
}

Individuo AG::mutacion(Individuo a){
	if(random(1)>0.8){
		int pos1=random(0,9);
		int pos2;
		do{
			pos2=random(0,9);
		}while(pos2==pos1);
		swap(a.Gen[pos1],a.Gen[pos2]);
	}
	return a;
	
}

void AG::busqueda_local(Individuo &a){
	Individuo Nuevo;
	int H=0;
	
	Nuevo =mutacion(a);
	while(H<=10 and Nuevo.fitness<a.fitness){
		//cout<<endl<<"arbol"<<endl;
		H++;
		
		Nuevo =mutacion(a);
		//mostrar_individuo(Nuevo);
	}
	if(Nuevo.fitness>a.fitness){
		busqueda_local(Nuevo);
		//cout<<endl<<"El mejor del arbol"<<endl;
		//mostrar_individuo(Nuevo);
		a=Nuevo;
	}


}

void AG::Memetico(){
	PMT=PM.size();
	mostrarPM();
	for (int it = 0; it < iteraciones; ++it)
	{
		sum=0;
		for (int i = 0; i < PMT; ++i)
		{
			sum+=P[i].fitness;
			rangos[i]=P[i].fitness;
		}
		
		
		for (int i = 0; i < PMT; ++i)
		{
			if (i==0)
			{
				rangos[i]=rangos[i]/sum;
			}else{
				rangos[i]=rangos[i]/sum+rangos[i-1];
			}
			
		}
		casaminetoM();
		int res=PM.size()-PMT;
		sort (PM.begin(), PM.end(),CompF1());
		for (int i = 0; i < res; ++i)
		{
			PM.pop_back();
		}
		printf("\n");
		mostrarPM();
	}
	printf("\n");
	mostrarPM();
}

int AG::buscar_rangos(Num numero){
	for(int i = 0; i<TP; ++i){
		if(i==0){
			if(rangos[i]>numero && numero>=0){
				return i;
			}
		}
		else if(rangos[i]>numero && rangos[i-1]<=numero){
			return i;
		}
	}
}
void AG::Mutacion(){
	for (int i = 0; i < P.size(); ++i)
	{
		if(random(1)>0.5){
			int pos1=random(0,9);
			int pos2;
			do{
				pos2=random(0,9);
			}while(pos2==pos1);
			swap(P[i].Gen[pos1],P[i].Gen[pos2]);
			P[i].fitness=FO(P[i],Vuelos,LTF);
		}
	}
}

void AG::casamineto(){
	Individuo Padre;
	Individuo Madre;
	std::vector<std::vector<int>> H1;
	std::vector<std::vector<int>> H2;
	int pos1;
	int pos2;
	
	pos1=buscar_rangos(random(1));
	
	do{
		pos2=buscar_rangos(random(1));
	}while(pos2==pos1);
	//cout<<pos2<<endl;
	Padre=P[pos1];
	//cout<<"HOLA"<<endl;
	Madre=P[pos2];
	H1=Padre.Gen;
	H2=Madre.Gen;

	for (int i = 0; i < Vuelos.size()/2; ++i)
	{
		swap(H1[i],H2[i]);
	}
	Padre.Gen=H1;
	Madre.Gen=H2;
	Padre.fitness=FO(Padre,Vuelos,LTF);
	Madre.fitness=FO(Madre,Vuelos,LTF);
	P.push_back(Padre);
	P.push_back(Madre);

}

void AG::mostrarPM(){
	for (int i = 0; i < PM.size(); ++i)
	{
		for (int j = 0; j < PM[i].Gen.size(); ++j)
		{
			for (int k = 0; k < PM[i].Gen[j].size(); ++k)
			{
				printf("%d", PM[i].Gen[j][k] );
			}
			printf(" ");
			
		}
		printf("\t FITNESS %f\n",PM[i].fitness);
	}
}
void AG::mostrarP(){
	for (int i = 0; i < TP; ++i)
	{
		for (int j = 0; j < P[i].Gen.size(); ++j)
		{
			for (int k = 0; k < P[i].Gen[j].size(); ++k)
			{
				printf("%d", P[i].Gen[j][k] );
			}
			printf(" ");
			
		}
		printf("\t FITNESS %f\n",P[i].fitness);
	}
}

void AG::convertir_cromosomas(){
	std::vector<int> tmp;
	for (int i = 0; i < LTF.size(); ++i)
	{
		tmp.push_back(0);
	}
	vector<std::vector<int>> I;
	Individuo Ind;
	for (int i = 0; i < Vuelos.size(); ++i)
	{
		I.push_back(tmp);
	}
	for (int i = 0; i < CS.size(); ++i)
	{	
		for (int j = 0; j < Vuelos.size(); ++j)
		{
			I[j]=tmp;
		}
		for (int j = 0; j < CS[i].size(); ++j)
		{
			I[get<0>(CS[i][j])][get<1>(CS[i][j])]=1;
		}
		Ind.Gen=I;
		Ind.fitness=FO(Ind,Vuelos,LTF);
		P.push_back(Ind);
	}
}

void AG::Genetico(){
	convertir_cromosomas();
	TP=P.size();
	PM=P;
	mostrarP();
	for (int it = 0; it < iteraciones; ++it)
	{
		sum=0;
		if (it==0)
		{
			for (int i = 0; i < TP; ++i)
			{
				sum+=P[i].fitness;
				rangos.push_back(P[i].fitness);
			}
		}else{
			for (int i = 0; i < TP; ++i)
			{
				sum+=P[i].fitness;
				rangos[i]=P[i].fitness;
			}
		}
		
		for (int i = 0; i < TP; ++i)
		{
			if (i==0)
			{
				rangos[i]=rangos[i]/sum;
			}else{
				rangos[i]=rangos[i]/sum+rangos[i-1];
			}
			
		}
		
		casamineto();
		Mutacion();
		sort (P.begin(), P.end(),CompF1());
		P.pop_back();
		P.pop_back();
		printf("\n");
		mostrarP();
	}
	printf("\n");
	
	mostrarP();
}

void AG::mostrarS(){
	for (int i = 0; i < S.size(); ++i)
	{
		printf("[%d %d] ",get<0>(S[i]),get<1>(S[i]));
	}
	printf("\n");
}

tFlota seleccion_aleatoria(ITFlota RCL){
	return RCL[random(0,RCL.size())];
}

tVuelo obtener_siguiente_vuelo(IVuelos RTS){
	return RTS.back();
}

AG::AG(int iteraciones){
	Vuelos=Crear_vuelos(10);
	RTS=Vuelos;
	sort (RTS.begin(), RTS.end(),CompV());
	LTF=Crear_Flotas(5);/*
	auto a=make_tuple(0,0);
	for (int i = 0; i < RTS.size(); ++i)
	{
		S.push_back(a);

	}
	*/
	for (int i = 0; i < MI; ++i)
	{
		for (int K = 0; K < LTF.size(); ++K)
		{
			disponibles.push_back(LTF[K].NumDisp);
		}
		IVuelos tempRTS=RTS;
		ITFlota tempLTF=LTF;
		
		while(tempRTS.size()!=0 and tempLTF.size()!=0 ){
			//cout<<i<<endl;
			V=obtener_siguiente_vuelo(tempRTS);
			tempRTS.pop_back();
			buscar_candidatos();
			generar_RCL();
			A=seleccion_aleatoria(RCL);
			auto a=make_tuple(0,0);
			if (RCL.size()==0)
			{
				a=make_tuple(V.cod_Vuelo,0);
			}else{
				if (A.cod_Flota<0 or A.cod_Flota>5)
				{
					a=make_tuple(V.cod_Vuelo,random(0,4));	
				}else{
				a=make_tuple(V.cod_Vuelo,A.cod_Flota);
				}
			}
			S.push_back(a);
		}
		mostrarS();
		CS.push_back(S);
		S.clear();
	}
	printf("Inicio de Genetico\n");
	Genetico();
	printf("\n\nInicio de Memetico\n");
	Memetico();

	printf("\n\nmejor de Genetico\n");
	for (int j = 0; j < P[0].Gen.size(); ++j)
		{
			for (int k = 0; k < P[0].Gen[j].size(); ++k)
			{
				printf("%d", P[0].Gen[j][k] );
			}
			printf(" ");
			
		}
		printf("\t FITNESS %f\n",P[0].fitness);

	printf("mejor de Memetico\n");
	for (int j = 0; j < PM[0].Gen.size(); ++j)
		{
			for (int k = 0; k < PM[0].Gen[j].size(); ++k)
			{
				printf("%d", PM[0].Gen[j][k] );
			}
			printf(" ");
			
		}
		printf("\t FITNESS %f\n",PM[0].fitness);	
}

Num CalcularBondad(tFlota C, tVuelo V){
	return ((C.cant_asientos*V.factor_Demanda)/(C.cons_comb*V.Distancia));
}

void ordenar(ITFlota &CA){
	//sort()
}

Num bondad(tFlota C){
	return C.bondad;
}

Num max_bondad(ITFlota CA){
	return CA.front().bondad;
}

Num min_bondad(ITFlota CA){
	return CA.back().bondad;
}

tFlota obtener_siguiente_candidato(ITFlota CA){
	return CA.back();
}

vector<tFlota> obtenerAeronavesDisponibles(std::vector<int> v, ITFlota LTF){
	std::vector<tFlota> CAA;
	for (int i = 0; i < v.size(); ++i)
	{
		for (int j = 0; j < v[i]; ++j)
		{
			CAA.push_back(LTF[i]);
		}
		
	}
	return CAA;
}
void remover_candidato(ITFlota &CA, tFlota C){
	CA.pop_back();
}
void AG::buscar_candidatos(){
	CAA=obtenerAeronavesDisponibles(disponibles,LTF);
	tFlota C;
	while(CAA.size()!=0){
		C=obtener_siguiente_candidato(CAA);
		C.bondad=CalcularBondad(C,V);
		CA.push_back(C);
		remover_candidato(CAA,C);
	}
	sort (CA.begin(), CA.end(),CompB());
}


void AG::generar_RCL(){
	MXB=max_bondad(CA);
	MNB=min_bondad(CA);
	Num LI=MXB-alfa*(MXB-MNB);
	tFlota C;
	while(CA.size()!=0){
		C=obtener_siguiente_candidato(CA);
		if(bondad(C)>LI){
			RCL.push_back(C);
		}
		remover_candidato(CA,C);
	}
}
#endif	
