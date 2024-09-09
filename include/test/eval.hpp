#include <iostream>
using namespace std;

int64_t ip_pt(const vector<int64_t>& input1, const vector<int64_t>& input2, int64_t pt_mod){
  int64_t ip = 0;
  for (int i = 0; i < input1.size(); ++i){
    ip += input1[i]*input2[i];
    ip = modq_64(ip, pt_mod);
  }
  return ip;
}


extern void enc_vec_dis_test(){
  cout <<"Task: Test for ciphertexts multiplication. "<<endl;
  int64_t ct_modulus = 576460752154525697;//3221225473;
  int64_t delta = 1;
  int logq = 60;//32;
  int degree = 2048;//1024;
  double var = 3.2;
  int64_t b = 1<<30;
  int logb = 30;
  int64_t modulus = 65537;//16384; //4096; 
  //int64_t primitive_root = 11;
  cout <<"Parameters: Ciphertext Modulus = "<<ct_modulus<<", degree = "<<degree<<", variance = "<<var<<endl;
  cout <<"base of decomposition = "<<b<<endl;
  cout <<"Plaintext Modulus = "<<modulus <<endl;

  int vec_len = 768;//1024;//512;
  int pre_store_vec_num = 5000;
  cout <<"vector length = "<<vec_len<<", number of pre stored encrypted vectors = "<<pre_store_vec_num<<endl;

  //generate test vectors
  //input test vector
  vector<int64_t> input_vec(vec_len,0);
  for (int i = 0; i < vec_len; ++i){
    input_vec[i] = 1;
  }

  //pre-stored vectors
  vector<vector<int64_t>> pre_stored_vec(pre_store_vec_num,vector<int64_t>(vec_len,0));
  for (int i = 0; i < pre_store_vec_num; ++i){
    for (int j = 0; j < vec_len; ++j){
      pre_stored_vec[i][j] = i/100; 
    }
  }

  cout <<"test vectors generated. "<<endl;

  polynomial s=RLWE64_KeyGen(degree);
  int *lwe_s = new int [degree];
  for(int i = 0 ; i < degree ; ++i){
    lwe_s[i] = (int)s[i];
  }
 // cout <<"secret key: "<<endl;


  vector<vector<polynomial>> RelK=RelK_Gen(s,degree,ct_modulus,ct_modulus,logq,var,b,logb);

  cout <<"Relinearization key generated. "<<endl;
  cout <<endl;

  vector<int64_t> test_input(degree,0);
  for(int i = 0 ; i < vec_len ; ++i){
    test_input[i] = input_vec[i];
  }

  vector<polynomial> RLWE_y=RLWE64_Enc(degree,ct_modulus,modulus,var,test_input,s);

  cout <<"input test vector encrypted. "<<endl;

  vector<vector<polynomial>> pre_store_enc_vec(pre_store_vec_num);

  for(int k = 0 ; k < pre_store_vec_num ; ++k){
    vector<int64_t> input1(degree,0);
    input1[0] = pre_stored_vec[k][0];
    for (int i = 1; i < vec_len; ++i){
      input1[degree-i] = -1 * pre_stored_vec[k][i];
    }

    vector<polynomial> RLWE_y2=RLWE64_Enc(degree,ct_modulus,modulus,var,input1,s);

    pre_store_enc_vec[k] = RLWE_y2;
  }

  cout <<"pre stored test vectors encrypted. "<<endl;

  vector<vector<int64_t>> enc_result(pre_store_vec_num);

  struct timeval tstart, tend;

  cout <<"------------TEST START------------"<<endl;

  gettimeofday(&tstart,NULL);

  #pragma omp parallel for

  for (int k = 0; k < pre_store_vec_num; ++k){

    vector<polynomial> RLWE_mul = ct_multiplication(RLWE_y,pre_store_enc_vec[k], RelK, degree, ct_modulus,modulus, 
    logq, b, logb,s);

    vector<int64_t> LWE_ip = extract_0(RLWE_mul,degree);

    enc_result[k] = LWE_ip;

  }

  gettimeofday(&tend,NULL);
  

  cout <<"------------EVALUATION END------------"<<endl;
  double  time_ek = tend.tv_sec-tstart.tv_sec+(tend.tv_usec-tstart.tv_usec)/1000000.0;
  cout <<"Total time for evaluations: "<<time_ek<<"s. "<<endl;
  cout <<"Average time for per evaluation: "<<time_ek/(double)pre_store_vec_num<<"s. "<<endl;

  vector<int64_t>dec_result(pre_store_vec_num);
  double div = 0.0;

  cout <<"Test result: "<<endl;
  for (int k = 0; k < pre_store_vec_num; ++k){
    dec_result[k] = LWE64_Dec(modulus,ct_modulus,degree,enc_result[k],lwe_s);
    
    int64_t pt_result = ip_pt(test_input, pre_stored_vec[k], modulus);

    //cout <<dec_result[k] <<" "<<pt_result<<endl;

    div += ((double)(pt_result)-(double)(dec_result[k]))*((double)(pt_result)-(double)(dec_result[k]));
    
  }
  div /= (double)pre_store_vec_num;
  div = sqrt(div);

  

  cout <<"Standard div = "<<div<<endl;

  

}
  


