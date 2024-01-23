
#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<stdio.h>
#include <fcntl.h> // for open
#include <unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<math.h>
long int p,q,n,t,flag,e[100],d[100],temp[100],j,m[100],en[100],i;
void encrypt1(char *message) {//encrpyts or creates signature in rsa
 
    long int pt,ct,key=e[0],k,len;
 
    i=0;
 
    len=4;
 
    while(i!=len) {
 
        pt=m[i];
 
        pt=pt-96;
 
        k=1;
 
        for (j=0;j<key;j++) {
 
            k=k*pt;
 
            k=k%n;
 
        }
 
        temp[i]=k;
 
        ct=k+96;
 
        en[i]=ct;
 
        i++;
 
    }
 
    en[i]=-1;
 
    
 
    for (i=0;en[i]!=-1;i++)
 
    printf("%c",en[i]);
    printf("\n");
 
}
int prime(long int pr) {
    int i;
    j=sqrt(pr);
    for (i=2;i<=j;i++) {
        if(pr%i==0)
            return 0;
    }
    return 1;
}
long int cd(long int x) {
 
    long int k=1;
 
    while(1) {
 
        k=k+t;
 
        if(k%x==0)
 
            return(k/x);
 
    }
 
}
void decrypt() {
 
    long int pt,ct,key=d[0],k;
 
    i=0;
 
    while(en[i]!=-1) {
 
        ct=temp[i];
 
        k=1;
 
        for (j=0;j<key;j++) {
 
            k=k*ct;
 
            k=k%n;
 
        }
 
        m[i]=k+96;
 
        
 
        i++;
 
    }
 
    m[i]=-1;
 

 
    for (i=0;m[i]!=-1;i++)
 
    printf("%c",m[i]);
 
}

int main(int argc, const char * argv[]) {
    //server side : we need to take input public and private parameters of server :
    //entering public and private key parameters for server-side :
    //we will be generating public key first :
    //    Our Public Key is made of n and e.
    //for that we need public key parameters p and q [TWO FAIRLY LARGE PRIME NUMBERS ]:
    int network_socket;
     //for tcp setting up socket
    network_socket = socket(AF_INET,SOCK_STREAM,0);

    //specify an address for the socket
    struct sockaddr_in server_address;

    server_address.sin_family=AF_INET;
    //specifying port as 9002
    server_address.sin_port=htons(9002);
    server_address.sin_addr.s_addr=INADDR_ANY;

    //connecting
    int connection_status = connect(network_socket,(struct sockaddr * ) &server_address , sizeof(server_address));
    //depend on the value of connection_status will get to know the status of connection

    //check for error with the connection
    
    if(connection_status==-1){
    printf("there is an error in connecting to the remote socket\n\n");}

    //if no error send or recieve data
    //recieving data from the server
    char server_response[256];
    recv(network_socket,&server_response,sizeof(server_response),0);
    
    //print out the server's response
        
//    listen(network_socket,5);

    printf("\n\nthe client sent the data : %s\n",server_response);
        recv(network_socket,&server_response,sizeof(server_response),0);
        printf("\n");
        printf("%s",server_response);
//    char sen[10]="11";
            
//    printf()
    printf("\nENTER THE SERVER PARAMETERS : ");
    printf("\n");
    printf("\nENTER FIRST PRIME NUMBER\n");
        scanf("%d",&p);
    flag=prime(p);
        if(flag==0) {
            printf("\nWRONG INPUT\n");
            exit(1);
        }
    printf("\nENTER ANOTHER PRIME NUMBER\n");
        scanf("%d",&q);
        flag=prime(q);
    char str[10];
    sprintf(str, "%d", p);
    send(network_socket,str,2,0);
    char str1[10];
    sprintf(str1, "%d", q);
    send(network_socket,str1,2,0);
        if(flag==0||p==q) {
            printf("\nWRONG INPUT\n");
            exit(1);
        }
    
    char enc_secret_key[40]="4AF5";
        for (i=0;enc_secret_key[i]!=NULL;i++)
     
        m[i]=enc_secret_key[i];
     
        n=p*q;
    //next is generating private key[d] :
    // for that we need prev values of p and q to calculate phi(n) and will calculate key using d = (k*Φ(n) + 1) / e ; this formula.
    t=(p-1)*(q-1);
 
int k;
 
    k=0;
 
    for (i=2;i<t;i++) {
 
        if(t%i==0)
 
            continue;
 
        flag=prime(i);
 
        if(flag==1&&i!=p&&i!=q) {
 
            e[k]=i;
 
            flag=cd(e[k]);
 
            if(flag>0) {
 
                d[k]=flag;
 
                k++;
 
            }
 
            if(k==99)
 
                    break;
 
        }
 
    }
 
    printf("\nPOSSIBLE VALUES OF e AND d ARE\n");
 
    for (i=0;i<j-1;i++)
 
    printf("\n%ld\t%ld",e[i],d[i]);
    //AND  we will choose the first one
//    char key="1234";
    printf("\nENCRYPTED SECRET KEY : ");
    encrypt1(enc_secret_key);
    printf("\n");
//    char server_response1[100];
//    recv(network_socket,&server_response1,sizeof(server_response1),0);
//    printf("%s",server_response1);
    printf("\nTHE SECRET KEY IS : ");
    decrypt();
    printf("\n");
    int cipher[16]={0 ,0 ,1 ,0 ,0 ,1, 0 ,0, 1, 1, 1, 0, 1, 1, 0, 0 };
    int r0[16]={0};
    int key_arr[16]={0};
    char key[40];
    key[0]=m[0];
    key[1]=m[1];
    key[2]=m[2];
    key[3]=m[3];
    const char *hexkey = &key[0];
    
    int numkey = (int)strtol(hexkey, NULL, 16);

//    printf("%d",numkey);
    //converting decimal to binary :
    int z=0;
    while(numkey>0){
        if(numkey%2==0)
        key_arr[15-z]=0;
        else
            key_arr[15-z]=1;
        numkey=numkey/2;
        z++;
    }
    z=0;
    
    //converting decimal to binary
    //splitting input key to w0 and w1 ;
    int w0[8],w1[8];
    for(int i=0;i<=7;i++){
        w0[i]=key_arr[i];
    }
    for(int i=8;i<16;i++){
        w1[i-8]=key_arr[i];
    }
    //for w2 :
    int rcon_1[8]={1,0,0,0,0,0,0,0};
    int rot_nib_w1[8]={0};
    for(int i=0;i<4;i++){
        rot_nib_w1[i+4]=w1[i];
    }
    for(int i=4;i<8;i++){
        rot_nib_w1[i-4]=w1[i];
    }
    //defining the s-box
    int sbox[4][4]={{9,4,10,11},{13,1,8,5},{6,2,0,3},{12,14,15,7}};
    //for accessing s-box
    int cnt1=0;
    int cnt2=0;
    for(int i =3;i>=0;i--){
        cnt1+=rot_nib_w1[i]*pow(2,3-i);
    }

    for(int i =7;i>=4;i--){
        cnt2+=rot_nib_w1[i]*pow(2,7-i);
    }

    int z1=0;
    //subnib values :
    int subnib_ar[8]={0};
    int subnib=0;
    int subnib2=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            z1++;
            if(z1==cnt1+1){
                subnib=sbox[i][j];

            }
        }
    }
    z1=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            z1++;
            if(z1==cnt2+1){
                subnib2=sbox[i][j];

            }
        }
    }
    z=0;
    while(subnib>0){
        if(subnib%2==0)
        subnib_ar[3-z]=0;
        else
            subnib_ar[3-z]=1;
        subnib=subnib/2;
        z++;
    }
    z=z-1;
    z=0;
    while(subnib2>0){
        if(subnib2%2==0)
        subnib_ar[7-z]=0;
        else
            subnib_ar[7-z]=1;
        subnib2=subnib2/2;
        z++;
    }

    
    //S-AES key generation :
    //now calculating the w2 :
    //w2 = w0 xor rcon xor subnib_ar
    int w2[8]={0};
    for(int i=0;i<8;i++){
        w2[i]=w0[i]^rcon_1[i]^subnib_ar[i];
    }

    
    int w3[8];
    for(int i=0;i<8;i++){
        w3[i]=w2[i]^w1[i];
    }

    //now similarly will find for w4 and w5 :
    int rcon_2[8]={0,0,1,1,0,0,0,0};
    
    int rot_nib_w3[8]={0};
    for(int i=0;i<4;i++){
        rot_nib_w3[i+4]=w3[i];
    }
    for(int i=4;i<8;i++){
        rot_nib_w3[i-4]=w3[i];
    }
    int subnib_ar_w3[8]={0};
    int subnib_w3=0;
    int subnib2_w3=0;
    cnt1=0;
    cnt2=0;
    for(int i =3;i>=0;i--){
        cnt1+=rot_nib_w3[i]*pow(2,3-i);
    }
    
    for(int i =7;i>=4;i--){
        cnt2+=rot_nib_w3[i]*pow(2,7-i);
    }
    z1=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            z1++;
            if(z1==cnt1+1){
                subnib_w3=sbox[i][j];
                
            }
        }
    }
    z1=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            z1++;
            if(z1==cnt2+1){
                subnib2_w3=sbox[i][j];
                
            }
        }
    }
    z=0;
    
    while(subnib_w3>0){
        if(subnib_w3%2==0)
        subnib_ar_w3[3-z]=0;
        else
            subnib_ar_w3[3-z]=1;
        subnib_w3=subnib_w3/2;
        z++;
    }
    z=z-1;
    z=0;
    while(subnib2_w3>0){
        if(subnib2_w3%2==0)
        subnib_ar_w3[7-z]=0;
        else
            subnib_ar_w3[7-z]=1;
        subnib2_w3=subnib2_w3/2;
        z++;
    }
    //w4 :
    int w4[8];
    for(int i=0;i<8;i++){
        w4[i]=w2[i]^rcon_2[i]^subnib_ar_w3[i];
    }

    //w5 :
    int w5[8]={0};
    for(int i=0;i<8;i++){
        w5[i]=w4[i]^w3[i];
    }

    //for key0 :
    int key0[16];
    for(int i=0;i<8;i++)
    key0[i]=w0[i];
    for(int i=8;i<16;i++)
    key0[i]=w1[i-8];
    //for key1 :
    int key1[16];
    for(int i=0;i<8;i++)
    key1[i]=w2[i];
    for(int i=8;i<16;i++)
    key1[i]=w3[i-8];
    //for key2 :
    int key2[16];
    for(int i=0;i<8;i++)
    key2[i]=w4[i];
    for(int i=8;i<16;i++)
    key2[i]=w5[i-8];
    //all the keys generated
    for(int i=0;i<16;i++){
        r0[i]=cipher[i]^key2[i];
    }
    printf("\n\nAFTER PRE-ROUND TRANSFORMATION : ");
    printf("\n\nROUND KEY K2 : ");
    for(int i=0;i<16;i++)
    printf("%d ",key2[i]);
    
//    for(int i=0;i<16;i++)
//    printf("%d",r0[i]);
    //round : 1 - inverse shift row :
    
    int shrow2[16];
    for(int i=0;i<4;i++)
    shrow2[i]=r0[i];
    for(int i=8;i<12;i++)
    shrow2[i]=r0[i];
    for(int i=4;i<=7;i++)
    shrow2[i]=r0[8+i];
    for(int i=12;i<16;i++)
    shrow2[i]=r0[i-8];
    printf("\n");
    printf("\nAFTER ROUND 1 INVSHIFT ROWS : ");
    for(int i=0;i<16;i++)
    printf("%d ",shrow2[i]);
    int inv_sbox[4][4]={{10,5,9,11},{1,7,8,15},{6,0,2,3},{12,4,13,14}};
    //round 1 : inverse nibble substitution :
     cnt1=0;
     cnt2=0;
    int cnt3=0;
    int cnt4=0;
    z=0;z1=0;
    int subnb1,subnb2,subnb3,subnb4;
    for(int i =3;i>=0;i--){
        cnt1+=shrow2[i]*pow(2,3-i);
    }
    for(int i =7;i>=4;i--){
        cnt2+=shrow2[i]*pow(2,7-i);
    }
    for(int i =11;i>=8;i--){
        cnt3+=shrow2[i]*pow(2,11-i);
    }
    for(int i =15;i>=12;i--){
        cnt4+=shrow2[i]*pow(2,15-i);
    }
    z1=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            z1++;
            if(z1==cnt1+1){
                subnb1=inv_sbox[i][j];
//                cout<<sbox[i][j];
            }
        }
    }
    z1=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            z1++;
            if(z1==cnt2+1){
                subnb2=inv_sbox[i][j];
//                cout<<sbox[i][j];
            }
        }
    }
    z1=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            z1++;
            if(z1==cnt3+1){
                subnb3=inv_sbox[i][j];
//                cout<<sbox[i][j];
            }
        }
    }
    z1=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            z1++;
            if(z1==cnt4+1){
                subnb4=inv_sbox[i][j];
//                cout<<sbox[i][j];
            }
        }
    }
    z=0;
    int subnib_round2[16]={0};
    while(subnb1>0){
        if(subnb1%2==0)
        subnib_round2[3-z]=0;
        else
            subnib_round2[3-z]=1;
        subnb1/=2;
        z++;
    }
    z=0;
    while(subnb2>0){
        if(subnb2%2==0)
            subnib_round2[7-z]=0;
        else
            subnib_round2[7-z]=1;
        subnb2/=2;
        z++;
    }
    z=0;
    while(subnb3>0){
        if(subnb3%2==0)
            subnib_round2[11-z]=0;
        else
            subnib_round2[11-z]=1;
        subnb3/=2;
        z++;
    }
    z=0;
    while(subnb4>0){
        if(subnb4%2==0)
            subnib_round2[15-z]=0;
        else
            subnib_round2[15-z]=1;
        subnb4/=2;
        z++;
    }
    printf("\n");
    printf("\nAFTER ROUND 1 INVSUBSTITUTE NIBBLES : ");
    for(int i=0;i<16;i++)
    printf("%d ",subnib_round2[i]);
    //add round : 1 key
    

    int add_round[16];
    for(int i=0;i<16;i++){
        add_round[i]=key1[i]^subnib_round2[i];
    }
    printf("\n");
    printf("\nAFTER ROUND 1 INVADD ROUND KEY : ");
    for(int i=0;i<16;i++)
    printf("%d ",add_round[i]);
    //round 1 : inverse mix columns :
    int decr[3][15]={{2,4,6,8,10,12,14,3,1,7,5,11,9,15,13},{4,8,12,3,7,11,15,6,2,14,10,5,1,13,9},{9,1,8,2,11,3,10,4,13,5,12,6,15,7,14}};
    int comp1[4]={0},comp10[4]={0},comp2[4]={0},comp20[4]={0},comp3[4]={0},comp30[4]={0},comp4[4]={0},comp40[4]={0};
    int comp100[4]={0},comp200[4]={0},comp300[4]={0},comp400[4]={0};
    for(int i=0;i<4;i++)
    comp1[i]=add_round[i];
    for(int i=4;i<8;i++)
    comp2[i-4]=add_round[i];
    for(int i=8;i<12;i++)
    comp3[i-8]=add_round[i];
    for(int i=12;i<16;i++)
    comp4[i-12]=add_round[i];
    int number2=0,number3=0,number1=0,number4=0;
    for(int i =3;i>=0;i--){
        number1+=add_round[i]*pow(2,3-i);
    }
    for(int i =15;i>=12;i--){
        number4+=add_round[i]*pow(2,15-i);
    }
    for(int i =7;i>=4;i--){
        number2+=add_round[i]*pow(2,7-i);
    }
    for(int i =11;i>=8;i--){
        number3+=add_round[i]*pow(2,11-i);
    }
    number1-=1;
    number1=decr[2][number1];
     z=0;
    while(number1>0){
        if(number1%2==0)
            comp100[3-z]=0;
        else
            comp100[3-z]=1;
        z++;
        number1/=2;
    }
//    recv(network_socket,&server_response,sizeof(server_response),0);
//    recv(network_socket,&server_response,sizeof(server_response),0);
    //number 2 for comp1:
    for(int i =3;i>=0;i--){
        number1+=add_round[i]*pow(2,3-i);
    }
    number1-=1;
    number1=decr[0][number1];
     z=0;
    while(number1>0){
        if(number1%2==0)
            comp10[3-z]=0;
        else
            comp10[3-z]=1;
        z++;
        number1/=2;
    }
        //comp2
    number2-=1;
    number2=decr[0][number2];
    z=0;
    while(number2>0){
        if(number2%2==0)
            comp20[3-z]=0;
        else
            comp20[3-z]=1;
        z++;
        number2/=2;
    }
        for(int i =7;i>=4;i--){
            number2+=add_round[i]*pow(2,7-i);
        }
        number2-=1;
        number2=decr[2][number2];
        z=0;
        while(number2>0){
            if(number2%2==0)
                comp200[3-z]=0;
            else
                comp200[3-z]=1;
            z++;
            number2/=2;
        }
        //comp3 :
        number3-=1;
        number3=decr[0][number3];
        z=0;
        while(number3>0){
            if(number3%2==0)
                comp30[3-z]=0;
            else
                comp30[3-z]=1;
            z++;
            number3/=2;
        }
        for(int i =11;i>=8;i--){
            number3+=add_round[i]*pow(2,11-i);
        }
            number3-=1;
            number3=decr[2][number3];
            z=0;
            while(number3>0){
                if(number3%2==0)
                    comp300[3-z]=0;
                else
                    comp300[3-z]=1;
                z++;
                number3/=2;
            }
        //comp4 :
        number4-=1;
        number4=decr[0][number4];
        z=0;
        while(number4>0){
            if(number4%2==0)
                comp40[3-z]=0;
            else
                comp40[3-z]=1;
            z++;
            number4/=2;
        }
        for(int i =15;i>=12;i--){
            number4+=add_round[i]*pow(2,15-i);
        }
            number4-=1;
            number4=decr[2][number4];
            z=0;
            while(number4>0){
                if(number4%2==0)
                    comp400[3-z]=0;
                else
                    comp400[3-z]=1;
                z++;
                number4/=2;
            }
    int mix_cols[16];
    for(int i=0;i<4;i++)
    mix_cols[i]=comp100[i]^comp20[i];
    
    printf("\n\nROUND KEY K1 : ");
    for(int i=0;i<16;i++)
    printf("%d ",key1[i]);
    printf("\n\n%s","AFTER ROUND 1 INVMIX COLUMNS : ");
    for(int i=4;i<8;i++){
        mix_cols[i]=comp10[i-4]^comp200[i-4];
//        printf("%d ",mix_cols[i]);
    }
    
    
    for(int i=8;i<12;i++)
    mix_cols[i]=comp300[i-8]^comp40[i-8];
   
    for(int i=12;i<16;i++)
    mix_cols[i]=comp30[i-12]^comp400[i-12];
//    printf("\n%s","mix cols : ");
    for(int i=0;i<16;i++)
    printf("%d ",mix_cols[i]);
    //round 2 :
    //inverse shift row :
    int ishrow2[16];
    for(int i=0;i<4;i++)
    ishrow2[i]=mix_cols[i];
    for(int i=8;i<12;i++)
    ishrow2[i]=mix_cols[i];
    for(int i=4;i<=7;i++)
    ishrow2[i]=mix_cols[8+i];
    for(int i=12;i<16;i++)
    ishrow2[i]=mix_cols[i-8];
    printf("\n\n%s","AFTER ROUND 2 INVSHIFT ROWS : ");
    for(int i=0;i<16;i++)
    printf("%d ",ishrow2[i]);
    //round 2 : inverse nibble sub :
    cnt1=0;
    cnt2=0;
    cnt3=0;
    cnt4=0;
    for(int i =3;i>=0;i--){
        cnt1+=ishrow2[i]*pow(2,3-i);
    }
    for(int i =7;i>=4;i--){
        cnt2+=ishrow2[i]*pow(2,7-i);
    }
    for(int i =11;i>=8;i--){
        cnt3+=ishrow2[i]*pow(2,11-i);
    }
    for(int i =15;i>=12;i--){
        cnt4+=ishrow2[i]*pow(2,15-i);
    }
    z1=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            z1++;
            if(z1==cnt1+1){
                subnb1=inv_sbox[i][j];
            }
        }
    }
    z1=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            z1++;
            if(z1==cnt2+1){
                subnb2=inv_sbox[i][j];
            }
        }
    }
    int f=0;
    z1=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            z1++;
            if(z1==cnt3+1){
                subnb3=inv_sbox[i][j];
            }
        }
    }
    z1=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            z1++;
            if(z1==cnt4+1){
                subnb4=inv_sbox[i][j];
            }
        }
    }
    z=0;
    int isubnib_round2[16]={0};
    
    while(subnb1>0){
        if(subnb1%2==0)
        isubnib_round2[3-z]=0;
        else
            isubnib_round2[3-z]=1;
        subnb1/=2;
        z++;
    }
    z=0;
    while(subnb2>0){
        if(subnb2%2==0)
            isubnib_round2[7-z]=0;
        else
            isubnib_round2[7-z]=1;
        subnb2/=2;
        z++;
    }
    z=0;
    while(subnb3>0){
        if(subnb3%2==0)
            isubnib_round2[11-z]=0;
        else
            isubnib_round2[11-z]=1;
        subnb3/=2;
        z++;
    }
    z=0;
    
    while(subnb4>0){
        if(subnb4%2==0)
            isubnib_round2[15-z]=0;
        else
            isubnib_round2[15-z]=1;
        subnb4/=2;
        z++;
    }
    printf("\n");
    printf("\nAFTER ROUND 2 SUBSTITUTE NIBBLES : ");
    
    for(int i=0;i<16;i++)
    printf("%d ",isubnib_round2[i]);
    //add round 2 key :
    

    int r2[16];
    for(int i=0;i<16;i++){
        r2[i]=isubnib_round2[i]^key0[i];
    }
    printf("\n\nAFTER ROUND 2 ADD ROUND KEY : ");
    for (int i=0; i<16; i++) {
        printf("%d ",r2[i]);
    }
    printf("\n");
    printf("\nROUND KEY K0 : ");
    for (int i=0; i<16; i++) {
        printf("%d ",key0[i]);
    }
    printf("\n\nPLAINTEXT : ");
    //plaintext :
    cnt1=0;
    cnt2=0;
    cnt3=0;
    cnt4=0;
    char message1[40];
    for(int i=3;i>=0;i--){
        cnt1+=r2[i]*pow(2,3-i);
    }
    for(int i =7;i>=4;i--){
        cnt2+=r2[i]*pow(2,7-i);
    }
    for(int i =11;i>=8;i--){
        cnt3+=r2[i]*pow(2,11-i);
    }
    for(int i =15;i>=12;i--){
        cnt4+=r2[i]*pow(2,15-i);
    }
//    printf("%d %d %d %d ",cnt1,cnt2,cnt3,cnt4);
    k=0;
    if(cnt1>9){
        printf("%c",(cnt1-10+65));
        message1[k++]=(cnt1-10+65);
    }
    if(cnt1<=9){
        printf("%d",cnt1);
        message1[k++]=(cnt1);
    }
    if(cnt2>9){
        printf("%c",(cnt2-10+65));
        message1[k++]=(cnt2-10+65);
    }
    if(cnt2<=9){
        printf("%d",cnt2);
        message1[k++]=(cnt2);
    }
    if(cnt3>9){
        printf("%c",(cnt3-10+65));
        message1[k++]=(cnt3-10+65);
    }
    if(cnt3<=9){
        printf("%d",cnt3);
        message1[k++]=(cnt3);
    }
    if(cnt4>9){
        printf("%c",(cnt4-10+65));
        message1[k++]=(cnt3-10+65);
    }
    if(cnt4<=9){
        printf("%d",cnt4);
        message1[k++]=(cnt4);
    }
    int len=0;
    for(int i=0;message1[i]!='\0';i++){
        len++;
    }
    for(int i=0;i<len;i++){
        message1[i]=(char)(message1[i]+1);
    }
        printf("\nDIGEST : ");
        
    printf("%s",message1);printf("839");
        printf("\n");
    for (i=0;message1[i]!=NULL;i++)
 
    m[i]=message1[i];
    p=17;
    q=11;
    n=p*q;
//next is generating private key[d] :
// for that we need prev values of p and q to calculate phi(n) and will calculate key using d = (k*Φ(n) + 1) / e ; this formula.
 
    t=(p-1)*(q-1);
 

 
    k=0;
 
    for (i=2;i<t;i++) {
 
        if(t%i==0)
 
            continue;
 
        flag=prime(i);
 
        if(flag==1&&i!=p&&i!=q) {
 
            e[k]=i;
 
            flag=cd(e[k]);
 
            if(flag>0) {
 
                d[k]=flag;
 
                k++;
 
            }
 
            if(k==99)
 
                    break;
 
        }
 
    }
    
    //digest to convert and into signature and need to verify the digital signature then :
    long int en_prev[100];
    for (i=0;en[i]!=-1;i++)
    en_prev[i]=en[i];
    printf("\nSIGNATURE GENERATED : ");
    encrypt1(message1);
    //transmitted signature from client side if same will result in verified other wise will go in else part.
    if(f==0)
        printf("\nSIGNATURE VERIFIED\n");
    else
        printf("\nSIGNATURE UN-VERIFIED\n");
    
    //closing the socket

    close(network_socket);
    return 0;
}
