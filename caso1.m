(* ::Package:: *)

(* ::Input:: *)
(*<<"/home/iubuntu/Descargas/github/caso1/RRT/RandomData.m"*)


(* ::Input:: *)
(*lambda=100;*)
(*mu=100;*)
(*ro=lambda/mu;*)
(*nmax=10000;*)


(* ::Subchapter:: *)
(*Apartado 2: Distribucion uniforme*)


(* ::Input:: *)
(**)
(*histuniform= Table[RandomData[],{i,nmax}];*)
(*Histogram[histuniform]*)


(* ::Subchapter:: *)
(*Apartado 3: Numeros aleatorios con randomExp*)


(* ::Text:: *)
(*El array InterArr es un array que almacena el espacio de tiempo que hay entre las llegadas de los paquetes. Esto se puede simular con una distrbuci\[OAcute]n exponencial con tasa de llegada lambda.*)


(* ::Input:: *)
(*InterArr= Table[RandomExp[lambda],nmax];*)
(*Histogram[InterArr]*)


(* ::Input:: *)
(*Histogram[InterArr, 50,"CDF"]*)


(* ::Text:: *)
(*Para hacer funciones: P.ej, acumular arrivals (sumar una con la anterior)*)


(* ::Input:: *)
(*Arriv=Accumulate[InterArr];*)


(* ::Input:: *)
(*ServiceTime=Table[RandomExp[mu],nmax];*)


(* ::Text:: *)
(*La siguiente funcion lo que hace es recibir los tiempos de llegada y de servicio de la cola.  Se analiza paquete a paquete para conseguir los tiempos en los que se estan sirviendo los paquetes.*)


(* ::Input:: *)
(*FifoSchedulling[arrivals_,service_]:=Module[{n,checkTime},n=1;checkTime=arrivals[[1]];*)
(*(If[checkTime>=#,checkTime+=service[[n++]],checkTime=#+service[[n++]]])&/@arrivals]*)
(**)


(* ::Input:: *)
(*DeparturesTime=FifoSchedulling[Arriv,ServiceTime];*)


(* ::Input:: *)
(*Show[ListPlot[Arriv[[1;;20]]],ListPlot[DeparturesTime[[1;;20]]]]*)


(* ::Input:: *)
(*Manipulate[ListPlot[{Arriv[[origin;;origin+width]],DeparturesTime[[origin;;origin+width]]}],{origin,1,1000-width,1},{width,10,40,1}]*)


(* ::Text:: *)
(*Funcion que se ha inventado para hacer la escalera:*)


(* ::Input:: *)
(*PointStair[lst_]:=Module[{n=0,lastTime=0},Flatten[Map[({{lastTime,n},{lastTime=#,n++}})&,lst],1]]*)


(* ::Input:: *)
(*Manipulate[ListLinePlot[{PointStair[Arriv[[1;;width]]],PointStair[DeparturesTime[[1;;width]]]}],{width,10,40,1}]*)


(* ::Text:: *)
(*Otra opcion (usando funcion del Mathematica) podr\[IAcute]a ser la siguiente funci\[OAcute]n. Esto es solo un ejemplo, pero podr\[IAcute]a sustituirse por las funciones ListLinePlot y PointStair de arriba.*)


(* ::Input:: *)
(*ListStepPlot[Arriv[[1;;10]]]*)


(* ::Input:: *)
(**)


(* ::Title:: *)
(*PARTE 2 *)


(* ::Subchapter:: *)
(*Apartado 4*)


(* ::Text:: *)
(*Para monta\[NTilde]as (Numero de usuarios en el sistema)*)


(* ::Input:: *)
(*ArrivalsEvent[lst_]:=Map[{#,1}&,lst];*)


(* ::Input:: *)
(*DepartureEvents[lst_]:=Map[{#,-1}&,lst];*)


(* ::Input:: *)
(*DrawMontain[lst_]:=Module[{n=0,lastTime=0},*)
(*Flatten[*)
(*Map[{{lastTime,n},{lastTime=#[[1]],*)
(*If[#[[2]]==1,n++,n--]}}&,*)
(*lst],*)
(*1*)
(*]]*)


(* ::Input:: *)
(**)
(*EventList=Sort[Join[ArrivalsEvent[Arriv[[]]],DepartureEvents[DeparturesTime[[]]]]];*)


(* ::Input:: *)
(**)
(*listStat=DrawMontain[EventList];*)


(* ::Input:: *)
(*ListLinePlot[DrawMontain[listStat]]*)


(* ::Input:: *)
(*Manipulate[*)
(*ListLinePlot[listStat[[1;;width]]],*)
(*{width,10,100,1}]*)


(* ::Input:: *)
(*GetStat[lst_,stat_]:=Module[{time=0,lastTime=0},Map[(If[#[[2]]==stat,time+=#[[1]]-lastTime];*)
(*lastTime=#[[1]])&,lst];time]*)


(* ::Input:: *)
(*ProbTotal[lst_,numest_]:=Module[{estados=Table[i,{i,0,numest,1}]},Map[(GetStat[lst,#]/(lst[[Length[lst]]][[1]]-lst[[1]][[1]]))&,estados]]*)


(* ::Input:: *)
(*CheckProb[probs_]:=Module[{acum=0},Map[(acum+=#)&,probs];acum]*)


(* ::Input:: *)
(*probabilities=ProbTotal[listStat,8];*)
(*CheckProb[probabilities]*)


(* ::Text:: *)
(*Otra funcion que me he montado pero que no funciona aun*)


(* ::Text:: *)
(*ObtainMaxUserConnected[lst_] := *)
(* Module[{maxValue = 0},*)
(*  Map[(If[#[lst[[]]]])];*)
(*  maxValue]*)


(* ::Text:: *)
(**)
(*ObtainMaxUserConnected[listStat];*)


(* ::Subchapter:: *)
(*Apartado 5*)


(* ::Text:: *)
(*Primeramente calculamos el tiempo medio de espera estimado para unos valores de mu y lambda concreto. He definido una funci\[OAcute]n que calcula la media de tiempo, y luego esa la utilizo dentro de la funci\[OAcute]n que utiliza los parametros mu, lambda y ro para poder calcular la media de tiempo para esos valores concretos.*)


(* ::Input:: *)
(*GetMeanTime[ArrivalTimes_,DepartureTimes_]:=Module[{acum,i},For[i=0,i<Length[ArrivalTimes],i++;*)
(*	acum+=DepartureTimes[[i]]-ArrivalTimes[[i]];];Return[acum/Length[ArrivalTimes]]]*)


(* ::Input:: *)
(*MeanTimeOfRo[lambda_,mu_,n_]:=Module[{ro=lambda/mu,i,acum},Table[i,{i,0,n,1}];*)
(*For[i=1,i<=n,n++,*)
(*InterArrTime=Table[RandomExp[lambda],n];*)
(*Arriv=Accumulate[InterArrTime];*)
(*ServiceTime=Table[RandomExp[mu],n];*)
(*DeparturesTime=FifoSchedulling[Arriv,ServiceTime];*)
(*acum[[i]]=GetMeanTime[Arriv,DeparturesTime];]Return[acum]];*)
(**)


(* ::Text:: *)
(*Se compara con la media te\[OAcute]rica*)


(* ::Input:: *)
(*teoric=Plot[1/(1-ro),{ro,0,1},AxesOrigin->{0,0},MeanTimeOfRo[lambda,mu,ro]];*)


(* ::Subchapter:: *)
(*Apartado 6*)
