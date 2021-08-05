double E(double x){	
 //E = 1/2 m (d/t)^2 	
double c0 = 46978.28; // c0 = 939.5656*100/2	
double c1 = 1.0254; // c1 = tof distance 	
double c2 = 2.998; // c2 = speed of light * 10^-8	
	
return(c0*(c1*c1/(x*x*c2*c2))); //x is tof in bins, 1 bin = 1/10.19530774425 ns	
}     // hence the 103.9443 coefficient	
	
	
double LO_00(double y){ //2 Vpp input + 90% of dynamic range
double d0 = 0.668500687757909;
double d1 = 63.8665749656121;
	
	
return(y*d0+d1); 	
}      	
	
double LO_01(double y){ //2 Vpp input + 90% of dynamic range
double d0 = 1.00621118012422;
double d1 = -131.757763975155;
	
	
return(y*d0+d1); 	
}      	
	
double LO_02(double y){ //2 Vpp input + 90% of dynamic range
double d0 = 0.725373134328358;
double d1 = -61.9522388059702;
	
	
return(y*d0+d1); 	
}      	
double LO_03(double y){ //2 Vpp input + 90% of dynamic range
double d0 = 1.10454545454545;
double d1 = 66.1090909090909;
	
	
return(y*d0+d1); 	
}      	
double LO_04(double y){ //2 Vpp input + 90% of dynamic range
double d0 = 1.27894736842105;
double d1 = -356.873684210526;
	
	
return(y*d0+d1); 	
}      	
	
double LO_05(double y){ //2 Vpp input + 90% of dynamic range
double d0 = 1.06578947368421;
double d1 = -652.736842105263;
	
	
return(y*d0+d1); 	
}      	
	
double LO_06(double y){ //2 Vpp input + 90% of dynamic range
double d0 = 0.731927710843373;
double d1 = 84.6867469879518;
	
	
return(y*d0+d1); 	
}      	
	
double LO_07(double y){ //2 Vpp input + 90% of dynamic range
double d0 = 0.792822185970636;
double d1 = 63.9396411092985;
	
	
return(y*d0+d1); 	
}      	
	
double LO_08(double y){ //2 Vpp input + 90% of dynamic range
double d0 = 0;
double d1 = 0;
	
return(y*d0+d1); 	
}      	
double LO_09(double y){ //2 Vpp input + 90% of dynamic range
double d0 = 0.65587044534413;
double d1 = 77.5748987854251;
	
	
return(y*d0+d1); 	
}      	
	
double LO_10(double y){ //2 Vpp input + 90% of dynamic range
double d0 = 0;
double d1 = 0;
	
	
return(y*d0+d1); 	
}      	
	
double LO_11(double y){ //2 Vpp input + 90% of dynamic range
double d0 = 0.82793867120954;
double d1 = -33.0102214650767;
	
	
return(y*d0+d1); 	
}      	
	
double LO_12(double y){ //2 Vpp input + 90% of dynamic range
double d0 = 0.966202783300199;
double d1 = 48.0059642147117;
	
	
return(y*d0+d1); 	
}      	
	
double LO_13(double y){ //2 Vpp input + 90% of dynamic range
double d0 = 0.861702127659574;
double d1 = 54.7659574468085;
	
	
return(y*d0+d1); 	
}      	
	
double LO_14(double y){ //2 Vpp input + 90% of dynamic range
double d0 = 0;
double d1 = 0;
	
	
return(y*d0+d1); 	
}      	
	
double LO_15(double y){ //2 Vpp input + 90% of dynamic range
double d0 = 0.81135225375626;
double d1 = 86.7395659432387;
	
	
return(y*d0+d1); 	
}	

