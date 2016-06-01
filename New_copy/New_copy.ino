#include <LiquidCrystal.h>
int pin[14];
const int lcd_pin1=61;
const int lcd_pin2=56;
const int lcd_pin3=57;
const int lcd_pin4=58;
const int lcd_pin5=59;
const int lcd_pin6=60;
const int identify_pin=13;
const int test_pin=25;
const int green1=11;
const int green2=12;
const int red1=18;
const int red2=19;

LiquidCrystal lcd(lcd_pin1, lcd_pin2, lcd_pin3, lcd_pin4, lcd_pin5, lcd_pin6);
/* initialized a variable for each pin  */
/*
 * Function Details
 * pinMode(pin_no. , mode) : sets Mode of the given pin
 * digitalWite(pin_no. , HIGH/LOW) : write value to given pin. 
 * digitalRead(pin_no.) : read value from the given pin.
 */

void setup(){
  Serial.begin(9600);  
  lcd.begin(16, 2);
 // Print a message to the LCD.
  lcd.print("Welcome :) ...");
  delay(4000);
  lcd.clear();
  lcd.print("Press Button:");
  delay(1000);
  pinMode(identify_pin,INPUT);
  pinMode(test_pin,INPUT);
  pin[1]=3;
  pin[2]=4;
  pin[3]=5;
  pin[4]=6;
  pin[5]=7; 
  pin[6]=8;
  pin[8]=21;
  pin[9]=20;
  pin[10]=17;
  pin[11]=16;
  pin[12]=15;
  pin[13]=14;
  pinMode(red1,OUTPUT);
  pinMode(red2,OUTPUT);
  pinMode(green1,OUTPUT);
  pinMode(green2,OUTPUT);
  digitalWrite(red1,0);
  digitalWrite(red2,0);
  digitalWrite(green1,0);
  digitalWrite(green2,0);
}
int checkFourInput();
int checkTripleInput();
void loop()
{
   int check=0;
  check=checkFourInput();            // check if IC is triple INPUT
  if(check==1){
    loop();
    
  }
  check=checkTripleInput();            // check if IC is triple INPUT
  if(check==1){
    loop();
    
  }
  check=checkDoubleInput();            // check if IC is triple INPUT
  if(check==1){
    loop();
  }
  check=checkSingleInput();            // check if IC is triple INPUT
  if(check==1){
    loop();
    
  }
  
  else{
  //lcd.print("error");
  //delay(1000);
  }
}
bool check_Four_AND_IC(bool working[]){
    int z=0;
    int is_gate1=checkQuadAND(pin[1],pin[2],pin[4],pin[5], pin[6]);
    int is_gate2=checkQuadAND(pin[13],pin[12],pin[10],pin[9], pin[8]);
    if(is_gate1==1){
      working[0]=1;
      z=1;
    }
    if(is_gate2==1){
      working[1]=1;
      z=1;
    }
    return (z!=0);
}

bool check_Four_NAND_IC(bool working[]){
    int z=0;
    int is_gate1=checkQuadNAND(pin[1],pin[2],pin[4],pin[5], pin[6]);
    int is_gate2=checkQuadNAND(pin[13],pin[12],pin[10],pin[9], pin[8]);
    if(is_gate1==1){
      working[0]=1;
      z=1;
    }
    if(is_gate2==1){
      working[1]=1;
      z=1;
    }
    return (z!=0);
}

bool check_Four_NOR_IC(bool working[]){
    int z=0;
    int is_gate1=checkQuadNOR(pin[1],pin[2],pin[4],pin[5], pin[6]);
    int is_gate2=checkQuadNOR(pin[13],pin[12],pin[10],pin[9], pin[8]);
    if(is_gate1==1){
      working[0]=1;
      z=1;
    }
    if(is_gate2==1){
      working[1]=1;
      z=1;
    }
    return (z!=0);
}
void commonfour(char arr1[],char arr2[],bool working[])
{
  int identify=digitalRead(identify_pin);
    delay(50);
    int test=digitalRead(test_pin);
    delay(50);
    if(identify==0 && test==1){
      lcd.clear();
      lcd.print(arr1);
      lcd.setCursor(0,1);
      lcd.print(arr2);
      delay(1000);
      int i;
      for(i=0;i<2;i++){
        if(working[i]==0)
          break;
      }
      if(i==2){
        digitalWrite(green1,1);
        digitalWrite(green2,1);
      }
      else{
        digitalWrite(red1,1);
        digitalWrite(red2,1);
      }
    }
    else if(test==0 && identify==1){
      lcd.clear();
      int i;
      for(i=0;i<1;i++){
        if(working[i]==0){
          lcd.print(i+1);
          lcd.print(":FY ");
        }
        else{
          lcd.print(i+1);
          lcd.print(":OK ");
        }
      }
      lcd.setCursor(0,1);
      for(i=1;i<2;i++){
        if(working[i]==0){
          lcd.print(i+1);
          lcd.print(":FY ");
        }
        else{
          lcd.print(i+1);
          lcd.print(":OK ");
        }

      }
      delay(1000);
      int BT_value=0;      //  value of working to be sent over bluetooth stored in BT_value
      int working_length=2;
      int k;
      for(k=0;k<working_length;k++){
        if(working[k]==1){
          BT_value = (BT_value*10) + 1;
        }
        else{
          BT_value = (BT_value*10) + 0;
        }
      }
      while(k<6){
        BT_value = BT_value*10 + 2;
        k++;
      }
      Serial.println(BT_value);
    }
    else if(test==0 && identify==0){
      lcd.clear();
      lcd.print("Please be");
      lcd.setCursor(0,1);
      lcd.print("specific");
      delay(1000);
    }
  
}

              /*       Function to check if the IC is a 4 INPUT IC        */

int checkFourInput(){  
  bool working[2]={0,0};
  bool x=0;
  x=check_Four_NAND_IC(working);
  if(x){
      commonfour("IC 7420 (4 i/p)","Dual-NAND Gate",working);
    // screen send using working[] 
    
    // code patch was inserted here.
    return 1;
  }
  x=check_Four_NOR_IC(working);
  if(x){
    // screen send using working[] 
    commonfour("IC 7425 (4 i/p)","Dual-NOR Gate",working);
    // code patch was inserted here
    return 1;
  }
  x=check_Four_AND_IC(working);
  if(x){
    // screen send using working[] 
    commonfour("IC 7421 (4 i/p)","Dual-AND Gate",working);
    // code patch was inserted here.
    return 1;
  }
  return 0;
}
                                                    
                                          /*    utility functions to check for Gates     */
                                          
                                          /*    Four Inout Gates       */

int checkQuadNAND(int pin1, int pin2, int pin3, int pin4, int pin5){          //  check quad NAND GATE
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(pin4,OUTPUT);
  pinMode(pin5,INPUT);
  int quadNAND[16]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0};
  int i;
  for(i=0;i<16;i++){
    int bit1=i&8;
    int bit2=i&4;
    int bit3=i&2;
    int bit4=i&1;
    digitalWrite(pin1,bit1);
    digitalWrite(pin2,bit2);
    digitalWrite(pin3,bit3);
    digitalWrite(pin4,bit4);
    int val=digitalRead(pin5);
    delay(50);
    if(val!=quadNAND[i]){
      break;
    }
  }
  if(i==16){
    return 1;
  }
  else{
    return 0;
  }
}

int checkQuadAND(int pin1, int pin2, int pin3, int pin4, int pin5){       //  check quad AND GATE
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(pin4,OUTPUT);
  pinMode(pin5,INPUT);
  int quadAND[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
  int i;
  for(i=0;i<16;i++){
    int bit1=i&8;
    int bit2=i&4;
    int bit3=i&2;
    int bit4=i&1;
    digitalWrite(pin1,bit1);
    digitalWrite(pin2,bit2);
    digitalWrite(pin3,bit3);
    digitalWrite(pin4,bit4);
    int val=digitalRead(pin5);
    delay(50);
    if(val!=quadAND[i]){
      break;
    }
  }
  if(i==16){
    return 1;
  }
  else{
    return 0;
  }
}

int checkQuadNOR(int pin1, int pin2, int pin3, int pin4, int pin5){       // check quad NOR GATE
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(pin4,OUTPUT);
  pinMode(pin5,INPUT);
  int quadNOR[16]={1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int i;
  for(i=0;i<16;i++){
    int bit1=i&8;
    int bit2=i&4;
    int bit3=i&2;
    int bit4=i&1;
    digitalWrite(pin1,bit1);
    digitalWrite(pin2,bit2);
    digitalWrite(pin3,bit3);
    digitalWrite(pin4,bit4);
    int val=digitalRead(pin5);
    delay(50);
    if(val!=quadNOR[i]){
      break;
    }
  }
  if(i==16){
    return 1;
  }
  else{
    return 0;
  }
}
bool check_Tri_NAND_IC(bool working[]){
    int z=0;
    int is_gate1=checkTriNAND(pin[1],pin[2],pin[13],pin[12]);
    int is_gate2=checkTriNAND(pin[3],pin[4],pin[5],pin[6]);
    int is_gate3=checkTriNAND(pin[11],pin[10],pin[9],pin[8]); 
    if(is_gate1==1){
      working[0]=1;
      z=1;
    }
    if(is_gate2==1){
      working[1]=1;
      z=1;
    }
    if(is_gate3==1){
      working[2]=1;
      z=1;
    }
    return (z!=0);
}

bool check_Tri_NOR_IC(bool working[]){
    int z=0;
    int is_gate1=checkTriNOR(pin[1],pin[2],pin[13],pin[12]);
    int is_gate2=checkTriNOR(pin[3],pin[4],pin[5],pin[6]);
    int is_gate3=checkTriNOR(pin[11],pin[10],pin[9],pin[8]); 
    if(is_gate1==1){
      working[0]=1;
      z=1;
    }
    if(is_gate2==1){
      working[1]=1;
      z=1;
    }
    if(is_gate3==1){
      working[2]=1;
      z=1;
    }
    return (z!=0);
}

bool check_Tri_AND_IC(bool working[]){
    int z=0;
    int is_gate1=checkTriAND(pin[1],pin[2],pin[13],pin[12]);
    int is_gate2=checkTriAND(pin[3],pin[4],pin[5],pin[6]);
    int is_gate3=checkTriAND(pin[11],pin[10],pin[9],pin[8]); 
    if(is_gate1==1){
      working[0]=1;
      z=1;
    }
    if(is_gate2==1){
      working[1]=1;
      z=1;
    }
    if(is_gate3==1){
      working[2]=1;
      z=1;
    }
    return (z!=0?1:0);
}
void commontri(char arr1[],char arr2[],bool working[])
{
   int identify=digitalRead(identify_pin);
    delay(50);
    int test=digitalRead(test_pin);
    delay(50);
    if(identify==0 && test==1){
      lcd.clear();
      lcd.print(arr1);
      lcd.setCursor(0,1);
      lcd.print(arr2);
      delay(1000);
      int i;
      for(i=0;i<3;i++){
        if(working[i]==0)
          break;
      }
      if(i==3){
        digitalWrite(green1,1);
        digitalWrite(green2,1);
      }
      else{
        digitalWrite(red1,1);
        digitalWrite(red2,1);
      }
      
        if(arr2=="Tri-NAND Gate"){
          Serial.println(04);
        }
        if(arr2=="Tri-AND Gate"){
          Serial.println(05);
        }
      
    }
    else if(test==0 && identify==1){
      lcd.clear();
      int i;
      for(i=0;i<3;i++){
        if(working[i]==0){
          lcd.print(i+1);
          lcd.print(":FY ");
        }
        else{
          lcd.print(i+1);
          lcd.print(":OK ");
        }
      }
      delay(1000);
      int BT_value=0;      //  value of working to be sent over bluetooth stored in BT_value
      int working_length=3;
      int k;
      for(k=0;k<working_length;k++){
        if(working[k]==1){
          BT_value = (BT_value*10) + 1;
        }
        else{
          BT_value = (BT_value*10) + 0;
        }
      }
      while(k<6){
        BT_value = BT_value*10 + 2;
        k++;
      }
      Serial.println(BT_value);
    }
    else if(test==0 && identify==0){
      lcd.clear();
      lcd.print("Please be");
      lcd.setCursor(0,1);
      lcd.print("specific");
      delay(1000);
    }
  
}

int checkTripleInput(){  
  bool working[3]={0,0,0};
  bool x=0;
  x=check_Tri_NAND_IC(working);
  if(x){
      commontri("IC 7410 (3 i/p)","Tri-NAND Gate",working);
    // screen send using working[]
   
    // code patch was inserted here. 
    return 1;
  }
  x=check_Tri_NOR_IC(working);
  if(x){
    // screen send using working[] 
   commontri("IC 7427 (3 i/p)","Tri-NOR Gate",working);
    // code patch was inserted here. 
    return 1;
  }
  x=check_Tri_AND_IC(working);
  if(x){
      commontri("IC 7411 (3 i/p)","Tri-AND Gate",working);
    // screen send using working[]
   
    // code patch was inserted here. 
    return 1;
  }
  
  return 0;
}
int checkTriNAND(int pin1, int pin2, int pin3, int pin4){        // Checking for 3 Input NAND gate
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(pin4,INPUT);
  int triNAND[8]={1,1,1,1,1,1,1,0};                             //truth table for 3 input NAND.
  int i;
  for(i=0;i<8;i++){
    int bit1=i&4;
    int bit2=i&2;
    int bit3=i&1;
    digitalWrite(pin1,bit1);
    delay(5);
    digitalWrite(pin2,bit2);
    delay(5);
    digitalWrite(pin3,bit3);
    delay(5);
    int val=digitalRead(pin4);
    delay(5);
    if(val!=triNAND[i]){
      break;
    }
  }
  if(i==8){
    return 1;
  }
  else{
    return 0;
  } 
}  

int checkTriNOR(int pin1, int pin2, int pin3, int pin4){        // Checking for 3 Input NOR gate
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(pin4,INPUT);
  int triNOR[8]={1,0,0,0,0,0,0,0};             //truth table for 3 input NOR.
  int i;
  for(i=0;i<8;i++){
    int bit1=i&4;
    int bit2=i&2;
    int bit3=i&1;
    digitalWrite(pin1,bit1);
    delay(5);
    digitalWrite(pin2,bit2);
    delay(5);
    digitalWrite(pin3,bit3);
    delay(5);
    int val=digitalRead(pin4);
    delay(5);
    if(val!=triNOR[i]){
      break;
    }
  }
  if(i==8){
    return 1;
  }
  else{
    return 0;
  } 
}  

int checkTriAND(int pin1, int pin2, int pin3, int pin4){        // Checking for 3 Input AND gate
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(pin4,INPUT);
  int triAND[8]={0,0,0,0,0,0,0,1};                       //truth table for 3 input AND.
  int i;
  for(i=0;i<8;i++){
    int bit1=i&4;
    int bit2=i&2;
    int bit3=i&1;
    digitalWrite(pin1,bit1);
    delay(5);
    digitalWrite(pin2,bit2);
    delay(5);
    digitalWrite(pin3,bit3);
    delay(5);
    int val=digitalRead(pin4);
    delay(5);
    if(val!=triAND[i]){
      break;
    }
  }
  if(i==8){
    return 1;
  }
  else{
    return 0;
  } 
}
bool check_AND_IC(bool working[]){
  int a=1, b=2, c=3, z=0;
  int i=0;
  while(a<7){
    int is_gate1=checkAND(pin[a],pin[b],pin[c]);
    int is_gate2=checkAND(pin[14-a],pin[14-b],pin[14-c]);
    if(is_gate1==1){
      working[i]=1;
      z=1;
    }
    if(is_gate2==1){
      working[3-i]=1;
      z=1;
    }
    a+=3;
    b+=3;
    c+=3;
    i++;
  }
  return (z!=0);
}
bool check_NAND_IC(bool working[]){
  int a=1, b=2, c=3, z=0;
  int i=0;
  while(a<7){
    int is_gate1=checkNAND(pin[a],pin[b],pin[c]);
    int is_gate2=checkNAND(pin[14-a],pin[14-b],pin[14-c]);
    if(is_gate1==1){
      working[i]=1;
      z=1;
    }
    if(is_gate2==1){
      working[3-i]=1;
      z=1;
    }
    a+=3;
    b+=3;
    c+=3;
    i++;
  }
  return (z!=0?1:0);
}
int checkNOR(int pin1, int pin2, int pin3);
bool check_NOR_IC(bool working[]){
  int a=1, b=2, c=3, z=0;
  int i=0;
  while(a<7){
    int is_gate1=checkNOR(pin[a],pin[b],pin[c]);
    int is_gate2=checkNOR(pin[14-a],pin[14-b],pin[14-c]);
    if(is_gate1==1){
      working[i]=1;
      z=1;
    }
    if(is_gate2==1){
      working[3-i]=1;
      z=1;
    }
    a+=3;
    b+=3;
    c+=3;
    i++;
  }
  return (z!=0?1:0);
}
bool check_OR_IC(bool working[]){
  int a=1, b=2, c=3, z=0;
  int i=0;
  while(a<7){
    int is_gate1=checkOR(pin[a],pin[b],pin[c]);
    int is_gate2=checkOR(pin[14-a],pin[14-b],pin[14-c]);
    if(is_gate1==1){
      working[i]=1;
      z=1;
    }
    if(is_gate2==1){
      working[3-i]=1;
      z=1;
    }
    a+=3;
    b+=3;
    c+=3;
    i++;
  }
  return (z!=0?1:0);
}
bool check_XOR_IC( bool working[]){
  int a=1, b=2, c=3, z=0;
  int i=0;
  while(a<7){
    int is_gate1=checkXOR(pin[a],pin[b],pin[c]);
    int is_gate2=checkXOR(pin[14-a],pin[14-b],pin[14-c]);
    if(is_gate1==1){
      working[i]=1;
      z=1;
    }
    if(is_gate2==1){
      working[3-i]=1;
      z=1;
    }
    a+=3;
    b+=3;
    c+=3;
    i++;
  }
  return (z!=0?1:0);
}
void common(char arr1[],char arr2[],bool working[])
{
  int identify=1;
    identify=digitalRead(identify_pin);
    delay(50);
    int test=1;
    test=digitalRead(test_pin);
    delay(50);
    if(identify==0 && test==1){
      lcd.clear();
      lcd.print(arr1);
      lcd.setCursor(0,1);
      lcd.print(arr2);
      delay(1000);
      int i;
      for(i=0;i<4;i++){
        if(working[i]==0)
          break;
      }
      if(i==4){
        digitalWrite(green1,1);
        digitalWrite(green2,1);
      }
      else{
        digitalWrite(red1,1);
        digitalWrite(red2,1);
      }
     
        if(arr2=="Quad-NAND Gate"){
          Serial.println(01);
        }
        if(arr2=="Quad-XOR Gate"){
          Serial.println(07);
        }
        if(arr2=="Quad-OR Gate"){
          Serial.println(06);
        }
        if(arr2=="Quad-AND Gate"){
          Serial.println(03);
        }
        
    }
    else if(test==0 && identify==1){
      lcd.clear();
      int i;
      for(i=0;i<2;i++){
        if(working[i]==0){
          lcd.print(i+1);
          lcd.print(":FY ");
        }
        else{
          lcd.print(i+1);
          lcd.print(":OK ");
        }
      }
      lcd.setCursor(0,1);
      for(i=2;i<4;i++){
        if(working[i]==0){
          lcd.print(i+1);
          lcd.print(":FY ");
        }
        else{
          lcd.print(i+1);
          lcd.print(":OK ");
        }
      }
      delay(1000);
      int BT_value=0;      //  value of working to be sent over bluetooth stored in BT_value
      int working_length=4;
      int k;
      for(k=0;k<working_length;k++){
        if(working[k]==1){
          BT_value = (BT_value*10) + 1;
        }
        else{
          BT_value = (BT_value*10) + 0;
        }
      }
      while(k<6){
        BT_value = BT_value*10 + 2;
        k++;
      }
      Serial.println(BT_value);
    }
    else if(test==0 && identify==0){
      lcd.clear();
      lcd.print("Please be");
      lcd.setCursor(0,1);
      lcd.print("specific");
      delay(1000);
    }
    // code patch was inserted here.
}
int checkDoubleInput(){
  int pin1=pin[1];
  int pin2=pin[2];
  int pin3=pin[3];
  bool working[4]={0,0,0,0};
  bool x=0;
  x=check_NAND_IC(working);
  if(x){
    // print on screen using working[] 

    common("IC 7400 (2 i/p)","Quad-NAND Gate",working);
    // code patch was inserted here.
    return 1;
  }
  x=check_XOR_IC(working);
  if(x){
    // screen send using working[] 
    common("IC 7486 (2 i/p)","Quad-XOR Gate",working);
    // code patch was inserted here.
    return 1;
  }
  x=check_AND_IC(working);
  if(x){
    // screen send using working[] 
    common("IC 7408 (2 i/p)","Quad-AND Gate",working);
    // code patch was inserted here.
    return 1;
  }
  x=check_OR_IC(working);
  if(x){
    // screen send using working[]
    common("IC 7432 (2 i/p)","Quad-OR Gate",working);
    // code patch was inserted here.
    return 1;
  }
  x=check_NOR_IC(working);
  if(x){
    // screen send using working[] 
    common("IC 7402 (2 i/p)","Quad-NOR Gate",working);
    // code patch was inserted here.
    return 1;
  }
  return 0;
}
int checkXOR(int pin1, int pin2, int pin3){                          // function to check if a gate is a XOR.
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,INPUT);
  int XOR[4]={0,1,1,0};
  int i;
  for(i=0;i<4;i++){
    int left_bit= 2&i;
    int right_bit= 1&i;
    digitalWrite(pin1,left_bit);
    digitalWrite(pin2,right_bit);
    int val=digitalRead(pin3);
    delay(5);
    if(val!=XOR[i]){
      break;
    }
  }
  if(i==4){
    return 1;
  }
  else{
    return 0;
  }
}

int checkNAND(int pin1, int pin2, int pin3){                          // function to check if a gate is a NAND.
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,INPUT);
  int nand[4]={1,1,1,0};
  int i;
  for(i=0;i<4;i++){
    int left_bit= 2&i;
    int right_bit= 1&i;
    digitalWrite(pin1,left_bit);
    digitalWrite(pin2,right_bit);
    int val=digitalRead(pin3);
    delay(50);
    if(val!=nand[i]){
      break;
    }
  }
  if(i==4){
    return 1;
  }
  else{
    return 0;
  }
}
int checkNOR(int pin1, int pin2, int pin3){                                  //function to check if gate is NOR.
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,INPUT);
  int Nor[4]={1,0,0,0};
  int i;
  for(i=0;i<4;i++){
    int left_bit= 2&i;
    int right_bit= 1&i;
    digitalWrite(pin1,left_bit);
    digitalWrite(pin2,right_bit);
    int val=digitalRead(pin3);
    delay(50);
    if(val!=Nor[i]){
      break;
    }
  }
  if(i==4){
    return 1;
  }
  else{
    return 0;
  }
}

int checkAND(int pin1, int pin2, int pin3){                                    // function to check if gate is AND.
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,INPUT);
  int And[4]={0,0,0,1};
  int i; 
  for(i=0;i<4;i++){
    int left_bit= 2&i;
    int right_bit= 1&i;
    digitalWrite(pin1,left_bit);
    digitalWrite(pin2,right_bit);
    int val=digitalRead(pin3);
    delay(50);
    if(val!=And[i]){
      break;
    }
  }
  if(i==4){
    return 1;
  }
  else{
    return 0;
  }
}

int checkOR(int pin1, int pin2, int pin3){                                    // function to check if gate is OR.
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,INPUT);
  int Or[4]={0,1,1,1};
  int i; 
  for(i=0;i<4;i++){
    int left_bit= 2&i;
    int right_bit= 1&i;
    digitalWrite(pin1,left_bit);
    digitalWrite(pin2,right_bit);
    int val=digitalRead(pin3);
    delay(50);
    if(val!=Or[i]){
      break;
    }
  }
  if(i==4){
    return 1;
  }
  else{
    return 0;
  }
}
bool checkNOT_IC( bool working[]){
  int x=1,y=2, z=0;
  int i=0;
  while(x<7){
    int is_not1=checkNOT(pin[x],pin[y]);
    int is_not2=checkNOT(pin[14-x],pin[14-y]);
    if(is_not1==1){
      working[i]=1;
      z=1;
    }
    if(is_not2==1){
      working[5-i]=1;
      z=1;
    }
    x+=2;
    y+=2;
    i++;
  }
  return (z!=0?1:0);
}

int checkSingleInput(){
  int pin1=pin[1];
  int pin2=pin[2];
  bool working[6]={0,0,0,0,0,0};
  bool x=0;
  x=checkNOT_IC(working);
  if(!x){
    return 0;
  }
  else{
    // print on screen using working[]
    int identify=digitalRead(identify_pin);
    delay(50);
    int test=digitalRead(test_pin);
    delay(50);
    if(identify==0 && test==1){
      lcd.clear();
      lcd.print("IC 7404 (1i/p)");
      lcd.setCursor(0,1);
      lcd.print("Hex-NOT Gate");
      delay(1000);
      int i;
      for(i=0;i<6;i++){
        if(working[i]==0)
          break;
      }
      if(i==6){
        digitalWrite(green1,1);
        digitalWrite(green2,1);
      }
      else{
        digitalWrite(red1,1);
        digitalWrite(red2,1);
      }
        Serial.println(02);
    }
    else if(test==0 && identify==1){
      lcd.clear();
      int i;
      for(i=0;i<3;i++){
        if(working[i]==0){
          lcd.print(i+1);
          lcd.print(":FY ");
        }
        else{
          lcd.print(i+1);
          lcd.print(":OK ");
        }
      }
      lcd.setCursor(0,1);
      for(i=3;i<6;i++){
        if(working[i]==0){
          lcd.print(i+1);
          lcd.print(":FY ");
        }
        else{
          lcd.print(i+1);
          lcd.print(":OK ");
        }
      }
      delay(1000);
      int BT_value=0;      //  value of working to be sent over bluetooth stored in BT_value
      int working_length=6;
      int k;
      for(k=0;k<working_length;k++){
        if(working[k]==1){
          BT_value = (BT_value*10) + 1;
        }
        else{
          BT_value = (BT_value*10) + 0;
        }
      }
      while(k<6){
        BT_value = BT_value*10 + 2;
        k++;
      }
      Serial.println(BT_value);
    }
    else if(test==0 && identify==0){
      lcd.clear();
      lcd.print("Please be");
      lcd.setCursor(0,1);
      lcd.print("specific");
      delay(1000);
    }
    return 1;
  }
}

int checkNOT(int pin1,int pin2){                                      // function to check if gate is NOT gate.
  pinMode(pin1,OUTPUT);
  pinMode(pin2,INPUT);
  int Not[2]={1,0};
  int i;
  for(i=0;i<2;i++){
    int bitVal= i&1;
    digitalWrite(pin1,bitVal);
    delay(5);
    int val=digitalRead(pin2);
    delay(5);
    if(val!=Not[i]){
      break;
    }
  }
  if(i==2){
    return 1;
  }
  else{
    return 0;
  }
}

