#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include <fcntl.h> // for open
#include <unistd.h>//for close
#include <string.h>
#include <math.h>
long int p,q,n,t,flag,e[100],d[100],temp[100],j,m[100],en[100],i;
void encrypt1(char *message) {//encrpyts or creates signature in rsa
 
    long int pt,ct,key=e[0],k,len;
 
    i=0;
 
    len=strlen(message);
 
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
 
}
 
void decrypt() {//decrypts in rsa
 
    long int pt,ct,key=d[0],k;
 
    i=0;
 
    while(en[i]!=-1) {
 
        ct=temp[i];
 
        k=1;
 
        for (j=0;j<key;j++) {
 
            k=k*ct;
 
            k=k%n;
 
        }
 
        pt=k+96;
 
        m[i]=pt;
 
        i++;
 
    }
 
    m[i]=-1;
 

 
    for (i=0;m[i]!=-1;i++)
 
    printf("%c",m[i]);
 
}
long int cd(long int x) {
 
    long int k=1;
 
    while(1) {
 
        k=k+t;
 
        if(k%x==0)
 
            return(k/x);
 
    }
 
}
int prime(long int pr) {//checks prime or not for rsa , if not code is terminated
    int i;
    j=sqrt(pr);
    for (i=2;i<=j;i++) {
        if(pr%i==0)
            return 0;
    }
    return 1;
}
int main(){
    //starting from asking the parameters from the server and will use them as given in the flow diagram.
char server_message[256]="you have reached the server";
    int server_socket;
    printf("\nWAITING FOR SERVER PARAMETERS :  \n");
    server_socket=socket(AF_INET,SOCK_STREAM,0);

    //define the server address

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port=htons(9002);
    server_address.sin_addr.s_addr=INADDR_ANY;

    //bind the socket to our specified IP and port

    bind(server_socket,(struct sockaddr*) &server_address,sizeof(server_address));

    //listening the connections

    listen(server_socket,5);

    int client_socket;
    client_socket=accept(server_socket,NULL,NULL);

    //sending message
    send(client_socket,server_message,sizeof(server_message),0);
        char server_message1[256]="SEND THE PUBLIC PARAMETERS : ";
        send(client_socket,server_message1,sizeof(server_message1),0);
        char server_response[256]="";
        recv(client_socket,&server_response,sizeof(server_response),0);
    printf("\nSERVER PARAMETERS RECEIVED : ");
        printf("\n%s\n",server_response);
    char p_new[2];
    p_new[0]=server_response[0];
    p_new[1]=server_response[1];
    //p received need to convert
//    memset(server_response, 0, 255);
    recv(client_socket,&server_response,sizeof(server_response),0);
//    printf("\n%s\n",server_response);
//    printf("and %s\n",server_response);
    char q_new[2];
    q_new[0]=server_response[2];
    q_new[1]=server_response[3];
    //q received need to convert
//algorithm starts :
    printf("INPUT PLAINTEXT : ");
    char message[40]="";
//    printf("here");
    scanf("%s",message);
//    printf("here");
    int i=0;
    int max=-10;
    while(message[i]!='\0'){
        if(message[i]>max)
            max=message[i];
        i++;
    }
    
    printf("INPUT CIPHER KEY : ");
    
    char key[40];
    scanf("%s",key);
    
    printf("\nAFTER PRE-ROUND TRANSFORMATION : ");
    int msg[16]={0};
    int key_arr[16]={0};
    const char *hexkey = &key[0];
    const char *hexmsg = &message[0];
    int numkey = (int)strtol(hexkey, NULL, 16);
    int nummsg = (int)strtol(hexmsg, NULL, 16);
    if(max<97){//code for hexadecimal plaintext of 16 bits :
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
    while(nummsg>0){
        if(nummsg%2==0)
        msg[15-z]=0;
        else
            msg[15-z]=1;
        nummsg=nummsg/2;
        z++;
    }
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
    //displaying key values :
    printf("\n\nROUND KEY K0 :");
    for(int i=0;i<16;i++)
    printf("%d ",key0[i]);
    
    
//    printf("\np:");
//    for(int i=0;i<16;i++)
//    printf("%d",msg[i]);
    //round 0 :
    int r0[16];
    for(int i=0;i<16;i++){
        r0[i]=msg[i]^key0[i];
    }
//    printf("\nR0 :");
//    for(int i=0;i<16;i++)
//    printf("%d",r0[i]);
    //ROUND 1 :
    //nibble substitution for round1 :
    int subnib_round2[16]={0};
    cnt1=0;
    cnt2=0;
    int cnt3=0;
    int cnt4=0;
    for(int i =3;i>=0;i--){
        cnt1+=r0[i]*pow(2,3-i);
    }
    for(int i =7;i>=4;i--){
        cnt2+=r0[i]*pow(2,7-i);
    }
    for(int i =11;i>=8;i--){
        cnt3+=r0[i]*pow(2,11-i);
    }
    for(int i =15;i>=12;i--){
        cnt4+=r0[i]*pow(2,15-i);
    }
    //round 1 : substituting nibble values :
    int subnib_array[16]={0};
    int subnb1=0,subnb2=0,subnb3=0,subnb4=0;
    z1=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            z1++;
            if(z1==cnt1+1){
                subnb1=sbox[i][j];

            }
        }
    }
    z1=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            z1++;
            if(z1==cnt2+1){
                subnb2=sbox[i][j];

            }
        }
    }
    z1=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            z1++;
            if(z1==cnt3+1){
                subnb3=sbox[i][j];

            }
        }
    }
    z1=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            z1++;
            if(z1==cnt4+1){
                subnb4=sbox[i][j];

            }
        }
    }
    z=0;
    while(subnb1>0){
        if(subnb1%2==0)
        subnib_array[3-z]=0;
        else
            subnib_array[3-z]=1;
        subnb1=subnb1/2;
        z++;
    }
    z=0;
    while(subnb2>0){
        if(subnb2%2==0)
        subnib_array[7-z]=0;
        else
            subnib_array[7-z]=1;
        subnb2=subnb2/2;
        z++;
    }
    z=0;
    while(subnb3>0){
        if(subnb3%2==0)
        subnib_array[11-z]=0;
        else
            subnib_array[11-z]=1;
        subnb3=subnb3/2;
        z++;
    }
    z=0;
    while(subnb4>0){
        if(subnb4%2==0)
        subnib_array[15-z]=0;
        else
            subnib_array[15-z]=1;
        subnb4=subnb4/2;
        z++;
    }
    printf("\n\nAFTER ROUND 1 SUBSTITUTE NIBBLES :  ");
    for(int i=0;i<16;i++)
    printf("%d ",subnib_array[i]);
    //round1 : shift row : swap 2nd and 4th nibble -
    int shrow[16];
    for(int i=0;i<4;i++)
    shrow[i]=subnib_array[i];
    for(int i=8;i<12;i++)
    shrow[i]=subnib_array[i];
    for(int i=4;i<=7;i++)
    shrow[i]=subnib_array[8+i];
    for(int i=12;i<16;i++)
    shrow[i]=subnib_array[i-8];
    printf("\n\nAFTER ROUND 1 SHIFT ROWS : ");
    for(int i=0;i<16;i++)
    printf("%d ",shrow[i]);
    //round 1 : mix columns :
    int mix_col_table[3][15]={{2,4,6,8,10,12,14,3,1,7,5,11,9,15,13},{4,8,12,3,7,11,15,6,2,14,10,5,1,13,9},{9,1,8,2,11,3,10,4,13,5,12,6,15,7,14}};
    int comp1[4],comp2[4],comp3[4],comp4[4];
    int comp10[4],comp20[4],comp30[4],comp40[4];
    int number2=0,number3=0,number1=0,number4=0;
        int mix_cols[16];
    
    for(int i=0;i<4;i++)
    comp1[i]=shrow[i];
    for(int i=4;i<8;i++)
    comp2[i-4]=shrow[i];
    for(int i=8;i<12;i++)
    comp3[i-8]=shrow[i];
    for(int i=12;i<16;i++)
    comp4[i-12]=shrow[i];
    
    for(int i =3;i>=0;i--){
        number1+=shrow[i]*pow(2,3-i);
    }
    for(int i =15;i>=12;i--){
        number4+=shrow[i]*pow(2,15-i);
    }
    for(int i =7;i>=4;i--){
        number2+=shrow[i]*pow(2,7-i);
    }
    for(int i =11;i>=8;i--){
        number3+=shrow[i]*pow(2,11-i);
    }
    number2-=1;
    number2=mix_col_table[1][number2];
    number1-=1;
    number1=mix_col_table[1][number1];
    number3-=1;
    number3=mix_col_table[1][number3];
    number4-=1;
    number4=mix_col_table[1][number4];
    z=0;
    while(number1>0){
        if(number1%2==0)
            comp10[3-z]=0;
        else
            comp10[3-z]=1;
        z++;
        number1/=2;
    }
    z=0;
    while(number2>0){
        if(number2%2==0)
            comp20[3-z]=0;
        else
            comp20[3-z]=1;
        z++;
        number2/=2;
    }
    z=0;
    while(number3>0){
        if(number3%2==0)
            comp30[3-z]=0;
        else
            comp30[3-z]=1;
        z++;
        number3/=2;
    }
    z=0;
    while(number4>0){
        if(number4%2==0)
            comp40[3-z]=0;
        else
            comp40[3-z]=1;
        z++;
        number4/=2;
    }
    for(int i=0;i<4;i++){
        mix_cols[i]=comp1[i]^comp20[i];
    }

    for(int i=4;i<8;i++){
        mix_cols[i]=comp10[i-4]^comp2[i-4];
    }

    for(int i=8;i<12;i++){
        mix_cols[i]=comp3[i-8]^comp40[i-8];
    }
    for(int i=12;i<16;i++)
    mix_cols[i]=comp30[i-12]^comp4[i-12];
    printf("\n\nAFTER ROUND 1 MIX COLUMNS : ");
    for(int i=0;i<16;i++)
    printf("%d ",mix_cols[i]);
    //round 1 : add round key 1 -
    int r1[16];
    for(int i=0;i<16;i++){
        r1[i]=key1[i]^mix_cols[i];
    }
    printf("\n\nADD ROUND 1 ADD ROUND KEY : ");
    for(int i=0;i<16;i++)
    printf("%d ",r1[i]);
    printf("\n\nROUND KEY K1 :");
    for(int i=0;i<16;i++)
    printf("%d ",key1[i]);
    //round 2 :
    //nibble substitution :
    cnt1=0;
    cnt2=0;
    cnt3=0;
    cnt4=0;
    for(int i =3;i>=0;i--){
        cnt1+=r1[i]*pow(2,3-i);
    }
    for(int i =7;i>=4;i--){
        cnt2+=r1[i]*pow(2,7-i);
    }
    for(int i =11;i>=8;i--){
        cnt3+=r1[i]*pow(2,11-i);
    }
    for(int i =15;i>=12;i--){
        cnt4+=r1[i]*pow(2,15-i);
    }
    z1=0;
    
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            z1++;
            if(z1==cnt1+1){
                subnb1=sbox[i][j];

            }
        }
    }
    z1=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            z1++;
            if(z1==cnt2+1){
                subnb2=sbox[i][j];

            }
        }
    }
    z1=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            z1++;
            if(z1==cnt3+1){
                subnb3=sbox[i][j];

            }
        }
    }
    z1=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            z1++;
            if(z1==cnt4+1){
                subnb4=sbox[i][j];

            }
        }
    }
    z=0;

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
    printf("\n\nAFTER ROUND 2 SUBSTITUTE NIBBLES :  ");
    for(int i=0;i<16;i++)
    printf("%d ",subnib_round2[i]);
    //round : 2 shift row -
    int shrow2[16];
    for(int i=0;i<4;i++)
    shrow2[i]=subnib_round2[i];
    for(int i=8;i<12;i++)
    shrow2[i]=subnib_round2[i];
    for(int i=4;i<=7;i++)
    shrow2[i]=subnib_round2[8+i];
    for(int i=12;i<16;i++)
    shrow2[i]=subnib_round2[i-8];
    printf("\n\nAFTER ROUND 2 SHIFT ROWS :  ");
    for(int i=0;i<16;i++)
    printf("%d ",shrow2[i]);
    //round 2 - add round key to generate cipher text :
    int r2[16];
    for(int i=0;i<16;i++){
        r2[i]=key2[i]^shrow2[i];
    }
    printf("\n\nROUND KEY K2 :");
    for(int i=0;i<16;i++)
    printf("%d ",key2[i]);
    printf("\n\nCIPHER TEXT : ");
    for(int i=0;i<16;i++){
        printf("%d ",r2[i]);
    }
    }
    //code for sentences
    else{
        int len=0;
        int i=0;
        while(message[i]!='\0'){
            len++;
            i++;
        }
        int a,b;
        i=0;
        for( i=0;i<len;i+=2){
            printf("\n");
            printf("%c %c",message[i],message[i+1]);
            a=(int)message[i];
            if(i+1!=len){
                 b=(int)message[i+1];}
            else
                b=0;
            int first[8]={0};
            int second[8]={0};
            int z=0;
            while(a>0){
                if(a%2==0)
                first[7-z]=0;
                else
                    first[7-z]=1;
                a=a/2;
                z++;
            }
            z=0;
            while(b>0){
                if(b%2==0)
                second[7-z]=0;
                else
                    second[7-z]=1;
                b=b/2;
                z++;
            }
            int msg[16];
            for(int j=0;j<8;j++)
            msg[j]=first[j];
            for(int j=8;j<16;j++)
            msg[j]=second[j-8];
            printf("\n");
            for(int j=0;j<16;j++)
            printf("%d",msg[j]);
            //converting decimal to binary :
            z=0;
            while(numkey>0){
                if(numkey%2==0)
                key_arr[15-z]=0;
                else
                    key_arr[15-z]=1;
                numkey=numkey/2;
                z++;
            }
            z=0;
            while(nummsg>0){
                if(nummsg%2==0)
                msg[15-z]=0;
                else
                    msg[15-z]=1;
                nummsg=nummsg/2;
                z++;
            }
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
            //displaying key values :
            printf("\n\nROUND KEY K0 :");
            for(int i=0;i<16;i++)
            printf("%d ",key0[i]);
            
            
        //    printf("\np:");
        //    for(int i=0;i<16;i++)
        //    printf("%d",msg[i]);
            //round 0 :
            int r0[16];
            for(int i=0;i<16;i++){
                r0[i]=msg[i]^key0[i];
            }
        //    printf("\nR0 :");
        //    for(int i=0;i<16;i++)
        //    printf("%d",r0[i]);
            //ROUND 1 :
            //nibble substitution for round1 :
            int subnib_round2[16]={0};
            cnt1=0;
            cnt2=0;
            int cnt3=0;
            int cnt4=0;
            for(int i =3;i>=0;i--){
                cnt1+=r0[i]*pow(2,3-i);
            }
            for(int i =7;i>=4;i--){
                cnt2+=r0[i]*pow(2,7-i);
            }
            for(int i =11;i>=8;i--){
                cnt3+=r0[i]*pow(2,11-i);
            }
            for(int i =15;i>=12;i--){
                cnt4+=r0[i]*pow(2,15-i);
            }
            //round 1 : substituting nibble values :
            int subnib_array[16]={0};
            int subnb1=0,subnb2=0,subnb3=0,subnb4=0;
            z1=0;
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    z1++;
                    if(z1==cnt1+1){
                        subnb1=sbox[i][j];

                    }
                }
            }
            z1=0;
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    z1++;
                    if(z1==cnt2+1){
                        subnb2=sbox[i][j];

                    }
                }
            }
            z1=0;
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    z1++;
                    if(z1==cnt3+1){
                        subnb3=sbox[i][j];

                    }
                }
            }
            z1=0;
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    z1++;
                    if(z1==cnt4+1){
                        subnb4=sbox[i][j];

                    }
                }
            }
            z=0;
            while(subnb1>0){
                if(subnb1%2==0)
                subnib_array[3-z]=0;
                else
                    subnib_array[3-z]=1;
                subnb1=subnb1/2;
                z++;
            }
            z=0;
            while(subnb2>0){
                if(subnb2%2==0)
                subnib_array[7-z]=0;
                else
                    subnib_array[7-z]=1;
                subnb2=subnb2/2;
                z++;
            }
            z=0;
            while(subnb3>0){
                if(subnb3%2==0)
                subnib_array[11-z]=0;
                else
                    subnib_array[11-z]=1;
                subnb3=subnb3/2;
                z++;
            }
            z=0;
            while(subnb4>0){
                if(subnb4%2==0)
                subnib_array[15-z]=0;
                else
                    subnib_array[15-z]=1;
                subnb4=subnb4/2;
                z++;
            }
            printf("\n\nAFTER ROUND 1 SUBSTITUTE NIBBLES :  ");
            for(int i=0;i<16;i++)
            printf("%d ",subnib_array[i]);
            //round1 : shift row : swap 2nd and 4th nibble -
            int shrow[16];
            for(int i=0;i<4;i++)
            shrow[i]=subnib_array[i];
            for(int i=8;i<12;i++)
            shrow[i]=subnib_array[i];
            for(int i=4;i<=7;i++)
            shrow[i]=subnib_array[8+i];
            for(int i=12;i<16;i++)
            shrow[i]=subnib_array[i-8];
            printf("\n\nAFTER ROUND 1 SHIFT ROWS : ");
            for(int i=0;i<16;i++)
            printf("%d ",shrow[i]);
            //round 1 : mix columns :
            int mix_col_table[3][15]={{2,4,6,8,10,12,14,3,1,7,5,11,9,15,13},{4,8,12,3,7,11,15,6,2,14,10,5,1,13,9},{9,1,8,2,11,3,10,4,13,5,12,6,15,7,14}};
            int comp1[4],comp2[4],comp3[4],comp4[4];
            int comp10[4],comp20[4],comp30[4],comp40[4];
            int number2=0,number3=0,number1=0,number4=0;
                int mix_cols[16];
            
            for(int i=0;i<4;i++)
            comp1[i]=shrow[i];
            for(int i=4;i<8;i++)
            comp2[i-4]=shrow[i];
            for(int i=8;i<12;i++)
            comp3[i-8]=shrow[i];
            for(int i=12;i<16;i++)
            comp4[i-12]=shrow[i];
            
            for(int i =3;i>=0;i--){
                number1+=shrow[i]*pow(2,3-i);
            }
            for(int i =15;i>=12;i--){
                number4+=shrow[i]*pow(2,15-i);
            }
            for(int i =7;i>=4;i--){
                number2+=shrow[i]*pow(2,7-i);
            }
            for(int i =11;i>=8;i--){
                number3+=shrow[i]*pow(2,11-i);
            }
            number2-=1;
            number2=mix_col_table[1][number2];
            number1-=1;
            number1=mix_col_table[1][number1];
            number3-=1;
            number3=mix_col_table[1][number3];
            number4-=1;
            number4=mix_col_table[1][number4];
            z=0;
            while(number1>0){
                if(number1%2==0)
                    comp10[3-z]=0;
                else
                    comp10[3-z]=1;
                z++;
                number1/=2;
            }
            z=0;
            while(number2>0){
                if(number2%2==0)
                    comp20[3-z]=0;
                else
                    comp20[3-z]=1;
                z++;
                number2/=2;
            }
            z=0;
            while(number3>0){
                if(number3%2==0)
                    comp30[3-z]=0;
                else
                    comp30[3-z]=1;
                z++;
                number3/=2;
            }
            z=0;
            while(number4>0){
                if(number4%2==0)
                    comp40[3-z]=0;
                else
                    comp40[3-z]=1;
                z++;
                number4/=2;
            }
            for(int i=0;i<4;i++){
                mix_cols[i]=comp1[i]^comp20[i];
            }

            for(int i=4;i<8;i++){
                mix_cols[i]=comp10[i-4]^comp2[i-4];
            }

            for(int i=8;i<12;i++){
                mix_cols[i]=comp3[i-8]^comp40[i-8];
            }
            for(int i=12;i<16;i++)
            mix_cols[i]=comp30[i-12]^comp4[i-12];
            printf("\n\nAFTER ROUND 1 MIX COLUMNS : ");
            for(int i=0;i<16;i++)
            printf("%d ",mix_cols[i]);
            //round 1 : add round key 1 -
            int r1[16];
            for(int i=0;i<16;i++){
                r1[i]=key1[i]^mix_cols[i];
            }
            printf("\n\nADD ROUND 1 ADD ROUND KEY : ");
            for(int i=0;i<16;i++)
            printf("%d ",r1[i]);
            printf("\n\nROUND KEY K1 :");
            for(int i=0;i<16;i++)
            printf("%d ",key1[i]);
            //round 2 :
            //nibble substitution :
            cnt1=0;
            cnt2=0;
            cnt3=0;
            cnt4=0;
            for(int i =3;i>=0;i--){
                cnt1+=r1[i]*pow(2,3-i);
            }
            for(int i =7;i>=4;i--){
                cnt2+=r1[i]*pow(2,7-i);
            }
            for(int i =11;i>=8;i--){
                cnt3+=r1[i]*pow(2,11-i);
            }
            for(int i =15;i>=12;i--){
                cnt4+=r1[i]*pow(2,15-i);
            }
            z1=0;
            
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    z1++;
                    if(z1==cnt1+1){
                        subnb1=sbox[i][j];

                    }
                }
            }
            z1=0;
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    z1++;
                    if(z1==cnt2+1){
                        subnb2=sbox[i][j];

                    }
                }
            }
            z1=0;
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    z1++;
                    if(z1==cnt3+1){
                        subnb3=sbox[i][j];

                    }
                }
            }
            z1=0;
            for(int i=0;i<4;i++){
                for(int j=0;j<4;j++){
                    z1++;
                    if(z1==cnt4+1){
                        subnb4=sbox[i][j];

                    }
                }
            }
            z=0;

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
            printf("\n\nAFTER ROUND 2 SUBSTITUTE NIBBLES :  ");
            for(int i=0;i<16;i++)
            printf("%d ",subnib_round2[i]);
            //round : 2 shift row -
            int shrow2[16];
            for(int i=0;i<4;i++)
            shrow2[i]=subnib_round2[i];
            for(int i=8;i<12;i++)
            shrow2[i]=subnib_round2[i];
            for(int i=4;i<=7;i++)
            shrow2[i]=subnib_round2[8+i];
            for(int i=12;i<16;i++)
            shrow2[i]=subnib_round2[i-8];
            printf("\n\nAFTER ROUND 2 SHIFT ROWS :  ");
            for(int i=0;i<16;i++)
            printf("%d ",shrow2[i]);
            //round 2 - add round key to generate cipher text :
            int r2[16];
            for(int i=0;i<16;i++){
                r2[i]=key2[i]^shrow2[i];
            }
            printf("\n\nROUND KEY K2 :");
            for(int i=0;i<16;i++)
            printf("%d ",key2[i]);
            printf("\n\nCIPHER TEXT : ");
            for(int i=0;i<16;i++){
                printf("%d ",r2[i]);
            }
            
        }
    }
//hash algo to create digest :
    //hash algorithm is nothing but simply adding 1 to the ascii value , not a very complex hash algorithm just wanted to make it simple.
   
    int len=0;
    for(int i=0;message[i]!='\0';i++){
        len++;
    }
    for(int i=0;i<len;i++){
        message[i]=(char)(message[i]+1);
    }
    printf("\nREQUESTING SERVER PUBLIC KEY : ");
        printf("\n\nDIGEST : ");
        
        printf("%s",message);
        printf("\n");
    //entering public and private key parameters for client-side :
    //we will be generating public key first :
    //    Our Public Key is made of n and e.
    //for that we need public key parameters p and q [TWO FAIRLY LARGE PRIME NUMBERS ]:
    
    printf("\nENTER CLIENT PARAMETERS : \n");
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
        if(flag==0||p==q) {
            printf("\nWRONG INPUT\n");
            exit(1);
        }
    
     
        for (i=0;message[i]!=NULL;i++)
     
        m[i]=message[i];
     
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
     
        printf("\nPOSSIBLE VALUES OF e AND d ARE FOR DIGITAL SIGNATURE ARE : \n");
     
        for (i=0;i<j-1;i++)
     
        printf("\n%ld\t%ld",e[i],d[i]);
    //AND  we will choose the first one
    printf("\nTHE CLIENT SIGNATURE IS : ");
    encrypt1(message);
//    send(client_socket,en,sizeof(en),0);
    printf("\n\n");
    

    //encrypted secret key :

    const char *str = p_new;
        sscanf(str, "%d", &p);
    const char *str1 = q_new;
        sscanf(str1, "%d", &q);
    q/=100;
//    printf("\np and q : %d %d",p,q);
    for (i=0;key[i]!=NULL;i++)
 
    m[i]=key[i];
 
    n=p*q;

 
    t=(p-1)*(q-1);
 
//int k;
 
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
 
    printf("\nPOSSIBLE VALUES OF e AND d FOR EXNCRYPTED SECRET KEY ARE\n");
 
    for (i=0;i<j-1;i++)
 
    printf("\n%ld\t%ld",e[i],d[i]);
//AND  we will choose the first one
printf("\n\nTHE ECNCRYPTED SECRET KEY IS : ");
encrypt1(key);
printf("\n\n");
    printf("\nTRANSMITTING DETAILS TO SERVER....\n\n");
    char *encrypted_secret;
    char sec_key[10];
    k=0;
    for (i=0;en[i]!=-1;i++){
        sec_key[k++]=en[i];
    }
    encrypted_secret=sec_key;
//    send(client_socket,sec_key,k,0);
    
close(server_socket);
return 0;}
