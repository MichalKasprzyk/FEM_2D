#pragma once
class Element_Universal
{
public:
	double* ksi;
	double* eta;

	double** dN_dEta;
	double** dN_dKsi;
	double** N;
	int matrix_size = 4;


	void init_N_Matrix();
	void init_d_KsiMatrix();
	void init_d_EtaMatrix();
	void init_Ksi_Eta();



	double** getDn_dEta();
	double** getN();
	double** getDn_dKsi();
	int get_matrix_size();


	Element_Universal();
	~Element_Universal();
};

